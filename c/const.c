void main(void) {
  char x = 10;
  const char * a = &x;
  char const * b = &x;
  char * const c = &x;
  const char * const d = &x;

  a = &x;
//  *a = 50;

  b = &x;
//  *b = 60;

//  c = &x;
  *c = 70;

//  d = &x;
//  *d = 80;
}
