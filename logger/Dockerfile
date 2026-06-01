FROM debian:oldstable

RUN apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends make gcc && rm -rf /var/lib/apt/lists/*

COPY . /fortress/logger

WORKDIR /fortress/logger

RUN make && mkdir -p /var/log/fortress/logs/

ENTRYPOINT ["./Logger"]