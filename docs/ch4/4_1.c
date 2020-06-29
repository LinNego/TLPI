/*实现一个tee命令*/
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#ifndef MAXLINE
#define MAXLINE 4096
#endif


ssize_t Write(int fd, void *buf, size_t count) {
	size_t nleft = count;
	ssize_t nwrite;
	while(nleft > 0) {
		nwrite = write(fd, buf, nleft);
		if(nwrite < 0) {
			fprintf(stderr, "write: %s\n", strerror(errno));
			exit(-1);
		}
		else if(nwrite < 0 && errno == EINTR) {
			nwrite = 0;
		}
		nleft -= nwrite;
	}
	return count;
}

int main(int argc, char *argv[]) {
	int opt, is_append = 1 << 9;
	char *ptr = argv[1];
	while((opt = getopt(argc, argv, "a:")) != -1) {
		if(opt == 'a') {
			is_append <<= 1;	
			ptr = optarg;
		}
	}
	int fd, nread;
	//printf("%o %o\n", O_TRUNC & is_append, O_TRUNC);
	//printf("%o %o\n", O_APPEND & is_append, O_APPEND);
	if((fd = open(ptr, O_WRONLY | O_CREAT | (O_TRUNC & is_append) | (O_APPEND & is_append), S_IRUSR | S_IWUSR)) == -1)  {
		fprintf(stderr, "open: %s\n", strerror(errno));
		exit(1);
	}
	char buf[MAXLINE];
	while((nread = read(STDIN_FILENO, buf, MAXLINE)) > 0) {
		Write(STDOUT_FILENO, buf, nread) ;
		Write(fd, buf, nread);
	}
	close(fd);
	return 0;
}
