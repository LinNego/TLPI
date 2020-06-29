/*实现一个小cp,并且保证源文件和目的文件的空洞大小相同*/
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
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
	if(argc != 3) {
		fprintf(stderr, "usage <src file> <dst file>\n");
		exit(0);
	}
	int dfd, sfd;
	if(!strcmp(argv[1], argv[2])) {
		fprintf(stderr, "%s as same as %s\n", argv[1], argv[2]);
	}
	if((sfd = open(argv[1], O_RDONLY)) == -1)  {
		fprintf(stderr, "open: %s\n", strerror(errno));
		exit(0);
	}
	if((dfd == open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1) {
		fprintf(stderr, "open: %s\n", strerror(errno));
		exit(0);
	}
	size_t nread = 0;
	char buf[MAXLINE];
	while((nread = read(fd, buf, MAXLINE)) > 0) {
		Write(fd, buf, nread);
	}
	return 0;
}
