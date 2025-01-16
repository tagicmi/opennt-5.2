class CWPAClass4 {
public:
	DWORD field_0;
	DWORD field_4;
	DWORD field_8;
	DWORD field_C;
	DWORD field_10;
	WCHAR field_14[0x21];
	char field_56[8]; // sizeof(HWID)
	// WORD padding;
	DWORD field_60;
	DWORD field_64;
	DWORD field_68;
	DWORD field_6C;
	char field_70[20];
	DWORD field_84;
	CWPAClass4() {
		field_0 = 0;
		field_8 = 0;
		field_10 = 0;
		field_4 = 0;
		field_60 = 0;
		field_64 = 0;
		field_68 = 0;
		ZeroMemory(field_14, sizeof(field_14));
		ZeroMemory(field_56, sizeof(field_56));
		field_6C = 0;
		field_84 = 0;
		ZeroMemory(field_70, sizeof(field_70));
	}
	void sub_105487E(LPCWSTR arg_0) {
		ZeroMemory(field_14, sizeof(field_14) - sizeof(WCHAR));
		lstrcpyn(field_14, arg_0, sizeof(field_14) / sizeof(field_14[0]));
	}
	void sub_105492E(LPCVOID arg_0, DWORD arg_4) {
		if (arg_4 > sizeof(field_70)) {
			return;
		}
		field_84 = arg_4;
		ZeroMemory(field_70, sizeof(field_70));
		memcpy(field_70, arg_0, field_84);
	}
};
