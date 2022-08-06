#include <iostream>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

char* stack_memory() {
	const int stackSize = 65536;
	auto *stack = new (std::nothrow) char[stackSize];
	
	if (stack == nullptr) {
		printf("Cannot allocate memory \n");
		exit(EXIT_FAILURE);
	}

	return stack + stackSize;
}

int jail(void *args) {
	printf("Hello !! (child) \n");
	return EXIT_SUCCESS;
}

int main() {
	printf("Hello, world! (parent) \n");

	clone(jail, stack_memory(), SIGCHLD, 0);

	return EXIT_SUCCESS;
}
