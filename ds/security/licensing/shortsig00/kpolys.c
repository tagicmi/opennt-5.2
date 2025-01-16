#include <crypto/bignum.h>
#include "field.h"
#include "kpolys.h"

typedef unsigned _DWORD;
typedef unsigned char _BYTE;

int KPadd(const kpoly_t *arg_0, const kpoly_t *arg_4, kpoly_t *arg_8, const field_desc_t *arg_C)
{
  DWORD v9; // [sp+30h] [bp-4h]@5
  {
  DWORD v16; // [sp+2Ch] [bp-8h]@1
  {
  DWORD v15; // [sp+28h] [bp-Ch]@1
  {
  DWORD v14; // [sp+24h] [bp-10h]@7
  {
  int v12; // [sp+20h] [bp-14h]@7
  {
  DWORD v10; // [sp+1Ch] [bp-18h]@2
  {
  DWORD i; // [sp+18h] [bp-1Ch]@9

  v16 = arg_0->degree + 1;
  v15 = arg_4->degree + 1;
  v10 = ( v16 > v15 ) ? v15 : v16;
  v9 = ( v16 > v15 ) ? v16 : v15;
  v14 = arg_C->elng;
  v12 = 1;
  if ( arg_8->maxlength < v9 )
  {
    mp_errno = 23;
    v12 = 0;
  }
  else
  {
    for ( i = 0; i != v10 * v14; i += v14 )
    {
      v12 = v12 && Kadd(&arg_0->coefs[i], &arg_4->coefs[i], &arg_8->coefs[i], arg_C);
    }
    arg_8->degree = v9 - 1;
    if ( v16 > v15 )
    {
      v12 = v12 && Kcopy(&arg_0->coefs[i], &arg_8->coefs[i], v16 - v15, arg_C);
    }
    else if ( v15 > v16 )
    {
      v12 = v12 && Kcopy(&arg_4->coefs[i], &arg_8->coefs[i], v15 - v16, arg_C);
    }
    else
    {
      v12 = v12 && KPcheck_degree(arg_8, arg_C);
    }
  }
  return v12;
  }}}}}}
}

int KPcheck_degree(kpoly_t *arg_0, const field_desc_t *arg_4)
{
  DWORD v4; // [sp+4h] [bp-4h]@1
  {
  DWORD v3; // [sp+0h] [bp-8h]@1

  v4 = arg_0->degree;
  v3 = arg_4->elng;
  while ( v4 != (DWORD)-1 && Kiszero(&arg_0->coefs[v4 * v3], arg_4) )
    --v4;
  arg_0->degree = v4;
  return 1;
  }
}

int KPcopy(const kpoly_t *arg_0, kpoly_t *arg_4, const field_desc_t *arg_8)
{
  DWORD v7; // [sp+0Ch] [bp-4h]
  {
  DWORD v6; // [sp+8h] [bp-8h]@1
  {
  int v5; // [sp+4h] [bp-Ch]@2

  v6 = arg_0->degree;
  v7 = v6 + 1;
  v5 = 1;
  arg_4->degree = v6;
  if ( arg_4->maxlength < v7 )
  {
    mp_errno = 23;
    v5 = 0;
  }
  else
  {
    v5 = v6 == (DWORD)-1 || Kcopy(arg_0->coefs, arg_4->coefs, v7, arg_8);
  }
  return v5;
  }}
}

