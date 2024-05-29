# Echo Service

## Local Build/Run
### Build

From the project root directory of the project run the following commands.
```bash
cmake .
make
```

### Run Server

Navigate to the bin directory and execute the server binary.
```bash
cd bin
./echo-server
```

### Run Client

Navigate to the bin directory and execute the client binary.
```bash
cd bin
./echo-client
```

To change the message sent to the server from the client set an ECHO_MSG environment variable:
```bash
export ECHO_MSG="<enter message here>"
```

## Containerized Build/Run
### Build Server Container

From the root directory of the project use the following command to build the server container.
```bash
docker build -t echo-server -f server/Dockerfile .
```

Alternatively, you can pull the image from Docker Hub.
```bash
docker image pull andrewwtpowell/echo-server
```

### Run Server Container

To run the server use the following command.
```bash
docker run --rm -p 50051:50051 --name echo-server echo-server bin/echo-server -a 0.0.0.0:50051
```

### Build Client Container

From the root directory of the project use the following command to build the client container.
```bash
docker build -t echo-client -f client/Dockerfile .
```

Alternatively, you can pull the image from Docker Hub.
```bash
docker image pull andrewwtpowell/echo-client
```

### Run Client Container

To run the server use the following command.
```bash
docker run --rm -e ECHO_MSG="<insert msg>" --network=host echo-client bin/echo-client
```

Alternatively, connect using the server container's IP over the docker bridge rather than the host network.
```bash
docker run --rm -e ECHO_MSG="<insert msg>" echo-client bin/echo-client -t <server container IP>:50051
```

## Kubernetes Deployment
### Pre-Deployment Setup

Ensure there is a local Docker registry available to hold the container image.
```bash
docker run -d -p 5000:5000 --name registry registry:2.7
```

Build the server container, tagging with the local registry location, and push the image to the local registry.
```bash
docker build -t localhost:5000/echo-server -f server/Dockerfile .
docker push localhost:5000/echo-server
```

### Deploy to the Cluster

```bash
kubectl apply -f server/echo-deployment.yaml
```

### Testing the Service

Check that the service is running (and identify external IP).
```bash
kubectl get svc
```

Connect to the service using the local client.
```bash
cd bin
./echo_client -t <service-external-IP>:50051
```
