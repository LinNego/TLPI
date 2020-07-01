/*错误的代码*/
/*不当使用setjmp(), longjum()*/
#include "tlpi_hdr.h"

jmp_buf env;

void X() {
	printf("错误即将到来, 准备跳入不存在的栈帧\n");
	longjmp(env, 3);
}

void Y() {
	int x = 5;
	printf("错误的道路\n");
	setjmp(env);	
	printf("x: %d\n", x);
}
int main() {
	Y();
	X();
	return 0;
}
