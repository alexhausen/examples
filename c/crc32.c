// CRC-32 Castagnoli Reversed (0x82F63B78)
// compare results to http://www.digsys.se/JavaScript/CRC.aspx or
// http://checksumcalc.live.conceptcontrols.com/
// compile: gcc -msse4.2 -Wall -Wextra crc32.c
// usage: crc32 <input> <output>

#include <nmmintrin.h>

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CRC32_INITIAL 0xFFFFFFFFu
#define CRC32_XOR_OUT 0xFFFFFFFFu
#define CRC32_POLYNOMIAL 0x82F63B78u

static const uint32_t crc_table[256] = {
    0x00000000u, 0xf26b8303u, 0xe13b70f7u, 0x1350f3f4u, 0xc79a971fu,
    0x35f1141cu, 0x26a1e7e8u, 0xd4ca64ebu, 0x8ad958cfu, 0x78b2dbccu,
    0x6be22838u, 0x9989ab3bu, 0x4d43cfd0u, 0xbf284cd3u, 0xac78bf27u,
    0x5e133c24u, 0x105ec76fu, 0xe235446cu, 0xf165b798u, 0x030e349bu,
    0xd7c45070u, 0x25afd373u, 0x36ff2087u, 0xc494a384u, 0x9a879fa0u,
    0x68ec1ca3u, 0x7bbcef57u, 0x89d76c54u, 0x5d1d08bfu, 0xaf768bbcu,
    0xbc267848u, 0x4e4dfb4bu, 0x20bd8edeu, 0xd2d60dddu, 0xc186fe29u,
    0x33ed7d2au, 0xe72719c1u, 0x154c9ac2u, 0x061c6936u, 0xf477ea35u,
    0xaa64d611u, 0x580f5512u, 0x4b5fa6e6u, 0xb93425e5u, 0x6dfe410eu,
    0x9f95c20du, 0x8cc531f9u, 0x7eaeb2fau, 0x30e349b1u, 0xc288cab2u,
    0xd1d83946u, 0x23b3ba45u, 0xf779deaeu, 0x05125dadu, 0x1642ae59u,
    0xe4292d5au, 0xba3a117eu, 0x4851927du, 0x5b016189u, 0xa96ae28au,
    0x7da08661u, 0x8fcb0562u, 0x9c9bf696u, 0x6ef07595u, 0x417b1dbcu,
    0xb3109ebfu, 0xa0406d4bu, 0x522bee48u, 0x86e18aa3u, 0x748a09a0u,
    0x67dafa54u, 0x95b17957u, 0xcba24573u, 0x39c9c670u, 0x2a993584u,
    0xd8f2b687u, 0x0c38d26cu, 0xfe53516fu, 0xed03a29bu, 0x1f682198u,
    0x5125dad3u, 0xa34e59d0u, 0xb01eaa24u, 0x42752927u, 0x96bf4dccu,
    0x64d4cecfu, 0x77843d3bu, 0x85efbe38u, 0xdbfc821cu, 0x2997011fu,
    0x3ac7f2ebu, 0xc8ac71e8u, 0x1c661503u, 0xee0d9600u, 0xfd5d65f4u,
    0x0f36e6f7u, 0x61c69362u, 0x93ad1061u, 0x80fde395u, 0x72966096u,
    0xa65c047du, 0x5437877eu, 0x4767748au, 0xb50cf789u, 0xeb1fcbadu,
    0x197448aeu, 0x0a24bb5au, 0xf84f3859u, 0x2c855cb2u, 0xdeeedfb1u,
    0xcdbe2c45u, 0x3fd5af46u, 0x7198540du, 0x83f3d70eu, 0x90a324fau,
    0x62c8a7f9u, 0xb602c312u, 0x44694011u, 0x5739b3e5u, 0xa55230e6u,
    0xfb410cc2u, 0x092a8fc1u, 0x1a7a7c35u, 0xe811ff36u, 0x3cdb9bddu,
    0xceb018deu, 0xdde0eb2au, 0x2f8b6829u, 0x82f63b78u, 0x709db87bu,
    0x63cd4b8fu, 0x91a6c88cu, 0x456cac67u, 0xb7072f64u, 0xa457dc90u,
    0x563c5f93u, 0x082f63b7u, 0xfa44e0b4u, 0xe9141340u, 0x1b7f9043u,
    0xcfb5f4a8u, 0x3dde77abu, 0x2e8e845fu, 0xdce5075cu, 0x92a8fc17u,
    0x60c37f14u, 0x73938ce0u, 0x81f80fe3u, 0x55326b08u, 0xa759e80bu,
    0xb4091bffu, 0x466298fcu, 0x1871a4d8u, 0xea1a27dbu, 0xf94ad42fu,
    0x0b21572cu, 0xdfeb33c7u, 0x2d80b0c4u, 0x3ed04330u, 0xccbbc033u,
    0xa24bb5a6u, 0x502036a5u, 0x4370c551u, 0xb11b4652u, 0x65d122b9u,
    0x97baa1bau, 0x84ea524eu, 0x7681d14du, 0x2892ed69u, 0xdaf96e6au,
    0xc9a99d9eu, 0x3bc21e9du, 0xef087a76u, 0x1d63f975u, 0x0e330a81u,
    0xfc588982u, 0xb21572c9u, 0x407ef1cau, 0x532e023eu, 0xa145813du,
    0x758fe5d6u, 0x87e466d5u, 0x94b49521u, 0x66df1622u, 0x38cc2a06u,
    0xcaa7a905u, 0xd9f75af1u, 0x2b9cd9f2u, 0xff56bd19u, 0x0d3d3e1au,
    0x1e6dcdeeu, 0xec064eedu, 0xc38d26c4u, 0x31e6a5c7u, 0x22b65633u,
    0xd0ddd530u, 0x0417b1dbu, 0xf67c32d8u, 0xe52cc12cu, 0x1747422fu,
    0x49547e0bu, 0xbb3ffd08u, 0xa86f0efcu, 0x5a048dffu, 0x8ecee914u,
    0x7ca56a17u, 0x6ff599e3u, 0x9d9e1ae0u, 0xd3d3e1abu, 0x21b862a8u,
    0x32e8915cu, 0xc083125fu, 0x144976b4u, 0xe622f5b7u, 0xf5720643u,
    0x07198540u, 0x590ab964u, 0xab613a67u, 0xb831c993u, 0x4a5a4a90u,
    0x9e902e7bu, 0x6cfbad78u, 0x7fab5e8cu, 0x8dc0dd8fu, 0xe330a81au,
    0x115b2b19u, 0x020bd8edu, 0xf0605beeu, 0x24aa3f05u, 0xd6c1bc06u,
    0xc5914ff2u, 0x37faccf1u, 0x69e9f0d5u, 0x9b8273d6u, 0x88d28022u,
    0x7ab90321u, 0xae7367cau, 0x5c18e4c9u, 0x4f48173du, 0xbd23943eu,
    0xf36e6f75u, 0x0105ec76u, 0x12551f82u, 0xe03e9c81u, 0x34f4f86au,
    0xc69f7b69u, 0xd5cf889du, 0x27a40b9eu, 0x79b737bau, 0x8bdcb4b9u,
    0x988c474du, 0x6ae7c44eu, 0xbe2da0a5u, 0x4c4623a6u, 0x5f16d052u,
    0xad7d5351u,
};

