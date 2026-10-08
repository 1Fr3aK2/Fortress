FROM debian:oldstable AS builder

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        g++ \
        make \
        nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fortress/analysis-engine

COPY . .

RUN make

FROM debian:oldstable AS runtime

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        libstdc++6 \
    && rm -rf /var/lib/apt/lists/* \
    && groupadd --system --gid 10001 analyser \
    && useradd --system --uid 10001 --gid 10001 \
        --no-create-home --shell /usr/sbin/nologin analyser \
    && mkdir -p /var/log/fortress/alerts \ 
    && chown analyser:analyser /var/log/fortress/alerts

COPY --from=builder \
    /fortress/analysis-engine/Analyser \
    /usr/local/bin/Analyser

USER analyser

ENTRYPOINT ["/usr/local/bin/Analyser"]