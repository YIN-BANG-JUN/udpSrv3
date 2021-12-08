// udpSrv3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//服务端

#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	std::cout << "服务端" << std::endl << std::endl;

	//初始化套接字
	WORD wVersion;
	WSADATA wsaData;
	int err;

	wVersion = MAKEWORD(1, 1);
	err = WSAStartup(wVersion, &wsaData);
	if (err != 0)
	{
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	//创建套接字
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6002);

	//绑定到本机6002端口
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//接收请求,处理请求
	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	char sendBuf[] = "UDP Server >>>";
	char recvBuf[100];

	std::cout << "Start UDP server with port 6002......." << std::endl;

	while (true)
	{
		//接收数据
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrCli, &len);
		
		std::cout << "接收数据:" << recvBuf << std::endl;

		//发送数据
		sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrCli, len);

		std::cout << "发送数据:" << sendBuf << std::endl;
	}

	closesocket(sockSrv);
	WSACleanup();

	system("pause");
	return 0;
}



//客户端

#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	std::cout << "客户端" << std::endl << std::endl;

	//初始化套接字
	WORD wVersion;
	WSADATA wsaData;
	int err;

	wVersion = MAKEWORD(1, 1);
	err = WSAStartup(wVersion, &wsaData);
	if (err != 0)
	{
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	//创建UDP套接字
	SOCKET sockCli = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN	addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6002);

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	char sendBuf[100];
	char recvBuf[100];

	int n = 5;
	while (n--)
	{
		std::cout << "请输入:";
		scanf_s("%s", sendBuf, 100);
		std::cout << "发送数据:" << sendBuf << std::endl;

		sendto(sockCli, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, len);

		recvfrom(sockCli, recvBuf, 100, 0, (SOCKADDR*)&addrCli, &len);

		std::cout << "接收数据:" << recvBuf << std::endl;
	}

	closesocket(sockCli);
	WSACleanup();

	system("pause");
	return 0;
}