int KPdiv(const kpoly_t *arg_0, const kpoly_t *arg_4, kpoly_t *arg_8, kpoly_t *arg_C, const field_desc_t *arg_10)
{
  DWORD v26; // [sp+250h] [bp-4h]@1
  {
  DWORD v25; // [sp+24Ch] [bp-8h]@1
  {
  int v24; // [sp+248h] [bp-Ch]@1
  {
  int v23; // [sp+244h] [bp-10h]@1
  {
  DWORD v22; // [sp+240h] [bp-14h]@1

  v24 = arg_10->elng;
  v26 = arg_0->degree;
  v25 = arg_4->degree;
  v22 = v26 - v25;
  v23 = 1;
  if ( v25 == (DWORD)-1 )
  {
    v23 = 0;
    mp_errno = 24;
  }
  else if ( v26 == (DWORD)-1 || v26 < v25 )
  {
    v22 = (DWORD)-1;
    v23 = v23 && KPcopy(arg_0, arg_C, arg_10);
  }
  else if ( arg_C->maxlength < v25 )
  {
    mp_errno = 23;
    v23 = 0;
  }
  else if ( arg_8 && arg_8->maxlength <= v22 )
  {
    mp_errno = 23;
    v23 = 0;
  }
  else
  {
    DWORD i; // [sp+23Ch] [bp-18h]@25
    {
    digit_t v20[64]; // [sp+13Ch] [bp-118h]@17
    {
    int v19; // [sp+138h] [bp-11Ch]@15

    v19 = Kequal(&arg_4->coefs[v25 * v24], arg_10->one, arg_10);
    if ( !v19 )
    {
      v23 = v23 && Kinvert(&arg_4->coefs[v25 * v24], v20, arg_10);
    }
    v23 = v23 && Kcopy(&arg_0->coefs[(v22 + 1) * v24], arg_C->coefs, v25, arg_10);
    for ( i = v22; i != (DWORD)-1; --i )
    {
      digit_t v18[64]; // [sp+38h] [bp-21Ch]@28
      {
      digit_t *v17; // [sp+34h] [bp-220h]@30
      {
      digit_t *v12; // [sp+30h] [bp-224h]@28
      {
      const digit_t *v11; // [sp+2Ch] [bp-228h]@31
      {
      int j; // [sp+28h] [bp-22Ch]@45

      v12 = arg_8 == NULL ? v18 : &arg_8->coefs[i * v24];
      v17 = &arg_0->coefs[i * v24];
      v11 = v25 == 0 ? v17 : &arg_C->coefs[(v25 - 1) * v24];
      if ( v19 )
      {
        v23 = v23 && Kcopy(v11, v12, 1, arg_10);
      }
      else
      {
        v23 = v23 && Kmul(v11, v20, v12, arg_10);
      }
      if ( v25 )
      {
        for ( j = (v25 - 1) * v24; j; j -= v24 )
        {
          v23 = v23 && Kmulsubfrom(&arg_4->coefs[j], v12, &arg_C->coefs[j - v24], &arg_C->coefs[j], arg_10);
        }
        v23 = v23 && Kmulsubfrom(arg_4->coefs, v12, v17, arg_C->coefs, arg_10);
      }
      }}}}
    }
    arg_C->degree = v25 - 1;
    v23 = v23 && KPcheck_degree(arg_C, arg_10);
    }}
  }
  if ( arg_8 )
    arg_8->degree = v22;
  return v23;
  }}}}
}

