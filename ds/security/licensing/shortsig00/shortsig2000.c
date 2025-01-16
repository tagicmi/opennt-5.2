#include <crypto/bignum.h>
#include "shortsig2000.h"
#include "field.h"
#include "kpolys.h"

typedef unsigned _DWORD;
typedef unsigned char _BYTE;

typedef struct tagWPAShortSigKey
{
  _DWORD dword0;
  _DWORD dword4;
  _DWORD dword8;
  _DWORD dwordC;
  _DWORD dword10;
  _DWORD dword14;
  void *pvoid18;
  unsigned int *punsigned1C;
  _DWORD *pvoid20;
  unsigned int *punsigned24;
  unsigned int *punsigned28;
  unsigned int *punsigned2C;
  unsigned int *punsigned30;
  unsigned int *punsigned34;
  _DWORD *dword38;
  _DWORD *dword3C;
  mp_modulus_t mp_modulus40;
  field_desc_t kstruc1284;
  _BYTE gap12A4[20];
  modmultemp_t modmultemp;
  kpoly_t dword35E8;
  kpoly_t kp_struc35F4[3];
  _DWORD *pvoid3618[3][3];
  kpoly_t pvoid363C[2];
  _DWORD *pvoid3654[2];
  _DWORD *dword365C[2];
} CWPAShortSigKey;

typedef struct _shortsig00_struc_1
{
  kpoly_t field_0;
  kpoly_t field_C;
  digit_t field_14[14];
  int field_50;
} shortsig00_struc_1;

static int sub_1062486(const shortsig00_struc_1 *a1, const shortsig00_struc_1 *a2, int a3, shortsig00_struc_1 *a4, const CWPAShortSigKey *a5);
static int sub_106234E(const shortsig00_struc_1 *a1, shortsig00_struc_1 *a2, const CWPAShortSigKey *a3);
static int sub_106241C(shortsig00_struc_1 *a1, const CWPAShortSigKey *a2, int a3);
static int sub_10631F8(digit_tc a1[], DWORD a2, const CWPAShortSigKey *a3, BYTE *a4);
static int sub_106356D(digit_tc a1[], const CWPAShortSigKey *a2, digit_t a3[]);
static int sub_106370F(const kpoly_t *a1, const CWPAShortSigKey *a2, digit_t a3[]);
static int sub_1064CEF(const shortsig00_struc_1* a1, const CWPAShortSigKey * a2, kpoly_t* a3);
static int sub_1064941(const kpoly_t *a1, const CWPAShortSigKey *a2, digit_t a3[]);
static int sub_1064C7D(const kpoly_t *a1, const CWPAShortSigKey *a2, kpoly_t *a3);
static int sub_1064D6C(const shortsig00_struc_1 *a1, const CWPAShortSigKey *a2, shortsig00_struc_1 *a3);
static int sub_1064DFC(digit_tc a1[], const CWPAShortSigKey *a2, shortsig00_struc_1 *a3, int* a4);
static int sub_106441B(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t* a4, const field_desc_t* a5);
static int sub_1064134(digit_t a1[], DWORD* a2, const kpoly_t* a3, const field_desc_t* a4);
static int sub_10644AF(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t *a4, const kpoly_t *a5, const field_desc_t *a6);
static int sub_106427E(digit_tc a1[], digit_t a2[], const kpoly_t* a3, const field_desc_t* a4);
static int sub_10648B3(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t* a4, const field_desc_t* a5);

const unsigned dword_101A160 = 0xB4EBA631;

