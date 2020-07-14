/*20_1* 实现一个abort() 有可能有bug*/
//LinNego
#include "tlpi_hdr.h"
//调用abort()意味着想要达到结果是退出程序，或者是捕获了SIGARRT信号并调用了非本地跳转的函数
void my_abort() {
	sigset_t blockset, preset;
	pid_t pid = getpid();
	kill(pid, SIGABRT);//向自身发送信号，理论上不会返回错误值
	while(sigfillset(&blockset) == -1) continue;
	while(sigdelset(&blockset, SIGABRT) == -1) continue;
	while(sigprocmask(SIG_BLOCK, &blockset, &preset) == -1) continue;
	/*运行到这里时，证明SIGABRT已经执行完，剩下的就是刷新缓冲区和退出进程*/
	/*所以阻塞所有信号,虽然有些信号阻塞也没用，但通常不能阻塞的信号是退出程序的信号*/
	/*调用exit(1)而不是_exit(),原因需要刷新stdout，阻塞了所有信号后，也变的安全*/
	/*上述个人理解*/
	/*如果返回的是-1，exit()调用失败*/
	struct sigaction act;
	act.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &act, NULL);
	kill(pid, SIGABRT);
}

void handler(int sig) {
	printf("SIGABRT处理\n");
}

int main() {
	printf("运行\n");
	struct sigaction act;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if(sigaction(SIGABRT, &act, NULL) == -1) printf("sig错误\n");
	my_abort();
	printf("不应该运行到这里\n");
	return -1;
}