int KPexpon(const kpoly_t* a1, digit_tc a2[], DWORDC a3, kpoly_t* a4, const kpoly_t* a5, const field_desc_t* a6) {
  DWORD v32; // [sp+70h] [bp-4h]@1
  {
  int v31 = 1; // [sp+6Ch] [bp-8h]@1

  v32 = a5->degree;
  {
  int v30; // [sp+68h] [bp-Ch]@1
  v30 = mp_significant_bit_count(a2, a3);
  if ( a4->maxlength < v32 ) {
    mp_errno = 23;
  } else if ( !v32 ) {
    a4->degree = (DWORD)-1;
  } else if ( !v30 ) {
    a4->degree = 0;
    v31 = v31 && Kcopy(a6->one, a4->coefs, 1, a6);
  } else {
    unsigned int v29; // [sp+64h] [bp-10h]@11
    {
    digit_t* v28; // [sp+60h] [bp-14h]@11
    {
    kpoly_t v26; // [sp+54h] [bp-20h]@13
    {
    kpoly_t v24; // [sp+48h] [bp-2Ch]@13
    v29 = v32 * a6->elng;
    v28 = mp_alloc_temp(sizeof(digit_t) * (4 * v29));
    if ( !v28 ) {
      v31 = 0;
    } else {
      kpoly_t v22;
      {
      signed int v21; // [sp+38h] [bp-3Ch]@19
      v24.coefs = v28;
      v26.coefs = v28 + v29;
      v22.coefs = v28 + (v29 * 2);
      v24.maxlength = v32;
      v26.maxlength = v32;
      v22.maxlength = 2 * v32;
      v31 = v31 && KPdiv(a1, a5, 0, &v24, a6);
      if ( v30 == 1 )
      {
        v31 = v31 & KPcopy(&v24, a4, a6);
        }
        else
        {
          int v20; // [sp+34h] [bp-40h]@19
          v21 = mp_getbit(a2, v30 - 2) != 0;
          v20 = 0;
          v31 = v31 && KPmul(&v24, &v24, &v22, a6) && KPdiv(&v22, a5, 0, &v26, a6);
          if ( v21 )
          {
            v31 = v31 && KPmul(&v24, &v26, &v22, a6) && KPdiv(&v22, a5, 0, &v26, a6);
          }
          v31 = v31 && KPcopy(&v26, a4, a6);
          v30 -= 2;
          while ( v30 )
          {
            v20 = (int)mp_getbit(
				        a2,
				        --v30
				        ) + 2 * v20;
            switch ( v20 & 3 )
            {
              case 0:
              case 1:
                v31 = v31 && KPmul(a4, a4, &v22, a6) && KPdiv(&v22, a5, 0, a4, a6);
                break;
              case 2:
                v31 = v31 && KPmul(a4, &v24, &v22, a6) && KPdiv(&v22, a5, 0, a4, a6);
                v31 = v31 && KPmul(a4, a4, &v22, a6) && KPdiv(&v22, a5, 0, a4, a6);
                v20 = 0;
                break;
              case 3:
                if ( !v21 )
                {
                  v21 = 1;
                  v31 = v31 && KPmul(&v24, &v26, &v22, a6) && KPdiv(&v22, a5, 0, &v26, a6);
                }
                v31 = v31 && KPmul(a4, a4, &v22, a6) && KPdiv(&v22, a5, 0, a4, a6);
                v31 = v31 && KPmul(a4, &v26, &v22, a6) && KPdiv(&v22, a5, 0, a4, a6);
                v20 = 0;
                break;
            }
          }
          if ( v20 )
          {
            v31 = v31 && KPmul(a4, &v24, &v22, a6) && KPdiv(&v22, a5, 0, a4, a6);
          }
        }
        mp_free_temp(v28);
      }}
    }
    }}}
  }
  return v31;
  }
}

