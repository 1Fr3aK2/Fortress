# FORTRESS — Um Honeypot Infrastructure com Análise de Intrusão em Tempo Real

> Projeto portfolio para transição para Cybersecurity | C / C++ / Docker / Shell

---

## Visão Geral

**Fortress** é uma infraestrutura containerizada de honeypot com detecção e análise de intrusões em tempo real. O projeto simula serviços reais (SSH, HTTP, FTP) para atrair e registar comportamento de atacantes, analisa os dados com um motor em C++, e apresenta os resultados num dashboard em tempo real.

É um projeto que **consolida tudo o que fizeste na 42** (parsing, sockets, processos, Docker, segurança) e **adiciona conceitos novos e altamente valorizados** em Cybersecurity: honeypots, IDS, análise forense de rede, SIEM lightweight.

---

## Por que este projeto se destaca no CV

| O que os recrutadores de security vêem | Como o Fortress responde |
|---|---|
| Conhecimento de redes e protocolos | Implementas SSH/HTTP/FTP do zero em C |
| Experiência com containers seguros | Docker com network isolation, least privilege |
| Capacidade de analisar tráfego | Motor de análise de logs em C++ com parsing real |
| Iniciativa além do curriculo | Honeypot é um conceito avançado e autónomo |
| Pensamento ofensivo e defensivo | Simulas o atacante E o defensor ao mesmo tempo |

---

## Arquitectura do Sistema

```
┌─────────────────────────────────────────────────────┐
│                   HOST MACHINE                      │
│                                                     │
│  ┌──────────────────────────────────────────────┐  │
│  │           DOCKER NETWORK: fortress-net        │  │
│  │                                              │  │
│  │  ┌─────────────┐   ┌──────────────────────┐ │  │
│  │  │  HONEYPOT   │   │   ANALYSIS ENGINE    │ │  │
│  │  │  CONTAINER  │──▶│     CONTAINER        │ │  │
│  │  │             │   │   (C++ / logs)       │ │  │
│  │  │ - SSH :2222 │   └──────────────────────┘ │  │
│  │  │ - HTTP:8080 │              │              │  │
│  │  │ - FTP :2121 │              ▼              │  │
│  │  └─────────────┘   ┌──────────────────────┐ │  │
│  │                    │   DASHBOARD          │ │  │
│  │  ┌─────────────┐   │   CONTAINER          │ │  │
│  │  │   LOGGER    │──▶│   (HTTP server C++)  │ │  │
│  │  │  CONTAINER  │   │   porta 443 / TLS    │ │  │
│  │  │  (syslog)   │   └──────────────────────┘ │  │
│  │  └─────────────┘                             │  │
│  └──────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────┘
```

---

## Módulos do Projeto

### Módulo 1 — Honeypot Server (C)
*Conceitos 42 reutilizados: Minishell (processos/fork), Webserv (sockets/HTTP)*

Implementas servidores que **simulam** serviços reais mas não executam nada:

**SSH Honeypot**
- Socket TCP na porta 2222
- Responde com banner SSH real (`SSH-2.0-OpenSSH_8.9`)
- Aceita qualquer credencial e finge autenticar
- Regista: IP, username, password, timestamp, fingerprint
- Implementa o handshake suficiente para enganar scanners automáticos

**HTTP Honeypot**
- Baseado no teu Webserv mas com rotas armadilhadas
- Serve páginas falsas (admin panel, login WordPress, phpMyAdmin)
- Deteta e regista: User-Agent, métodos, paths tentados, payloads
- Simula vulnerabilidades (SQLi, path traversal) sem as executar realmente

**FTP Honeypot** *(conceito novo — simples)*
- Socket TCP na porta 2121
- Implementa protocolo FTP mínimo (RFC 959)
- Regista tentativas de login e comandos enviados

**Conceitos novos a aprender:**
- Protocolo SSH (RFC 4253) — estrutura do handshake
- Protocolo FTP (RFC 959) — máquina de estados
- Banner grabbing e fingerprinting
- Como os scanners automáticos (Shodan, Masscan) funcionam

---

### Módulo 2 — Logger & Event Bus (C / Shell)
*Conceitos 42 reutilizados: pipes, file descriptors, Minishell*

