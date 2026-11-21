# aooserver (Docker)

The Docker documentation has been merged into the [README in the repository root](../README.md#docker)
(section "DOCKER").

Short version:

```bash
# Prebuilt image from the GitHub Container Registry
docker pull ghcr.io/essej/aooserver:latest

# Local build (the build context is the root directory of the repository)
docker build -t aooserver -f docker/Dockerfile .
```

The [`Dockerfile`](Dockerfile) uses a multi-stage build on top of `debian:13-slim`: the
builder stage compiles `aooserver` from source, the runtime stage only contains the
binary and the required `libcurl` runtime library. The server runs as a non-root user
with UID/GID `10001`.

Supported platforms of the published image: `linux/amd64`, `linux/arm64`, `linux/arm/v7`.
