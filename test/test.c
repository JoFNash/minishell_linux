#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
	int buf = dup(1);

	int fd1 = open("wwwasw", O_RDWR | O_CREAT, 0644);
	int fd2 = open("wwwasw", O_RDWR | O_CREAT, 0644);
	printf("%d %d\n", fd1, fd2);

}