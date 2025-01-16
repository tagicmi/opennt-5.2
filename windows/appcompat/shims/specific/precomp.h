
#ifndef _APPSPECIFIC_PRECOMP_H_
#define _APPSPECIFIC_PRECOMP_H_

#include "ShimHook.h"
#include "StrSafe.h"

using namespace ShimLib;

#pragma warning(disable: 4235 4242 4244 4311 4312)

#if defined(_WIN64)
	#define GWL_WNDPROC GWLP_WNDPROC
	#define DWL_DLGPROC DWLP_DLGPROC
#endif

#endif // _APPSPECIFIC_PRECOMP_H_
