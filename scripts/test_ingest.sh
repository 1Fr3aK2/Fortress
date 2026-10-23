#!/bin/bash
# Testa a validação de eventos no logger (passo 3).

shopt -s lastpipe

NET="${NET:-fortress_fortress}"

send() { docker run --rm -i --network "$NET" alpine nc -u -w1 logger 5140; }
mk() { printf '{\n\t"timestamp": "%s",\n\t"ip": "%s",\n\t"port": "%s",\n\t"user": "%s",\n\t"password": "%s",\n\t"client_version": "%s"\n}\n' "$@"; }
count() { docker logs logger 2>&1 | grep -c "\[ingest\] $1"; }

pass=0
fail=0

check() {   # check <accepted|rejected> <descrição>, com o evento no stdin
    local exp="$1" desc="$2" a0 r0 a1 r1 got
    a0=$(count accepted); r0=$(count rejected)
    send
    sleep 0.5
    a1=$(count accepted); r1=$(count rejected)
    if [ $((a1 - a0)) -eq 1 ] && [ $((r1 - r0)) -eq 0 ]; then
        got=accepted
    elif [ $((r1 - r0)) -eq 1 ] && [ $((a1 - a0)) -eq 0 ]; then
        got=rejected
    else
        got="inesperado (+$((a1 - a0)) accepted, +$((r1 - r0)) rejected)"
    fi
    if [ "$got" = "$exp" ]; then
        pass=$((pass + 1)); printf 'PASS  %-9s %s\n' "$exp" "$desc"
    else
        fail=$((fail + 1)); printf 'FAIL  esperado %s, obtido %s: %s\n' "$exp" "$got" "$desc"
    fi
}

OK=(2026-10-21T23:00:00Z 1.2.3.4 1234 u p SSH-2.0-test)
A96=$(head -c 96 /dev/zero | tr '\0' A)
A97=$(head -c 97 /dev/zero | tr '\0' A)

mk "${OK[@]}"                                                    | check accepted "evento válido"
mk 2026-10-21T23:00:00Z 1.2.3.4 1234 u 'a\"b\\c' SSH-2.0-test    | check accepted "escapes válidos"
mk 2026-10-21T23:00:00Z 1.2.3.4 1234 u "$A96" SSH-2.0-test       | check accepted "password com 96 bytes (limite)"

echo lixo                                                        | check rejected "não é um evento"
mk 2026-10-21T23:00:00Z 999.1.1.1 1234 u p SSH-2.0-test          | check rejected "IP inválido"
mk 2026-10-21T23:00:00Z 1.2.3.4 70000 u p SSH-2.0-test           | check rejected "porta fora do intervalo"
mk hoje 1.2.3.4 1234 u p SSH-2.0-test                            | check rejected "timestamp inválido"
mk 2026-10-21T23:00:00Z 1.2.3.4 1234 u 'a"b' SSH-2.0-test        | check rejected "aspa por escapar"
mk 2026-10-21T23:00:00Z 1.2.3.4 1234 u 'a\nb' SSH-2.0-test       | check rejected "escape que o honeypot não gera"
mk 2026-10-21T23:00:00Z 1.2.3.4 1234 u $'a\tb' SSH-2.0-test      | check rejected "caractere de controlo cru"
mk 2026-10-21T23:00:00Z 1.2.3.4 1234 u "$A97" SSH-2.0-test       | check rejected "password com 97 bytes"
mk "${OK[@]}" | grep -v '"user"'                                 | check rejected "falta um campo"
mk "${OK[@]}" | sed 's/^}$/\t"received_at": "x"\n}/'             | check rejected "campo extra (received_at forjado)"

echo
echo "Resultado: $pass passaram, $fail falharam"
[ "$fail" -eq 0 ]