int PID_setup_key(CWPAHyperellipticParams *arg_0, CWPAShortSigKey **arg_4)
{
  unsigned int lng; // [sp+32Ch] [bp-4h]@1
  {
  unsigned int v76; // [sp+328h] [bp-8h]@1
  {
  int v75; // [sp+324h] [bp-Ch]@94
  {
  unsigned int v74; // [sp+320h] [bp-10h]@1
  {
  CWPAShortSigKey *v73; // [sp+31Ch] [bp-14h]@1
  {
  unsigned int i; // [sp+318h] [bp-18h]@33
  {
  unsigned int lngb; // [sp+314h] [bp-1Ch]@1
  {
  unsigned int v70; // [sp+310h] [bp-20h]@1
  {
  unsigned int j; // [sp+30Ch] [bp-24h]@38
  {
  unsigned int lngp; // [sp+308h] [bp-28h]@1
  {
  unsigned int k; // [sp+304h] [bp-2Ch]@160
  {
  int v66; // [sp+300h] [bp-30h]@1

  v66 = 1;
  v74 = arg_0->dwCurveGenus;
  v70 = arg_0->dwModulusSize;
  lngp = v70;
  lng = v74 * lngp;
  v76 = arg_0->field_8;
  lngb = v76;
  v73 = (CWPAShortSigKey *)mp_alloc_temp(sizeof(CWPAShortSigKey));
  if ( !v73 )
  {
    v66 = 0;
  }
  else
  {
    arg_0->field_10 = 4 * v74 * v70;
    v73->dword10 = arg_0->field_10;
    v73->dword0 = dword_101A160;
    v73->pvoid18 = 0;
    v73->dword4 = v74;
    v73->dword8 = lngp;
    v73->dwordC = lngb;
  }
  v66 = v66 && v70 > 0 && v70 <= 2;
  if ( v74 == 2 )
  {
    v66 = v66 && (*arg_0->pModulus & 1) == 1;
  }
  else if ( v74 == 3 )
  {
    v66 = v66 && (*arg_0->pModulus & 3) == 3;
  }
  else
  {
    v66 = 0;
  }
  v66 = v66 && v74 <= 3;
  v66 = v66 && v76 <= 6;
  if ( v66 )
  {
    DWORD_PTR *v65; // [sp+2FCh] [bp-34h]@31
    {
    unsigned int v64; // [sp+2F8h] [bp-38h]@31

    v64 = (v74 * 2 * v74 + 7 * v74 + 16) * lngp + 4 * lngb;
    v65 = mp_alloc_temp(sizeof(digit_t) * v64);
    if ( !v65 )
    {
      v66 = 0;
    }
    else
    {
      DWORD_PTR *v63 = v65; // [sp+2F4h] [bp-3Ch]@33

      for ( i = 0; i != v64; ++i )
        v65[i] = 0;
      v73->pvoid18 = v63;
      v73->punsigned1C = (_DWORD*)v63;
      v63 += lngp;
      v73->pvoid20 = (_DWORD*)v63;
      v63 += lng;
      v73->punsigned24 = (_DWORD*)v63;
      v63 += lng;
      v73->punsigned28 = (_DWORD*)v63;
      v63 += lngp;
      v73->punsigned2C = (_DWORD*)v63;
      v63 += 2 * lngp;
      v73->punsigned30 = (_DWORD*)v63;
      v63 += 2 * lngp;
      v73->punsigned34 = (_DWORD*)v63;
      v63 += 3 * lngp;
      v73->dword38 = (_DWORD*)v63;
      v63 += lngp;
      v73->dword3C = (_DWORD*)v63;
      v63 += lngp;
      v73->dword35E8.maxlength = v74 + 1;
      v73->dword35E8.coefs = (digit_t*)v63;
      v63 += (v74 + 1) * lngp;
      v73->pvoid363C[0].maxlength = 2 * v74 + 2;
      v73->pvoid363C[0].coefs = (digit_t*)v63;
      v63 += (2 * v74 + 2) * lngp;
      v73->pvoid363C[1].maxlength = 2 * v74 + 2;
      v73->pvoid363C[1].coefs = (digit_t*)v63;
      v63 += (2 * v74 + 2) * lngp;
      for ( i = 0; i != v74; ++i )
      {
        v73->kp_struc35F4[i].maxlength = v74;
        v73->kp_struc35F4[i].coefs = (digit_t*)v63;
        v63 += v74 * lngp;
        for ( j = 0; j != v74; ++j )
        {
          v73->pvoid3618[i][j] = (_DWORD*)v63;
          v63 += lngp;
        }
      }
      v73->pvoid3654[0] = (_DWORD*)v63;
      v63 += lngb;
      v73->pvoid3654[1] = (_DWORD*)v63;
      v63 += lngb;
      v73->dword365C[0] = (_DWORD*)v63;
      v63 += lngb;
      v73->dword365C[1] = (_DWORD*)v63;
      v63 += lngb;
      if ( v63 != &v65[v64] )
        v66 = 0;
    }}
  }
  if ( v66 )
  {
    dwords_to_digits(arg_0->pModulus, (digit_t*)v73->punsigned1C, v70);
	
    if(!test_primality((digit_t*)v73->punsigned1C, lngp)) v66 = 0;
    
	divide_immediate((digit_t*)v73->punsigned1C, 2u, 0, (digit_t*)v73->punsigned28, lngp);
    multiply((digit_tc*)v73->punsigned1C, lngp, (digit_tc*)v73->punsigned1C, lngp, (digit_t*)v73->punsigned30);
    multiply((digit_tc*)v73->punsigned1C, lngp, (digit_t*)v73->punsigned30, 2 * lngp, (digit_t*)v73->punsigned34);
    divide_immediate((digit_t*)v73->punsigned30, 2u, 0, (digit_t*)v73->punsigned2C, 2 * lngp);
    sub_diff((digit_t*)v73->punsigned30, 2 * lngp, (digit_tc*)v73->punsigned1C, lngp, (digit_t*)v73->punsigned30);
    sub_diff((digit_t*)v73->punsigned34, 3 * lngp, (digit_tc*)v73->punsigned1C, lngp, (digit_t*)v73->punsigned34);
    divide_immediate((digit_t*)v73->punsigned30, 2u, 0, (digit_t*)v73->punsigned30, 2 * lngp);
    divide_immediate((digit_t*)v73->punsigned34, 3u, 0, (digit_t*)v73->punsigned34, 3 * lngp);
    memcpy(v73->pvoid20, (digit_tc*)v73->punsigned1C, 4 * lngp);
    for ( i = 2; i <= v74; ++i )
    {
      unsigned int lnga; // [sp+2F0h] [bp-40h]@49
      lnga = (i - 1) * lngp;
      memcpy(v73->pvoid363C[0].coefs, v73->pvoid20, 4 * lnga);
      multiply(v73->pvoid363C[0].coefs, lnga, (digit_tc*)v73->punsigned1C, lngp, (digit_t*)v73->pvoid20);
    }
    v66 = v66 && mp_shift((digit_tc*)v73->pvoid20, -1, (digit_t*)v73->pvoid20, lng) == 1;
    if ( v74 == 3 )
    {
      v66 = v66 && !add_immediate((digit_t*)v73->pvoid20, 1u, (digit_t*)v73->punsigned24, lng);
      v66 = v66 && !mp_shift((digit_t*)v73->punsigned24, -1, (digit_t*)v73->punsigned24, lng);
    }
  }
  v66 = v66 && create_modulus((digit_tc*)v73->punsigned1C, lngp, 0, &v73->mp_modulus40);
  v66 = v66 && Kinitialize_prime(&v73->mp_modulus40, &v73->modmultemp, &v73->kstruc1284);
  if ( v66 )
  {
    unsigned int v61; // [sp+2ECh] [bp-44h]@73
    {
    int v60; // [sp+2E8h] [bp-48h]@73

    v61 = *v73->punsigned1C & 7;
    v60 = 0;
    if ( v61 == 3 || v61 == 5 )
    {
      v60 = 2;
    }
    else
    {
      int numer; // [sp+2E4h] [bp-4Ch]@76

      v60 = 0;
      for ( numer = 3; !v60 && numer <= 99; numer += 2 )
      {
        if ( mod_jacobi_immediate(numer, &v73->mp_modulus40) == -1 )
          v60 = numer;
      }
    }
    if ( !v60 )
      v66 = 0;
    if ( v66 )
    {
      v66 = v66 && Kimmediate(v60, (digit_t*)v73->dword38, (field_desc_t*)&v73->kstruc1284);
      v66 = v66 && Kinvert((digit_tc*)v73->dword38, (digit_t*)v73->dword3C, (field_desc_t*)&v73->kstruc1284);
    }
    }
  }
  v75 = v66;
  if ( v66 && v74 == 3 )
  {
    field_desc_t *arg_C; // [sp+2E0h] [bp-50h]@96
    {
    digit_t a[2]; // [sp+2D8h] [bp-58h]@99
    {
    kpoly_t v56; // [sp+2CCh] [bp-64h]@96
    {
    mp_modulus_t *modulo; // [sp+2C8h] [bp-68h]@96
    {
    _DWORD v54[6]; // [sp+2B0h] [bp-80h]@96

    arg_C = &v73->kstruc1284;
    modulo = &v73->mp_modulus40;
    v56.maxlength = 3;
    v56.coefs = (digit_t*)v54;
    for ( i = 0; v66 && i <= v74; ++i )
    {
      dwords_to_digits(&arg_0->field_20[i * v70], a, v70);
      to_modular(a, lngp, &v73->dword35E8.coefs[i * lngp], modulo);
    }
    v73->dword35E8.degree = v74;
    if ( !Kequal(&v73->dword35E8.coefs[lng], arg_C->one, arg_C) )
      v66 = 0;
    v66 = v66 && KPmonomial(v73->kstruc1284.one, 1, v73->kp_struc35F4, arg_C);
    for ( i = 1; v66 && i != v74; ++i )
    {
      v66 = v66 && KPexpon(&v73->kp_struc35F4[i - 1], (digit_tc*)v73->punsigned1C, lngp, &v73->kp_struc35F4[i], &v73->dword35E8, arg_C);
      v66 = v66 && KPsub(&v73->kp_struc35F4[i], v73->kp_struc35F4, &v56, arg_C);
      v66 = v66 && KPgcd(&v56, &v73->dword35E8, &v56, 0, 0, arg_C);
      if ( v66 )
      {
        if ( v56.degree != 0 )
          v66 = 0;
      }
    }
    v56.degree = (DWORD)-1;
    for ( i = 0; v66 && i != v74; ++i )
    {
      v66 = v66 && KPadd(&v56, &v73->kp_struc35F4[i], &v56, arg_C);
    }
    if ( v66 && v56.degree != 0 )
      v66 = 0;
    }}}}
  }
  if ( v66 && v74 == 3 )
  {
    field_desc_t *v53; // [sp+2ACh] [bp-84h]@138
    {
    _DWORD *ptr[3]; // [sp+2A0h] [bp-90h]@140

    v53 = &v73->kstruc1284;
    for ( i = 0; i != v74; ++i )
      ptr[i] = 0;
    for ( i = 0; v66 && i != v74; ++i )
    {
      ptr[i] = mp_alloc_temp(sizeof(digit_t) * (2 * lng));
      if ( !ptr[i] )
      {
        v66 = 0;
      }
      else
      {
        v66 = v66 && Kclear((digit_t*)ptr[i], 2 * v74, v53);
        v66 = v66 && Kcopy(v53->one, (digit_t*)&ptr[i][(i + v74) * lngp], 1, v53);
      }
    }
    for ( i = 0; v66 && i != v74; ++i )
    {
      unsigned int v51; // [sp+29Ch] [bp-94h]@159
      {
      kpoly_t *v50; // [sp+298h] [bp-98h]@159

      v50 = &v73->kp_struc35F4[i];
      v51 = v50->degree;
      if ( v51 != (DWORD)-1 )
      {
        for ( k = 0; k <= v51; ++k )
        {
          v66 = v66 && Kcopy(&v50->coefs[k * lngp], (digit_t*)&ptr[k][i * lngp], 1, v53);
        }
      }
      }
    }
    for ( i = 0; v66 && i != v74; ++i )
    {
      int v49; // [sp+294h] [bp-9Ch]@171

      v49 = -1;
      for ( j = i; j != v74; ++j )
      {
        if ( !Kiszero((digit_t*)&ptr[j][i * lngp], v53) )
          v49 = j;
      }
      if ( v49 == -1 )
      {
        v66 = 0;
      }
      else
      {
        _DWORD *v48; // [sp+290h] [bp-A0h]@178
        {
        digit_t v47[64]; // [sp+190h] [bp-1A0h]@179

        v48 = ptr[v49];
        ptr[v49] = ptr[i];
        ptr[i] = v48;
        v66 = v66 && Kinvert((digit_t*)&v48[i * lngp], v47, v53);
        for ( k = i; k != 2 * v74; ++k )
        {
          v66 = v66 && Kmul((digit_tc*)&v48[k * lngp], v47, (digit_t*)&v48[k * lngp], v53);
        }
        for ( j = 0; v66 && j != v74; ++j )
        {
          if ( j != i )
          {
            v66 = v66 && Kcopy((digit_tc*)&ptr[j][i * lngp], v47, 1, v53);
            for ( k = i; k != 2 * v74; ++k )
            {
              v66 = v66 && Kmulsubfrom(v47, (digit_tc*)&v48[k * lngp], (digit_t*)&ptr[j][k * lngp], (digit_t*)&ptr[j][k * lngp], v53);
            }
          }
        }
        }
      }
    }
    for ( i = 0; i != v74; ++i )
    {
      for ( k = 0; k != v74; ++k )
      {
        v66 = v66 && Kcopy((digit_tc*)&ptr[i][(k + v74) * lngp], (digit_t*)v73->pvoid3618[i][k], 1, v53);
      }
    }
    for ( i = 0; i != v74; ++i )
    {
      if ( ptr[i] )
        mp_free_temp(ptr[i]);
    }
    }
  }
  if ( v66 )
  {
    field_desc_t *v46; // [sp+18Ch] [bp-1A4h]@222
    {
    digit_t v45[16]; // [sp+14Ch] [bp-1E4h]@222
    {
    digit_t v44[16]; // [sp+10Ch] [bp-224h]@222
    {
    digit_t a1[2]; // [sp+104h] [bp-22Ch]@225
    {
    digit_t v42[16]; // [sp+C4h] [bp-26Ch]@222
    {
    kpoly_t v40; // [sp+B8h] [bp-278h]@222
    {
    kpoly_t v38; // [sp+ACh] [bp-284h]@222
    {
    kpoly_t v36; // [sp+A0h] [bp-290h]@222
    {
    mp_modulus_t *v35; // [sp+9Ch] [bp-294h]@222

    v35 = &v73->mp_modulus40;
    v46 = &v73->kstruc1284;
    v38.maxlength = 2 * v74 + 2;
    v40.maxlength = 2 * v74 + 2;
    v36.maxlength = 2 * v74 + 2;
    v38.coefs = v44;
    v40.coefs = v45;
    v36.coefs = v42;
    for ( i = 0; v66 && i <= 2 * v74 + 1; ++i )
    {
      _DWORD *v33; // [sp+94h] [bp-29Ch]@225
      unsigned int *b; // [sp+98h] [bp-298h]@225

      b = (unsigned int*)&v73->pvoid363C[0].coefs[i * lngp];
      v33 = (_DWORD*)&v73->pvoid363C[1].coefs[i * lngp];
      dwords_to_digits(&arg_0->pCurveCoefficients[i * v70], a1, v70);
      to_modular(
		a1,
		lngp,
		(digit_t*)b,
		v35);
      if ( v74 == 2 )
      {
        v66 = v66 && Kcopy(
			(digit_tc*)b,
			(digit_t*)v33,
			1,
			v46);
      }
      else
      {
        v66 = v66 && Knegate((digit_tc*)b,
							(digit_t*)v33,
							v46);
      }
    }
    v73->pvoid363C[0].degree = 2 * v74 + 1;
    v73->pvoid363C[1].degree = 2 * v74 + 1;
    if ( v66 )
    {
      if ( all_zero(a1, lngp) )
        v66 = 0;
    }
    }}}}}}}}
  }
  v73->dword14 = arg_0->dwPublicMultiplier;
  for ( i = 0; v66 && i != 2; ++i )
  {
    digit_t v32; // [sp+90h] [bp-2A0h]@243
    {
    DWORD v31; // [sp+8Ch] [bp-2A4h]@246

    v32 = v73->dword14;
    dwords_to_digits(
		arg_0->field_24[i],
		(digit_t*)v73->pvoid3654[i],
		v76);
    if ( v74 == 2 )
      memcpy(v73->pvoid3654[1], v73->pvoid3654[0], 4 * lngb);
    if ( !all_zero((digit_tc*)v73->pvoid3654[i], lngb) )
    {
      digit_t gcd[6]; // [sp+74h] [bp-2BCh]@246

      v31 = mp_gcdex(
		&v32,
		1u,
		(digit_tc*)v73->pvoid3654[i],
		lngb,
		(digit_t*)v73->dword365C[i],
		0,
		gcd,
		0);
      if ( compare_immediate(gcd, 1u, v31) )
        v66 = 0;
    }
    }
  }
  if ( !v66 )
  {
    if ( v75 )
      Kfree(&v73->kstruc1284);
    if ( v73 )
    {
      if ( v73->pvoid18 )
        mp_free_temp(v73->pvoid18);
      mp_free_temp(v73);
      v73 = 0;
    }
  }
  *arg_4 = v73;
  return v66;
  }}}}}}}}}}}
}

