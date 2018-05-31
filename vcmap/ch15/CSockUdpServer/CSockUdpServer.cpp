#include "stdafx.h"
#include "../../shared/mcd.h"
#include <afxsock.h>

int _tmain()
{
	setlocale(LC_ALL, "chs");

	int nRetCode = 0;

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0) ||
		!AfxSocketInit())
	{
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		CSocket ListenSocket;
		ListenSocket.Create(0x1224, SOCK_DGRAM, _T("127.0.0.1"));
		ListenSocket.Bind(0x1224);
		_tprintf(_T("正在监听...\r\n"));

		CString address;
		UINT port;
		int params[2];
		int bytes;

		bytes = ListenSocket.ReceiveFrom((char *)params, sizeof(params), address, port);
		_tprintf(_T("已有客户端连接接入！来自%s:%d\r\n"), address, port);
		_tprintf(_T("成功接收%d个字节，内容：%d, %d\r\n"), bytes, params[0], params[1]);
		int m = mcd(params[0], params[1]);
		bytes = ListenSocket.SendTo((const char *)&m, sizeof(m), port, address);
		_tprintf(_T("成功回复%d个字节，内容：%d\r\n"), bytes, m);
		ListenSocket.Close();
	}

	return nRetCode;
}