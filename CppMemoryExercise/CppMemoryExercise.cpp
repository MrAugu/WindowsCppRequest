#include "CppMemoryExercise.h"

using namespace std;

int main()
{
	HINTERNET hSession = WinHttpOpen(
		L"MyApp/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS,
		0
	);

	if (!hSession) {
		cout << "Error: WinHttpOpen failed\n";
		return 1;
	}

	HINTERNET hConnection = WinHttpConnect(hSession,
		L"127.0.0.1",
		3000,
		0
	);

	if (!hConnection) {
		cout << "Error: WinHttpConnect failed.\n";
		WinHttpCloseHandle(hSession);
		return 1;
	}

	wstring path = L"/?id=";
	int id = 45;
	path += to_wstring(id);

	HINTERNET hRequest = WinHttpOpenRequest(
		hConnection,
		L"GET",
		path.c_str(),
		NULL,
		WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES,
		0
	);

	if (!hRequest) {
		cout << "Error: WinHttpOpenRequest failed\n";
		WinHttpCloseHandle(hConnection);
		WinHttpCloseHandle(hSession);
		return 1;
	}

	const wchar_t* requestHeaders = L"Content-Type: application/json\r\n";

	BOOL bResults = WinHttpSendRequest(
		hRequest,
		requestHeaders,
		-1L,
		WINHTTP_NO_REQUEST_DATA,
		0,
		0,
		0
	);

	if (!bResults) {
		cout << "Error: WinHttpSendRequest failed.";
		WinHttpCloseHandle(hConnection);
		WinHttpCloseHandle(hSession);
		return 1;
	}

	bResults = WinHttpReceiveResponse(hRequest, NULL);

	if (!bResults) {
		cout << "Error: WinHttpReceiveResponse failed.";
		WinHttpCloseHandle(hConnection);
		WinHttpCloseHandle(hSession);
		return 1;
	}

	DWORD dwSize = 0;
	string response;

	do {
		DWORD dwDownloaded = 0;
		WinHttpQueryDataAvailable(hRequest, &dwSize);

		if (!dwSize) break;
		std::string buffer(dwSize, '\0');

		WinHttpReadData(
			hRequest,
			buffer.data(),
			dwSize,
			&dwDownloaded
		);

		response.append(buffer.data(), dwDownloaded);
	} while (dwSize > 0);

	cout << response;

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnection);
	WinHttpCloseHandle(hSession);

	return 0;
}