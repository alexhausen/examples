/* timer test */

#include <stdio.h>
#include <time.h>

// man timer_create

int main() {

	time_t start_time = time(NULL);
	
	time_t end_time = time(NULL);
	printf("start time: %s\n", asctime(localtime(&start_time)));
	printf("end time: %s\n", asctime(localtime(&end_time)));
	return 0;
}

