//20_2.c
//LinNego
#define _GNU_SOURCE
#include "tlpi_hdr.h"
#include <signal.h>

typedef void (*hander)(int);

int main() {
	sigset_t curset, oldset;
	sigemptyset(&curset);
	sigaddset(&curset, 10);
	sigaddset(&curset, 5);
	printSigset(stdout, "pending sigal\n", &curset);
	struct sigaction newact;
	newact.sa_handler = SIG_IGN;
	sigaction(10, &newact, NULL);
	sigaction(5, &newact, NULL);
	sigdelset(&curset, 10);
	sigdelset(&curset, 5);
	return 0;
}