Sistema de logging estruturado que centraliza todos os eventos:

**Formato de log (JSON estruturado):**
```json
{
  "timestamp": "2025-04-01T14:32:11Z",
  "service": "ssh",
  "src_ip": "192.168.1.100",
  "src_port": 54321,
  "event_type": "login_attempt",
  "data": {
    "username": "root",
    "password": "123456",
    "ssh_version": "SSH-2.0-libssh-0.9.3"
  },
  "session_id": "a3f2c1d9"
}
```

**Componentes:**
- Daemon em C que recebe eventos via Unix socket ou named pipe
- Rotação de logs por tamanho e tempo (implementada manualmente)
- Script shell para parsear e filtrar logs em tempo real

**Conceitos novos:**
- Unix domain sockets
- Daemon processes (double fork, setsid)
- Structured logging
- Log rotation

---

### Módulo 3 — Analysis Engine (C++)
*Conceitos 42 reutilizados: parsing (Minishell), memory management (Cub3D)*
*Conceito dos projetos que não fizeste: IRC (gestão de múltiplas conexões/estado)*

Motor de análise que processa os logs e detecta padrões:

**Detecção de padrões:**
- Brute force: N tentativas do mesmo IP em X segundos
- Port scanning: mesmo IP a tentar múltiplos serviços
- Credential stuffing: mesmo par user/pass em múltiplos IPs
- Anomaly detection: User-Agents conhecidos de ferramentas (Hydra, Nmap, Metasploit)

**Estruturas de dados implementadas:**
```cpp
// Sliding window para rate limiting
class SlidingWindowCounter {
    std::deque<time_t> events;
    size_t window_seconds;
public:
    bool add_event(); // retorna true se threshold excedido
};

// Trie para matching de padrões em strings
class PatternTrie {
    // Para detecção rápida de ferramentas por User-Agent
};

// Hash map para tracking de IPs
std::unordered_map<std::string, AttackerProfile> ip_profiles;
```

**Output do motor:**
- Ficheiro de alertas com severity (INFO / WARNING / CRITICAL)
- Estatísticas agregadas por período
- Top 10 IPs mais activos, top 10 passwords tentadas, etc.

**Conceitos novos:**
- Sliding window algorithm
- Trie data structure
- Anomaly detection básico
- Threat intelligence (como usar listas de IPs maliciosos conhecidos)

---

### Módulo 4 — HTTP Dashboard (C++)
*Conceitos 42 reutilizados: Webserv completo (HTTP/1.1, TLS via Inception)*

Servidor HTTP em C++ que serve um dashboard em tempo real:

**Endpoints:**
```
GET  /                    → Dashboard HTML
GET  /api/events          → Últimos N eventos (JSON)
GET  /api/stats           → Estatísticas agregadas (JSON)
GET  /api/alerts          → Alertas activos (JSON)
GET  /api/stream          → Server-Sent Events (SSE) — tempo real
POST /api/block           → Adicionar IP à blocklist
```

**Server-Sent Events (SSE):**
- Conceito novo: o servidor mantém a conexão HTTP aberta
- Envia eventos para o browser sem polling
- Implementado sobre o teu HTTP server existente

**Frontend (HTML/JS simples):**
- Mapa de IPs atacantes (usando uma lib JS gratuita)
- Gráfico de tentativas ao longo do tempo
- Lista de alertas em tempo real
- Estatísticas: passwords mais usadas, países de origem

**TLS:**
- Reutilizas exactamente o que fizeste no Inception (NGINX com TLS)
- Ou implementas directamente com OpenSSL no teu C++ server

---

### Módulo 5 — Infrastructure (Docker / Shell)
*Conceitos 42 reutilizados: Inception completo*

**docker-compose.yml com 4 containers:**

