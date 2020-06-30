/*实现dup函数*/
#include "tlpi_hdr.h"

int my_dup(int oldfd) {
	int newfd;
	if((newfd = fcntl(oldfd, F_DUPFD, 0)) == -1) {
		errExit("fcntl");
	}
	return newfd;
}

int my_dup2(int oldfd, int newfd) {
	if(oldfd == newfd) {
		if(fcntl(oldfd, F_GETFL) == -1) {
			return -1;
		}
		else return oldfd;
	}
	else {
		if(fcntl(newfd, F_GETFL) != -1) close(newfd);
		return fcntl(oldfd, F_DUPFD, newfd);
	}
}

int main() {
	int m, d;
	m = my_dup(1);
	close(m);
	d = dup(1);
	close(d);
	printf("my_dup:%d  dup:%d\n", m, d);
	m = my_dup2(1, 3);
	close(m);
	d = dup2(1, 3);
	close(d);
	printf("my_dup2%d  dup2%d\n", m, d);
	return 0;
}
