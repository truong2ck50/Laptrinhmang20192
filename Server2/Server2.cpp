#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
    //Khoi tao thu vien
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    //Tao socket cho ket noi
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //Khai bao dia chi server
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    //Gan dia chi voi socket
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    //Chuyen sang trang thai cho ket noi
    listen(listener, 5);

    while (1) {
        SOCKET client = accept(listener, NULL, NULL);

        // Nhan du lieu
        char buf[2048];
        int ret = recv(client, buf, sizeof(buf),0);
        if (ret <= 0) {
            closesocket(client);
            continue;
        }
        if (ret < sizeof(buf))
            buf[ret] = 0;
        printf("%s\n", buf);

        const char* msg = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello World</h1></body></html>";
        send(client, msg, strlen(msg), 0);

        closesocket(client);
    }
}