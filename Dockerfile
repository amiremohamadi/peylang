FROM gcc:7

RUN set -ex; \
    apt-get update;
RUN apt-get install -y --no-install-recommends bison flex

COPY ./ /src/peylang
WORKDIR /src/peylang

