#include <stdio.h>
#include <string.h>

#define MAX_VECTOR_LEN 100

typedef struct {
  int len;
  int vec[MAX_VECTOR_LEN];
} int_vector;

int equals_i(int_vector* v1, int_vector* v2) {
  return memcmp(v1, v2, sizeof(int_vector)) == 0;
}

typedef struct {
  char str1[24];
  char str2[24];
  char str3[24];
  char str4[24];
  char str5[24];
} string_vector;

int equals_s(string_vector* v1, string_vector* v2) {
  return memcmp(v1, v2, sizeof(string_vector)) == 0;
}

void fill_string_vector(string_vector* out, const char* str, unsigned size) {
  memset(out, 0, sizeof(string_vector));
  memcpy(out, "hello", 5);
  printf("&out->str1=%p out%p\n", &out->str1, &out[0]);

  // it doesn't work because theses addresses (to the middle of the struct) are not the same !!!!!!!
  printf("&out->str2=%p &out[24]%p\n", &out->str2, &out[24]);

  memcpy(&out[24], str, size);
}

int main(void) {
  int_vector v1, v2;

  v1.len = 3;
  v1.vec[0] = 10;
  v1.vec[1] = 20;
  v1.vec[2] = 30;

  v2 = v1; /*Assume uninitialized values are also copied*/

  if(equals_i(&v1, &v2)) {
    puts("Equal - 1st test");
  }

  int_vector v3;
  memcpy(&v3 + sizeof(int), &v2, MAX_VECTOR_LEN * sizeof(int));
  v3.len = 3;

  if(equals_i(&v1, &v2)) {
    puts("Equal - 2nd test");
  }

  string_vector v4;
  char test[24*4];
  strcat(&test[24], "world");
  strcat(&test[48], "!!!");
  fill_string_vector(&v4, test, 24*4);
  
  string_vector v5;
  memset(&v5, 0, sizeof(string_vector));
  strcat(v5.str1, "hello");
  strcat(v5.str2, "world");
  strcat(v5.str3, "!!!");
  if (equals_s(&v4, &v5)) {
    puts("Equal - 3rd test");
  } else {
    printf("%s, %s, %s, %s, %s\n", v4.str1, v4.str2, v4.str3, v4.str4, v4.str5);
    printf("%s, %s, %s, %s, %s\n", v5.str1, v5.str2, v5.str3, v5.str4, v5.str5);
  }

  string_vector v6;
  v6 = v5;
  if (equals_s(&v5, &v6)) {
    puts("Equal - 4th test");
  }
  return 0;
}
