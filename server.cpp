#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include <cstring>
#include <sys/time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#define PORT 6667

int main()
{
	addrinfo config;
	addrinfo *ai;

	memset(&config, 0, sizeof(config));
	config.ai_family = AF_UNSPEC;
	config.ai_socktype = SOCK_STREAM;
	config.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, "6667", &config, &ai) != 0)
		return 1;

	int listener; // listening socket descriptor
	int yes = 1;
	addrinfo *next = ai;
	for (; next != NULL; next = next->ai_next)
	{
		listener = socket(next->ai_family, next->ai_socktype, next->ai_protocol);
		if (listener < 0)
			continue;
		//socket level option, So_reuseaddr permnet de reutiliser l'address (yes = 1 pour dire oui a l'option, yes à la taille d'un int)
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(listener, next->ai_addr, next->ai_addrlen) < 0) //on bind sur une des address que getaddrinfo nous a passé
		{
			close(listener);//close fd si on arrive pas à bind
			continue;
		}
		break;
	}
	if (next == NULL)
	{// on a pas reussi a bind
		exit(2);
	}

	freeaddrinfo(ai);

	if (listen(listener, 10) == -1) //prepare le fd pour accepter les requetes
	{
		perror("listen");
		exit(3);
	}

	fd_set master;
	fd_set read_fds; // temp file descriptor list for select()
	int fdmax;

	FD_ZERO(&master);
	FD_SET(listener, &master);

	fdmax = listener;

	int newfd; // newly accepted socket descriptor
	struct sockaddr_storage remoteaddr; // client address
	socklen_t addrlen;

	char buf[256]; // buffer for client data
	int nbytes;

	for(;;)
	{
		read_fds = master; // copy it
		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
		{
			perror("select");
			exit(4);
		}
		for(int i = 0; i <= fdmax; i++)
		{
			if (FD_ISSET(i, &read_fds))
			{ // we got one!!
				if (i == listener)
				{
					// handle new connections
					addrlen = sizeof(remoteaddr);
					newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
					if (newfd == -1)
					{
						perror("accept");
					}
				}
				else
				{
					FD_SET(newfd, &master); // add to master set
					if (newfd > fdmax)
					{ // keep track of the max
						fdmax = newfd;
					}
					std::cout << "select server: new connection from %s on socket %d\n"
							<< inet_ntoa(((struct sockaddr_in *)&remoteaddr)->sin_addr)
							<< newfd;
				}
			}
			else
			{
				// handle data from a client
				if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
				{
					// got error or connection closed by client
					if (nbytes == 0)
					{
						// connection closed
						printf("selectserver: socket %d hung up\n", i);
					}
					else
					{
						perror("recv");
					}
					close(i); // bye!
					FD_CLR(i, &master); // remove from master set
				}
				else
				{
					// we got some data from a client
					for(int j = 0; j <= fdmax; j++)
					{
					// send to everyone!
						if (FD_ISSET(j, &master))
						{
						// except the listener and ourselves
							if (j != listener && j != i)
							{
								if (send(j, buf, nbytes, 0) == -1)
								{
									perror("send");
								}
							}
						}
					}
				}
			}
		}
	}
	return (0);


// 	struct sockaddr_in servaddr;
// 	int fd;
// 	int hey;
// 	socklen_t len = 0;
// 	fd = socket(AF_INET, SOCK_STREAM, 0); //creer un socket (fd qui va pouvoir etre bind, une prise qui peut recevoir du courant)
// 	if (fd == -1){
//     std::cout << "Failed to create socket. errno: " << errno << std::endl;
//     exit(EXIT_FAILURE);
//   }
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_addr.s_addr = INADDR_ANY;
// 	servaddr.sin_port = htons(PORT);
// 	if (bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){ //connect un socket vers un port avec different option possible
//     std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
//     exit(EXIT_FAILURE);
//   }
// 	if (listen(fd, 10) < 0){ //prepare le socket a ecouter sur le port
//     std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
//     exit(EXIT_FAILURE);
//   }
// 	hey = accept(fd, (struct sockaddr*)&servaddr, (socklen_t*)&len); //attend une connexion sur le socket
// 	if (hey < 0){
//     std::cout << "Failed to grab connection. errno: " << errno << std::endl;
//     exit(EXIT_FAILURE);
//   }
//   while(1)
//   {
// 	char buffer[100];
// 	recv(hey, buffer, 100, 0);
// 	std::cout << "The message was: " << buffer;
// 	std::string response = "Good talking to you\n";
// 	send(hey, response.c_str(), response.size(), 0);
//   }
// 	// Close the connections
// 	close(hey);
// 	close(fd);
// 	return 0;
}
