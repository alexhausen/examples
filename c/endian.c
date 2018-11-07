#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void WriteUint16LE(uint16_t in, uint8_t* out) {
  assert(out != NULL);
  out[0] = in & 0x00FFu;
  out[1] = (in & 0xFF00u) >> 8;
  printf("W 16 LE: 0x%04x -> \"0x%02x%02x\"\n", in, out[0], out[1]);
}

void WriteUint16BE(uint16_t in, uint8_t* out) {
  assert(out != NULL);
  out[0] = (in & 0xFF00u) >> 8;
  out[1] = in & 0x00FFu;
  printf("W 16 BE: 0x%04x -> \"0x%02x%02x\"\n", in, out[0], out[1]);
}

uint16_t ReadUint16LE(const uint8_t* data) {
  assert(data != NULL);
  uint16_t le = data[0] << 0 | data[1] << 8;
  printf("R 16 LE: \"0x%02x%02x\" -> 0x%04x\n", data[0], data[1], le);
  return le;
}

uint16_t ReadUint16BE(const uint8_t* data) {
  assert(data != NULL);
  uint16_t be = data[0] << 8 | data[1] << 0;
  printf("R 16 BE: \"0x%02x%02x\" -> 0x%04x\n", data[0], data[1], be);
  return be;
}

void WriteUint32LE(uint32_t in, uint8_t* out) {
  assert(out != NULL);
  out[0] = in & 0xFF;
  out[1] = (in >> 8) & 0xff;
  out[2] = (in >> 16) & 0xff;
  out[3] = in >> 24;
  printf("W 32 LE: 0x%08x -> \"0x%02x%02x%02x%02x\"\n", in, out[0], out[1], out[2],
         out[3]);
}

void WriteUint32BE(uint32_t in, uint8_t* out) {
  assert(out != NULL);
  out[0] = in >> 24;
  out[1] = (in >> 16) & 0xff;
  out[2] = (in >> 8) & 0xff;
  out[3] = in & 0xFF;
  printf("W 32 BE: 0x%08x -> \"0x%02x%02x%02x%02x\"\n", in, out[0], out[1], out[2],
         out[3]);
}

uint32_t ReadUint32LE(const uint8_t* data) {
  assert(data != NULL);
  uint32_t le = data[0] << 0 | data[1] << 8 | data[2] << 16 | data[3] << 24;
  printf("R 32 LE: \"0x%02x%02x%02x%02x\" -> 0x%08x\n", data[0], data[1], data[2],
         data[3], le);
  return le;
}

uint32_t ReadUint32BE(const uint8_t* data) {
  assert(data != NULL);
  uint32_t be = data[3] << 0 | data[2] << 8 | data[1] << 16 | data[0] << 24;
  printf("R32  BE: \"0x%02x%02x%02x%02x\" -> 0x%08x\n", data[0], data[1], data[2],
         data[3], be);
  return be;
}

int main(void) {

  // data 43981 LE encoded
  const uint8_t data16_le[] = { 0xcd, 0xab };

  // data 43981 BE encoded
  const uint8_t data16_be[] = { 0xab, 0xcd };

  // Read LE
  uint16_t le16 = ReadUint16LE(data16_le);
  assert(0xabcd == le16);

  // Read BE
  uint16_t be16 = ReadUint16BE(data16_be);
  assert(0xabcd == be16);

  // Write LE
  uint8_t out16_le[2] = {0};
  WriteUint16LE(le16, out16_le);
  assert(memcmp(out16_le, data16_le, 2) == 0);

  // Write BE
  uint8_t out16_be[2] = {0};
  WriteUint16BE(be16, out16_be);
  assert(memcmp(out16_be, data16_be, 2) == 0);

  // data 1234567890 LE enconde
  const uint8_t data32_le[] = {0xd2, 0x02, 0x96, 0x49};

  // data 1234567890 BE enconde
  const uint8_t data32_be[] = {0x49, 0x96, 0x02, 0xd2};

  // Read LE
  uint32_t le32 = ReadUint32LE(data32_le);
  assert(1234567890u == le32);
  assert(0x499602d2u == le32);

  // Read BE
  uint32_t be32 = ReadUint32BE(data32_be);
  assert(1234567890u == be32);
  assert(0x499602d2u == be32);

  // Write LE
  uint8_t out32_le[4] = {0};
  WriteUint32LE(le32, out32_le);
  assert(memcmp(out32_le, data32_le, 4) == 0);

  // Write BE
  uint8_t out32_be[4] = {0};
  WriteUint32BE(1234567890u, out32_be);
  assert(memcmp(data32_be, out32_be, 4) == 0);

  //#if __x86__
  //  assert(1234567890u == *((uint32_t*)data32_le));
  //#elif __ppc__
  //  assert(1234567890u == *((uint32_t*)data32_be));
  //#endif

  puts("ok");

  return 0;
}
