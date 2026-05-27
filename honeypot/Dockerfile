FROM debian:oldstable

RUN apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends libssh-dev make gcc  \
        && rm -rf /var/lib/apt/lists/*

COPY . /fortress/honeypot/

WORKDIR /fortress/honeypot/

RUN make && mkdir -p /var/log/fortress/events

EXPOSE 2222

ENTRYPOINT ["./Fortress"]