```yaml
services:
  honeypot:
    build: ./honeypot
    networks: [fortress-net]
    ports: ["2222:2222", "8080:8080", "2121:2121"]
    read_only: true          # filesystem read-only
    cap_drop: [ALL]          # remove todas as capabilities Linux
    cap_add: [NET_BIND_SERVICE]  # só o necessário
    volumes:
      - logs:/var/log/fortress:rw

  logger:
    build: ./logger
    networks: [fortress-net]
    volumes:
      - logs:/var/log/fortress:rw
    depends_on: [honeypot]

  analyzer:
    build: ./analyzer
    networks: [fortress-net]
    volumes:
      - logs:/var/log/fortress:ro  # só leitura
      - alerts:/var/alerts:rw

  dashboard:
    build: ./dashboard
    networks: [fortress-net]
    ports: ["443:443"]
    volumes:
      - alerts:/var/alerts:ro
      - ./certs:/etc/ssl:ro
    depends_on: [analyzer]

networks:
  fortress-net:
    driver: bridge
    internal: false  # só honeypot exposto para fora

volumes:
  logs:
  alerts:
```

**Scripts Shell:**
```bash
./scripts/setup.sh        # gera certificados, configura rede
./scripts/start.sh        # arranca toda a infra
./scripts/stop.sh         # para tudo limpo
./scripts/rotate-logs.sh  # rotação manual de logs
./scripts/report.sh       # gera relatório do dia em texto
./scripts/geoip.sh        # enriquece logs com geolocalização de IP
```

**Conceitos novos:**
- Linux capabilities (`cap_drop`, `cap_add`)
- Read-only containers
- Docker secrets vs environment variables (já documentado no teu Inception)
- `seccomp` profiles para limitar syscalls
- Health checks nos containers

---

## Conceitos Novos a Aprender (Ordenados por Prioridade)

### Nível 1 — Essencial (aprender primeiro)

**1. Sockets avançados**
- `epoll` / `select` — I/O multiplexing para múltiplas conexões simultâneas
- Diferença entre blocking e non-blocking I/O
- Timeout em sockets (`SO_RCVTIMEO`, `SO_SNDTIMEO`)
- Recurso: `man 7 socket`, `man 2 epoll_create`

**2. Protocolos de rede**
- Como funciona um handshake SSH (RFC 4253) — só a leitura é suficiente
- HTTP/1.1 já sabes — aprender `Transfer-Encoding: chunked` e SSE
- FTP alertSeverity machine (RFC 959) — é simples, ~15 comandos básicos

**3. Estruturas de dados para análise**
- Hash maps em C++ (`std::unordered_map`) — já provavelmente sabes
- Sliding window counter — para rate limiting
- Circular buffer — para manter os últimos N eventos em memória

### Nível 2 — Importante

**4. Segurança Linux**
- Linux capabilities — o que é `CAP_NET_BIND_SERVICE`, `CAP_SYS_PTRACE`, etc.
- `seccomp` — filtrar syscalls que um processo pode fazer
- `chroot` / namespaces — isolamento de processos
- Recurso: `man 7 capabilities`, https://book.hacktricks.xyz/linux-hardening/privilege-escalation/linux-capabilities

**5. Criptografia aplicada (OpenSSL)**
- TLS handshake — como funciona por baixo
- Usar a biblioteca OpenSSL em C para criar um socket TLS
- Hashing de passwords (para o teu log não guardar passwords em claro — usa SHA-256)
- Recurso: `man SSL_CTX_new`, exemplos OpenSSL BIO

**6. Análise de logs**
- Formato syslog (RFC 5424)
- JSON structured logging
- `jq` — ferramenta de linha de comando para parsear JSON
- Recurso: `man 3 syslog`

### Nível 3 — Diferenciador

**7. Threat Intelligence**
- O que é um IOC (Indicator of Compromise)
- Listas públicas de IPs maliciosos (AbuseIPDB, Shodan API)
- GeoIP — mapear IPs para países (usar MaxMind GeoLite2, gratuito)

**8. IDS/IPS concepts**
- Diferença entre IDS (Intrusion Detection) e IPS (Intrusion Prevention)
- Signature-based vs anomaly-based detection
- Como o Snort/Suricata funcionam (estudar a documentação, não implementar)

**9. Server-Sent Events (SSE)**
- Protocolo simples sobre HTTP para streaming de eventos
- Muito mais simples que WebSockets, suficiente para o dashboard

---

## Conceitos dos Projectos Não Feitos que Importam

### Do IRC (não fizeste — mas aprende isto)

