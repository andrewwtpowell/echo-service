#include <iostream>
#include <getopt.h>
#include <string>
#include <mutex>
#include <condition_variable>

#include <grpcpp/grpcpp.h>
#include "echo_service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using echo::EchoService;
using echo::Phrase;

void Usage() {
    std::cout <<
        "\nUSAGE: callback_server [OPTIONS]\n"
        "-t, --target <server address>:       The server address to connect to (default: localhost:50051)\n"
        "-h, --help:                    Show help\n\n";
    exit(1);
}

class EchoClient {
    public:
        EchoClient(std::shared_ptr<Channel> channel)
            : stub_(EchoService::NewStub(channel)) {}

        // Assembles the client's payload, sends it and presents the response back
        // from the server.
        std::string Echo(const std::string& message_text) {
            // Data we are sending to the server.
            Phrase request;
            request.set_text(message_text);

            // Container for the data we expect from the server.
            Phrase reply;

            // Context for the client. It could be used to convey extra information to
            // the server and/or tweak certain RPC behaviors.
            ClientContext context;

            // The actual RPC.
            std::mutex mu;
            std::condition_variable cv;
            bool done = false;
            Status status;
            stub_->async()->Echo(&context, &request, &reply,
                    [&mu, &cv, &done, &status](Status s) {
                    status = std::move(s);
                    std::lock_guard<std::mutex> lock(mu);
                    done = true;
                    cv.notify_one();
                    });

            std::unique_lock<std::mutex> lock(mu);
            while (!done) {
                cv.wait(lock);
            }

            // Act upon its status.
            if (status.ok()) {
                return reply.text();
            } else {
                std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
                return "RPC failed";
            }
        }

    private:
        std::unique_ptr<EchoService::Stub> stub_;
};

int main(int argc, char** argv) {

    const char* const short_opts = "t:h";

    const option long_opts[] = {
        {"target", optional_argument, nullptr, 't'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
    };

    char option_char;
    std::string target = "localhost:50051";

    while((option_char = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch(option_char) {
            case 'a':
                target = std::string(optarg);
                break;
            case 'h':
            case '?':
            default:
                Usage();
                break;
        }
    }

    EchoClient client(
            grpc::CreateChannel(target, grpc::InsecureChannelCredentials()));
    std::string msg("Don't tell no lies bout me and I won't tell truths about you.");
    std::cout << "Client sent: " << msg << "\n";
    std::string reply = client.Echo(msg);
    std::cout << "Client received: " << reply << std::endl;
}
