FROM alpine as build-env
RUN apk add --no-cache build-base
WORKDIR /app
COPY source/main.c .
# Compile the binaries
RUN gcc -o test main.c
FROM alpine
COPY --from=build-env /app/test /app/test
WORKDIR /app
CMD ["/app/test"]
EXPOSE 8080