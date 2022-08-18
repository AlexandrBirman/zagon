#include <iostream>
#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <fstream>

#define CGROUP_FOLDER "/sys/fs/cgroup/pids/container/"
#define concat(a,b) (a"" b)

void write_rule(const char* path, const char* value) {
	int fp = open(path, O_WRONLY | O_APPEND);
	write(fp, value, strlen(value));
	close(fp);
}

void limitProcessCreation() {
	int err = mkdir(CGROUP_FOLDER, S_IRUSR | S_IWUSR);
	if (err < 0) {
		printf("fuuuuuck: %s \n",strerror(err));
		//exit(EXIT_FAILURE);
	}
	const char* pid = std::to_string(getpid()).c_str();
	write_rule(concat(CGROUP_FOLDER, "cgroup.procs"), pid);
	write_rule(concat(CGROUP_FOLDER, "notify_on_release"), "1");
	write_rule(concat(CGROUP_FOLDER, "pids.max"), "5");
}

char* stack_memory() { 
	const int stackSize = 65536;
	auto *stack = new (std::nothrow) char[stackSize];
	
	if (stack == nullptr) {
		printf("Cannot allocate memory \n");
		exit(EXIT_FAILURE);
	}

	return stack + stackSize;
}

void setHostName(std::string hostname) {
	sethostname(hostname.c_str(), hostname.size());
}

void setup_variables() {
	clearenv();
	setenv("TERM", "xterm-256color", 0);
	setenv("PATH", "/bin/:/sbin/:usr/bin:/usr/sbin", 0);
}

template <typename... P>
int run(P... params) {
	char *args[] = {(char *)params..., (char *)0};
	return execvp(args[0], args);
}

void setup_root(const char* folder) {
	chroot(folder);
	chdir("/");
}

template <typename Function>
void clone_process(Function&& function, int flags) {
	auto pid = clone(function, stack_memory(), flags, 0);

	wait(nullptr);
}

int jail(void *args) {
	limitProcessCreation();

	printf("child process: %d \n", getpid());

	setHostName("my-container");
	setup_variables();
	setup_root("./root");
	mount("proc", "/proc", "proc", 0, 0);

	auto runThis = [](void *args) ->int { run("bin/sh"); };

	clone_process(runThis, SIGCHLD);

	umount("/proc");
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
