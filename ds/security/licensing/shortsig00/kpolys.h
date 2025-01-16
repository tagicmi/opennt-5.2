typedef struct
{
  digit_t* coefs;
  DWORD maxlength;
  DWORD degree;
} kpoly_t;

typedef struct field_desc_t field_desc_t;

int KPadd(const kpoly_t* p1, const kpoly_t* p2, kpoly_t* p3, const field_desc_t* fdesc);
int KPgcd(const kpoly_t* p1, const kpoly_t* p2, kpoly_t* pgcd, kpoly_t* pmul1, kpoly_t* pmul2, const field_desc_t* fdesc);
int KPsub(const kpoly_t* p1, const kpoly_t* p2, kpoly_t* p3, const field_desc_t* fdesc);
int KPexpon(const kpoly_t* pbase, digit_tc exponent[], DWORDC lng_expon, kpoly_t* answer, const kpoly_t* pmonic, const field_desc_t* fdesc);
int KPmonomial(digit_tc fval[], DWORDC degree, kpoly_t* p, const field_desc_t* fdesc);
int KPcopy(const kpoly_t* p1, kpoly_t* p2, const field_desc_t* fdesc);
int KPdiv(const kpoly_t* numer, const kpoly_t* denom, kpoly_t* quot, kpoly_t* rem, const field_desc_t* fdesc);
int KPmul(const kpoly_t* p1, const kpoly_t* p2, kpoly_t* p3, const field_desc_t* fdesc);
int KPmul_scalar(const kpoly_t* p1, digit_tc fval[], kpoly_t* p2, const field_desc_t* fdesc);
int KPrandom(kpoly_t* p, const field_desc_t* fdesc);
int KPcheck_degree(kpoly_t* p, const field_desc_t* fdesc);
