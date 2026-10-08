FROM debian:oldstable AS builder

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        libssh-dev \
        make \
        gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fortress/honeypot

COPY . .

RUN make

FROM debian:oldstable AS runtime

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        libssh-4 \
        openssh-client \
    && rm -rf /var/lib/apt/lists/* \
    && groupadd --system --gid 10003 honeypot \
    && useradd --system --uid 10003 --gid 10003 \
        --no-create-home --shell /usr/sbin/nologin honeypot \
    && mkdir -p /etc/fortress/keys \
    && mkdir -p /var/log/fortress/events \
    && ssh-keygen -t rsa -b 2048 \
        -f /etc/fortress/keys/ssh_host_rsa_key \
        -N "" \
        -q \
    && chown -R honeypot:honeypot /etc/fortress/keys /var/log/fortress/events

COPY --from=builder \
    /fortress/honeypot/Honeypot \
    /usr/local/bin/Honeypot

USER honeypot

EXPOSE 2222

ENTRYPOINT ["/usr/local/bin/Honeypot"]