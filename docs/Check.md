# FORTRESS v2.0 — Checklist do que falta fazer

> O MVP está concluído. Este ficheiro cobre apenas o que falta para o projecto completo.

---

## Estado actual (MVP concluído ✅)

| Componente | Estado |
|---|---|
| SSH Honeypot (epoll, fork, libssh, JSON logging) | ✅ Feito |
| Logger com hashmap + min-heap + stats.json | ✅ Feito |
| Report script em Shell | ✅ Feito |
| Docker Compose com cap_drop, read_only, resource limits | ✅ Feito |
| README técnico + GitHub publicado | ✅ Feito |
| LinkedIn + CV actualizados | ✅ Feito |

---

## Módulo 1 — Honeypot Server (C)

### HTTP Honeypot ⬜
- [ ] Servidor TCP na porta 8080
- [ ] Serve páginas falsas — admin panel, login WordPress, phpMyAdmin
- [ ] Regista: User-Agent, método HTTP, path tentado, payload
- [ ] Detecção de path traversal, SQLi strings, scanner signatures
- [ ] Integração com o event bus (mesmo formato JSON do SSH)
- [ ] Testar com `curl`, `nmap -sV`, `nikto`

### FTP Honeypot ⬜
- [ ] Servidor TCP na porta 2121
- [ ] Máquina de estados com comandos FTP básicos (RFC 959): `USER`, `PASS`, `LIST`, `QUIT`
- [ ] Banner FTP real (`220 ProFTPD 1.3.5 Server`)
- [ ] Regista: IP, username, password tentada, comandos enviados
- [ ] Testar com `ftp localhost 2121` e `hydra -l admin -P wordlist ftp://localhost:2121`

### Event Loop partilhado ⬜
- [ ] Refactorizar o `epoll` loop actual para ser genérico e partilhado entre SSH, HTTP e FTP
- [ ] Cada serviço regista os seus handlers no mesmo loop
- [ ] Ficheiro `epoll_loop.c` partilhado

---

## Módulo 2 — Logger avançado (C)

### Unix Socket / Event Bus ⬜
- [ ] Daemon em C que recebe eventos via Unix domain socket
- [ ] Honeypot envia eventos para o socket em vez de escrever directamente no ficheiro
- [ ] Formato de evento com campo `"service": "ssh" / "http" / "ftp"`
- [ ] Aprender: `socket(AF_UNIX, ...)`, `bind`, `listen`, `accept` com path em vez de IP

### Rotação de logs ⬜
- [ ] Rotação automática quando o ficheiro excede tamanho configurável (ex: 10MB)
- [ ] Rotação por tempo (diária)
- [ ] Script `rotate-logs.sh` que comprime logs antigos com `gzip`
- [ ] Aprender: `inotify` ou polling de tamanho com `stat()`

### Daemon process ⬜
- [ ] Logger corre como daemon (double fork + `setsid`)
- [ ] Handler para `SIGTERM` — fecha limpo
- [ ] Handler para `SIGHUP` — recarrega configuração sem reiniciar
- [ ] Aprender: `fork()`, `setsid()`, `umask()`, fechar fds herdados

---

## Módulo 3 — Analysis Engine (C++)

### Parser de logs ⬜
- [ ] Lê `events.json` linha a linha com `std::ifstream`
- [ ] Parseia campos JSON manualmente ou com uma lib leve (rapidjson)
- [ ] Estrutura `AttackerProfile` por IP — guarda timestamps, serviços tentados, credentials

### Detecção de padrões ⬜
- [ ] **Brute force** — N tentativas do mesmo IP em X segundos via sliding window
- [ ] **Port scanning** — mesmo IP a tentar SSH + HTTP + FTP
- [ ] **Credential stuffing** — mesmo par user/pass visto em múltiplos IPs
- [ ] **Tool fingerprinting** — User-Agents conhecidos (Hydra, Nmap, libssh, Go)

### Sliding Window Counter ⬜
- [ ] Implementar com `std::deque<time_t>`
- [ ] Método `add_event()` retorna `true` se threshold excedido
- [ ] Configurável: janela de tempo e threshold de eventos

### Sistema de alertas ⬜
- [ ] Ficheiro `alerts.json` com severity: `INFO / WARNING / CRITICAL`
- [ ] Cada alerta tem: timestamp, IP, tipo de ataque, contagem
- [ ] O dashboard consome este ficheiro

### Estruturas de dados adicionais ⬜
- [ ] `std::unordered_map<string, AttackerProfile>` para tracking de IPs
- [ ] Trie para matching rápido de User-Agents maliciosos (opcional / diferenciador)

---

## Módulo 4 — Dashboard (C++)

