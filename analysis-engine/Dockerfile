FROM debian:oldstable

RUN apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends build-essential && apt-get install -y --no-install-recommends nlohmann-json3-dev && rm -rf /var/lib/apt/lists/* 

COPY . /fortress/analysis-engine

WORKDIR /fortress/analysis-engine

RUN make && mkdir -p /var/log/fortress/alerts/

ENTRYPOINT [ "./Analyser" ]