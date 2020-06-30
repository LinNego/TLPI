/*5_2　实验一下O_APPEND*/
#include "tlpi_hdr.h"
int main() {
	int fd, seek;
	if((fd = open("test.txt", O_WRONLY | O_APPEND)) == -1) {
		errExit("open");
	}
	if((seek = lseek(fd, 0, SEEK_SET)) == -1) {
		close(fd);
		errExit("lseek");
	}
	char buf[10] = {
		"hello"
	};
	if(write(fd, buf, 10) == -1) {
		close(fd);
		errExit("write");
	}
	return 0;	
}
