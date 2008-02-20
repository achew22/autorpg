#include <string>
#include <iostream>

#include "SDL_net.h"

const int AUTORPG_SERVER_PORT = 2000;

int main(int argc, char **argv)
{
	IPaddress ip;		/* Server address */
	TCPsocket sd;		/* Socket descriptor */
	int quit, len;
	std::string buffer;
    //This code is gold, NEVER lose it
    //This code remaps stderr and stdout back to where they were (Against the wishes of SDL_net for some reason) WINDOWS ONLY;
    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );

	// Resolve the host we are connecting to (Always localhost, we don't want to be able to run this elsewhere)
	char * address = "127.0.0.1";
	if (SDLNet_ResolveHost(&ip, address, AUTORPG_SERVER_PORT) < 0) {
		std::cout << "SDLNet_ResolveHost: " << SDLNet_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	/* Open a connection with the IP provided (listen on the host's port) */
	if (!(sd = SDLNet_TCP_Open(&ip))) {
		std::cout << "SDLNet_TCP_Open: " << SDLNet_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	/* Send messages */
	quit = 0;
	while (!quit) {
		std::cout << "Write something:\n>";
		std::cin >> buffer;

		if (SDLNet_TCP_Send(sd, (void *)buffer.c_str(), buffer.length() + 1) < len) {
			std::cout << "SDLNet_TCP_Send: " << SDLNet_GetError() << "\n";
			exit(EXIT_FAILURE);
		}

		if(buffer == "exit") {
		    quit = 1;
		}
		else if(buffer == "quit") {
		    quit = 1;
		}
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();

	return EXIT_SUCCESS;
}
