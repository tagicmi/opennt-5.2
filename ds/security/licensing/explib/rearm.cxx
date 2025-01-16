#include "precomp.h"
#pragma hdrstop
//#include "autoptr1.h"
#include "rearm.h"
#include "../lib/licmgr.h"

DWORD dword_1075D30 = 0;

#define ERROR_NO_RECORD 83

HRESULT sub_104B9E5(BOOL arg_0) {
	HRESULT status;
	AutoPtr<CWPALicenseManager> var_20 = new CWPALicenseManager;
	if (!var_20) {
		return E_OUTOFMEMORY;
	}
	DWORD var_10 = 0xFCD7E8A8;
	DWORD err = var_20.get()->sub_1053728(&var_10, sizeof(var_10));
	if (err != ERROR_SUCCESS) {
x:
		return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
	}
	err = var_20.get()->sub_1053D0D(dword_1075D30);
	if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
		//return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		goto x;
	}
	if (arg_0) {
		err = var_20.get()->sub_1053D0D(0x33);
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_1053F48();
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_1053FF3();
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_1053E99();
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_1053DB7(dword_1075D30);
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_1054789(dword_1075D30);
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_10541E2();
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_105413C();
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_1054098();
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
		err = var_20.get()->sub_10546A9(dword_1075D30);
		if (err != ERROR_SUCCESS && err != ERROR_NO_RECORD) {
			return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, err);
		}
	}
	return S_OK;
}
