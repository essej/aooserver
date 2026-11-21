# syntax=docker/dockerfile:1

## -----------------------------------------------------------------------------
## Source selection
##
##   SOURCE=source-local   (default) builds the source from the build context,
##                          i.e. the checkout of this repository
##   SOURCE=source-remote  fetches a branch, tag or commit of AOOSERVER_REPO
##                          instead of using the build context
##
## Select it with:  --build-arg SOURCE=source-remote
## -----------------------------------------------------------------------------
ARG SOURCE=source-local
ARG AOOSERVER_REPO=https://github.com/essej/aooserver.git
ARG AOOSERVER_REF=master

## -----------------------------------------------------------------------------
## Stage 1: Toolchain
## -----------------------------------------------------------------------------
FROM debian:13-slim AS toolchain

ARG DEBIAN_FRONTEND=noninteractive

# Retain downloaded .deb packages in the BuildKit cache mount
RUN rm -f /etc/apt/apt.conf.d/docker-clean \
    && echo 'Binary::apt::APT::Keep-Downloaded-Packages "true";' > /etc/apt/apt.conf.d/keep-cache

# Install build dependencies (ca-certificates is required for HTTPS git fetch with --no-install-recommends)
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked \
    --mount=type=cache,target=/var/lib/apt/lists,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
        ca-certificates \
        g++ \
        git \
        libcurl4-openssl-dev \
        make \
        pkg-config

WORKDIR /src

## -----------------------------------------------------------------------------
## Stage 2a: Source taken from the build context
## -----------------------------------------------------------------------------
FROM toolchain AS source-local

COPY . /src

## -----------------------------------------------------------------------------
## Stage 2b: Source taken from a remote git ref
## -----------------------------------------------------------------------------
FROM toolchain AS source-remote

ARG AOOSERVER_REPO
ARG AOOSERVER_REF

# Shallow fetch supports branches, tags, and full commit SHAs
RUN git init . \
    && git remote add origin "${AOOSERVER_REPO}" \
    && git fetch --depth 1 origin "${AOOSERVER_REF}" \
    && git checkout --detach FETCH_HEAD \
    && git submodule update --init --recursive --depth 1

## -----------------------------------------------------------------------------
## Stage 3: Build aooserver from source
## -----------------------------------------------------------------------------
FROM ${SOURCE} AS builder

WORKDIR /src/Builds/LinuxMakefile
RUN make -j"$(nproc)" CONFIG=Release \
    && strip --strip-unneeded build/aooserver

## -----------------------------------------------------------------------------
## Stage 4: Minimal runtime image
## -----------------------------------------------------------------------------
FROM debian:13-slim AS runtime

ARG DEBIAN_FRONTEND=noninteractive

LABEL org.opencontainers.image.title="aooserver" \
      org.opencontainers.image.description="Standalone AoO connection server for SonoBus" \
      org.opencontainers.image.source="https://github.com/essej/aooserver"

# Install only the required runtime shared library (not the curl CLI binary)
RUN --mount=type=cache,target=/var/lib/apt/lists,sharing=locked \
    apt-get update && apt-get install -y --no-install-recommends \
        libcurl4t64 \
    && groupadd --system --gid 10001 aooserver \
    && useradd --system --uid 10001 --gid aooserver --no-create-home --shell /usr/sbin/nologin aooserver

COPY --from=builder --chmod=0755 /src/Builds/LinuxMakefile/build/aooserver /usr/local/bin/aooserver

USER aooserver

EXPOSE 10998/tcp 10998/udp

ENTRYPOINT ["/usr/local/bin/aooserver"]
