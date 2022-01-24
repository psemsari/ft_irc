#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#define PORT 9999

int main()
{
	struct sockaddr_in servaddr;
	int fd;
	int hey;
	socklen_t len = 0;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1){
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	if (bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
    std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
	if (listen(fd, 10) < 0){
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
	hey = accept(fd, (struct sockaddr*)&servaddr, (socklen_t*)&len);
	if (hey < 0){
    std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
	char buffer[100];
	read(hey, buffer, 100);
	std::cout << "The message was: " << buffer;
	std::string response = "Good talking to you\n";
	send(hey, response.c_str(), response.size(), 0);

	// Close the connections
	close(hey);
	close(fd);
	return 0;
}
