#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// compare results to https://www.lammertbies.nl/comm/info/crc-calculation.html

#define CRC16_GENERATOR 0xD175 // this is a good polynomial (HD=4) for CRC-16 with message size <= 32751 bits
                               // see: https://users.ece.cmu.edu/~koopman/crc/index.html
//#define CRC16_GENERATOR 0xA001 // mostly used polynomial, but it's a bad one

// lazy evaluated lookup table for performance
static bool table_init[256] = {false};
static int16_t table[256] = {0};

uint16_t get_value_from_table(uint8_t x) {
  if (table_init[x]) return table[x];
  
  uint16_t crc = x;
  for (int bit = 8; bit != 0; --bit) {
    bool lowbit = crc & 0x0001;
    crc >>= 1;
    if (lowbit) crc ^= CRC16_GENERATOR;
  }
  table[x] = crc;
  table_init[x] = true;
  return crc;
}

uint16_t crc16(const uint8_t* data, int n) {
  assert(data != NULL);
  assert(n >= 0);
  uint16_t crc = 0;
  for (int i = 0; i < n; ++i) {
    crc = (crc >> 8) ^ get_value_from_table((crc ^ data[i]) & 0xFF);
  }
  return crc;
}

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

int main() {

  const char* input1 = "abcdefghijklmnopqrstuvwxyz";
  uint16_t output1 = crc16((const uint8_t*)input1, strlen(input1));
  printf("crc '%s' = 0x%04X\n", input1, output1);
  assert(output1 == 0x71F9); // <- 0xD175
  //assert(output1 == 0x9C1D);

  const uint8_t input2[] = { 0 };
  uint16_t output2 = crc16(input2, ARRAY_SIZE(input2));
  printf("crc 0x%04X = 0x%04X\n", input2[0], output2);
  assert(output2 == 0);

  const uint8_t input3[] = { 1 };
  uint16_t output3 = crc16(input3, ARRAY_SIZE(input3));
  printf("crc 0x%04X = 0x%04X\n", input3[0], output3);
  assert(output3 == 0x93D0); // <- 0xD175
  //assert(output3 == 0xC0C1);

  const uint8_t input4[] = { 1 };
  uint16_t output4 = crc16(input4, 0);
  assert(output4 == 0);

  const uint8_t input5[] = {  0x47, 0x1, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6 };
  uint16_t output5 = crc16(input5, ARRAY_SIZE(input5));
  printf("crc (%lu) 0x%04X\n", ARRAY_SIZE(input5), output5);
  assert(output5 == 0x610A); // <- 0xD175


  return 0;
}
