#include <iostream>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

char* stack_memory() {
	const int stackSize = 65536;
	auto *stack = new (std::nothrow) char[stackSize];
	
	if (stack == nullptr) {
		printf("Cannot allocate memory \n");
		exit(EXIT_FAILURE);
	}

	return stack + stackSize;
}

template <typename... P>
int run(P... params) {
	char *args[] = {(char *)params..., (char *)0};
	return execvp(args[0], args);
}

void setup_variables() {
	clearenv();
	setenv("TERM", "xterm-256color", 0);
	setenv("PATH", "/bin/:/sbin/:usr/bin:/usr/sbin", 0);
}

void setup_root(const char* folder) {
	chroot(folder);
	chdir("/");
}

int jail(void *args) {
	printf("child process: %d \n", getpid());

	setup_variables();
	setup_root("./root");

	run("/bin/sh");
	return EXIT_SUCCESS;
}

int main() {
	printf("parent process: %d \n", getpid());
	int error_code = clone(jail, stack_memory(), CLONE_NEWPID | CLONE_NEWUTS | SIGCHLD, 0);
	if (error_code <= -1) {
		printf("Sempai something went wrong!:\n%s \n", strerror(errno));
	}
	wait(nullptr);
	return EXIT_SUCCESS;
}
