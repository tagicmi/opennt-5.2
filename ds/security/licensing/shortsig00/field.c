#include <crypto/bignum.h>
#include "field.h"

static void random_digits(digit_t* array, DWORDC lng);
extern void random_mod(digit_tc n[], digit_t arr[], DWORDC lng);
extern void random_bytes(BYTE* byte_array, DWORDC nbyte);

int Kadd(digit_tc f1[], digit_tc f2[], digit_t f3[], const field_desc_t* fdesc)
{
  int v7; // [sp+Ch] [bp-4h]@6
  {
  int i; // [sp+8h] [bp-8h]@6

  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    mod_add(f1, f2, f3, fdesc->modulo);
    return 1;
  case FIELD_2_NORMAL:
  case FIELD_2_POLYNOMIAL:
    v7 = fdesc->elng;
    for ( i = 0; i != v7; ++i )
      f3[i] = f1[i] ^ f2[i];
    return 1;
  default:
    return 0;
  }
  }
}

int Kclear(digit_t f1[], DWORDC nelmt, const field_desc_t* fdesc)
{
  mp_clear(f1, nelmt * fdesc->elng);
  return 1;
}

int Kcopy(digit_tc f1[], digit_t f2[], DWORDC nelmt, const field_desc_t* fdesc)
{
  mp_copy(f1, f2, nelmt * fdesc->elng);
  return 1;
}

int Kequal(digit_tc f1[], digit_tc f2[], const field_desc_t* fdesc)
{
  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
  case FIELD_2_NORMAL:
  case FIELD_2_POLYNOMIAL:
    return compare_same(f1, f2, fdesc->elng) == 0;
  default:
    return 0;
  }
}

int Kfree(field_desc_t *fdesc)
{
  int v4 = 1;
  if ( fdesc->ftype == FIELD_2_NORMAL && fdesc->mulshifts )
  {
    mp_free_temp(fdesc->mulshifts);
    fdesc->mulshifts = 0;
  }
  if ( fdesc->ftype == FIELD_Q_MP && fdesc->modulo_allocated && fdesc->modulo )
  {
    mp_free_temp((mp_modulus_t*)fdesc->modulo); // const_cast
    fdesc->modulo_allocated = 0;
    fdesc->modulo = 0;
  }
  if ( fdesc->montgomery_one_allocated )
  {
    mp_free_temp(fdesc->montgomery_one_allocated);
    fdesc->montgomery_one_allocated = 0;
  }
  fdesc->ftype = FIELD_TYPE_INVALID;
  return v4;
}

int Kimmediate(const long scalar, digit_t f1[], const field_desc_t *fdesc)
{
  const digit_t abssc = abs(scalar);

  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    to_modular(&abssc, 1u, f1, fdesc->modulo);
    if ( scalar < 0 )
      Knegate(f1, f1, fdesc);
    return 1;
  case FIELD_2_NORMAL:
  case FIELD_2_POLYNOMIAL:
    if ( abssc & 1 )
      return Kcopy(fdesc->one, f1, 1, fdesc);
    else
      return Kclear(f1, 1, fdesc);
  default:
    return 0;
  }
}

int Kinitialize_prime(mp_modulus_tc* modulo, modmultemp_t* modmultemps, field_desc_t* fdesc)
{
  unsigned int lnga; // [sp+10h] [bp-4h]@1
  {
  int v7; // [sp+Ch] [bp-8h]@1

  lnga = modulo->length;
  v7 = 1;
  fdesc->montgomery_one_allocated = 0;
  fdesc->modulo_allocated = 0;
  fdesc->degree = 1;
  fdesc->elng = lnga;
  fdesc->ftype = FIELD_Q_MP;
  fdesc->modulo = modulo;
  fdesc->modmultemps = modmultemps;
  fdesc->mulshifts = 0;
  fdesc->nonzero_trace_power = 0;
  fdesc->one = modulo->one;
  if ( !v7 )
  {
  }
  else if ( !modulo->reddir )
  {
    fdesc->montgomery_one = fdesc->one;
  }
  else
  {
    digit_t *b; // [sp+8h] [bp-Ch]@3
    b = (digit_t *)mp_alloc_temp(sizeof(digit_t) * lnga);
    if ( !b )
      v7 = 0;
    fdesc->montgomery_one_allocated = b;
    fdesc->montgomery_one = b;
    v7 = v7 && modular_reduce(fdesc->one, lnga, modulo->reddir, b, modulo, modmultemps);
    v7 = v7 && modular_reduce(b, lnga, modulo->reddir, b, modulo, modmultemps);
    if ( !v7 && b )
      mp_free_temp(b);
  }
  return v7;
  }
}

