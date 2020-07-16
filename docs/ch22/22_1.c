//22_1 验证SIGCONT
//LinNego
#include "tlpi_hdr.h"

void handler(int sig) {
	printf("执行SIGCONT的信号处理器函数\n"); //unsafe
	return ;
}

int main(int argc, char *argv[]) {

	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	if(sigaction(SIGCONT, &act, NULL) == -1) errExit("sigaction error\n");
	sigset_t curset, preset;
	sigemptyset(&curset);
	sigaddset(&curset, SIGCONT);
	sigprocmask(SIG_BLOCK, &curset, &preset);
	printf("睡眠5秒\n");
	sleep(5);//睡眠期间发送SIGSTOP信号, 再发送SIGCONT信号
	//printSigset(stdout, "SIGCONT处于阻塞前的处置\n", &curset);
	printf("不阻塞了\n");
	//pause();
	sigprocmask(SIG_BLOCK, &preset, NULL);
	printf("睡眠5秒\n");
	sleep(5); //发送SIGSTOP信号,再发送SIGCONT信号
	//printSigset(stdout, "SIGCONT处于不阻塞的处置\n", &preset);
	return 0;
}
