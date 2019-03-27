#include <fcntl.h>

int main(int ac, char **av)
{
	char buf[256] = {0};
	int fd = open("/sys/kernel/debug/t/id", O_RDWR);
	int ret = 0;

		ret = read(fd, buf, 4);
	printf("read string buf[4]: %s, ret value : %d \n", buf, ret);
	bzero(buf,256);
	printf("read string buf[6]: %s, ret value : %d\n",buf,ret);
	bzero(buf,256);

	printf("write(nidzik) : %d \n",write(fd, "nidzik", 6));
	printf("write(nidzikk) : %d \n",write(fd, "nidzikk", 7));


	int fd1 = open("/sys/kernel/debug/t/jiffies", O_RDWR);
	
	ret = read(fd1, buf, 14);
	printf("-------------\n\nread jiffies [14]: %s, ret value : %d\n",buf,ret);

	bzero(buf,256);
	int fd2 = open("/sys/kernel/debug/t/foo", O_RDWR);

	printf("-------------\n\nfoo : write(nidzik) : %d \n",write(fd2, "nidzik", 6));
	ret = read(fd2, buf, 14);
	printf("read jiffies [14]: %s, ret value : %d\n",buf,ret);
return 0;
}




