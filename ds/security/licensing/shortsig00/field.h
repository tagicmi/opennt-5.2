typedef struct
{
  unsigned short shift1;
  unsigned short shift2;
} k2nmulshifts_t;

typedef struct field_desc_t
{
  DWORD elng;
  DWORD degree;
  enum
  {
    FIELD_TYPE_INVALID = 0,
    FIELD_Q_MP = 1,
    FIELD_2_NORMAL = 2,
    FIELD_2_POLYNOMIAL = 3,
  } ftype;
  int modulo_allocated; // made-up name, absent in other versions
  digit_tc *one;
  digit_t *montgomery_one_allocated; // made-up name, absent in other versions
  modmultemp_t *modmultemps;
  mp_modulus_tc *modulo;
  const digit_t *montgomery_one; // made-up name, absent in other versions
  DWORD dword24;
  DWORD dword28;
  k2nmulshifts_t *mulshifts;
  DWORD nonzero_trace_power;
} field_desc_t;

int Kfree(field_desc_t* fdesc);
int Knegate(digit_tc f1[], digit_t f2[], const field_desc_t* fdesc);
int Kmulsubfrom(digit_tc f1[], digit_tc f2[], digit_tc f3[], digit_t f4[], const field_desc_t* fdesc);
int Kmul(digit_tc f1[], digit_tc f2[], digit_t f3[], const field_desc_t* fdesc);
int Kiszero(digit_tc f1[], const field_desc_t* fdesc);
int Kcopy(digit_tc f1[], digit_t f2[], DWORDC nelmt, const field_desc_t* fdesc);
int Kclear(digit_t f1[], DWORDC nelmt, const field_desc_t* fdesc);
int Kequal(digit_tc f1[], digit_tc f2[], const field_desc_t* fdesc);
int Kinvert(digit_tc f1[], digit_t f2[], const field_desc_t* fdesc);
int Kimmediate(const long scalar, digit_t f1[], const field_desc_t* fdesc);
int Kinitialize_prime(mp_modulus_tc* modulo, modmultemp_t* modmultemps, field_desc_t* fdesc);
int Kadd(digit_tc f1[], digit_tc f2[], digit_t f3[], const field_desc_t* fdesc);
int Ksub(digit_tc f1[], digit_tc f2[], digit_t f3[], const field_desc_t* fdesc);
int Kmuladd(digit_tc f1[], digit_tc f2[], digit_tc f3[], digit_t f4[], const field_desc_t* fdesc);
int Krandom(digit_t f1[], DWORDC nelmt, const field_desc_t* fdesc);
int Ksqrt(digit_tc f1[], digit_t f2[], const field_desc_t* fdesc);