int KPgcd(const kpoly_t *arg_0, const kpoly_t *arg_4, kpoly_t *arg_8, kpoly_t *arg_C, kpoly_t *arg_10, const field_desc_t *arg_14)
{
  DWORD v66; // [sp+234h] [bp-4h]@5
  {
  int v65; // [sp+230h] [bp-8h]@5
  {
  DWORD v64; // [sp+22Ch] [bp-Ch]@5
  {
  int v63; // [sp+228h] [bp-10h]@5
  {
  int v62; // [sp+224h] [bp-14h]@5
  {
  int v61; // [sp+220h] [bp-18h]@35
  {
  int v60; // [sp+21Ch] [bp-1Ch]@35
  {
  digit_t *ptr; // [sp+218h] [bp-20h]@35
  {
  kpoly_t v55[3]; // [sp+1F4h] [bp-44h]@37
  {
  int v54; // [sp+1F0h] [bp-48h]@37
  {
  int v53; // [sp+1ECh] [bp-4Ch]@37
  {
  int v52; // [sp+1E8h] [bp-50h]@54
  {
  int v51; // [sp+1E4h] [bp-54h]@64
  {
  digit_t *v50; // [sp+1E0h] [bp-58h]@64
  {
  int v49; // [sp+1DCh] [bp-5Ch]@64
  {
  kpoly_t v48; // [sp+1D0h] [bp-68h]@66
  {
  kpoly_t v46[2]; // [sp+1B8h] [bp-80h]@66
  {
  kpoly_t mulab[2][2]; // [sp+17Ch] [bp-BCh]@66
  {
  kpoly_t v39;
  {
  int v38; // [sp+178h] [bp-C0h]@82
  {
  int i; // [sp+174h] [bp-C4h]@82
  {
  unsigned int j; // [sp+170h] [bp-C8h]@93
  {
  DWORD v35; // [sp+16Ch] [bp-CCh]@122

  v63 = arg_C || arg_10;
  v66 = arg_0->degree;
  v64 = arg_4->degree;
  v62 = 1;
  v65 = arg_14->elng;
  if ( v66 == (DWORD)-1 )
  {
    v62 = v62 && KPcopy(arg_4, arg_8, arg_14);
    if ( v63 )
    {
      arg_C->degree = (DWORD)-1;
      if ( v64 == (DWORD)-1 )
      {
        arg_10->degree = (DWORD)-1;
      }
      else
      {
        v62 = v62 && KPmonomial(arg_14->one, 0, arg_10, arg_14);
      }
    }
  }
  else if ( v64 == (DWORD)-1 )
  {
    v62 = v62 && KPcopy(arg_0, arg_8, arg_14);
    if ( v63 )
    {
      arg_10->degree = (DWORD)-1;
      v62 = v62 && KPmonomial(arg_14->one, 0, arg_C, arg_14);
    }
  }
  else if ( v63 == 0 )
  {
    v60 = ( v66 > v64 ) ? v64 : v66;
    v61 = (v60 + 1) * v65;
    ptr = (digit_t *)mp_alloc_temp(sizeof(digit_t) * (3 * v61));
    if ( !ptr )
    {
      v62 = 0;
    }
    else
    {
      v54 = 0;
      v53 = 1;
      v55[0].coefs = ptr;
      v55[1].coefs = &ptr[v61];
      v55[2].coefs = &ptr[2 * v61];
      v55[0].maxlength = v60 + 1;
      v55[1].maxlength = v60 + 1;
      v55[2].maxlength = v60 + 1;
      v62 = v62 && KPcopy(v66 < v64 ? arg_0 : arg_4, &v55[0], arg_14);
      v62 = v62 && KPdiv(v66 < v64 ? arg_4 : arg_0, &v55[0], 0, &v55[1], arg_14);
      while ( v62 && v55[v53].degree != (DWORD)-1 )
      {
        v52 = 3 - v54 - v53;
        v62 = KPdiv(&v55[v54], &v55[v53], 0, &v55[v52], arg_14);
        v54 = v53;
        v53 = v52;
      }
      v62 = v62 && KPcopy(&v55[v54], arg_8, arg_14);
      mp_free_temp(ptr);
    }
  }
  else
  {
    v49 = ( v66 > v64 ) ? v66 : v64;
    v51 = (v49 + 1) * v65;
    v50 = mp_alloc_temp(sizeof(digit_t) * (8 * v51));
    if ( !v50 )
    {
      v62 = 0;
    }
    else
    {
      v39.coefs = v50;
      v48.coefs = &v50[v51];
      v46[0].coefs = &v50[2 * v51];
      v46[1].coefs = &v50[3 * v51];
      mulab[0][0].coefs = &v50[4 * v51];
      mulab[0][1].coefs = &v50[5 * v51];
      mulab[1][0].coefs = &v50[6 * v51];
      mulab[1][1].coefs = &v50[7 * v51];
      v39.maxlength = v49 + 1;
      v48.maxlength = v49 + 1;
      v46[0].maxlength = v49 + 1;
      v46[1].maxlength = v49 + 1;
      mulab[0][0].maxlength = v49 + 1;
      mulab[0][1].maxlength = v49 + 1;
      mulab[1][0].maxlength = v49 + 1;
      mulab[1][1].maxlength = v49 + 1;
      v62 = v62 && KPmonomial(arg_14->one, 0, &mulab[0][0], arg_14);
      mulab[0][1].degree = (DWORD)-1;
      mulab[1][0].degree = (DWORD)-1;
      v62 = v62 && KPmonomial(arg_14->one, 0, &mulab[1][1], arg_14);
      v62 = v62 && KPcopy(arg_0, &v46[0], arg_14);
      v62 = v62 && KPcopy(arg_4, &v46[1], arg_14);
      v38 = v46[0].degree < v46[1].degree;
      i = 1 - v38;
      while ( v62 && v46[i].degree != (DWORD)-1 )
      {
        v62 = v62 && KPdiv(&v46[v38], &v46[i], &v39, &v48, arg_14);
        v62 = v62 && KPcopy(&v48, &v46[v38], arg_14);
        for ( j = 0; j <= 1; ++j )
        {
          v62 = v62 && KPmul(&mulab[i][j], &v39, &v48, arg_14);
          v62 = v62 && KPsub(&mulab[v38][j], &v48, &mulab[v38][j], arg_14);
        }
        v38 = 1 - v38;
        i = 1 - i;
      }
      v62 = v62 && KPcopy(&v46[v38], arg_8, arg_14);
      if ( arg_C )
      {
        v62 = v62 && KPcopy(&mulab[v38][0], arg_C, arg_14);
      }
      if ( arg_10 )
      {
        v62 = v62 && KPcopy(&mulab[v38][1], arg_10, arg_14);
      }
      mp_free_temp(v50);
    }
  }
  v35 = arg_8->degree;
  if ( v62 && v35 != (DWORD)-1 )
  {
    digit_t v34[64]; // [sp+6Ch] [bp-1CCh]@125
    v62 = v62 && Kinvert(&arg_8->coefs[v35 * v65], v34, arg_14);
    v62 = v62 && KPmul_scalar(arg_8, v34, arg_8, arg_14);
    if ( arg_C )
    {
      v62 = v62 && KPmul_scalar(arg_C, v34, arg_C, arg_14);
    }
    if ( arg_10 )
    {
      v62 = v62 && KPmul_scalar(arg_10, v34, arg_10, arg_14);
    }
  }
  return v62;
  }}}}}}}}}}}}}}}}}}}}}}
}

