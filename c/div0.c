#include <stdio.h>
void main() {
	printf("%f\n", 5.0/0.0); /* inf */
	printf("%d\n", 5/0); /* UB (undefined behaviour) */
}
