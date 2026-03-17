#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from Server!";

    // 1. 创建 socket 文件描述符
    // AF_INET: IPv4, SOCK_STREAM: TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. 设置地址结构
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // 监听所有网卡接口
    address.sin_port = htons(PORT);       // 转换字节序为网络字节序

    // 3. 绑定 socket 到地址和端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. 开始监听
    // 参数 3 表示排队等待连接的最大数量
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    // 5. 接受客户端连接 (阻塞直到有连接)
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 6. 读取客户端发送的数据
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    std::cout << "Received from client: " << buffer << std::endl;

    // 7. 发送响应给客户端
    send(new_socket, message, strlen(message), 0);
    std::cout << "Message sent to client." << std::endl;

    // 8. 关闭连接
    close(new_socket);
    close(server_fd);

    return 0;
}