O IRC ensinaria gestão de estado de múltiplos clientes em simultâneo. Para o teu honeypot, precisas exactamente disto:

**O que aprender:**
- `epoll_wait` — gerir centenas de conexões sem uma thread por cliente
- Event loop — o padrão central de qualquer servidor de alta performance
- alertSeverity machine por conexão — cada cliente SSH/FTP está num estado diferente

```c
// Padrão básico de event loop com epoll
int epfd = epoll_create1(0);

// Para cada cliente novo
struct epoll_event ev;
ev.events = EPOLLIN | EPOLLET;  // Edge-triggered
ev.data.fd = client_fd;
epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);

// Loop principal
while (1) {
    int n = epoll_wait(epfd, events, MAX_EVENTS, -1);
    for (int i = 0; i < n; i++) {
        handle_event(events[i]);  // não bloqueia
    }
}
```

### Do Transcendence (não fizeste — podes usar uma lib JS simples em vez disso)

O Transcendence ensinaria frontend. Para o dashboard, não precisas de reinventar a roda — usa HTML/JS puro com uma lib pequena. O foco é o backend em C++.

### Do Minitalk (não fizeste — mas os sinais são úteis)

Minitalk ensinaria sinais UNIX. Para o teu daemon, precisas de:
```c
signal(SIGTERM, graceful_shutdown);  // para limpo com docker stop
signal(SIGHUP, reload_config);       // recarregar config sem reiniciar
signal(SIGCHLD, reap_children);      // limpar processos filhos
```

---

## Estrutura de Pastas do Repositório

```
fortress/
├── README.md                    ← documentação técnica detalhada (essencial para CV)
├── docker-compose.yml
├── Makefile                     ← build de tudo com um comando
│
├── honeypot/                    ← Módulo 1 (C)
│   ├── Dockerfile
│   ├── Makefile
│   ├── src/
│   │   ├── main.c
│   │   ├── ssh_honeypot.c
│   │   ├── http_honeypot.c
│   │   ├── ftp_honeypot.c
│   │   ├── event_emitter.c      ← envia eventos para o logger
│   │   └── epoll_loop.c         ← event loop partilhado
│   └── include/
│       └── fortress.h
│
├── logger/                      ← Módulo 2 (C + Shell)
│   ├── Dockerfile
│   ├── src/
│   │   ├── daemon.c
│   │   └── unix_socket.c
│   └── scripts/
│       └── rotate.sh
│
├── analyzer/                    ← Módulo 3 (C++)
│   ├── Dockerfile
│   ├── Makefile
│   └── src/
│       ├── main.cpp
│       ├── log_parser.cpp
│       ├── pattern_engine.cpp   ← detecção de brute force, scanning
│       ├── sliding_window.cpp
│       └── alert_writer.cpp
│
├── dashboard/                   ← Módulo 4 (C++)
│   ├── Dockerfile
│   ├── Makefile
│   ├── src/
│   │   ├── http_server.cpp      ← baseado no teu Webserv
│   │   ├── api_handlers.cpp
│   │   └── sse_stream.cpp       ← Server-Sent Events
│   └── static/
│       ├── index.html
│       ├── dashboard.js
│       └── style.css
│
└── scripts/                     ← Módulo 5 (Shell)
    ├── setup.sh
    ├── start.sh
    ├── stop.sh
    ├── geoip.sh
    └── report.sh
```

---

## Plano de Desenvolvimento (12 a 16 Semanas)

### Fase 1 — Fundações (Semanas 1-2)
- [ ] Estudar `epoll` e event loop não-bloqueante
- [ ] Implementar TCP server genérico em C com epoll
- [ ] Testar com `telnet` e `nc` localmente
- [ ] Configurar repositório Git com branches por módulo

### Fase 2 — Honeypot Core (Semanas 3-5)
- [ ] SSH honeypot: banner + accept credentials + log
- [ ] HTTP honeypot: rotas falsas + log de payloads
- [ ] FTP honeypot: alertSeverity machine básica
- [ ] Testar com Nmap (`nmap -sV localhost`) e verificar que parece real

