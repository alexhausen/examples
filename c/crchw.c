// gcc -msse4.2 -Wall -Wextra crchw.c
// http://www.digsys.se/JavaScript/CRC.aspx
#include <stdio.h>
#include <nmmintrin.h>
#include <assert.h>

int main ()
{
    unsigned int crc1 = 0xffffffffu;
    unsigned char input[] = {
      'a', 'b', 'c', 'd'
    };
    int n = sizeof(input)/sizeof(input[0]);
    for (int i = 0; i < n; i++) {
      crc1 = _mm_crc32_u8(crc1, input[i]);
    }
    crc1 ^= 0xffffffffu;
    printf("CRC: 0x%08x\n", crc1);
    assert(crc1 == 0x92c80a31);

    unsigned int crc2 = 0xffffffffu;
    assert(n % 4 == 0);
    for (int i = 0; i < n; i += 4) {
      unsigned int* ptr = (unsigned int*)&input[i];
      crc2 = _mm_crc32_u32(crc2, *ptr);
    }
    crc2 ^= 0xffffffffu;
    printf("CRC: %08x\n", crc2);
    assert(crc2 == 0x92c80a31);
    puts("pass");
    return 0;
}
