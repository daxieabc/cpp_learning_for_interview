#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *hello = "Hello from Client";

    // 1. 创建 socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    // 2. 设置服务器地址结构
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将 IP 地址从文本转换为二进制形式
    // 这里假设服务器在本地，如果是远程请修改 "127.0.0.1" 为服务器 IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        return -1;
    }

    // 3. 连接服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        close(sock);
        return -1;
    }

    std::cout << "Connected to server." << std::endl;

    // 4. 发送数据
    send(sock, hello, strlen(hello), 0);
    std::cout << "Message sent: " << hello << std::endl;

    // 5. 接收服务器响应
    int valread = read(sock, buffer, BUFFER_SIZE);
    std::cout << "Received from server: " << buffer << std::endl;

    // 6. 关闭 socket
    close(sock);

    return 0;
}