int KPmonomial(digit_tc arg_0[], DWORDC arg_4, kpoly_t* arg_8, const field_desc_t* arg_C)
{
  int v6; // [sp+4h] [bp-4h]@1
  {
  int v5; // [sp+0h] [bp-8h]@1

  v5 = 1;
  v6 = arg_C->elng;
  if ( Kiszero(arg_0, arg_C) )
  {
    arg_8->degree = (DWORD)-1;
  }
  else if ( arg_8->maxlength <= arg_4 )
  {
    v5 = 0;
    mp_errno = 23;
  }
  else
  {
    arg_8->degree = arg_4;
    Kclear(arg_8->coefs, arg_4, arg_C);
    Kcopy(arg_0, &arg_8->coefs[v6 * arg_4], 1, arg_C);
  }
  return v5;
  }
}

int KPmul(const kpoly_t *arg_0, const kpoly_t *arg_4, kpoly_t *arg_8, const field_desc_t *arg_C)
{
  DWORD v15; // [sp+24h] [bp-4h]@1
  {
  DWORD v14; // [sp+20h] [bp-8h]@1
  {
  DWORD v13; // [sp+1Ch] [bp-Ch]@1
  {
  int v12; // [sp+18h] [bp-10h]@1

  v15 = arg_0->degree;
  v14 = arg_4->degree;
  v13 = v15 + v14;
  v12 = 1;
  if ( v15 == (DWORD)-1 || v14 == (DWORD)-1 )
  {
    arg_8->degree = (DWORD)-1;
  }
  else if ( arg_8->maxlength <= v13 )
  {
    mp_errno = 23;
    v12 = 0;
    arg_8->degree = (DWORD)-1;
  }
  else
  {
    DWORD j; // [sp+14h] [bp-14h]@13
    {
    DWORD v10; // [sp+10h] [bp-18h]@6
    {
    DWORD i; // [sp+Ch] [bp-1Ch]@6

    v10 = arg_C->elng;
    arg_8->degree = v13;
    for ( i = 0; i <= v15 * v10; i += v10 )
    {
      v12 = v12 && Kmul(&arg_0->coefs[i], arg_4->coefs, &arg_8->coefs[i], arg_C);
    }
    for ( j = v10; j <= v14 * v10; j += v10 )
    {
      for ( i = 0; i != v15 * v10; i += v10 )
      {
        v12 = v12
          && Kmuladd(&arg_0->coefs[i], &arg_4->coefs[j], &arg_8->coefs[i + j], &arg_8->coefs[i + j], arg_C);
      }
      v12 = v12 && Kmul(&arg_0->coefs[i], &arg_4->coefs[j], &arg_8->coefs[i + j], arg_C);
    }
    }}
  }
  return v12;
  }}}
}

