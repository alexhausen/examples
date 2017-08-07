#include <assert.h>
#include <stdint.h>
#include <stdio.h>

//TODO void WriteUint32LE(uint32_t in, uint8_t* out);
//TODO void WriteUint32BE(uint32_t in, uint8_t* out);

uint32_t ReadUint32LE(const uint8_t* data) {
/*
  printf("0x%08x ", data[0] << 0);
  printf("0x%08x ", data[1] << 8);
  printf("0x%08x ", data[2] << 16);
  printf("0x%08x\n", data[3] << 24);
*/
  return data[0] << 0 | data[1] << 8 | data[2] << 16 | data[3] << 24;
}

uint32_t ReadUint32BE(const uint8_t* data) {
/*
  printf("0x%08x ", data[3] << 0);
  printf("0x%08x ", data[2] << 8);
  printf("0x%08x ", data[1] << 16);
  printf("0x%08x\n", data[0] << 24);
*/
  return data[3] << 0 | data[2] << 8 | data[1] << 16 | data[0] << 24;
}

int main(void) {

  const uint8_t data_le[] = { 0xd2, 0x02, 0x96, 0x49 } ;
  uint32_t x = ReadUint32LE(data_le);
  assert(1234567890u == x);
  assert(0x499602d2u == x);

//  uint8_t out_le[4];
//  WriteUint32LE(1234567890u, out_le);
//  assert(memcmp(data_le, out_le, 4) == 0);

  const uint8_t data_be[] = { 0x49, 0x96, 0x02, 0xd2 };
  uint32_t y = ReadUint32BE(data_be);
  assert(1234567890u == y);
  assert(0x499602d2u == y);

//  uint8_t out_be[4];
//  WriteUint32BE(1234567890u, out_be);
//  assert(memcmp(data_be, out_be, 4) == 0);

//#if __x86__
//  assert(1234567890u == *((uint32_t*)data_le));
//#elif __ppc__
//  assert(1234567890u == *((uint32_t*)data_be));
//#endif

  puts("ok");

  return 0;
}
