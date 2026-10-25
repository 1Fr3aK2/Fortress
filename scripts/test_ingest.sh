#!/bin/bash
# Testa a validação de eventos no logger (passos 3 e 4).
shopt -s lastpipe

NET="${NET:-fortress_ingest}"

send() { docker run --rm -i --network "$NET" alpine nc -u -w1 logger 5140; }
mk() { printf '{\n\t"timestamp": "%s",\n\t"ip": "%s",\n\t"port": "%s",\n\t"user": "%s",\n\t"password": "%s",\n\t"client_version": "%s"\n}\n' "$@"; }
lines() { docker exec logger wc -l /var/log/fortress/events/events.json | awk '{print $1}'; }

pass=0
fail=0

check() {   # check <accepted|rejected> <descrição>, com o evento no stdin
    local exp="$1" desc="$2" l0 l1 got
    l0=$(lines)
    send
    sleep 0.5
    l1=$(lines)
    case $((l1 - l0)) in
        9) got=accepted ;;
        0) got=rejected ;;
        *) got="inesperado (+$((l1 - l0)) linhas)" ;;
    esac
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