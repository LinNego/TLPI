/*8_2.c 实现getpwnam();*/
#include "tlpi_hdr.h"
#include <string.h>
#include <pwd.h>
//struct passwd* getpwend(void);
//void setpwent(void);
//void endpwent(void);

struct passwd* my_getpwnam(const char *name) {
	struct passwd *pwd;
	while((pwd = getpwent()) != NULL) {
		if(!strcmp(pwd->pw_name, name)) {
			endpwent();
			return pwd;
		}
	}
	endpwent();
	return NULL;
}

int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "usage: filename <username>\n");
		return -1;
	}
	struct passwd *pwd = my_getpwnam(argv[1]);
	if(pwd != NULL) {
		printf("%s:%s:%ld:%ld:%s:%s:%s\n", pwd->pw_name, pwd->pw_passwd, pwd->pw_uid,
							pwd->pw_gid, pwd->pw_gecos, pwd->pw_dir, pwd->pw_shell);
	}
}
