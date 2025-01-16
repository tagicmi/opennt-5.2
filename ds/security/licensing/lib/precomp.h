#include <nt.h>
#include <ntrtl.h>
#include <nturtl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define XINC x++;
#define XINC4 XINC XINC XINC XINC
#define XINC16 XINC4 XINC4 XINC4 XINC4
#define XINC64 XINC16 XINC16 XINC16 XINC16
#define XINC256 XINC64 XINC64 XINC64 XINC64
#define XINC1024 XINC256 XINC256 XINC256 XINC256
inline void ignore() {
int x;
XINC1024 XINC1024 XINC1024 XINC1024
}

#include "../include/autoptr.h"
