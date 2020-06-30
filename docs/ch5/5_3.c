/*测试为啥那么O_APPEND是必要的*/
#include "tlpi_hdr.h"
/*O_APPEND 02000*/
int main(int argc, char *argv[]) {
	int is_append = 1 << 10, x = 0;
	if(argc < 3 || (argc == 4 && argv[3][0] != 'x')) {
		usageErr("./%s <filename> <num-bytes> [x]\n", argv[0]);
	}
	else if(argc == 4 && argv[3][0] == 'x')	{
		is_append <<= 1;
		x = 1;
	}
	int fd, nbyte, ret;
	if((nbyte = atoi(argv[2])) == -1) {
		errExit("atoi\n");
	}
	char buf[MAXLINE];
	memset(buf, 0, sizeof(buf));
	if((fd = open(argv[1], O_WRONLY | O_CREAT | (O_APPEND & is_append), S_IRUSR | S_IWUSR)) == -1) {
		errExit("open\n");
	}
	while(nbyte > 0) {
		if(x) {
			if((ret = lseek(fd, 0, SEEK_END)) == -1) {
				close(fd);
				errExit("lseek\n");
			}
		}

		if((ret = write(fd, buf, MAXLINE)) == -1)	{
			close(fd);
			errExit("write");
		}
		nbyte -= ret;
	}
	return 0;	
	
}
