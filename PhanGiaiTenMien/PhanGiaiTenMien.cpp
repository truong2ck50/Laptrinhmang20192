#include<stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<winsock2.h>
#include<ws2tcpip.h>

#pragma comment (lib,"ws2_32")

char ch[256];

void nhap() {
	printf("Nhap vao ten mien:");
	gets_s(ch);
}

int check() {
	int i;
	for (i = 0; i < strlen(ch); i++) {
		if (((ch[i] >= 'a' && ch[i] <= 'z') || (ch[i] >= 'A' && ch[i] <= 'Z') || (ch[i] >= '0' && ch[i] <= '9') || ch[i] == '-' || ch[i] == '.'))
			continue;
		else {
			break;
		}
	}
	if (i == strlen(ch)) return 1;
	return 0;
}

int main() {
	//Nhap ten mien
	nhap();

	//Kiem tra ten mien
	if (check() == 0) {
		printf("Ten mien khong hop le\n");
	}
	else {

		// Khoi tao thu vien Winsock
		WSADATA wsa;
		WSAStartup(MAKEWORD(2, 2), &wsa);

		//Phan giai ten mien
		addrinfo* info;
		SOCKADDR_IN addr;

		int ret = getaddrinfo(ch, "http", NULL, &info);
		if (ret == 0) {
			memcpy(&addr, info->ai_addr, info->ai_addrlen);
			printf("Phan giai ten mien thanh cong.\n");
			printf("Dia chi IP: %s", inet_ntoa(addr.sin_addr));
		}
	}
}