int PID_unsetup_key(CWPAShortSigKey *pKey)
{
  CWPAShortSigKey* pKeyCopy = pKey;
  {
  int v4; // [sp+8h] [bp-8h]@5

  v4 = pKeyCopy != NULL;
  v4 = v4 && pKeyCopy->dword0 == dword_101A160;
  if ( v4 )
  {
    v4 = v4 && Kfree(&pKeyCopy->kstruc1284);
    mp_free_temp(pKeyCopy->pvoid18);
    mp_free_temp(pKeyCopy);
  }
  return v4;
  }
}

int PID_allocate_key_fields_dwords(CWPAHyperellipticParams *arg_0)
{
  unsigned int v16; // [sp+2Ch] [bp-4h]@1
  {
  unsigned int v15; // [sp+28h] [bp-8h]@1
  {
  unsigned int v14; // [sp+24h] [bp-Ch]@1
  {
  int v13; // [sp+20h] [bp-10h]@15

  v13 = 1;
  v15 = arg_0->dwCurveGenus;
  v14 = arg_0->dwModulusSize;
  v16 = arg_0->field_8;
  arg_0->field_14 = 0;
  v13 = v13 && v14 > 0 && v14 <= 2;
  v13 = v13 && v16 > 0 && v16 <= 6;
  v13 = v13 && v15 > 0 && v15 <= 3;
  if ( v13 )
  {
    int v12; // [sp+1Ch] [bp-14h]@16
    {
    int v11; // [sp+18h] [bp-18h]@16
    {
    unsigned int *v10; // [sp+14h] [bp-1Ch]@16
    v11 = (v15 + 1) * v14;
    v12 = 3 * v11 + v14 + 2 * v16;
    v10 = (DWORD*)mp_alloc_temp(sizeof(DWORD) * v12);
    if ( !v10 )
    {
      v13 = 0;
    }
    else
    {
      int i; // [sp+10h] [bp-20h]@18
      {
      unsigned int *v1; // ST10_4@21

      v1 = v10;
      for ( i = 0; i != v12; ++i )
        v10[i] = 0;
      arg_0->field_14 = v1;
      arg_0->pModulus = v1;
      v1 += v14;
      arg_0->pCurveCoefficients = v1;
      v1 += 2 * v11;
      arg_0->field_20 = v1;
      v1 += v11;
      arg_0->field_24[0] = v1;
      v1 += v16;
      arg_0->field_24[1] = v1;
      v1 += v16;
      if ( v1 != &v10[v12] )
        v13 = 0;
    }}}}
  }
  return v13;
  }}}
}

int PID_free_key_fields_dwords(CWPAHyperellipticParams *arg_0)
{
  if ( arg_0->field_14 )
  {
    mp_free_temp(arg_0->field_14);
    arg_0->field_14 = 0;
    arg_0->pModulus = 0;
    arg_0->pCurveCoefficients = 0;
    arg_0->field_20 = 0;
    arg_0->field_24[0] = 0;
    arg_0->field_24[1] = 0;
    return 1;
  }
  else
  {
    return 0;
  }
}

// exact copy of compare_same without "inline"
// to get the function order right
#if !USEASM_MIPS
int compare_same_noinline(digit_tc  a[],
                               digit_tc  b[],
                               DWORDC    lng)
/*
        Compare two multiple precision numbers a and b each of length lng.
        Function value is the sign of a - b, namely

                          +1 if a > b
                           0 if a = b
                          -1 if a < b
*/
#if USEASM_IX86
    #pragma warning(disable : 4035)      /* No return value */
{
                    /*
                            We could use REPE CMPSD,
                            but REPE is slow (4 cycles)
                            on the Pentium.  Plus we
                            would need std and cld
                            to adjust the direction flag.
                            We anticipate that most loops
                            will have either 1 or 2 iterations,
                            and use RISC instructions.
                    */

    _asm {
        mov  eax,lng
        mov  esi,a
        mov  edi,b
     label1:
        test eax,eax
        jz   label2              ; If nothing left, exit with eax = 0

        mov  ecx,[esi+4*eax-4]   ;
        mov  edx,[edi+4*eax-4]

        dec  eax                 ; Decrement remaining loop count
        cmp  ecx,edx             ; Test a[i] - b[i]

        je   label1

        sbb  eax,eax             ; eax = 0 if a > b,   -1 if a < b
        or   eax,1               ; eax = 1 if a > b,   -1 if a < b
     label2:
    }
}
    #pragma warning(default : 4035)
#else
{
    DWORD i;
    for (i = lng-1; i != -1; i--) {
        if (a[i] != b[i]) return (a[i] > b[i] ? +1 : -1);
    }
    return 0;
}  /* compare_same */
#endif
#define compare_same compare_same_noinline
#endif

int sub_1061773(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t *a4, const field_desc_t *a5)
{
  DWORD v10; // [sp+14h] [bp-4h]@1
  {
  DWORD i; // [sp+10h] [bp-8h]@1
  {
  DWORD v8; // [sp+Ch] [bp-Ch]@1
  {
  int v7; // [sp+8h] [bp-10h]@1

  v10 = a4->degree;
  v8 = a5->elng;
  v7 = 1;
  for ( i = 0; i != v10; ++i )
  {
    DWORD v6 = i * v8; // [sp+4h] [bp-14h]

    v7 = v7 && Kadd(&a1[v6], &a2[v6], &a3[v6], a5);
  }
  return v7;
  }}}
}

