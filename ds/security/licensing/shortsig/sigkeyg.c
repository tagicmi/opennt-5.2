#include <windows.h>
extern BOOL NewGenRandom(DWORD unused1, DWORD unused2, PUCHAR pRandomData, ULONG cRandomData);
BOOL random_bytes(PUCHAR pRandomData, ULONG cRandomData) {
	return NewGenRandom(0, 0, pRandomData, cRandomData);
}
