# FORTRESS — MVP para Portfólio

> O que implementar primeiro para já ter algo sólido no CV

---

## A Regra de Ouro

Um projecto pequeno mas **completo de ponta a ponta** vale mais do que um projecto grande a meio.

O recrutador quer ver: código que corre, um README que explica decisões, e evidência de que pensas em segurança.

---

## O que é o MVP

**3 componentes. Tudo em Docker. Tudo funcional.**

```
┌─────────────────────────────────────────────┐
│                                             │
│  [SSH HONEYPOT em C]  ──logs──▶  [LOGGER]  │
│                                      │      │
│                                      ▼      │
│                              [REPORT SHELL] │
│                                             │
└─────────────────────────────────────────────┘
```

Nada mais. Isto já é suficiente para o CV.

---

## Componente 1 — SSH Honeypot em C

**O que faz:**
- Abre um socket TCP na porta 2222
- Responde com um banner SSH real (`SSH-2.0-OpenSSH_8.9p1`)
- Aceita a conexão e "finge" pedir credenciais
- Regista tudo: IP de origem, username, password, timestamp, SSH client version
- Fecha a conexão após capturar os dados

**O que NÃO fazes:** não implementas o protocolo SSH completo. Capturas só o suficiente para enganar ferramentas automáticas como Hydra e Metasploit.

**Ficheiros:**
```
honeypot/
├── Dockerfile
├── Makefile
└── src/
    ├── main.c           ← epoll loop, aceita conexões
    ├── ssh_trap.c       ← banner + captura de credenciais
    └── logger.c         ← escreve eventos em JSON para ficheiro
```

**Output de cada evento (JSON):**
```json
{
  "timestamp": "2025-04-01T14:32:11Z",
  "src_ip": "172.18.0.1",
  "src_port": 54321,
  "service": "ssh",
  "username": "root",
  "password": "123456",
  "client_version": "SSH-2.0-libssh-0.9.3",
  "session_id": "a3f2c1d9"
}
```

**Conceitos que demonstras:**
- TCP sockets em C do zero
- `epoll` para múltiplas conexões simultâneas
- Parsing manual de protocolo SSH (banner exchange)
- Conhecimento de como ferramentas de brute force funcionam

---

## Componente 2 — Logger Container

**O que faz:**
- Container separado que lê o ficheiro de logs partilhado
- Agrega estatísticas simples em memória:
  - Top 10 passwords mais tentadas
  - Top 10 IPs mais activos
  - Total de tentativas nas últimas 1h / 24h
- Escreve um ficheiro `stats.json` actualizado a cada 60 segundos

**Ficheiros:**
```
logger/
├── Dockerfile
└── src/
    ├── main.c           ← lê logs, agrega stats
    └── stats_writer.c   ← escreve stats.json
```

**Por que um container separado:**
Demonstras isolamento de responsabilidades — o honeypot só captura, o logger só analisa. Isto é arquitectura de segurança básica: se o honeypot for comprometido, o logger não é afectado.

---

## Componente 3 — Report Script em Shell

**O que faz:**
- Script shell que lê o `stats.json`
- Gera um relatório em texto formatado no terminal
- Pode ser corrido a qualquer momento

```bash
./scripts/report.sh
```

**Output exemplo:**
```
╔══════════════════════════════════════╗
║        FORTRESS — Daily Report       ║
║        2025-04-01  14:00 UTC         ║
╚══════════════════════════════════════╝

Total attempts today:     1,247
Unique IPs:                  89
Most active last hour:       34

TOP 5 PASSWORDS ATTEMPTED:
  1. 123456          (87 attempts)
  2. password        (61 attempts)
  3. admin           (54 attempts)
  4. root            (49 attempts)
  5. 1234567890      (41 attempts)

TOP 5 SOURCE IPs:
  1. 45.33.32.156    (134 attempts)  [Shodan scanner]
  2. 198.20.69.74    ( 98 attempts)
  3. 80.82.77.33     ( 76 attempts)
  4. 192.241.203.52  ( 54 attempts)
  5. 71.6.135.131    ( 43 attempts)

ALERT: Brute force detected from 45.33.32.156
       87 attempts in 10 minutes
```

