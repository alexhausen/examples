#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int split(const char* data) {
	if (!data || strlen(data) == 0) return 0;
	int i = 0;
	char* temp = strdup(data);
	char* curr = temp;

	while (curr) {
		char* next = strchr(curr + 1, ':');
		if (next) {
			*next = '\0';
			next++;
		}
		printf("%s ", curr);
		++i;
		curr = next;
	}
	printf("\n");
	free(temp);
	return i;	
}

int main() {
	const char* str1 = "a1:b2:c3:d4";
	const char* str2 = "abc";
	const char* str3 = (char*) 0;
	const char* str4 = "";
	assert(split(str3) == 0);
	assert(split(str2) == 1);
	assert(split(str1) == 4);
	assert(split(str4) == 0);
}