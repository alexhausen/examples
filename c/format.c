#include <stdio.h>

int main() {

	const char* string = "Hello world!";
	printf("[%.*s]\n", 5, string); /*Hello*/

	return 0;
}
