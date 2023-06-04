#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define TIME_SERVER "127.0.0.1"
#define TIME_PORT   5010

void ErrorHandling(char* message);

main() {
	WSADATA wsaData;
	int sock;
	struct sockaddr_in server;
	char buf[256];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() errer!");

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ErrorHandling("hSocketet() error!");

	server.sin_family = AF_INET;
	//server.sin_addr.s_addr = htonl(inet_addr(TIME_SERVER)); /* htonl() 생략 여부 */
	server.sin_addr.s_addr = inet_addr(TIME_SERVER); /* htonl() 생략 여부 */
	server.sin_port = htons(TIME_PORT);

	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == -1)
		ErrorHandling("connect() error!");

	printf("please write echo message\n");
	scanf_s("%s", &buf, (UINT)sizeof(buf));
	send(sock, buf, strlen(buf) + 1, 0);

	if (recv(sock, buf, sizeof(buf), 0) == -1) // 여기서 받음. buf에 싣고 받음
		ErrorHandling("read() error!");
	printf("echo message: %s", buf);
	closesocket(sock);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}