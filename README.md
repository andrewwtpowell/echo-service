# Echo Service

## Build Server Container

From the root directory of the project use the following command to build the server container.
```bash
docker build -t echo_server -f server/Dockerfile .
```

## Run Server Container

To run the server use the following command.
```bash
docker run --rm -p 50051:50051 --name echo_server echo_server bin/echo_server -a 0.0.0.0:50051
```

## Build Client Container

From the root directory of the project use the following command to build the client container.
```bash
docker build -t echo_client -f client/Dockerfile .
```

## Run Client Container

To run the server use the following command.
```bash
docker run --rm -e ECHO_MSG="<insert msg>" --network=host echo_client bin/echo_client
```

Alternatively, connect using the server container's IP over the docker bridge rather than the host network.
```bash
docker run --rm -e ECHO_MSG="<insert msg>" echo_client bin/echo_client -t <server container IP>:50051
```
