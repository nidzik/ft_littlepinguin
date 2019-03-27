
#include <fcntl.h>

int main(int ac, char **av)
{
	char buf[256] = {0};
	int fd = open("/dev/fortytwo", O_RDWR);
	int ret = 0;

	ret = read(fd, buf, 4);
	printf("read string buf[4]: %s, ret value : %d \n", buf, ret);
	bzero(buf,256);
	ret = read(fd, buf, 4);
	printf("read string buf[4]: %s, ret value : %d \n", buf,  ret);
	bzero(buf,256);
	ret = read(fd, buf, 6);
	printf("read string buf[6]: %s, ret value : %d\n",buf,ret);
	bzero(buf,256);
	ret = read(fd, buf, 16);
	printf("read string buf[16]: %s, ret value : %d\n", buf, ret);
	printf("----------------\n");

	printf("write(nidzik) : %d \n",write(fd, "nidzik", 6));
	printf("write(nidzikk) : %d \n",write(fd, "nidzikk", 7));
	printf("write(ni) : %d\n",write(fd, "ni", 2));
	printf("write(nidzikkkkk) :  %d\n",write(fd, "nidzikkkk\n", 10));
}
