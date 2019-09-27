// Ring/circular u8 buffer implementation using memcpy

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE (0 == 0)
#define FALSE (!TRUE)

typedef struct {
  uint8_t* buf;
  uint32_t capacity;
  uint32_t begin;
  uint32_t length;
} RingBuffer;

void Init(RingBuffer* rb, uint32_t capacity) {
  assert(rb != NULL);
  rb->buf = malloc(capacity);
  assert(rb->buf != NULL);
  memset(rb->buf, 0xFFu, capacity);
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

static void PrintPush(const uint8_t data[], uint32_t length) {
  printf("push([ ");
  for (uint32_t i = 0; i < length; i++) {
    printf("%d ", data[i]);
  }
  printf("])\n");
}

static void PrintPop(const uint8_t data[], uint32_t length) {
  printf("pop(%d) -> [ ", length);
  for (uint32_t i = 0; i < length; i++) {
    printf("%d ", data[i]);
  }
  printf("]\n");
}

void Print(const RingBuffer* rb) {
  printf("[ ");
  uint32_t pos = rb->begin;
  for (uint32_t i = 0; i < rb->length; i++) {
    printf("%d ", rb->buf[pos]);
    pos = (pos + 1) % rb->capacity;
  }
  printf("] : {%u, %u}\n", rb->length, rb->capacity);
}

_Bool Push(RingBuffer* rb, const uint8_t data[], uint32_t data_length) {
  assert(rb != NULL);
  if (data_length > rb->capacity) {
    return FALSE;
  }
  const uint32_t end = (rb->begin + rb->length) % rb->capacity;
  const uint32_t len = (end + data_length > rb->capacity) ? (rb->capacity - end) : data_length;
  uint8_t* end_ptr = &(rb->buf[end]);
  memcpy(end_ptr, data, len);
  const uint32_t len2 = data_length - len;
  memcpy(rb->buf, &data[len], len2);
  const uint32_t unused_space = rb->capacity - rb->length;
  if (data_length > unused_space) {
    rb->length = rb->capacity;
    rb->begin = (end + data_length) % rb->capacity;
  } else {
    rb->length += data_length;
  }
  PrintPush(data, data_length);
  Print(rb);
  return TRUE;
}

_Bool Pop(RingBuffer* rb, uint8_t data[], uint32_t data_length) {
  assert(rb != NULL);
  if (data_length > Count(rb)) {
    return FALSE;
  }
  const uint8_t* begin_ptr = &(rb->buf[rb->begin]);
  const uint32_t len =
      (rb->begin + data_length > rb->capacity) ? (rb->capacity - rb->begin) : data_length;
  memcpy(data, begin_ptr, len);
  memcpy(&data[len], rb->buf, data_length - len);
  rb->begin = (rb->begin + data_length) % rb->capacity;
  rb->length -= data_length;
  PrintPop(data, data_length);
  Print(rb);
  return TRUE;
}

_Bool Equal(const uint8_t actual[], const uint8_t expected[], uint32_t length) {
  for (uint32_t i = 0u; i < length; i++) {
    if (actual[i] != expected[i]) {
      printf("error at index %u: expected %u, got %u\n", i, expected[i], actual[i]);
      return FALSE;
    }
  }
  return TRUE;
}

int main() {
  // empty buffer
  printf("\n:test 0:\n");
  RingBuffer rb0;
  Init(&rb0, 0);
  Print(&rb0);
  assert(Empty(&rb0));

  // ring buffer test 1
  /*
  []
  push([1, 2, 3])
  [1, 2, 3]
  pop(3) -> [1, 2, 3]
  []
  */
  printf("\n:test 1:\n");
  RingBuffer rb1;
  Init(&rb1, 5u);
  Print(&rb1);
  assert(Empty(&rb1));
  assert(Count(&rb1) == 0);
  assert(rb1.capacity == 5);
  const uint8_t expected_empty[5] = {0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu};
  assert(Equal(rb1.buf, expected_empty, 5));
  // simple push
  const uint8_t input1[3] = {1, 2, 3};
  assert(Push(&rb1, input1, 3));
  assert(!Empty(&rb1));
  assert(Count(&rb1) == 3);
  const uint8_t expected1[5] = {1, 2, 3, 0xFFu, 0xFFu};
  assert(Equal(rb1.buf, expected1, 5));
  // simple pop
  uint8_t pop1[3] = {0};
  assert(Pop(&rb1, pop1, 3));
  assert(Empty(&rb1));
  assert(Count(&rb1) == 0);
  assert(Equal(pop1, input1, 3));
  assert(Equal(rb1.buf, expected1, 5));
  // release
  Release(&rb1);
  assert(rb1.buf == NULL);
  assert(rb1.length == 0);

  // ring buffer test 2
  /*
  []
  push([10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
  [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
  pop(7) -> [10, 20, 30, 40, 50, 60, 70]
  [80, 90, 100]
  push([1, 2, 3, 4, 5, 6, 7])
  [80, 90, 100, 1, 2, 3, 4, 5, 6, 7]
  pop(1) -> [80]
  [90, 100, 1, 2, 3, 4, 5, 6, 7]
  */
  printf("\n:test 2:\n");
  RingBuffer rb2;
  Init(&rb2, 10);
  Print(&rb2);
  // push full
  const uint8_t input2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  assert(Push(&rb2, input2, 10));
  assert(Count(&rb2) == 10);
  assert(Equal(rb2.buf, input2, 10));
  // pop some
  uint8_t pop2[7] = {0};
  assert(Pop(&rb2, pop2, 7));
  assert(Count(&rb2) == 3);
  assert(Equal(pop2, input2, 3));
  assert(rb2.begin == 7);
  const uint8_t expected2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  assert(Equal(rb2.buf, expected2, 10));
  // push full again
  const uint8_t input3[7] = {1, 2, 3, 4, 5, 6, 7};
  assert(Push(&rb2, input3, 7));
  assert(Count(&rb2) == 10);
  const uint8_t expected3[] = {1, 2, 3, 4, 5, 6, 7, 80, 90, 100};
  assert(Equal(rb2.buf, expected3, 10));
  // pop one more
  assert(Pop(&rb2, pop2, 1));
  assert(Count(&rb2) == 9);
  assert(pop2[0] == 80);

  // release
  Release(&rb2);

  // ring buffer test 3
  /*
  [10, 20 ]
  pop(2) -> [ 10 20 ]
  [ ]
  */
  printf("\n:test 3:\n");
  RingBuffer rb3;
  Init(&rb3, 7);
  // setup
  const uint8_t input4[2] = {10, 20};
  rb3.buf[1] = input4[0];
  rb3.buf[2] = input4[1];
  rb3.begin = 1;
  rb3.length = 2;
  Print(&rb3);
  const uint8_t expected4[] = {0xFFu, 10, 20, 0xFFu, 0xFFu, 0xFFu, 0xFFu};
  assert(Equal(rb3.buf, expected4, 7u));
  // pop
  uint8_t pop3[2] = {0};
  assert(Pop(&rb3, pop3, 2));
  assert(Empty(&rb3));
  assert(Equal(rb3.buf, expected4, 7));
  assert(Equal(pop3, input4, 2));
  // release
  Release(&rb3);

  // ring buffer test 4
  /*
  [ ]
  push([ 10 20 30 40 50 60 ])
  [ 10 20 30 40 50 60 ]
  pop(5) -> [ 10 20 30 40 50 ]
  [ 60 ]
  */
  printf("\n:test 4:\n");
  RingBuffer rb4;
  Init(&rb4, 7);
  Print(&rb4);
  // setup
  const uint8_t input5[6] = {10, 20, 30, 40, 50, 60};
  rb4.begin = 5;
  assert(Push(&rb4, input5, 6));
  assert(Count(&rb4) == 6);
  const uint8_t expected5[7] = {30, 40, 50, 60, 0xFFu, 10, 20};
  assert(Equal(rb4.buf, expected5, 7));
  // pop
  uint8_t pop4[5] = {0};
  assert(Pop(&rb4, pop4, 5));
  assert(Count(&rb4) == 1);
  assert(rb4.begin == 3);
  const uint8_t expected6[5] = {10, 20, 30, 40, 50};
  assert(Equal(pop4, expected6, 5));
  // release
  Release(&rb4);

  // ring buffer test 5
  /*
  []
  push([1,2])
  [1, 2]
  push([3, 4])
  [2, 3, 4]
  pop(2) -> [2, 3]
  [4]
  */
  printf("\n:test 5:\n");
  RingBuffer rb5;
  Init(&rb5, 3);
  // setup
  const uint8_t input6[2] = {1, 2};
  rb5.begin = 1;
  Print(&rb5);
  assert(Push(&rb5, input6, 2));
  assert(Count(&rb5) == 2);
  const uint8_t expected7[3] = {0xFFu, 1, 2};
  assert(Equal(rb5.buf, expected7, 3));
  // push and override
  const uint8_t input7[2] = {3, 4};
  assert(Push(&rb5, input7, 2));
  assert(Count(&rb5) == 3);
  assert(rb5.begin == 2);
  const uint8_t expected8[3] = {3, 4, 2};
  assert(Equal(rb5.buf, expected8, 3));
  // pop
  uint8_t pop5[2] = {0};
  assert(Pop(&rb5, pop5, 2));
  const uint8_t expected9[3] = {2, 3};
  assert(Equal(pop5, expected9, 2));
  assert(Count(&rb5) == 1);
  assert(rb5.begin == 1);
  assert(Equal(rb5.buf, expected8, 3));
  // release
  Release(&rb5);

  // ring buffer test 6
  /*
  []
  push([1])
  [1]
  push([2])
  [2]
  pop(1) -> [2]
  []
  */
  printf("\n:test 6:\n");
  RingBuffer rb6;
  Init(&rb6, 1);
  Print(&rb6);
  // push full
  const uint8_t input8 = 1;
  assert(Push(&rb6, &input8, 1));
  assert(Count(&rb6) == 1);
  // push full again
  const uint8_t input9 = 2;
  assert(Push(&rb6, &input9, 1));
  assert(Count(&rb6) == 1);
  // pop
  uint8_t pop6;
  assert(Pop(&rb6, &pop6, 1));
  assert(pop6 == 2);
  assert(Empty(&rb6));
  // release
  Release(&rb6);

  // ring buffer test 7
  /*
  [1]
  push([2, 3, 4])
  [2, 3, 4]
  */
  printf("\n:test 7:\n");
  RingBuffer rb7;
  Init(&rb7, 3);
  // setup
  rb7.begin = 1;
  rb7.length = 1;
  rb7.buf[1] = 1;
  Print(&rb7);
  // push full
  const uint8_t input10[3] = {2, 3, 4};
  assert(Push(&rb7, input10, 3));
  assert(Count(&rb7) == 3);
  const uint8_t expected10[3] = {3, 4, 2};
  assert(Equal(rb7.buf, expected10, 3));
  // release
  Release(&rb7);

  puts("\nok");
  return 0;
}
