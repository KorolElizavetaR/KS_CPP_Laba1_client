#define PORT 1234

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;
void GetAB(int& a, int& b);

#pragma warning(disable:4996)

void main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return;
	}
	std::cout << "Connected!\n";
	int a, b;
	GetAB(a, b);
	char ach[15] = "", bch[15] = "";
	itoa(a, ach, 10);
	itoa(b, bch, 10);
	send(Connection, ach, sizeof(ach), 0);
	std::cout << "A sended to server" << endl;
	send(Connection, bch, sizeof(bch), 0);
	std::cout << "B sended to server" << endl;

	char gcdch[15] = "";
	recv(Connection, gcdch, sizeof(gcdch), 0);
	cout << "GCD = " << gcdch;
	
	return;
}

void GetAB(int&a, int& b)
{
	cout << "A: ";
	cin >> a;
	cout << "\nB: ";
	cin >> b;
}