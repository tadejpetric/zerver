// server.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "settings.hpp"


void bind_socket(const prog_settings settings, int socket_fd) {
    // Bind the socket with file descriptor socket_fd
    // to the address:port described in the settings
    if (settings.in_family == AF_INET) {
        struct sockaddr_in addr4{};
        addr4.sin_family = AF_INET;
        addr4.sin_port = htons(settings.port);
        inet_pton(AF_INET, settings.address.c_str(), &addr4.sin_addr);
        if (bind(socket_fd, (struct sockaddr*)&addr4, sizeof(addr4)) < 0) {
        throw std::system_error(
            errno,
            std::system_category(), 
            "Failed to bind the socket."
        );
        }
    } else {
        struct sockaddr_in6 addr6{};
        addr6.sin6_family = AF_INET6;
        addr6.sin6_port = htons(settings.port);
        inet_pton(AF_INET6, settings.address.c_str(), &addr6.sin6_addr);
        if (bind(socket_fd, (struct sockaddr*)&addr6, sizeof(addr6)) < 0) {
        throw std::system_error(
            errno,
            std::system_category(),
            "Failed to bind the socket."
        );
        }
    }
}

int main(const int argc, const char* argv[]) {
    auto settings = get_settings(argc, argv);

    // Create socket
    int server_fd = socket(settings.in_family, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw std::system_error(
            errno,
            std::system_category(),
            "Failed to create a socket."
        );
    }


    // Allow reuse
    int opt = 1;
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::system_error(
            errno,
            std::system_category(),
            "Failed to set socket options."
        );
    }

    bind_socket(settings, server_fd);

    // Listen to the socket
    if (listen(server_fd, 1) < 0) {
        throw std::system_error(
            errno,
            std::system_category(),
            "Failed to listen to the socket."
        );
    } 
    std::cout << "Server listening on " << settings.address << ":" << settings.port << "\n";

    // Accept one client
    struct sockaddr_storage client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        throw std::system_error(
            errno,
            std::system_category(),
            "Failed to accept the client connection."
        );
    }

    // Read message
    char buffer[1024];
    ssize_t n = read(client_fd, buffer, sizeof(buffer)-1);
    if (n < 0) {
        throw std::system_error(
            errno,
            std::system_category(),
            "Failed to read from the socket."
        );
    } else {
        buffer[n] = '\0';
        std::cout << "Received: " << buffer << "\n";
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