int sub_1061807(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t* a4, const field_desc_t* a5)
{
  DWORD v16; // [sp+54h] [bp-4h]@1
  {
  digit_t v15[10]; // [sp+2Ch] [bp-2Ch]@1
  {
  DWORD i; // [sp+28h] [bp-30h]@1
  {
  int v12; // [sp+24h] [bp-34h]@1
  {
  DWORD j; // [sp+20h] [bp-38h]@3
  {
  int v9; // [sp+1Ch] [bp-3Ch]@1

  v16 = a4->degree;
  v12 = a5->elng;
  v9 = 1;
  v9 = v9 && Kclear(v15, 2 * v16 - 1, a5);
  for ( i = 0; i != v16; ++i )
  {
    int v6; // [sp+18h] [bp-40h]
    {
    int v7; // [sp+14h] [bp-44h]

    for ( j = 0; j != v16; ++j )
    {
      v6 = i * v12;
      v7 = j * v12;
      v9 = v9 && Kmuladd(&a1[v6], &a2[v7], &v15[v6] + v7, &v15[v6] + v7, a5);
    }
    }
  }
  for ( i = 2 * v16 - 2; i >= v16; --i )
  {
    digit_t* v8 = &v15[i * v12]; // [sp+10h] [bp-48h]
    for ( j = 0; j != v16; ++j )
    {
      v9 = v9 && Kmulsubfrom(v8, &a4->coefs[j * v12], &v15[(i - v16 + j) * v12], &v15[(i - v16 + j) * v12], a5);
    }
  }
  v9 = v9 && Kcopy(v15, a3, v16, a5);
  return v9;
  }}}}}
}

int sub_10619F5(shortsig00_struc_1 *a1, const CWPAShortSigKey *a2)
{
  int v4;
  unsigned int v2; // ST08_4@1
  int v3; // ST04_4@1

  v4 = 1;
  v2 = a2->dword4;
  v3 = a2->dword8;
  a1->field_0.coefs = a1->field_14;
  a1->field_0.maxlength = v2 + 1;
  a1->field_C.coefs = &a1->field_14[(v2 + 1) * v3];
  a1->field_C.maxlength = v2;
  return v4;
}

int sub_1061A54(const kpoly_t *a1, const kpoly_t *a2, kpoly_t *a3, const CWPAShortSigKey *a4, int *a5)
{
  digit_t v44[4]; // [sp+198h] [bp-10h]@1
  {
  digit_t v43[4]; // [sp+188h] [bp-20h]@1
  {
  unsigned int v42; // [sp+184h] [bp-24h]@1
  {
  const field_desc_t *v41; // [sp+180h] [bp-28h]@1
  {
  digit_t v40[12]; // [sp+150h] [bp-58h]@1
  {
  kpoly_t v39; // [sp+144h] [bp-64h]@1
  {
  digit_t v38[12]; // [sp+114h] [bp-94h]@1
  {
  int v37; // [sp+110h] [bp-98h]@1
  {
  kpoly_t v36; // [sp+104h] [bp-A4h]@1
  {
  digit_t v35[4]; // [sp+F4h] [bp-B4h]@1
  {
  digit_t v34[12]; // [sp+C4h] [bp-E4h]@1
  {
  kpoly_t v33; // [sp+B8h] [bp-F0h]@1
  {
  int v32; // [sp+B4h] [bp-F4h]@1
  {
  kpoly_t v31; // [sp+A8h] [bp-100h]@1
  {
  kpoly_t v30; // [sp+9Ch] [bp-10Ch]@1
  {
  unsigned int i; // [sp+98h] [bp-110h]@11
  {
  int v28; // [sp+94h] [bp-114h]@1
  {
  kpoly_t v27; // [sp+88h] [bp-120h]@1
  {
  digit_t v26[12]; // [sp+58h] [bp-150h]@1
  {
  kpoly_t v25; // [sp+4Ch] [bp-15Ch]@1

  v28 = 1;
  v37 = 0;
  v41 = &a4->kstruc1284;
  v32 = a4->dword8;
  v42 = mp_significant_bit_count((digit_tc*)a4->punsigned2C, 2 * v32);
  *a5 = 0;
  v39.maxlength = 6;
  v39.coefs = v38;
  v33.maxlength = 6;
  v33.coefs = v40;
  v30.maxlength = 6;
  v30.coefs = v34;
  v36.maxlength = 6;
  v36.coefs = v26;
  v27.maxlength = 2;
  v27.coefs = v44;
  v31.maxlength = 2;
  v31.coefs = v43;
  v25.maxlength = 2;
  v25.coefs = v35;
  v28 = v28 && KPexpon(a1, (digit_tc*)a4->punsigned2C, 2 * v32, &v39, a2, v41);
  if ( !v28 )
  {
  }
  else if ( v39.degree == (DWORD)-1 )
  {
    v37 = 1;
    *a5 = 1;
    a3->degree = (DWORD)-1;
  }
  else if ( v39.degree == 0 )
  {
    *a5 = Kequal(v41->one, v39.coefs, v41);
    v37 = *a5 == 0;
  }
  else
  {
    v28 = 0;
  }
  for ( i = 0; i < 0x64 && v28 && !v37; ++i )
  {
    DWORD j; // [sp+48h] [bp-160h]@23

    v25.degree = 1;
    v28 = v28 && KPrandom(&v25, v41);
    v28 = v28 && KPmonomial(v41->one, 0, &v31, v41);
    v27.degree = (DWORD)-1;
    for ( j = v42 - 1; v28 && j != (DWORD)-1; --j )
    {
      unsigned int v23; // [sp+44h] [bp-164h]@26
      {
      unsigned int k; // [sp+40h] [bp-168h]@42

      v23 = (unsigned int)mp_getbit((digit_tc*)a4->punsigned2C, j);
      v28 = v28 && KPmul(&v27, &v27, &v39, v41);
      v28 = v28 && KPmul(&v27, &v31, &v33, v41);
      v28 = v28 && KPadd(&v33, &v33, &v33, v41);
      v28 = v28 && KPmul(&v31, &v31, &v30, v41);
      for ( k = 0; k <= v23; ++k )
      {
        v28 = v28 && KPmul(&v39, a1, &v36, v41);
        v28 = v28 && KPadd(&v36, &v30, &v30, v41);
        v28 = v28 && KPdiv(&v33, a2, 0, &v27, v41);
        v28 = v28 && KPdiv(&v30, a2, 0, &v31, v41);
        if ( k != v23 )
        {
          v28 = v28 && KPcopy(&v27, &v39, v41);
          v28 = v28 && KPmul(&v27, &v25, &v33, v41);
          v28 = v28 && KPadd(&v33, &v31, &v33, v41);
          v28 = v28 && KPmul(&v31, &v25, &v30, v41);
        }
      }
      }
    }
    if ( v27.degree != (DWORD)-1 && v31.degree == (DWORD)-1 )
    {
      v28 = v28 && KPgcd(a2, &v27, &v33, 0, a3, v41);
      *a5 = 1;
      v37 = 1;
    }
  }
  if ( !v37 )
    v28 = 0;
  return v28;
  }}}}}}}}}}}}}}}}}}}
}

int sub_10621B2(const shortsig00_struc_1 *a1, digit_tc a2[], DWORD a3, const CWPAShortSigKey *a4, shortsig00_struc_1 *a5)
{
  const field_desc_t *v15; // [sp+78h] [bp-4h]@1
  {
  shortsig00_struc_1 a1a; // [sp+24h] [bp-58h]@1
  {
  int i; // [sp+20h] [bp-5Ch]@5
  {
  int v12; // [sp+1Ch] [bp-60h]@5

  v12 = 1;
  v15 = &a4->kstruc1284;
  v12 = v12 && sub_10619F5(&a1a, a4);
  v12 = v12 && sub_106241C(&a1a, a4, a1->field_50);
  for ( i = 32 * a3 - 1; i != -1; --i )
  {
    int v11; // [sp+18h] [bp-64h]@7
    v11 = (int)mp_getbit((digit_tc*)a2, (DWORDC)i);
    if ( a1a.field_0.degree == 0 )
    {
      if ( v11 == 1 )
      {
        v12 = v12 && sub_106234E(a1, &a1a, a4);
      }
    }
    else
    {
      v12 = v12 && sub_1062486(&a1a, &a1a, 1, &a1a, a4);
      if ( v11 == 1 )
      {
        v12 = v12 && sub_1062486(&a1a, a1, 1, &a1a, a4);
      }
    }
  }
  v12 = v12 && sub_106234E(&a1a, a5, a4);
  return v12;
  }}}
}

