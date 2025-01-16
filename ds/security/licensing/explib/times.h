struct CWPATimes {
	DWORD dwSize;
	DWORD dwProductId;
	SYSTEMTIME InstallTime;
	SYSTEMTIME LastUsageTime;
	BYTE Signature[0x10]; // encrypted md5 of first 4 fields
};