int Kinvert(digit_tc f1[], digit_t f2[], const field_desc_t* fdesc)
{
  int v12; // [sp+224h] [bp-4h]@1
  {
  digit_t v11[64]; // [sp+124h] [bp-104h]@6
  {
  digit_t gcd[64]; // [sp+24h] [bp-204h]@6
  {
  unsigned int lnga; // [sp+20h] [bp-208h]@1
  {
  int v8; // [sp+1Ch] [bp-20Ch]@1
  {
  digit_tc* v7; // [sp+18h] [bp-210h]
  {
  digit_t v3; // [sp+14h] [bp-214h]
  {
  mp_modulus_tc *b; // [sp+10h] [bp-218h]@5

  lnga = fdesc->elng;
  v12 = fdesc->degree;
  v8 = 1;
  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    b = fdesc->modulo;
    if ( b->reddir == 1 )
    {
      Kmul(f1, fdesc->montgomery_one, v11, fdesc);
      v7 = v11;
    }
    else
    {
      v7 = f1;
    }
    v3 = mp_gcdex(v7, lnga, b->modulus, lnga, f2, 0, gcd, 0);
    v8 = v8 && compare_immediate(gcd, 1u, (DWORDC)v3) == 0;
    break;
  case FIELD_2_POLYNOMIAL:
    v8 = v8 && compare_immediate(gcd, 1u, lnga) == 0;
    v8 = v8 && Kcopy(v11, f2, 1, fdesc);
    break;
  case FIELD_2_NORMAL:
    break;
  default:
    v8 = 0;
  }
  return v8;
  }}}}}}}
}

int Kiszero(digit_tc f1[], const field_desc_t* fdesc)
{
  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
  case FIELD_2_NORMAL:
  case FIELD_2_POLYNOMIAL:
    return all_zero(f1, fdesc->elng);
  default:
    return 0;
  }
}

int Kmul(digit_tc f1[], digit_tc f2[], digit_t f3[], const field_desc_t* fdesc)
{
  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    mod_mul(f1, f2, f3, fdesc->modulo, fdesc->modmultemps);
    return 1;
  default:
    return 0;
  }
}

int Kmuladd(digit_tc f1[], digit_tc f2[], digit_tc f3[], digit_t f4[], const field_desc_t* fdesc)
{
  digit_t v7[64]; // [sp+4h] [bp-100h]@1

  return Kmul(f1, f2, v7, fdesc) && Kadd(v7, f3, f4, fdesc);
}

int Kmulsubfrom(digit_tc f1[], digit_tc f2[], digit_tc f3[], digit_t f4[], const field_desc_t* fdesc)
{
  digit_t v7[64]; // [sp+4h] [bp-100h]@1

  return Kmul(f1, f2, v7, fdesc) && Ksub(f3, v7, f4, fdesc);
}

int Knegate(digit_tc f1[], digit_t f2[], const field_desc_t* fdesc)
{
  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    mod_negate(f1, f2, fdesc->modulo);
    return 1;
  case FIELD_2_NORMAL:
  case FIELD_2_POLYNOMIAL:
    return Kcopy(f1, f2, 1, fdesc);
  default:
    return 0;
  }
}

int Krandom(digit_t f1[], DWORDC nelmt, const field_desc_t* fdesc)
{
  int v8; // [sp+Ch] [bp-4h]@1
  {
  DWORD i; // [sp+8h] [bp-8h]@5
  {
  int v5; // [sp+4h] [bp-Ch]@9

  v8 = fdesc->elng;
  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    for ( i = 0; i != nelmt; ++i )
      random_mod(fdesc->modulo->modulus, &f1[i * v8], fdesc->elng);
    return 1;
  case FIELD_2_NORMAL:
  case FIELD_2_POLYNOMIAL:
    v5 = fdesc->degree;
    random_digits(f1, v8 * nelmt);
    for ( i = 0; i != nelmt; ++i )
      f1[i * v8 + v8 - 1] >>= RADIX_BITS * v8 - v5;
    return 1;
  default:
    return 0;
  }
  }}
}

void random_digits(digit_t* array, DWORDC lng)
{
  random_bytes((BYTE*)array, lng * sizeof(digit_t));
}

int Ksqrt(digit_tc f1[], digit_t f2[], const field_desc_t* fdesc)
{
  int v8; // [sp+18h] [bp-4h]@1
  {
  signed int i; // [sp+14h] [bp-8h]@5
  {
  signed int v6; // [sp+10h] [bp-Ch]@5

  v8 = fdesc->degree;
  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    return mod_sqrt(f1, f2, fdesc->modulo);
  case FIELD_2_POLYNOMIAL:
    v6 = 1;
    mp_copy(f1, f2, fdesc->elng);
    for ( i = 1; i != v8; ++i )
    {
      v6 = v6 && Kmul(f2, f2, f2, fdesc);
    }
    return v6;
  default:
    return 0;
  }
  }}
}

int Ksub(digit_tc f1[], digit_tc f2[], digit_t f3[], const field_desc_t* fdesc)
{
  int v7; // [sp+Ch] [bp-4h]@6
  {
  int i; // [sp+8h] [bp-8h]@6

  switch ( fdesc->ftype )
  {
  case FIELD_Q_MP:
    mod_sub(f1, f2, f3, fdesc->modulo);
    return 1;
  case FIELD_2_NORMAL:
  case FIELD_2_POLYNOMIAL:
    v7 = fdesc->elng;
    for ( i = 0; i != v7; ++i )
      f3[i] = f1[i] ^ f2[i];
    return 1;
  default:
    return 0;
  }
  }
}