int sub_106234E(const shortsig00_struc_1 *a1, shortsig00_struc_1 *a2, const CWPAShortSigKey *a3)
{
  const field_desc_t *arg_8; // [sp+10h] [bp-4h]@1
  {
  int v7; // [sp+Ch] [bp-8h]@1

  v7 = 1;
  arg_8 = &a3->kstruc1284;
  if ( a1 != a2 )
  {
    v7 = v7 && sub_10619F5(a2, a3) != 0;
    a2->field_50 = a1->field_50;
    v7 = v7 && KPcopy(&a1->field_0, &a2->field_0, arg_8);
    v7 = v7 && KPcopy(&a1->field_C, &a2->field_C, arg_8);
  }
  return v7;
  }
}

int sub_106241C(shortsig00_struc_1 *a1, const CWPAShortSigKey *a2, int a3)
{
  const field_desc_t *v2; // [sp+10h] [bp-4h]@1
  {
  int v3; // ST10_4@1

  v3 = 1;
  v2 = &a2->kstruc1284;
  v3 = v3 && KPmonomial(v2->one, 0, &a1->field_0, v2);
  a1->field_C.degree = (DWORD)-1;
  a1->field_50 = a3;
  return v3;
  }
}

int sub_1062486(const shortsig00_struc_1 *a1, const shortsig00_struc_1 *a2, int a3, shortsig00_struc_1 *a4, const CWPAShortSigKey *a5)
{
  unsigned int v58; // [sp+134h] [bp-4h]@1
  {
  const field_desc_t *v57; // [sp+130h] [bp-8h]@1
  {
  unsigned int v56; // [sp+12Ch] [bp-Ch]@1
  {
  int v55; // [sp+128h] [bp-10h]@92
  {
  digit_t *ptr; // [sp+124h] [bp-14h]@1
  {
  kpoly_t v53; // [sp+118h] [bp-20h]@3
  {
  kpoly_t v52; // [sp+10Ch] [bp-2Ch]@3
  {
  kpoly_t v51; // [sp+100h] [bp-38h]@3
  {
  unsigned int v50; // [sp+FCh] [bp-3Ch]@1
  {
  kpoly_t v49; // [sp+F0h] [bp-48h]@3
  {
  kpoly_t v48; // [sp+E4h] [bp-54h]@3
  {
  int v47; // [sp+E0h] [bp-58h]@1
  {
  kpoly_t v46; // [sp+D4h] [bp-64h]@3
  {
  kpoly_t v45; // [sp+C8h] [bp-70h]@3
  {
  int v44; // [sp+C4h] [bp-74h]@1
  {
  int v43; // [sp+C0h] [bp-78h]@1
  {
  kpoly_t v42; // [sp+B4h] [bp-84h]@3
  {
  kpoly_t v41; // [sp+A8h] [bp-90h]@3
  {
  kpoly_t v40; // [sp+9Ch] [bp-9Ch]@3
  {
  kpoly_t v39; // [sp+90h] [bp-A8h]@3
  {
  kpoly_t v38; // [sp+84h] [bp-B4h]@3

  v43 = 1;
  v44 = a1->field_50;
  v50 = a5->dword4;
  v47 = a5->dword8;
  v58 = v50 * v47;
  v57 = &a5->kstruc1284;
  v56 = (21 * v50 + 11) * v47;
  ptr = 0;
  ptr = mp_alloc_temp(sizeof(digit_t) * v56);
  if ( !ptr )
  {
    v43 = 0;
  }
  else
  {
    digit_t* v37; // [sp+80h] [bp-B8h]
    v37 = ptr;
    v52.maxlength = v50 + 1;
    v51.maxlength = v50 + 1;
    v39.maxlength = v50 + 1;
    v49.maxlength = v50 + 1;
    v45.maxlength = v50;
    v42.maxlength = v50;
    v40.maxlength = v50;
    v53.maxlength = 4 * v50 + 1;
    v48.maxlength = 3 * v50 + 2;
    v46.maxlength = 3 * v50 + 2;
    v41.maxlength = 2 * v50 + 1;
    v38.maxlength = 2 * v50 + 1;
    v52.coefs = v37;
    v37 += (v50 + 1) * v47;
    v51.coefs = v37;
    v37 += (v50 + 1) * v47;
    v39.coefs = v37;
    v37 += (v50 + 1) * v47;
    v49.coefs = v37;
    v37 += (v50 + 1) * v47;
    v45.coefs = v37;
    v37 += v50 * v47;
    v42.coefs = v37;
    v37 += v50 * v47;
    v40.coefs = v37;
    v37 += v50 * v47;
    v53.coefs = v37;
    v37 += (4 * v50 + 1) * v47;
    v48.coefs = v37;
    v37 += (3 * v50 + 2) * v47;
    v46.coefs = v37;
    v37 += (3 * v50 + 2) * v47;
    v41.coefs = v37;
    v37 += (2 * v50 + 1) * v47;
    v38.coefs = v37;
    v37 += (2 * v50 + 1) * v47;
  }
  if ( v43 && a2->field_50 != v44 )
    v43 = 0;
  v43 = v43 && (a3 == 1 ? KPadd : KPsub)(&a1->field_C, &a2->field_C, &v53, v57);
  v43 = v43 && KPgcd(&a1->field_0, &v53, &v52, &v45, &v42, v57);
  v43 = v43 && KPgcd(&v52, &a2->field_0, &v51, &v40, 0, v57);
  v43 = v43 && KPdiv(&a1->field_0, &v51, &v39, &v53, v57);
  v43 = v43 && KPdiv(&a2->field_0, &v51, &v49, &v48, v57);
  if ( v43 && (v53.degree != (DWORD)-1 || v48.degree != (DWORD)-1) )
    v43 = 0;
  v43 = v43 && KPmul(&a1->field_C, &a1->field_C, &v53, v57);
  v43 = v43 && KPsub(&a5->pvoid363C[v44], &v53, &v53, v57);
  v43 = v43 && KPdiv(&v53, &a1->field_0, &v48, &v46, v57);
  if ( v43 && v46.degree != (DWORD)-1 )
    v43 = 0;
  v43 = v43 && KPmul(&v42, &v48, &v53, v57);
  v43 = v43 && (a3 == 1 ? KPsub : KPadd)(&a1->field_C, &a2->field_C, &v48, v57);
  v43 = v43 && KPmul(&v45, &v48, &v46, v57);
  v43 = v43 && KPsub(&v53, &v46, &v48, v57);
  v43 = v43 && KPdiv(&v48, &v49, 0, &v53, v57);
  v43 = v43 && KPmul(&v40, &v53, &v48, v57);
  v43 = v43 && KPdiv(&v48, &v49, 0, &v53, v57);
  v43 = v43 && KPmul(&v39, &v49, &v41, v57);
  v43 = v43 && KPmul(&v53, &v39, &v38, v57);
  v43 = v43 && KPadd(&a1->field_C, &v38, &v38, v57);
  v55 = 1;
  while ( v55 && v43 )
  {
    v55 = 0;
    if ( v38.degree + 1 > v41.degree )
    {
      v43 = v43 && KPdiv(&v38, &v41, 0, &v53, v57);
      v43 = v43 && KPcopy(&v53, &v38, v57);
    }
    if ( v41.degree > v50 )
    {
      v43 = v43 && KPmul(&v38, &v38, &v53, v57);
      v43 = v43 && KPsub(&v53, &a5->pvoid363C[v44], &v53, v57);
      v43 = v43 && KPdiv(&v53, &v41, &v48, &v46, v57);
      if ( v43 && v46.degree != (DWORD)-1 )
      {
        v43 = 0;
      }
      else if ( v48.degree >= v41.degree )
      {
        v43 = 0;
      }
      if ( v43 )
      {
        v46.degree = (DWORD)-1;
        v43 = v43 && KPsub(&v46, &v38, &v38, v57);
        v43 = v43 && KPcopy(&v48, &v41, v57);
        v55 = 1;
      }
    }
  }
  v43 = v43 && sub_10619F5(a4, a5);
  a4->field_50 = v44;
  if ( v43 )
  {
    digit_t *v37; // [sp+7Ch] [bp-BCh]@139
    v37 = v46.coefs;
    v43 = v43 && Kinvert(&v41.coefs[v47 * v41.degree], v37, v57);
    v43 = v43 && KPmul_scalar(&v41, v37, &a4->field_0, v57);
    v43 = v43 && KPcopy(&v38, &a4->field_C, v57);
  }
  if ( ptr )
    mp_free_temp(ptr);
  return v43;
  }}}}}}}}}}}}}}}}}}}}
}

int sub_1063005(const kpoly_t *a1, const CWPAShortSigKey *a2, int *a3)
{
  DWORD v7; // [sp+10h] [bp-4h]@1
  {
  DWORD v6; // [sp+Ch] [bp-8h]@1
  {
  int v5; // [sp+8h] [bp-Ch]@1
  {
  digit_t b[2]; // [sp+0h] [bp-14h]@2

  v5 = 1;
  v6 = a2->dword8;
  v7 = a1->degree;
  *a3 = 1;
  if ( v7 != (DWORD)-1 )
  {
    from_modular(&a1->coefs[v7 * v6], b, &a2->mp_modulus40);
    *a3 = (~b[0] & 1) != 0 ? 1 : -1;
  }
  return v5;
  }}}
}

