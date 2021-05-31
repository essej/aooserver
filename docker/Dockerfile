FROM debian:buster
RUN apt-get update
RUN apt-get install -y git make bash g++ curl libcurl4-openssl-dev pkg-config

RUN mkdir /app

WORKDIR /app

RUN git clone --recursive https://github.com/essej/aooserver.git
WORKDIR /app/aooserver

EXPOSE 10998/udp
EXPOSE 10998/tcp

WORKDIR Builds/LinuxMakefile
RUN bash -c "CONFIG=Release make"

RUN mkdir /app/bin && cp /app/aooserver/Builds/LinuxMakefile/build/aooserver /app/bin/aooserver

ENV PATH="/app/bin:${PATH}"
RUN echo "export PATH=$PATH" > /etc/environment

CMD aooserver
