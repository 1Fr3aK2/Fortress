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
    && mkdir -p /var/log/fortress/alerts

COPY --from=builder \
    /fortress/analysis-engine/Analyser \
    /usr/local/bin/Analyser

ENTRYPOINT ["/usr/local/bin/Analyser"]