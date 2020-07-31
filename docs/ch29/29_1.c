/*29_1*/
#include "tlpi_hdr.h"
#include <pthread.h>
#include <stdio.h>

int main() {
	if(pthread_join(pthread_self(), NULL)) {
		printf("...\n")	;
		return -1;
	}
	return 0;
}
