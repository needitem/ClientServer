#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <time.h>

#define TIME_PORT 5010


void ErrorHandling(char* message);

main() {
	WSADATA wsaData;
	int sock, sock2;
	struct sockaddr_in server, client;
	int len;
	char buf[256];
	char msg[256];
	time_t today;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() errer!");

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ErrorHandling("hSocketet() error!");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(TIME_PORT);

	if (bind(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
		ErrorHandling("bind() error!");

	if (listen(sock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	while (1) {
		len = sizeof(client);
		if ((sock2 = accept(sock, (struct sockaddr*)&client, &len)) == -1)
			ErrorHandling("accept() error!!");

		if (recv(sock2, msg, sizeof(buf), 0) == -1) // ¿©±â¼­ ¹ÞÀ½. buf¿¡ ½Æ°í ¹ÞÀ½
			ErrorHandling("read() error!");

		strcpy(buf, msg);
		send(sock2, buf, strlen(buf) + 1, 0); // ¿©±â¼­ º¸³¿, buf¿¡ ½Æ°í º¸³¿
		closesocket(sock2);
	}
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}