---

## Docker Compose do MVP

```yaml
services:
  honeypot:
    build: ./honeypot
    ports:
      - "2222:2222"
    volumes:
      - logs:/var/log/fortress
    cap_drop: [ALL]
    cap_add: [NET_BIND_SERVICE]
    read_only: true

  logger:
    build: ./logger
    volumes:
      - logs:/var/log/fortress
    depends_on: [honeypot]

volumes:
  logs:
```

Dois containers. Volume partilhado. Hardening real (`cap_drop`, `read_only`).

---

## O que escrever no CV com só o MVP

**Linha no CV:**

> Built a containerized SSH honeypot in C using epoll for concurrent connections, capturing attacker credentials and client fingerprints in structured JSON. Deployed as a hardened Docker environment with capability dropping and read-only filesystems; a companion analysis container aggregates brute-force patterns and generates threat reports from live data.

**Isto demonstra:**
| Competência | Evidência |
|---|---|
| C systems programming | Socket, epoll, protocol parsing |
| Security mindset | Honeypot, credential capture, brute force detection |
| Docker hardening | cap_drop, read_only, volume isolation |
| Structured logging | JSON events, stats aggregation |
| Shell scripting | Report generation |

---

## Ordem de Implementação (3 a 4 semanas)

**Semana 1**
- [ ] TCP server em C que aceita conexões na porta 2222
- [ ] Responde com banner SSH correcto
- [ ] Lê e imprime o que o cliente envia (para ver o que as ferramentas mandam)
- [ ] Testar com `nc localhost 2222` e `nmap -sV localhost`

**Semana 2**
- [ ] Parsear credenciais do protocolo SSH (username/password do pacote `SSH_MSG_USERAUTH_REQUEST`)
- [ ] Escrever eventos em JSON para ficheiro
- [ ] Adicionar `epoll` para suportar múltiplas conexões simultâneas
- [ ] Testar com Hydra: `hydra -l root -P wordlist.txt ssh://localhost:2222`

**Semana 3**
- [ ] Container do logger com agregação de stats
- [ ] Script shell de report
- [ ] Docker Compose com ambos os containers
- [ ] Hardening: `cap_drop`, `read_only`, healthchecks

**Semana 4**
- [ ] README técnico detalhado (tão importante quanto o código)
- [ ] Demo: capturar um ataque real e mostrar o report
- [ ] Publicar no GitHub com screenshot do report no README

---

## O README é metade do projecto

Sem um bom README, o código não fala por si. Com um bom README, até um MVP parece sólido.

**Estrutura mínima do README:**

```markdown
## Architecture
[diagrama simples em ASCII]

## How it works
Explain: epoll loop → connection accepted → SSH banner sent
→ credentials captured → JSON logged

## Security decisions
- Why cap_drop ALL and re-add only NET_BIND_SERVICE
- Why read-only filesystem on the honeypot container
- Why a separate logger container (isolation principle)
- What the honeypot does NOT implement (and why that's intentional)

## Running
docker compose up -d
./scripts/report.sh

## Example output
[screenshot ou output de texto do report]

## What I learned
[3-4 linhas honestas sobre o que foi difícil e como resolveste]
```

A secção **"Security decisions"** é o que vai impressionar. Mostra que não só implementaste — pensaste no porquê.

---

## Quando está pronto para o CV

Está pronto quando:
- `docker compose up` corre sem erros
- `hydra` contra a porta 2222 gera eventos nos logs
- `./scripts/report.sh` mostra estatísticas reais
- O README tem o diagrama de arquitectura e a secção de decisões de segurança
- Há pelo menos um screenshot no README

Não precisas do dashboard, não precisas do analysis engine completo, não precisas do HTTP ou FTP honeypot.

**Esse é o Fortress v1.0. O resto é v2.0.**
