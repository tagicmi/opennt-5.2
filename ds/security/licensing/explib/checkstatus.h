#ifdef __cplusplus
extern "C" {
#endif

int GetSafeMode(DWORD* arg_0);
DWORD sub_1043104(DWORD timerId, DWORD* val);
DWORD sub_10432CC(int arg_0, int arg_4);
DWORD CALLBACK sub_1045263(LPVOID ThreadParam);
DWORD CALLBACK sub_10470D2(LPVOID arg_0);
HRESULT sub_1047F5F(HANDLE hUserToken, LPWSTR lpDesktop);
BOOL sub_10498CE(void);
HRESULT sub_1049CA1(HDESK arg_0, HDESK arg_4, LPWSTR arg_8, LPVOID arg_C, HANDLE hUserToken, HWND hWnd, int arg_18, int arg_1C, DWORD* arg_20, DWORD* arg_24, DWORD* arg_28);

#ifdef __cplusplus
}
#endif
