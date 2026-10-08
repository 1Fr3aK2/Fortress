FROM debian:oldstable AS builder

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        make \
        gcc \
        libc6-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fortress/logger

COPY . .

RUN make

FROM debian:oldstable AS runtime

RUN mkdir -p /var/log/fortress/logs
    
COPY --from=builder \
    /fortress/logger/Logger \
    /usr/local/bin/Logger

ENTRYPOINT ["/usr/local/bin/Logger"]