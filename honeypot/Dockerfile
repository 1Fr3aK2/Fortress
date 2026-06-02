FROM debian:oldstable

RUN apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends \
        libssh-dev make gcc openssh-client \
        && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /etc/fortress/keys && \
    ssh-keygen -t rsa -b 2048 \
    -f /etc/fortress/keys/ssh_host_rsa_key \
    -N "" -q

COPY . /fortress/honeypot/

WORKDIR /fortress/honeypot/

RUN make && mkdir -p /var/log/fortress/events

EXPOSE 2222

ENTRYPOINT ["./honeypot"]

