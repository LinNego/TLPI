/*实现readv(), writev()*/
/*调用read(),和write(), malloc()*/
/*需要保持原子性*/

#include "tlpi_hdr.h"
ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt) {
	size_t n = 0;
	for(int i = 0; i < iovcnt; ++i) {
		n += iov[i].iov_len;
	}
	char *buf = (char*)malloc(n);
	char *ptr = buf;
	ssize_t nread;
	if((nread = read(fd, buf, n)) == -1) {  
		errMsg("read");
		free(buf);
		return -1;
	}
	for(int i = 0; i < iovcnt; ++i)	 {
		memcpy(iov[i].iov_base, ptr, iov[i].iov_len);
		ptr += iov[i].iov_len;
	}
	free(buf);
	return nread;
}

ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt) {
	size_t n = 0;
	for(int i = 0; i < iovcnt; ++i) {
		n += iov[i].iov_len;
	}
	char *buf = (char*)malloc(n);
	char *ptr = buf;
	for(int i = 0; i < iovcnt; ++i)	{
		memcpy(ptr, iov[i].iov_base, iov[i].iov_len);
		ptr += iov[i].iov_len;
	}
	free(buf);
	ssize_t nwrite;
	if((nwrite = write(fd, buf, n)) == -1) {
		errMsg("write");
		return -1;
	}
	return nwrite;
}


int main(int argc, char *argv[]) {
	/*利用书本的代码测试自己的函数, 再增加测试my_writev的代码*/
	int fd;
    struct iovec iov[3];
    struct stat myStruct;       /* First buffer */
    int x;                      /* Second buffer */
#define STR_SIZE 100
    char str[STR_SIZE];         /* Third buffer */
    ssize_t numRead, totRequired, numWrite; /*测试my_writev*/

    if (argc != 3 || strcmp(argv[1], "--help") == 0) /*2 -> 3*/
        usageErr("%s <filename> <filename>\n", argv[0]);

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("open");

    totRequired = 0;

    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    totRequired += iov[2].iov_len;

    numRead = my_readv(fd, iov, 3);
    if (numRead == -1)
        errExit("readv");

    if (numRead < totRequired)
        printf("Read fewer bytes than requested\n");

    printf("total bytes requested: %ld; bytes read: %ld\n",
            (long) totRequired, (long) numRead);
	close(fd);
	
	fd = open("test2.txt", O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
	if(fd == -1) 
		errExit("open");
	numWrite = my_writev(fd, iov, 3)	;


    if (numWrite < totRequired)
        printf("Read fewer bytes than requested\n");

    printf("total bytes requested: %ld; bytes read: %ld\n",
            (long) totRequired, (long) numWrite);
	
	/*也许读入的文件和写出的文件的内容显示不同，但是字节数是相同的*/
	/*不是bug*/
    exit(EXIT_SUCCESS);
}
