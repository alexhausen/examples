
class Diogo {

static int crc16(byte[] buffer) {
	if (buffer == null) return 0;
	int crc = 0;
	for (int i = 0; i < buffer.length; i++) {
		short c = (short)buffer[i];
		crc ^= c << 8;
		for (int j = 8; j != 0 ; j--) {
			if ((crc & 0x8000) != 0) {
				crc = (crc<<1) ^ 0x3d65;
			}	
                  	else {
				crc = crc << 1;
			}
			crc = crc & 0xFFFF;
		}
	}
	return (int)crc;
}

public static void main(String[] args) {
	byte[] test = null;
	test = new byte[] {'a','d','m','i','n','6','b','8','b','4','5','6','7'};
	System.out.println(crc16(test));
}

}
