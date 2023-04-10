// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include "Data.cpp"

#define PORT 8080

int main(int argc, char const* argv[])
{
    int status, client_fd;
    struct sockaddr_in serv_addr;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
                "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((connect(client_fd, (struct sockaddr*)&serv_addr,
                           sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    while(true){
        Data data{};
        double ans;
        std::cout << "First number:" << std::endl;
        std::cin >> data.num1;
        std::cout << "Operator:" << std::endl;
        std::cin >> data.op;
        std::cout << "Second number:" << std::endl;
        std::cin >> data.num2;
        send(client_fd, &data, sizeof(data), 0);
        read(client_fd, &ans, 1024);
        printf("%f\n", ans);
    }


    // closing the connected socket
    close(client_fd);
    return 0;
}
