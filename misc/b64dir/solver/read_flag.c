#include <stdio.h>
#include<fcntl.h>
#include <unistd.h>

int main(void) {
	char buf[80] = {0};
	int fd = open("/home/user/flag-57a21074dc2ee2b4b8e6b512c8f017d0.txt", O_RDONLY);
	read(fd, buf, 80);
	printf("%s\n", buf);
	return 0;
}