### HTTP Server ⬜
- [ ] Baseado no Webserv — reutilizar lógica de sockets e parsing HTTP
- [ ] Servir ficheiros estáticos de `./static/`
- [ ] Suporte a `Content-Type` correcto para HTML, JS, CSS, JSON

### API REST ⬜
- [ ] `GET /api/events` — últimos N eventos do `events.json`
- [ ] `GET /api/stats` — conteúdo do `stats.json`
- [ ] `GET /api/alerts` — conteúdo do `alerts.json`
- [ ] `POST /api/block` — adicionar IP a uma blocklist

### Server-Sent Events (SSE) ⬜
- [ ] `GET /api/stream` — conexão HTTP mantida aberta
- [ ] Servidor envia `data: {...}\n\n` quando há novos eventos
- [ ] Cliente JS faz `new EventSource('/api/stream')` e actualiza o UI
- [ ] Aprender: protocolo SSE (simples — é HTTP com headers específicos)

### TLS ⬜
- [ ] NGINX como reverse proxy com TLS (reutilizar Inception)
- [ ] Ou OpenSSL directamente no C++ server
- [ ] Certificado auto-assinado gerado pelo `setup.sh`

### Frontend ⬜
- [ ] `index.html` — dashboard com layout simples
- [ ] Gráfico de tentativas ao longo do tempo (Chart.js CDN)
- [ ] Lista de alertas activos em tempo real via SSE
- [ ] Top 10 passwords e IPs
- [ ] Mapa de IPs (opcional — Leaflet.js com GeoIP)

---

## Módulo 5 — Infrastructure completa (Docker / Shell)

### Novos containers ⬜
- [ ] `analyzer/Dockerfile` — container C++ para o Analysis Engine
- [ ] `dashboard/Dockerfile` — container C++ para o Dashboard
- [ ] Actualizar `docker-compose.yml` para 4 containers

### Docker Compose v2 ⬜
```yaml
# O que falta adicionar ao docker-compose.yml:
  analyzer:
    build: ./analyzer
    volumes:
      - logs:/var/log/fortress:ro
      - alerts:/var/alerts:rw

  dashboard:
    build: ./dashboard
    ports: ["443:443"]
    volumes:
      - alerts:/var/alerts:ro
      - ./certs:/etc/ssl:ro
```

### Hardening adicional ⬜
- [ ] `seccomp` profiles para limitar syscalls em cada container
- [ ] `cap_drop: ALL` + capabilities mínimas nos novos containers
- [ ] `read_only: true` nos novos containers + `tmpfs` onde necessário
- [ ] Health checks para todos os containers
- [ ] `restart: unless-stopped` em todos

### Scripts Shell adicionais ⬜
- [ ] `scripts/rotate-logs.sh` — rotação manual de logs
- [ ] `scripts/geoip.sh` — enriquecer logs com país de origem via MaxMind GeoLite2
- [ ] `scripts/block.sh` — adicionar IP à blocklist via API

---

## Extras / Diferenciadores (opcional)

### GeoIP ⬜
- [ ] Integrar MaxMind GeoLite2 (gratuito com registo)
- [ ] Enriquecer cada evento com `"country": "RU"`, `"city": "Moscow"`
- [ ] Mostrar no dashboard como mapa

### Threat Intelligence ⬜
- [ ] Consultar AbuseIPDB API para cada IP novo
- [ ] Marcar IPs conhecidos como maliciosos no log
- [ ] Campo `"reputation": "malicious"` no evento JSON

### Seccomp profiles ⬜
- [ ] Criar perfil JSON que lista as syscalls permitidas para o honeypot
- [ ] Aplicar via `security_opt: seccomp:./seccomp/honeypot.json` no compose

---

## Ordem recomendada de implementação

```
1. HTTP Honeypot          ← reutiliza Webserv, valor imediato
2. FTP Honeypot           ← simples, máquina de estados pequena
3. Event loop partilhado  ← refactorizar para suportar os 3 serviços
4. Analysis Engine        ← o módulo mais impressionante para o CV
5. Alertas                ← ligar o engine ao dashboard
6. Dashboard API + SSE    ← C++ server + endpoints
7. Frontend básico        ← HTML/JS simples
8. TLS no dashboard       ← NGINX ou OpenSSL
9. Docker Compose v2      ← 4 containers
10. Hardening final        ← seccomp, healthchecks
11. GeoIP (opcional)       ← diferenciador
12. README v2 + demo       ← polish final
```

---

## O que escrever no CV quando estiver completo

> Built a multi-service honeypot infrastructure in C/C++ and Docker, simulating SSH, HTTP, and FTP services to capture attacker behaviour. Implemented a real-time analysis engine detecting brute force, port scanning, and credential stuffing via sliding window algorithms. Deployed as a hardened containerized environment with TLS, Linux capability dropping, read-only filesystems, and a C++ HTTP server serving live threat dashboards via Server-Sent Events.
