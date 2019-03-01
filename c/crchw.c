//gcc -msse4.2 -Wall -Wextra crchw.c

#include <stdio.h>
#include <nmmintrin.h>

int main ()
{
    unsigned int crc = 1;
    unsigned char input[] = {
    0x47, 0, 4, 42, 0x01, 0x02, 0x3, 0x4,
    };
    int n = sizeof(input)/sizeof(input[0]);
    for (int i = 0; i < n; i++) {
      crc = _mm_crc32_u8(crc, input[i]);
    }
    printf("CRC: %08x\n", crc);

    crc = 1;
    n /= 4;
    for (int i = 0; i < n; i++) {
      unsigned int* ptr = (unsigned int*)&input[i*4];
      crc = _mm_crc32_u32(crc, *ptr);
    }
    printf("CRC: %08x\n", crc);

    return 0;
}