int PID_verify(const BYTE *lpData, DWORD cbData, const CWPAShortSigKey *pKey, BYTE *lpOut)
{
  unsigned int i; // [sp+60h] [bp-4h]@15
  {
  const CWPAShortSigKey *v15; // [sp+5Ch] [bp-8h]@1
  {
  int v14; // [sp+58h] [bp-Ch]@5
  {
  DWORD v13; // [sp+54h] [bp-10h]@6
  {
  int v12; // [sp+50h] [bp-14h]@6
  {
  int v11; // [sp+4Ch] [bp-18h]@6
  {
  BYTE v10[24]; // [sp+34h] [bp-30h]@19
  {
  digit_t v9[6]; // [sp+1Ch] [bp-48h]@15
  {
  DWORD v8;

  v15 = pKey;
  v14 = v15 != NULL && v15->dword0 == dword_101A160;
  if ( v14 )
  {
    v11 = v15->dword8;
    v12 = v15->dword4;
    v13 = v12 * v11;
    v14 = v14 && cbData < 4 * v13;
    v14 = v14 && v15->dword10 <= 4 * v13;
    if ( v14 )
    {
      memset(v9, 0, 4 * v13);
      for ( i = 0; i != v15->dword10; ++i )
      {
        v8 = i / RADIX_BYTES;
        v9[v8] |= (digit_t)lpData[i] << (8 * i % RADIX_BITS);
      }
      v14 = v14 && sub_10631F8(v9, cbData, v15, v10);
      if ( v14 )
        memcpy(lpOut, &v10, cbData);
    }
  }
  return v14;
  }}}}}}}}
}

int sub_10631F8(digit_tc a1[], DWORD a2, const CWPAShortSigKey *a3, BYTE *a4)
{
  shortsig00_struc_1 a1a; // [sp+11Ch] [bp-54h]@7
  {
  digit_t a[6]; // [sp+104h] [bp-6Ch]@23
  {
  unsigned int v25; // [sp+100h] [bp-70h]@1
  {
  unsigned int i; // [sp+FCh] [bp-74h]@46
  {
  unsigned int v23; // [sp+F8h] [bp-78h]@1
  {
  int v22; // [sp+F4h] [bp-7Ch]@1
  {
  int a4a; // [sp+F0h] [bp-80h]@1
  {
  shortsig00_struc_1 a3a; // [sp+9Ch] [bp-D4h]@15
  {

  v22 = 1;
  a4a = 0;
  v25 = a3->dword4;
  v23 = a3->dword8;
  v22 = v22 && a2 > 0 && a2 <= v25 * v23 * RADIX_BYTES;
  if ( v25 == 2 )
  {
    kpoly_t v19; // [sp+90h] [bp-E0h]@6
    {
    digit_t v18[6]; // [sp+78h] [bp-F8h]@6

    v19.maxlength = 3;
    v19.coefs = v18;
    v22 = v22 && sub_1064DFC(a1, a3, &a1a, &a4a);
    v22 = v22 && a4a;
    v22 = v22 && sub_1064D6C(&a1a, a3, &a3a);
    v22 = v22 && sub_1064C7D(&a3a.field_0, a3, &v19);
    v22 = v22 && sub_1064941(&v19, a3, a);
    }
  }
  else if ( v25 == 3 )
  {
    kpoly_t v17; // [sp+6Ch] [bp-104h]@28
    {
    digit_t v16[6]; // [sp+54h] [bp-11Ch]@33
    {
    digit_t v15[8]; // [sp+34h] [bp-13Ch]@28

    v17.coefs = v15;
    v17.maxlength = v25 + 1;
    v22 = 0;
    v22 = v22 && sub_1064D6C(&a1a, a3, &a3a);
    v22 = v22 && sub_1064CEF(&a3a, a3, &v17);
    v22 = v22 && sub_106370F(&v17, a3, v16);
    v22 = v22 && sub_106356D(v16, a3, a);
    }}
  }
  else
  {
    v22 = 0;
  }
  v22 = v22 && mp_significant_bit_count(a, v25 * v23) <= 8 * a2;
  for ( i = 0; i != a2 && v22; ++i )
  {
    DWORD_PTR v20 = a[i / RADIX_BYTES] >> (8 * (i % RADIX_BYTES));
    a4[i] = (BYTE)v20;
  }
  return v22;
  }}}}}}}}
}

int sub_106356D(digit_tc a1[], const CWPAShortSigKey *a2, digit_t a3[])
{
  unsigned int *a; // [sp+64h] [bp-4h]@9
  {
  unsigned int v11; // [sp+60h] [bp-8h]@4
  {
  digit_t c[6]; // [sp+48h] [bp-20h]@9
  {
  digit_t v9[10]; // [sp+20h] [bp-48h]@3
  {
  unsigned int i; // [sp+1Ch] [bp-4Ch]@1
  {
  unsigned int lnga; // [sp+18h] [bp-50h]@1
  {
  int v0;
  {
  digit_t *b; // ST24_4@9
  {
  digit_t *v4; // [sp+0Ch] [bp-5Ch]

  v0 = 1;
  lnga = a2->dword8;
  for ( i = 0; i != 5; ++i )
    memcpy(&v9[i * lnga], &a1[(i % 3) * lnga], sizeof(digit_t) * lnga);
  v11 = 0;
  for ( i = 0; i <= 2; ++i )
  {
    int v1 = compare_same(&v9[v11], &v9[i * lnga], 3 * lnga); // [sp+8] [bp-60h]
    if ( v1 < 0 )
      v11 = i * lnga;
  }
  b = &v9[v11];
  v4 = b + lnga;
  a = (unsigned int*)&v4[lnga];
  multiply((digit_tc*)a, lnga, (digit_tc*)a, lnga, c);
  multiply((digit_tc*)a, lnga, c, (DWORDC)(2 * lnga), a3);
  sub_diff((digit_tc*)a3, 3 * lnga, (digit_tc*)a, lnga, a3);
  divide_immediate(a3, 3u, 0, a3, lnga);
  multiply(v4, lnga, (digit_tc*)a, lnga, c);
  add_diff(c, 2 * lnga, b, lnga, c);
  add_diff(a3, 3 * lnga, c, 2 * lnga, a3);
  return v0;
  }}}}}}}}
}

