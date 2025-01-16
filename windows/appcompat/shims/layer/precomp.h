
#ifndef _GPSHIMS_PRECOMP_H_
#define _GPSHIMS_PRECOMP_H_

#include "ShimHook.h"
#include <shlwapi.h>
#include "StrSafe.h"

using namespace ShimLib;

#pragma warning(disable: 4028 4133 4242 4244 4311 4312)

#if defined(_AMD64_)
	#define GWL_WNDPROC GWLP_WNDPROC
#endif

#endif // _GPSHIMS_PRECOMP_H_
