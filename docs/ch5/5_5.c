/*测试复制的文件描述符是否共享了文件偏移量和状态标志*/
#include "tlpi_hdr.h"

int main() {
	int oldfd, newfd;
	if((oldfd = open("test.txt", O_RDONLY)) == -1) errExit("open");
	if((newfd = dup(oldfd)) == -1) errExit("dup");
	int srcseek, dstseek, srcstate, dststate;
	if((srcseek = lseek(oldfd, 0, SEEK_CUR)) == -1) errExit("lseeksrc");
	if((dstseek = lseek(newfd, 0, SEEK_CUR)) == -1) errExit("lseekdst");
	printf("newfd: %d  oldfd: %d\n", dstseek, srcseek);
	if((srcstate = fcntl(oldfd, F_GETFL)) == -1) errExit("fcntlsrc");
	if((dststate = fcntl(newfd, F_GETFL)) == -1) errExit("fcntldst");
	printf("dststate: %d srcstate: %d\n", dststate, srcstate);
	return 0;
}
