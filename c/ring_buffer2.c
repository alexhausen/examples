// Ring/circular u16 buffer implementation

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE (0 == 0)
#define FALSE (!TRUE)

typedef struct {
  uint16_t* buf;
  uint32_t capacity;
  uint32_t begin;
  uint32_t length;
} RingBuffer;

void Init(RingBuffer* rb, uint32_t capacity) {
  assert(rb != NULL);
  size_t sz = capacity * sizeof(uint16_t);
  rb->buf = malloc(sz);
  assert(rb->buf != NULL);
  memset(rb->buf, 0xFFFFu, sz);
  rb->begin = 0;
  rb->length = 0;
  rb->capacity = capacity;
}

void Release(RingBuffer* rb) {
  free(rb->buf);
  rb->buf = NULL;
  rb->capacity = 0;
  rb->begin = 0;
  rb->length = 0;
}

_Bool Empty(const RingBuffer* rb) {
  return rb->length == 0u;
}

uint32_t Count(const RingBuffer* rb) {
  return rb->length;
}

void PrintArrayU16(const uint16_t data[], uint32_t length) {
  printf("[ ");
  for (uint32_t i = 0; i < length; i++) {
    printf("%u ", data[i]);
  }
  printf("]");
}

void PrintRB(const RingBuffer* rb) {
  printf("[ ");
  uint32_t pos = rb->begin;
  for (uint32_t i = 0; i < rb->length; i++) {
    printf("%u ", rb->buf[pos]);
    pos = (pos + 1) % rb->capacity;
  }
  printf("] : {%u, %u}\n", rb->length, rb->capacity);
}

_Bool Push(RingBuffer* rb, const uint16_t data[], uint32_t data_length) {
  assert(rb != NULL);
  if (data_length > rb->capacity) {
    return FALSE;
  }
  uint32_t pos = (rb->begin + rb->length) % rb->capacity;
  for (uint32_t i = 0; i < data_length; i++) {
    rb->buf[pos] = data[i];
    pos = (pos + 1) % rb->capacity;
  }
  uint32_t unused_space = rb->capacity - rb->length;
  if (data_length > unused_space) {
    rb->begin = (rb->begin + rb->length + data_length) % rb->capacity;
    rb->length = rb->capacity;
  } else {
    rb->length += data_length;
  }
  printf("push(");
  PrintArrayU16(data, data_length);
  printf(")\n");
  PrintRB(rb);
  return TRUE;
}

_Bool Pop(RingBuffer* rb, uint16_t data[], uint32_t data_length) {
  assert(rb != NULL);
  if (data_length > rb->length) {
    return FALSE;
  }
  uint32_t pos = rb->begin;
  for (uint32_t i = 0; i < data_length; i++) {
    data[i] = rb->buf[pos];
    pos = (pos + 1) % rb->capacity;
  }
  rb->begin = (rb->begin + data_length) % rb->capacity;
  rb->length -= data_length;
  printf("pop(%u) -> ", data_length);
  PrintArrayU16(data, data_length);
  printf("\n");
  PrintRB(rb);
  return TRUE;
}

_Bool Equal(const uint16_t actual[], const uint16_t expected[], uint32_t length) {
  for (uint32_t i = 0u; i < length; i++) {
    if (actual[i] != expected[i]) {
      printf("error at index %u: expected %u, got %u\n", i, expected[i], actual[i]);
      return FALSE;
    }
  }
  return TRUE;
}