/*
//used to generate the table above
void print_table(void) {
  printf("{");
  for (int i = 0; i < 256; ++i) {
    if (i % 8 == 0) printf("\n");
    printf("0x%08xu, ", crc_table[i]);
  }
  printf("}\n");
}

void make_table(void) {
  for (int i = 0; i < 256; ++i) {
    uint32_t crc = i;
    for (int j = 8; j != 0; --j) {
      bool low_bit = crc & 1;
      crc >>= 1;
      if (low_bit) crc ^= CRC32_POLYNOMIAL;
    }
    crc_table[i] = crc;
  }
}
*/

// Performs Hardware CRC operations
uint32_t crc32c_hw(const uint8_t* buffer, size_t size) {
  uint32_t crc = CRC32_INITIAL;
  for (size_t i = 0; i < size; ++i) {
    crc = _mm_crc32_u8(crc, buffer[i]);
  }
  return crc ^ CRC32_XOR_OUT;
}

// FIXME: assertion fail
// Performs Hardware CRC operations Optimized
uint32_t crc32c_hw_opt(const uint8_t* buffer, size_t size) {
  uint32_t crc = CRC32_INITIAL;

  // align input buffer
  uintptr_t size_to_align = (uintptr_t)buffer & 3;
  for (size_t i = 0; i < size_to_align; ++i) {
    crc = _mm_crc32_u8(crc, buffer[i]);
  }
  buffer += size_to_align;
  size -= size_to_align;

  // optimized part
  size_t size_words = size / 4;
  const uint32_t* words_ptr = (const uint32_t*)buffer + size_to_align;
  for (size_t i = 0; i < size_words; ++i) {
    crc = _mm_crc32_u32(crc, words_ptr[i]);
    buffer += 4;
  }

  size_t size_rest = size & 3;
  for (size_t i = 0; i < size_rest; ++i) {
    crc = _mm_crc32_u8(crc, buffer[i]);
  }

  // for (size_t i = 0; i < size; ++i) {
  //   crc = _mm_crc32_u32(crc, buffer[i]);
  // }
  return crc ^ CRC32_XOR_OUT;
}