int KPmul_scalar(const kpoly_t* arg_0, digit_tc arg_4[], kpoly_t* arg_8, const field_desc_t* arg_C)
{
  DWORD v9; // [sp+10h] [bp-4h]@1
  {
  int v8; // [sp+Ch] [bp-8h]@1

  v9 = arg_0->degree;
  v8 = 1;
  if ( v9 == (DWORD)-1 || Kiszero(arg_4, arg_C) )
  {
    arg_8->degree = (DWORD)-1;
  }
  else if ( arg_8->maxlength <= v9 )
  {
    mp_errno = 23;
    v8 = 0;
  }
  else
  {
    int v7; // [sp+8h] [bp-Ch]@6
    {
    DWORD i; // [sp+4h] [bp-10h]@6

    v7 = arg_C->elng;
    arg_8->degree = v9;
    for ( i = 0; i <= v9 * v7; i += v7 )
    {
      v8 = v8 && Kmul(&arg_0->coefs[i], arg_4, &arg_8->coefs[i], arg_C);
    }
    }
  }
  return v8;
  }
}

int KPrandom(kpoly_t *arg_0, const field_desc_t *arg_4)
{
  DWORD v6; // [sp+10h] [bp-4h]@1
  {
  int v5; // [sp+Ch] [bp-8h]@1
  {
  DWORD v2; // ST14_4@1

  v5 = 1;
  v2 = arg_0->degree;
  v6 = v2 + 1;
  if ( v2 == (DWORD)-1 )
  {
  }
  else if ( arg_0->maxlength < v6 )
  {
    mp_errno = 23;
    v5 = 0;
  }
  else
  {
    v5 = v5 && Krandom(arg_0->coefs, v6, arg_4);
    v5 = v5 && KPcheck_degree(arg_0, arg_4);
  }
  return v5;
  }}
}

int KPsub(const kpoly_t *arg_0, const kpoly_t *arg_4, kpoly_t *arg_8, const field_desc_t *arg_C)
{
  DWORD v9; // [sp+30h] [bp-4h]@5
  {
  DWORD v16; // [sp+2Ch] [bp-8h]@1
  {
  DWORD v15; // [sp+28h] [bp-Ch]@1
  {
  DWORD v14; // [sp+24h] [bp-10h]@7
  {
  int v13; // [sp+20h] [bp-14h]@7
  {
  DWORD v10; // [sp+1Ch] [bp-18h]@2

  v16 = arg_0->degree + 1;
  v15 = arg_4->degree + 1;
  v10 = ( v16 > v15 ) ? v15 : v16;
  v9 = ( v16 > v15 ) ? v16 : v15;
  v14 = arg_C->elng;
  v13 = 1;
  if ( arg_8->maxlength < v9 )
  {
    mp_errno = 23;
    v13 = 0;
    arg_8->degree = (DWORD)-1;
  }
  else
  {
    unsigned int i; // [sp+18h] [bp-1Ch]@9
    for ( i = 0; i != v10 * v14; i += v14 )
    {
      v13 = v13 && Ksub(&arg_0->coefs[i], &arg_4->coefs[i], &arg_8->coefs[i], arg_C);
    }
    arg_8->degree = v9 - 1;
    if ( v16 > v15 )
    {
      v13 = v13 && Kcopy(&arg_0->coefs[i], &arg_8->coefs[i], v16 - v15, arg_C);
    }
    else if ( v15 > v16 )
    {
      for ( i = v10 * v14; i != v15 * v14; i += v14 )
      {
        v13 = v13 && Knegate(&arg_4->coefs[i], &arg_8->coefs[i], arg_C);
      }
    }
    else
    {
      v13 = v13 && KPcheck_degree(arg_8, arg_C);
    }
  }
  return v13;
  }}}}}
}
