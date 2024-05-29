FROM ubuntu:22.04 as build

# Environment setup
RUN export GRPC_INSTALL_DIR=$HOME/.local &&\
    mkdir -p $GRPC_INSTALL_DIR &&\
    export PATH="$GRPC_INSTALL_DIR/bin:$PATH"

# Install necessary dependencies
RUN apt-get update &&\ 
    apt-get install -y build-essential \
                        autoconf \
                        libtool \
                        pkg-config \
                        cmake \
                        git

RUN git clone --recurse-submodules -b v1.64.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc
RUN mkdir -p grpc/cmake/build &&\
    cd grpc/cmake/build &&\
    cmake -DgRPC_INSTALL=ON \
        -DgRPC_BUILD_TESTS=OFF \
        -DCMAKE_INSTALL_PREFIX=$GRPC_INSTALL_DIR \
        ../.. &&\
    make -j 4 &&\
    make install

# Build server
WORKDIR /app

COPY . .

RUN rm CMakeCache.txt

RUN cmake . &&\
    make

# Move binary to minimal image
FROM ubuntu:22.04
COPY --from=build /app/bin/echo-server /bin/echo-server
EXPOSE 50051
CMD ["bin/echo-server"]
