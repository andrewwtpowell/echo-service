#include <getopt.h>
#include <string>
#include <iostream>

#include <grpcpp/grpcpp.h>
#include "echo_service.grpc.pb.h"

using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using echo::EchoService;
using echo::Phrase;

void Usage() {
    std::cout <<
        "\nUSAGE: callback_server [OPTIONS]\n"
        "-a, --address <address>:       The server address to connect to (default: localhost:50051)\n"
        "-h, --help:                    Show help\n\n";
    exit(1);
}

class EchoServiceImpl final : public EchoService::CallbackService {
  ServerUnaryReactor* Echo(CallbackServerContext* context,
                               const Phrase* request,
                               Phrase* response) override {
    response->set_text(request->text());

    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

void RunServer(std::string &address) {

  EchoServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {

    const char* const short_opts = "a:h";

    const option long_opts[] = {
        {"address", optional_argument, nullptr, 'a'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
    };

    char option_char;
    std::string server_address = "localhost:50051";

    while((option_char = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch(option_char) {
            case 'a':
                server_address = std::string(optarg);
                break;
            case 'h':
            case '?':
            default:
                Usage();
                break;
        }
    }

    RunServer(server_address);
}