int sub_106370F(const kpoly_t *a1, const CWPAShortSigKey *a2, digit_t a3[])
{
  unsigned int lnga; // [sp+150h] [bp-4h]@1
  {
  unsigned int v40; // [sp+14Ch] [bp-8h]@1
  {
  const field_desc_t *a6; // [sp+148h] [bp-Ch]@1
  {
  digit_t b[24]; // [sp+E8h] [bp-6Ch]@7
  {
  unsigned int v37; // [sp+E4h] [bp-70h]@1
  {
  digit_t v36[24]; // [sp+84h] [bp-D0h]@11
  {
  unsigned int v35; // [sp+80h] [bp-D4h]@1
  {
  int v34; // [sp+7Ch] [bp-D8h]@1
  {
  int v33; // [sp+78h] [bp-DCh]@1
  {
  int v32; // [sp+74h] [bp-E0h]@1
  {
  int v31; // [sp+70h] [bp-E4h]@1

  v37 = a2->dword4;
  v35 = a2->dword8;
  lnga = v37 * v35;
  a6 = &a2->kstruc1284;
  v40 = mp_significant_bit_count((digit_tc*)a2->pvoid20, lnga);
  v31 = 100;
  v34 = 1;
  v32 = 0;
  for (v33 = 0; v34 && !v32; v33++)
  {
    unsigned int a2a; // [sp+6Ch] [bp-E8h]@14
    {
    unsigned int v29; // [sp+68h] [bp-ECh]@31
    {
    unsigned int v28; // [sp+64h] [bp-F0h]@31
    {
    unsigned int i; // [sp+60h] [bp-F4h]@40
    {
    unsigned int j; // [sp+5Ch] [bp-F8h]@108

    if ( v33 == v31 )
      v34 = 0;
    v34 = v34 && Krandom(b, v37 * v37, a6);
    v34 = v34 && Kcopy(b, v36, v37 * v37, a6);
    for ( a2a = v40 - 2; a2a != (DWORD)-1; --a2a )
    {
      v34 = v34 && sub_10644AF(v36, v36, v36, a1, &a2->dword35E8, a6);
      if ( mp_getbit((digit_tc*)a2->pvoid20, a2a) )
      {
        v34 = v34 && sub_10644AF(v36, b, v36, a1, &a2->dword35E8, a6);
      }
    }
    v34 = v34 && Ksub(v36, a6->one, v36, a6);
    v28 = v37;
    v29 = v37 + 1;
    if ( v34 )
    {
      v34 = v34 && sub_1064134(v36, &v28, &a2->dword35E8, a6);
      v34 = v34 && Kclear(b, v29 * v37, a6);
      for ( i = 0; i != v29; ++i )
      {
        v34 = v34 && Kcopy(&a1->coefs[i * v35], &b[i * lnga], 1, a6);
      }
    }
    while ( v34 && v29 && v28 )
    {
      digit_t *v25; // [sp+58h] [bp-FCh]@54
      if ( compare_diff(a6->one, v35, &b[(v29 - 1) * lnga], lnga)
        || compare_diff(a6->one, v35, &v36[(v28 - 1) * lnga], lnga) )
      {
        v34 = 0;
      }
      if ( v29 >= v28 )
      {
        v25 = &b[(v29 - v28) * lnga];
        for ( i = 0; i != v28; ++i )
        {
          v34 = v34 && sub_106441B(&v25[i * lnga], &v36[i * lnga], &v25[i * lnga], &a2->dword35E8, a6);
        }
        v34 = v34 && sub_1064134(b, &v29, &a2->dword35E8, a6);
      }
      else
      {
        digit_t *v24; // [sp+54h] [bp-100h]@66

        v24 = &v36[(v28 - v29) * lnga];
        for ( i = 0; i != v29; ++i )
        {
          v34 = v34 && sub_106441B(&v24[i * lnga], &b[i * lnga], &v24[i * lnga], &a2->dword35E8, a6);
        }
        v34 = v34 && sub_1064134(v36, &v28, &a2->dword35E8, a6);
      }
    }
    if ( v34 )
    {
      digit_t *v23; // [sp+50h] [bp-104h]@80

      v23 = 0;
      if ( v29 )
      {
        v34 = v34 && Kcopy(b, v36, v29 * lnga, a6);
        v28 = v29;
      }
      if ( v28 == 2 )
      {
        v32 = 1;
        v23 = v36;
      }
      else if ( v28 == v37 )
      {
        v32 = 1;
        v23 = &v36[(v28 - 2) * lnga];
        for ( i = 0; i != v37; ++i )
        {
          v34 = v34 && Knegate(&v23[i * v35], &v23[i * v35], a6);
        }
        v34 = v34 && Kadd(v23, &a1->coefs[(v37 - 1) * v35], v23, a6);
      }
      if ( v32 )
      {
        v34 = v34 && Kclear(a3, v37, a6);
        for ( i = 0; i != v37; ++i )
        {
          for ( j = 0; j != v37; ++j )
          {
            _DWORD v22[2]; // [sp+48h] [bp-10Ch]@111

            v34 = v34 && Kmul((digit_t*)a2->pvoid3618[i][j], (digit_tc*)&v23[j * v35], (digit_t*)v22, a6);
            v34 = v34 && Kadd((digit_tc*)&a3[i * v35], (digit_t*)v22, &a3[i * v35], a6);
          }
          from_modular(
			&a3[i * v35], 
			&a3[i * v35], 
			&a2->mp_modulus40);
        }
      }
    }
    }}}}
  }
  return v34;
  }}}}}}}}}}
}

int sub_1064134(digit_t a1[], DWORD* a2, const kpoly_t* a3, const field_desc_t* a4)
{
  DWORD v14; // [sp+38h] [bp-4h]@1
  {
  unsigned int v13; // [sp+34h] [bp-8h]@1
  {
  unsigned int v12; // [sp+30h] [bp-Ch]@1
  {
  int v11; // [sp+2Ch] [bp-10h]@1
  {
  unsigned int v10; // [sp+28h] [bp-14h]@1

  v14 = a3->degree;
  v12 = a4->elng;
  v10 = v14 * v12;
  v13 = *a2;
  v11 = 1;
  v11 = v11 && v12 <= 2 && v14 <= 3;
  v13 = (significant_digit_count(a1, v13 * v10) + v10 - 1) / v10;
  if ( v11 && v13 )
  {
    digit_t v9[6]; // [sp+10h] [bp-2Ch]@8
    {
    unsigned int i; // [sp+Ch] [bp-30h]@11
    v11 = v11 && sub_106427E(&a1[(v13 - 1) * v10], v9, a3, a4);
    for ( i = 0; i != v13; ++i )
    {
      v11 = v11 && sub_1061807(&a1[i * v10], v9, &a1[i * v10], a3, a4);
    }
    }
  }
  *a2 = v13;
  return v11;
  }}}}
}

int sub_106427E(digit_tc a1[], digit_t a2[], const kpoly_t* a3, const field_desc_t* a4)
{
  DWORD v18; // [sp+84h] [bp-4h]@1
  {
  kpoly_t v17; // [sp+78h] [bp-10h]@5
  {
  unsigned int v16; // [sp+74h] [bp-14h]@1
  {
  int v15; // [sp+70h] [bp-18h]@1
  {
  kpoly_t v14; // [sp+64h] [bp-24h]@9
  {
  digit_t v13[8]; // [sp+44h] [bp-44h]@9
  {
  kpoly_t v12; // [sp+38h] [bp-50h]@9
  {
  digit_t v11[8]; // [sp+18h] [bp-70h]@9

  v16 = a4->elng;
  v18 = a3->degree;
  v15 = 1;
  v15 = v15 && v18 <= 3 && v16 <= 2;
  v17.coefs = (digit_t*)a1;
  v17.degree = v18 - 1;
  v17.maxlength = v18;
  v15 = v15 && KPcheck_degree(&v17, a4);
  v14.maxlength = v18 + 1;
  v14.coefs = v13;
  v12.maxlength = v18 + 1;
  v12.coefs = v11;
  v15 = v15 && KPgcd(&v17, a3, &v14, &v12, 0, a4);
  if ( v15 && v14.degree != 0 )
    v15 = 0;
  v15 = v15 && v14.degree == 0;
  v15 = v15 && Kclear(a2, v18, a4);
  v15 = v15 && Kcopy(v12.coefs, a2, v12.degree + 1, a4);
  return v15;
  }}}}}}}
}

int sub_106441B(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t* a4, const field_desc_t* a5)
{
  DWORD v10; // [sp+14h] [bp-4h]@1
  {
  DWORD i; // [sp+10h] [bp-8h]@1
  {
  DWORD v8; // [sp+Ch] [bp-Ch]@1
  {
  int v7; // [sp+8h] [bp-10h]@1

  v10 = a4->degree;
  v8 = a5->elng;
  v7 = 1;
  for ( i = 0; i != v10; ++i )
  {
    DWORD v6 = i * v8; // [sp+4h] [bp-14h]
    v7 = v7 && Ksub(&a1[v6], &a2[v6], &a3[v6], a5);
  }
  return v7;
  }}}
}

int sub_10644AF(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t *a4, const kpoly_t *a5, const field_desc_t *a6)
{
  digit_t v25[6]; // [sp+B8h] [bp-18h]@18
  {
  digit_t v24[30]; // [sp+40h] [bp-90h]@10
  {
  int v23; // [sp+3Ch] [bp-94h]@1
  {
  unsigned int v22; // [sp+38h] [bp-98h]@1
  {
  unsigned int v21; // [sp+34h] [bp-9Ch]@1
  {
  unsigned int i; // [sp+30h] [bp-A0h]@13
  {
  unsigned int v18; // [sp+2Ch] [bp-A4h]@1
  {
  unsigned int j; // [sp+28h] [bp-A8h]@15
  {
  int v15; // [sp+24h] [bp-ACh]@13

  v22 = a4->degree;
  v21 = a5->degree;
  v18 = a6->elng;
  v23 = v18 * v21;
  v15 = 1;
  v15 = v22 <= 3 && v21 <= 3;
  v15 = v15 && v18 <= 2;
  v15 = v15 && Kclear(v24, (2 * v22 - 1) * v23, a6);
  for ( i = 0; i != v22; ++i )
  {
    for ( j = 0; j != v22; ++j )
    {
      v15 = v15 && sub_1061807(&a1[i * v23], &a2[j * v23], v25, a5, a6);
      v15 = v15 && sub_1061773(&v24[(i + j) * v23], v25, &v24[(i + j) * v23], a5, a6);
    }
  }
  for ( i = 2 * v22 - 2; i >= v22; --i )
  {
    digit_t* v14 = &v24[i * v23]; // [sp+20h] [bp-B0h]
    for ( j = 0; j != v22; ++j )
    {
      v15 = v15 && sub_10648B3(v14, &a4->coefs[j * v18], v25, a5, a6);
      v15 = v15 && sub_106441B(&v24[(i - v22 + j) * v23], v25, &v24[(i - v22 + j) * v23], a5, a6);
    }
  }
  v15 = v15 && Kcopy(v24, a3, v22 * v21, a6);
  return v15;
  }}}}}}}}
}

