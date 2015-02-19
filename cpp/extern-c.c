#include "extern-c.h"

#ifdef __cplusplus
extern "C" {
#endif
int my_func() {
	return 0;
}
#ifdef __cplusplus
}
#endif

int main() {
	return my_func();
}