int main() {
  /*
  [ ] : {0, 0}
  */
  printf("\n:test 0:\n");
  RingBuffer rb0;
  Init(&rb0, 0);
  PrintRB(&rb0);
  assert(Empty(&rb0));

  /*
  [ ] : {0, 5}
  push([ 1 2 3 ])
  [ 1 2 3 ] : {3, 5}
  pop(3) -> [ 1 2 3 ]
  [ ] : {0, 5}
  */
  printf("\n:test 1:\n");
  RingBuffer rb1;
  Init(&rb1, 5u);
  PrintRB(&rb1);
  assert(Empty(&rb1));
  assert(Count(&rb1) == 0);
  assert(rb1.capacity == 5);
  const uint16_t expected_empty[5] = {0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu, 0xFFFFu};
  assert(Equal(rb1.buf, expected_empty, 5));
  // simple push
  const uint16_t input1[3] = {1, 2, 3};
  assert(Push(&rb1, input1, 3));
  assert(!Empty(&rb1));
  assert(Count(&rb1) == 3);
  const uint16_t expected1[5] = {1, 2, 3, 0xFFFFu, 0xFFFFu};
  assert(Equal(rb1.buf, expected1, 5));
  // simple pop
  uint16_t pop1[3] = {0};
  assert(Pop(&rb1, pop1, 3));
  assert(Empty(&rb1));
  assert(Count(&rb1) == 0);
  assert(Equal(pop1, input1, 3));
  assert(Equal(rb1.buf, expected1, 5));
  // release
  Release(&rb1);
  assert(rb1.buf == NULL);
  assert(rb1.length == 0);

  /*
  [ ] : {0, 10}
  push([ 10 20 30 40 50 60 70 80 90 100 ])
  [ 10 20 30 40 50 60 70 80 90 100 ] : {10, 10}
  pop(7) -> [ 10 20 30 40 50 60 70 ]
  [ 80 90 100 ] : {3, 10}
  push([ 1 2 3 4 5 6 7 ])
  [ 80 90 100 1 2 3 4 5 6 7 ] : {10, 10}
  pop(1) -> [ 80 ]
  [ 90 100 1 2 3 4 5 6 7 ] : {9, 10}
  */
  printf("\n:test 2:\n");
  RingBuffer rb2;
  Init(&rb2, 10);
  PrintRB(&rb2);
  // push full
  const uint16_t input2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  assert(Push(&rb2, input2, 10));
  assert(Count(&rb2) == 10);
  assert(Equal(rb2.buf, input2, 10));
  // pop some
  uint16_t pop2[7] = {0};
  assert(Pop(&rb2, pop2, 7));
  assert(Count(&rb2) == 3);
  assert(Equal(pop2, input2, 3));
  assert(rb2.begin == 7);
  const uint16_t expected2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  assert(Equal(rb2.buf, expected2, 10));
  // push full again
  const uint16_t input3[7] = {1, 2, 3, 4, 5, 6, 7};
  assert(Push(&rb2, input3, 7));
  assert(Count(&rb2) == 10);
  const uint16_t expected3[] = {1, 2, 3, 4, 5, 6, 7, 80, 90, 100};
  assert(Equal(rb2.buf, expected3, 10));
  // pop one more
  assert(Pop(&rb2, pop2, 1));
  assert(Count(&rb2) == 9);
  assert(pop2[0] == 80);

  /*
  [ 10 20 ] : {2, 7}
  pop(2) -> [ 10 20 ]
  [ ] : {0, 7}
  */
  printf("\n:test 3:\n");
  RingBuffer rb3;
  Init(&rb3, 7);
  // setup
  const uint16_t input4[2] = {10, 20};
  rb3.buf[1] = input4[0];
  rb3.buf[2] = input4[1];
  rb3.begin = 1;
  rb3.length = 2;
  PrintRB(&rb3);
  const uint16_t expected4[] = {0xFFFFu, 10, 20, 0xFFFFU, 0xFFFFU, 0xFFFFU, 0xFFFFU};
  assert(Equal(rb3.buf, expected4, 7u));
  // pop
  uint16_t pop3[2] = {0};
  assert(Pop(&rb3, pop3, 2));
  assert(Empty(&rb3));
  assert(Equal(rb3.buf, expected4, 7));
  assert(Equal(pop3, input4, 2));
  // release
  Release(&rb3);

  /*
  [ ] : {0, 7}
  push([ 10 20 30 40 50 60 ])
  [ 10 20 30 40 50 60 ] : {6, 7}
  pop(5) -> [ 10 20 30 40 50 ]
  [ 60 ] : {1, 7}
  */
  printf("\n:test 4:\n");
  RingBuffer rb4;
  Init(&rb4, 7);
  PrintRB(&rb4);
  // setup
  const uint16_t input5[6] = {10, 20, 30, 40, 50, 60};
  rb4.begin = 5;
  assert(Push(&rb4, input5, 6));
  assert(Count(&rb4) == 6);
  const uint16_t expected5[7] = {30, 40, 50, 60, 0xFFFFU, 10, 20};
  assert(Equal(rb4.buf, expected5, 7));
  // pop
  uint16_t pop4[5] = {0};
  assert(Pop(&rb4, pop4, 5));
  assert(Count(&rb4) == 1);
  assert(rb4.begin == 3);
  const uint16_t expected6[5] = {10, 20, 30, 40, 50};
  assert(Equal(pop4, expected6, 5));
  // release
  Release(&rb4);

  /*
  [ ] : {0, 3}
  push([ 1 2 ])
  [ 1 2 ] : {2, 3}
  push([ 3 4 ])
  [ 2 3 4 ] : {3, 3}
  pop(2) -> [ 2 3 ]
  [ 4 ] : {1, 3}
  */
  printf("\n:test 5:\n");
  RingBuffer rb5;
  Init(&rb5, 3);
  // setup
  const uint16_t input6[2] = {1, 2};
  rb5.begin = 1;
  PrintRB(&rb5);
  assert(Push(&rb5, input6, 2));
  assert(Count(&rb5) == 2);
  const uint16_t expected7[3] = {0xFFFFU, 1, 2};
  assert(Equal(rb5.buf, expected7, 3));
  // push and override
  const uint16_t input7[2] = {3, 4};
  assert(Push(&rb5, input7, 2));
  assert(Count(&rb5) == 3);
  const uint16_t expected8[3] = {3, 4, 2};
  assert(Equal(rb5.buf, expected8, 3));
  assert(rb5.begin == 2);
  // pop
  uint16_t pop5[2] = {0};
  assert(Pop(&rb5, pop5, 2));
  const uint16_t expected9[3] = {2, 3};
  assert(Equal(pop5, expected9, 2));
  assert(Count(&rb5) == 1);
  assert(rb5.begin == 1);
  assert(Equal(rb5.buf, expected8, 3));
  // release
  Release(&rb5);

  /*
  :test 6:
  [ ] : {0, 1}
  push([ 1 ])
  [ 1 ] : {1, 1}
  push([ 2 ])
  [ 2 ] : {1, 1}
  pop(1) -> [ 2 ]
  [ ] : {0, 1}
  */
  printf("\n:test 6:\n");
  RingBuffer rb6;
  Init(&rb6, 1);
  PrintRB(&rb6);
  // push full
  const uint16_t input8 = 1;
  assert(Push(&rb6, &input8, 1));
  assert(Count(&rb6) == 1);
  // push full again
  const uint16_t input9 = 2;
  assert(Push(&rb6, &input9, 1));
  assert(Count(&rb6) == 1);
  // pop
  uint16_t pop6;
  assert(Pop(&rb6, &pop6, 1));
  assert(pop6 == 2);
  assert(Empty(&rb6));
  // release
  Release(&rb6);

  /*
  [ 1 ] : {1, 3}
  push([ 2 3 4 ])
  [ 2 3 4 ] : {3, 3}
  */
  printf("\n:test 7:\n");
  RingBuffer rb7;
  Init(&rb7, 3);
  // setup
  rb7.begin = 1;
  rb7.length = 1;
  rb7.buf[1] = 1;
  PrintRB(&rb7);
  // push full
  const uint16_t input10[3] = {2, 3, 4};
  assert(Push(&rb7, input10, 3));
  assert(Count(&rb7) == 3);
  const uint16_t expected10[3] = {3, 4, 2};
  assert(Equal(rb7.buf, expected10, 3));
  // release
  Release(&rb7);

  puts("ok");
  return 0;
}
