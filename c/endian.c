#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void WriteUint32LE(uint32_t in, uint8_t* out) {
  out[0] = in & 0xFF;
  out[1] = (in >> 8) & 0xff;
  out[2] = (in >> 16) & 0xff;
  out[3] = in >> 24;
  printf("W LE: 0x%08x -> \"0x%02x%02x%02x%02x\"\n", in, out[0], out[1], out[2],
         out[3]);
}

void WriteUint32BE(uint32_t in, uint8_t* out) {
  out[0] = in >> 24;
  out[1] = (in >> 16) & 0xff;
  out[2] = (in >> 8) & 0xff;
  out[3] = in & 0xFF;
  printf("W BE: 0x%08x -> \"0x%02x%02x%02x%02x\"\n", in, out[0], out[1], out[2],
         out[3]);
}

uint32_t ReadUint32LE(const uint8_t* data) {
  uint32_t le = data[0] << 0 | data[1] << 8 | data[2] << 16 | data[3] << 24;
  printf("R LE: \"0x%02x%02x%02x%02x\" -> 0x%08x\n", data[0], data[1], data[2],
         data[3], le);
  return le;
}

uint32_t ReadUint32BE(const uint8_t* data) {
  uint32_t be = data[3] << 0 | data[2] << 8 | data[1] << 16 | data[0] << 24;
  printf("R BE: \"0x%02x%02x%02x%02x\" -> 0x%08x\n", data[0], data[1], data[2],
         data[3], be);
  return be;
}

int main(void) {
  // data 1234567890 is LE enconde
  const uint8_t data_le[] = {0xd2, 0x02, 0x96, 0x49};

  // data 1234567890 is BE enconde
  const uint8_t data_be[] = {0x49, 0x96, 0x02, 0xd2};

  // Read LE
  uint32_t le = ReadUint32LE(data_le);
  assert(1234567890u == le);
  assert(0x499602d2u == le);

  // Read BE
  uint32_t be = ReadUint32BE(data_be);
  assert(1234567890u == be);
  assert(0x499602d2u == be);

  // Write LE
  uint8_t out_le[4] = {0};
  WriteUint32LE(le, out_le);
  assert(memcmp(out_le, data_le, 4) == 0);

  // Write BE
  uint8_t out_be[4] = {0};
  WriteUint32BE(1234567890u, out_be);
  assert(memcmp(data_be, out_be, 4) == 0);

  //#if __x86__
  //  assert(1234567890u == *((uint32_t*)data_le));
  //#elif __ppc__
  //  assert(1234567890u == *((uint32_t*)data_be));
  //#endif

  puts("ok");

  return 0;
}