// Slow Software CRC32C
uint32_t crc32c_sw_slow(const uint8_t* buffer, size_t size) {
  uint32_t crc = CRC32_INITIAL;
  for (size_t i = 0; i < size; ++i) {
    crc ^= buffer[i];
    for (int j = 8; j != 0; --j) {
      bool low_bit = crc & 1;
      crc >>= 1;
      if (low_bit) crc ^= CRC32_POLYNOMIAL;
    }
  }
  return crc ^ CRC32_XOR_OUT;
}

// Fast Software CRC32C (uses a precomputed table)
uint32_t crc32c_sw_fast(const uint8_t* buffer, size_t size) {
  uint32_t crc = CRC32_INITIAL;
  for (size_t i = 0; i < size; ++i) {
    uint8_t x = (crc & 0xFFu) ^ buffer[i];
    crc = (crc >> 8) ^ crc_table[x];
  }
  return crc ^ CRC32_XOR_OUT;
}

// Fast Software CRC32C (table + loop unrooling)
uint32_t crc32c_sw_fast2(const uint8_t* buffer, size_t size) {
  uint32_t crc = CRC32_INITIAL;

  // align input buffer
  uintptr_t size_to_align = (uintptr_t)buffer & 3;
  for (size_t i = 0; i < size_to_align; ++i) {
    crc = (crc >> 8) ^ crc_table[((crc & 0xFFu) ^ buffer[i])];
  }
  buffer += size_to_align;
  size -= size_to_align;

  // unrool loop
  uint32_t remaining_size = size & 3;
  size -= remaining_size;
  const uint32_t* word_ptr = (const uint32_t*)buffer;
  for (size_t i = 0; i < size; i += 4) {
    const uint32_t word = *word_ptr;
    uint8_t byte0 = word & 0xFFu;
    uint8_t byte1 = (word >> 8) & 0xFFu;
    uint8_t byte2 = (word >> 16) & 0xFFu;
    uint8_t byte3 = (word >> 24) & 0xFFu;
    crc = (crc >> 8) ^ crc_table[((crc & 0xFFu) ^ byte0)];
    crc = (crc >> 8) ^ crc_table[((crc & 0xFFu) ^ byte1)];
    crc = (crc >> 8) ^ crc_table[((crc & 0xFFu) ^ byte2)];
    crc = (crc >> 8) ^ crc_table[((crc & 0xFFu) ^ byte3)];
    ++word_ptr;
  }

  // remaining
  buffer += size;
  for (size_t i = 0; i < remaining_size; ++i) {
    crc = (crc >> 8) ^ crc_table[((crc & 0xFFu) ^ buffer[i])];
  }

  return crc ^ CRC32_XOR_OUT;
}

typedef uint32_t os_uint32_t;
typedef uint8_t os_uint8_t;
typedef size_t os_size_t;
void CRC_Crc32cUpdate(os_uint32_t* crc, const os_uint32_t* buffer,
                      os_size_t size) {
  os_uint32_t temp_crc = *crc;
  // temp_crc ^= 0xffffffffu;
  os_size_t num_words = size / 4;
  for (os_size_t i = 0; i < num_words; i += 4) {
    const os_uint32_t word = *buffer;
    os_uint8_t byte0 = word & 0xffu;
    os_uint8_t byte1 = (word >> 8) & 0xffu;
    os_uint8_t byte2 = (word >> 16) & 0xffu;
    os_uint8_t byte3 = (word >> 24) & 0xffu;
    temp_crc = (temp_crc >> 8) ^ crc_table[(temp_crc & 0xffu) ^ byte0];
    temp_crc = (temp_crc >> 8) ^ crc_table[(temp_crc & 0xffu) ^ byte1];
    temp_crc = (temp_crc >> 8) ^ crc_table[(temp_crc & 0xffu) ^ byte2];
    temp_crc = (temp_crc >> 8) ^ crc_table[(temp_crc & 0xffu) ^ byte3];
    ++buffer;
  }
  temp_crc ^= 0xffffffffu;
  *crc = temp_crc;
}

void crc32c_update(uint32_t* crc, const uint8_t* buffer, size_t size) {
  *crc ^= CRC32_INITIAL;
  for (size_t i = 0; i < size; ++i) {
    uint8_t x = (*crc & 0xFFu) ^ buffer[i];
    *crc = (*crc >> 8) ^ crc_table[x];
  }
  *crc ^= CRC32_XOR_OUT;
}

typedef uint32_t (*crc_fn)(const uint8_t*, size_t);

static crc_fn crc32c = crc32c_hw;

