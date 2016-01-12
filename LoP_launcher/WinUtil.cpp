#include "WinUtil.h"
#include <utf8.h>
#include <Windows.h>

using namespace std;

string getWindowsErrorMessage()
{
	wstring wMessage;
	LPWSTR pErr = nullptr;

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, GetLastError(), 0, (LPWSTR)&pErr, ERROR_STR_MAX_SIZE, nullptr);

	wMessage = pErr;

	HeapFree(GetProcessHeap(), 0, pErr);

	string exceptionMessageUTF8;
	utf8::utf16to8(wMessage.begin(), wMessage.end(), back_inserter(exceptionMessageUTF8));

	return exceptionMessageUTF8;
}

