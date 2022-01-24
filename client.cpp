#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	int fd;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return (1);
}