int main(int argc, char** argv) {
  if (argc == 1) {
    // make_table();
    // print_table();
    const char* input0 = "";
    uint32_t crc0 = crc32c((const uint8_t*)input0, strlen(input0));
    assert(0x00000000 == crc0);

    const char* input1 = "a";
    uint32_t crc1 = crc32c((const uint8_t*)input1, strlen(input1));
    assert(0xC1D04330 == crc1);

    const char* input1_1 = "abc";
    uint32_t crc1_1 = crc32c((const uint8_t*)input1_1, strlen(input1_1));
    assert(0x364B3FB7 == crc1_1);

    const char* input1_2 = "abcd";
    uint32_t crc1_2 = crc32c((const uint8_t*)input1_2, strlen(input1_2));
    assert(0x92C80A31 == crc1_2);

    const char* input2 = "abcdefghijklmnopqrstuvwxyz";
    uint32_t crc2 = crc32c((const uint8_t*)input2, strlen(input2));
    assert(0x9EE6EF25 == crc2);

    const char* input2_1 = "abcdef";
    uint32_t crc2_1 =
        crc32c((const uint8_t*)&input2_1[2], 4);  // strlen(input2_1));
    assert(0x74EAFE62 == crc2_1);

    const char* input2_2 = "abcdefg";
    uint32_t crc2_2 = crc32c((const uint8_t*)input2_2, strlen(input2_2));
    // printf("0x%0x\n", crc2_2);
    assert(0xE627F441 == crc2_2);

    const uint8_t input2_3[] = {0x91, 0x00, 0x00, 0x2f};
    uint32_t crc2_3 = crc32c(input2_3, sizeof(input2_3));
    assert(0x50482B87 == crc2_3);

    const uint8_t input2_4[] = {0x91, 0x00, 0x00, 0x2f, 0xd9, 0x22, 0x70, 0x70};
    uint32_t crc2_4 = crc32c(input2_4, sizeof(input2_4));
    assert(0x585327D7 == crc2_4);

    const uint8_t input2_5[] = {
        0x91, 0x00, 0x00, 0x2F, 0xD9, 0x22, 0x70, 0x70, 0x54, 0x22, 0x91, 0x00,
        0x00, 0x3F, 0xD9, 0x33, 0x74, 0x70, 0x54, 0x33, 0x37, 0x03, 0x62, 0x31,
        0x37, 0x02, 0x61, 0x40, 0x37, 0x02, 0x78, 0x54, 0x8F, 0x85, 0x00, 0x50,
        0x37, 0x35, 0x02, 0x51, 0xB7, 0xF5, 0x04, 0x52, 0x37, 0x45, 0x01, 0x50,
        0xB7, 0x05, 0x81, 0x50, 0x74, 0x25, 0xB7, 0x15, 0x81, 0x50, 0xB7, 0x05,
        0x01, 0x50, 0xB7, 0x05, 0x02, 0x51, 0x74, 0x25, 0x54, 0x25, 0x54, 0x32};
    uint32_t crc2_5 = crc32c(input2_5, sizeof(input2_5));
    assert(0x524A3D29 == crc2_5);

    const char* input3_1 = "abcdefghijklm";
    const char* input3_2 = "nopqrstuvwxyz";
    uint32_t crc3 = 0;
    crc32c_update(&crc3, (const uint8_t*)input3_1, strlen(input3_1));
    assert(0x5FDBF778 == crc3);
    crc32c_update(&crc3, (const uint8_t*)input3_2, strlen(input3_2));
    assert(0x9EE6EF25 == crc3);

    uint32_t crc4 = 0;
    crc32c_update(&crc4, NULL, 0);
    assert(0 == crc4);

    puts("ok");

  } else if (argc == 3) {
    FILE* fp_in = fopen(argv[1], "rb");
    if (!fp_in) {
      printf("Error: open input file '%s'.", argv[1]);
      return 1;
    }
    fseek(fp_in, 0L, SEEK_END);
    long sz = ftell(fp_in);
    if (sz <= 0) {
      printf("Error: input file '%s' size: %ld.", argv[1], sz);
      fclose(fp_in);
      return 1;
    }
    unsigned long usz = (unsigned long)sz;
    if (usz > SIZE_MAX) {
      printf("Error: input file '%s' too large: %ld.", argv[1], sz);
      fclose(fp_in);
      return 1;
    }
    size_t size_in = (size_t)usz;
    rewind(fp_in);
    uint8_t* buffer = (uint8_t*)malloc(size_in);
    int c;
    int i = 0;
    while ((c = fgetc(fp_in)) != EOF) {
      buffer[i++] = (uint8_t)c;
    }
    uint32_t crc = crc32c(buffer, size_in);
    fclose(fp_in);

    FILE* fp_out = fopen(argv[2], "wb");
    if (!fp_out) {
      printf("Error: open file '%s'.", argv[1]);
      return 1;
    }
    fprintf(fp_out, "0x%0X", crc);
    fclose(fp_out);

  } else {
    puts("usage: exe <input file> <output file>\n");
    return 1;
  }

  return 0;
}
