/*使用putenv()实现setenv()和unsetenv()*/

#include "tlpi_hdr.h"

extern char **environ;

int my_setenv(const char *name, const char *value, int overwrite) {
	if(name == NULL || value == NULL || strchr(name, '=') || strchr(value, '=')) return -1;
	if(overwrite) {
		size_t name_len = strlen(name), value_len = strlen(value);
		char *new_env = (char*)malloc(name_len + value_len + 2);
		if(new_env == NULL) return -1;
		strcpy(new_env, name);
		strcat(new_env, "=");
		strcat(new_env, value);
		if(putenv(new_env) == -1) return -1;
	}
	else if(!overwrite && getenv(name) == NULL) return -1;
	else return 0;
}

/*参考了答案*/
/*reference book answer*/
int unsetenv(const char *name) {
	char **sp, **cp;
	size_t len;
	for(cp = environ; *cp; ) {
		len = strlen(*cp);
		if(!strncmp(*cp, name, len) && (*cp)[len] == '=') {
			for(sp = cp; *sp; ++sp)	 {
				*sp = *(sp + 1);
			}
		}
		else ++cp;
	}
	return 0;
}

int main() {
	if (my_setenv("TT", "xxxx", 1) != 0)
        perror("putenv");
	return 0;
}

