FROM alpine:latest
RUN mkdir -p /app
COPY build/SimpleServer /app
WORKDIR /app
CMD ["/app/SimpleServer"]
EXPOSE 8080