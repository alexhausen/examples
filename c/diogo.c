#include <string.h>
#include <stdio.h>

#define POLYNOME 0x3d65

unsigned short crc16(unsigned char *databuffer, int len) {
      unsigned char c;
      unsigned int crc = 0;
      int i;
      
      while(len--) {
            c=*databuffer;
            databuffer++;
            crc^=c<<8;
            for(i=8;i;i--) {
                  if(crc&0x8000){ crc=(crc<<1)^POLYNOME; } 
                  else { crc=crc<<1; } 
            }
      }
      return(crc);
}

int main() {
	char* test = "admin6b8b4567";
	printf("%d\n", crc16(test, strlen(test)));
	return 0;
}
