void TrimHeadBlank(LPCSTR& lpData, LPCSTR lpEnd) {
	for (; lpData <= lpEnd; ++lpData) {
		if (!isspace(*lpData)) {
			break;
		}
	}
}

void TrimTrailBlank(LPCSTR& lpData, LPCSTR lpStart) {
	for (; lpStart < lpData; --lpData) {
		if (!isspace(*lpData)) {
			break;
		}
	}
}

void TrimLF(LPCSTR& lpData, LPCSTR lpEnd) {
	for (; lpData <= lpEnd; ++lpData) {
		if (*lpData != '\r' && *lpData != '\n') {
			break;
		}
	}
}
