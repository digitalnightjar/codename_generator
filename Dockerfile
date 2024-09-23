FROM ubuntu AS base
RUN apt-get update && apt-get upgrade -y
RUN apt-get install brotli clang cmake meson openssl libssl-dev libbrotli-dev zlib1g-dev tar -y

FROM base AS builder
COPY ./ /app
RUN cd /app && ./build_deps.sh && ./build_release.sh

FROM ubuntu AS runtime
RUN apt-get update && apt-get upgrade -y
RUN apt-get install brotli openssl libbrotli-dev -y
COPY --from=builder /app/Release /app
EXPOSE 8080
ENTRYPOINT ["/app/namegen_svc"]