### Fase 3 — Logger & Infrastructure (Semanas 6-7)
- [ ] Daemon de logging com Unix socket
- [ ] Formato JSON estruturado
- [ ] Dockerfiles para honeypot + logger
- [ ] Docker Compose com volumes partilhados

### Fase 4 — Analysis Engine (Semanas 8-10)
- [ ] Parser de logs JSON em C++
- [ ] Detecção de brute force com sliding window
- [ ] Detecção de port scanning
- [ ] Sistema de alertas com severity levels

### Fase 5 — Dashboard (Semanas 11-13)
- [ ] HTTP server em C++ (basear no Webserv)
- [ ] API REST para eventos e estatísticas
- [ ] SSE para updates em tempo real
- [ ] Frontend HTML/JS com visualizações básicas
- [ ] TLS com OpenSSL ou NGINX como proxy

### Fase 6 — Hardening & Polish (Semanas 14-16)
- [ ] Linux capabilities em todos os containers
- [ ] Seccomp profiles
- [ ] Read-only filesystems
- [ ] GeoIP enrichment nos logs
- [ ] README técnico detalhado
- [ ] Demo video para LinkedIn

---

## Como Testar o Projecto

```bash
# Arrancar tudo
./scripts/setup.sh && docker compose up -d

# Simular um atacante (numa VM separada ou localhost)
nmap -sV -p 2222,8080,2121 localhost           # port scan
hydra -l root -P /usr/share/wordlists/rockyou.txt ssh://localhost:2222  # brute force
curl http://localhost:8080/admin               # path probing
curl http://localhost:8080/wp-login.php        # WordPress scan

# Ver o dashboard
open https://localhost:443

# Ver alertas em tempo real
curl -N https://localhost:443/api/stream

# Relatório
./scripts/report.sh --today
```

---

## O que escrever no CV

**Título do projecto:** Fortress — Honeypot Infrastructure with Real-Time Intrusion Analysis

**Descrição (3 linhas):**
> Built a multi-service honeypot infrastructure in C/C++ and Docker, simulating SSH, HTTP, and FTP services to capture attacker behaviour. Implemented a real-time analysis engine detecting brute force, port scanning, and credential stuffing via sliding window algorithms. Deployed as a hardened containerized environment with TLS, Linux capability dropping, read-only filesystems, and a C++ HTTP server serving live threat dashboards via Server-Sent Events.

**Skills demonstradas:**
- C / C++ / Shell / Docker / Docker Compose
- Network programming (TCP sockets, epoll, TLS/OpenSSL)
- Protocol implementation (SSH banners, HTTP/1.1, FTP alertSeverity machine)
- Security concepts (honeypots, IDS, brute force detection, threat intelligence)
- Linux hardening (capabilities, seccomp, namespaces)
- Real-time data streaming (SSE)

---

## Recursos de Estudo

| Tema | Recurso |
|---|---|
| Sockets e epoll | `man 7 epoll`, Beej's Guide to Network Programming |
| Linux Capabilities | `man 7 capabilities`, HackTricks Linux Hardening |
| OpenSSL / TLS | OpenSSL Wiki, `man SSL_CTX_new` |
| SSH Protocol | RFC 4253 (ler os primeiros 3 capítulos) |
| FTP Protocol | RFC 959 (curto e directo) |
| Docker Security | Docker docs: seccomp, capabilities |
| Threat Intelligence | AbuseIPDB API docs, MaxMind GeoLite2 |
| C++ moderno | cppreference.com — `std::unordered_map`, `std::deque` |
| pwn.college | Continuar o teu estudo actual — complementa este projecto |

---

## Notas Finais

Este projecto é deliberadamente ambicioso. Não tens de implementar tudo antes de o mostrar — uma versão funcional com SSH honeypot + logger + dashboard básico já é suficiente para um portfólio. Depois vais adicionando módulos.

O que vai destacar-te não é só o código — é o **README técnico**. Documenta cada decisão de design: por que usaste epoll em vez de threads, que tradeoffs existem entre Docker secrets e env vars, como o sliding window funciona. Recrutadores de security adoram ver pensamento crítico sobre as próprias escolhas.

Boa sorte, Rafael. Este projecto mostra exactamente a mentalidade que a área de segurança procura — alguém que pensa como o atacante para construir a defesa.
