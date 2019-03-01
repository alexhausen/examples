//gcc -msse4.2 -Wall -Wextra crchw.c

#include <stdio.h>
#include <nmmintrin.h>
#include <assert.h>

int main ()
{
    unsigned int crc1 = 1;
    unsigned char input[] = {
    0x47, 0, 4, 42, 0x01, 0x02, 0x3, 0x4,
    };
    int n = sizeof(input)/sizeof(input[0]);
    for (int i = 0; i < n; i++) {
      crc1 = _mm_crc32_u8(crc1, input[i]);
    }
    //printf("CRC: %08x\n", crc1);
    assert(crc1 == 0xd42a22cb);

    unsigned int crc2 = 1;
    assert(n % 4 == 0);
    for (int i = 0; i < n; i += 4) {
      unsigned int* ptr = (unsigned int*)&input[i];
      crc2 = _mm_crc32_u32(crc2, *ptr);
    }
    //printf("CRC: %08x\n", crc2);
    assert(crc2 == 0xd42a22cb);
    puts("pass");
    return 0;
}