int sub_10648B3(digit_tc a1[], digit_tc a2[], digit_t a3[], const kpoly_t* a4, const field_desc_t* a5)
{
  DWORD v10; // [sp+14h] [bp-4h]@1
  {
  DWORD i; // [sp+10h] [bp-8h]@1
  {
  DWORD v8; // [sp+Ch] [bp-Ch]@1
  {
  int v7; // [sp+8h] [bp-10h]@1

  v10 = a4->degree;
  v8 = a5->elng;
  v7 = 1;
  for ( i = 0; i != v10; ++i )
  {
    DWORD v6 = i * v8; // [sp+4h] [bp-14h]
    v7 = v7 && Kmul(&a1[v6], a2, &a3[v6], a5);
  }
  return v7;
  }}}
}

int sub_1064941(const kpoly_t *a1, const CWPAShortSigKey *a2, digit_t a3[])
{
  digit_t *v20; // [sp+5Ch] [bp-4h]@1
  {
  digit_t b[2]; // [sp+54h] [bp-Ch]@6
  {
  const field_desc_t *v18; // [sp+50h] [bp-10h]@1
  {
  unsigned int lng; // [sp+4Ch] [bp-14h]@1
  {
  int v16; // [sp+48h] [bp-18h]@1
  {
  digit_t c[2]; // [sp+40h] [bp-20h]@7
  {
  const mp_modulus_t *modulo; // [sp+3Ch] [bp-24h]@1
  {
  digit_t a[3]; // [sp+30h] [bp-30h]@24

  v16 = 1;
  lng = a2->dword8;
  modulo = &a2->mp_modulus40;
  v18 = &a2->kstruc1284;
  v20 = a1->coefs;
  v16 = v16 && a1->degree == 2;
  v16 = v16 && Kequal(v18->one, &v20[2 * lng], v18);
  if ( v16 )
  {
    mod_shift(&v20[lng], -1, b, modulo);
    v16 = v16 && Kmul(b, b, c, v18);
    v16 = v16 && Ksub(c, v20, c, v18);
  }
  v16 = v16 && significant_digit_count(c, lng);
  v16 = v16 && Kmul(c, (digit_tc*)a2->dword3C, c, v18);
  if ( v16 && !Ksqrt(c, a, v18) )
    v16 = 0;
  if ( v16 )
  {
    from_modular(b, b, modulo);
    from_modular(a, a, modulo);
    v16 = v16 && !sub_same((digit_tc*)a2->punsigned1C, a, c, lng);
    if ( compare_same(a, c, lng) > 0 )
      memcpy(a, c, sizeof(digit_t) * lng);
    v16 = v16 && !sub_immediate(a, 1, a, lng);
    multiply(a, lng, (digit_tc*)a2->punsigned1C, lng, a3);
    v16 = v16 && !add_diff(a3, 2 * lng, b, lng, a3);
    v16 = v16 && compare_same(
		a3,
		(digit_tc*)a2->punsigned30,
		2 * lng
	) < 0;
  }
  return v16;
  }}}}}}}
}

int sub_1064C7D(const kpoly_t *a1, const CWPAShortSigKey *a2, kpoly_t *a3)
{
  int v1 = 1;
  v1 = v1 && a1->degree == 2;
  v1 = v1 && KPcopy(a1, a3, &a2->kstruc1284);
  return v1;
}

int sub_1064CEF(const shortsig00_struc_1 *a1, const CWPAShortSigKey *a2, kpoly_t *a3)
{
  DWORD v2;
  {
  int v1 = 1;
  v2 = a2->dword4;
  v1 = v1 && a1->field_0.degree == v2;
  v1 = v1 && KPcopy(&a1->field_0, a3, &a2->kstruc1284);
  return v1;
  }
}

BOOL __stdcall sub_1064D6C(const shortsig00_struc_1 *a1, const CWPAShortSigKey *a2, shortsig00_struc_1 *a3)
{
  int v8; // [sp+14h] [bp-4h]@1
  {
  int v3; // ST24_4@1
  {
  DWORD v7; // [sp+Ch] [bp-Ch]@1
  {
  int v6; // [sp+4h] [bp-14h]@3

  v6 = 1;
  v8 = a2->dword14;
  v3 = a2->dwordC;
  v7 = a1->field_50;
  v6 = v6 && (v7 == 0 || v7 == 1);
  v6 = v6 && sub_10621B2(
	a1,
	(digit_tc*)&v8,
	1,
	a2,
	a3);
  return v6;
  }}}
}

int sub_1064DFC(digit_tc a1[], const CWPAShortSigKey *a2, shortsig00_struc_1 *a3, int* a4)
{
  const field_desc_t *v39; // [sp+10Ch] [bp-4h]@1
  {
  kpoly_t v38; // [sp+100h] [bp-10h]@1
  {
  digit_t quot[2][3]; // [sp+E8h] [bp-28h]@13
  {
  digit_t denom[2]; // [sp+E0h] [bp-30h]@13
  {
  digit_t v34[6]; // [sp+C8h] [bp-48h]@1
  {
  unsigned int v33; // [sp+C4h] [bp-4Ch]@1
  {
  int i; // [sp+C0h] [bp-50h]@14
  {
  unsigned int lden; // [sp+BCh] [bp-54h]@1
  {
  int a3a; // [sp+B8h] [bp-58h]@1
  {
  int v29; // [sp+B4h] [bp-5Ch]@1

  v29 = 1;
  v33 = a2->dword4;
  lden = a2->dword8;
  v39 = &a2->kstruc1284;
  a3a = 0;
  *a4 = 1;
  v38.maxlength = v33;
  v38.coefs = v34;
  v29 = v29 && v33 == 2;
  v29 = v29 && sub_10619F5(
	a3,
	a2);
  a3->field_50 = a3a;
  v29 = v29 && sub_106241C(a3, a2, a3a);
  add_immediate((digit_tc*)a2->punsigned1C, 1u, denom, lden);
  divide(a1, 2 * lden, denom, lden, 0, quot[0], quot[1]);
  if ( compare_same(quot[0], (digit_tc*)a2->punsigned1C, lden) <= 0 )
  {
    int v28; // [sp+B0h] [bp-60h]@14
    v28 = compare_same(quot[1], quot[0], lden) >= 0;
    for ( i = 0; v29 && i != 2; ++i )
    {
      if ( compare_same(quot[i], (digit_tc*)a2->punsigned1C, lden) )
      {
        int v26; // [sp+58h] [bp-B8h]@45
        shortsig00_struc_1 b; // [sp+5Ch] [bp-B4h]@19

        v29 = v29 && sub_10619F5(&b, a2);
        b.field_50 = a3a;
        v29 = v29 && KPmonomial(v39->one, 1, &b.field_0, v39);
        v29 = v29 && to_modular(quot[i], lden, b.field_0.coefs, &a2->mp_modulus40);
        v29 = v29 && KPdiv(&a2->pvoid363C[a3a], &b.field_0, 0, &v38, v39);
        if ( v38.degree == (DWORD)-1 )
        {
          b.field_C.degree = (DWORD)-1;
        }
        else
        {
          v29 = v29 && v38.degree == 0;
          b.field_C.degree = 0;
          if ( !v29 )
          {
          }
          else
          {
            if ( !Ksqrt(v38.coefs, b.field_C.coefs, v39) )
              *a4 = 0;
          }
        }
        if ( v29 && *a4 )
        {
          v26 = 1;
          v29 = v29 && sub_1063005(&b.field_C, a2, &v26);
          if ( i == 1 && !v28 )
            v26 = -v26;
          v29 = v29 && sub_1062486(a3, &b, v26, a3, a2);
        }
      }
    }
  }
  else
  {
    digit_t v25[2]; // [sp+50h] [bp-C0h]@79
    {
    digit_t *v24; // [sp+4Ch] [bp-C4h]@59

    v24 = a3->field_0.coefs;
    for ( i = 0; i != 2; ++i )
    {
      v29 = v29 && to_modular(quot[i], lden, quot[i], &a2->mp_modulus40);
    }
    v29 = v29 && KPmonomial(v39->one, 2, &a3->field_0, v39);
    v29 = v29 && Kadd(quot[1], quot[1], &v24[lden], v39);
    v29 = v29 && Kmul(quot[1], quot[1], v24, v39);
    v29 = v29 && Kmul(quot[0], quot[0], v25, v39);
    v29 = v29 && Kmul(v25, (digit_tc*)a2->dword38, v25, v39);
    v29 = v29 && Ksub(v24, v25, v24, v39);
    v29 = v29 && KPdiv(&a2->pvoid363C[a3a], &a3->field_0, 0, &v38, v39);
    v29 = v29 && sub_1061A54(&v38, &a3->field_0, &a3->field_C, a2, a4);
    }
  }
  return v29;
  }}}}}}}}}
}
