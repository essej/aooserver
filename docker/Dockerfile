## Building is done in a separate container
FROM debian:12 as builder
## Install dependencies
RUN apt-get update && apt-get install -y git make bash g++ curl libcurl4-openssl-dev pkg-config

## Clone the repository to build the source
WORKDIR /app
RUN git clone --recursive https://github.com/essej/aooserver.git

## Build the release
WORKDIR /app/aooserverBuilds/LinuxMakefile
RUN bash -c "CONFIG=Release make"


## Actual end container containing our service
FROM debian:12-slim
## Install dependencies
RUN apt-get update && apt-get install -y curl
## Copy our build from the build container
COPY --from=builder /app/aooserver/Builds/LinuxMakefile/build/aooserver /usr/bin/aooserver
## Add port exposure
EXPOSE 10998/udp
EXPOSE 10998/tcp
## Default command
CMD aooserver
