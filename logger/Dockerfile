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

RUN groupadd --system --gid 10002 logger \
    && useradd --system --uid 10002 --gid 10002 \
        --no-create-home --shell /usr/sbin/nologin logger \
    && mkdir -p /var/log/fortress/logs \
    && chown logger:logger /var/log/fortress/logs
    
COPY --from=builder \
    /fortress/logger/Logger \
    /usr/local/bin/Logger

USER logger

ENTRYPOINT ["/usr/local/bin/Logger"]