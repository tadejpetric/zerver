// client.cpp

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    const char* server_ip = "127.0.0.1";  // hardcoded
    const int server_port = 8080;         // hardcoded
    const char* message = "Hello from client!";

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::perror("socket");
        return 1;
    }

    struct sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address: " << server_ip << "\n";
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::perror("connect");
        close(sock);
        return 1;
    }

    send(sock, message, std::strlen(message), 0);
    std::cout << "Sent: " << message << "\n";

    close(sock);
    return 0;
}
