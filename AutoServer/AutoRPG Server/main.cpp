#include <SDL_net.h>
#include <string>
#include <iostream>

const int AUTORPG_SERVER_PORT = 2000;

int main ( int argc, char** argv )
{

    //This code is gold, NEVER lose it
    //This code remaps stderr and stdout back to where they were (Against the wishes of SDL_net for some reason);
    freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );

    std::cout << "Entering AutoRPG Server Main loop\n";

    TCPsocket sd, csd; // Socket descriptor, Client socket descriptor
	IPaddress ip, *remoteIP;
	int quit, quit2;
	char buffer[512];


	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	// Resolving the host using NULL make network interface to listen
	if (SDLNet_ResolveHost(&ip, NULL, AUTORPG_SERVER_PORT) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	// Open a connection with the IP provided (listen on the host's port)
	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	// Wait for a connection, send data and term
	quit = 0;
	while (!quit)
	{
		// This check the sd if there is a pending connection.
		// If there is one, accept that, and open a new socket for communicating
        //fprintf(stdout, "Checking for connections\n");
		if ((csd = SDLNet_TCP_Accept(sd)))
		{
            std::cout << "Got a connection\n";
			// Now we can communicate with the client using csd socket
			// sd will remain opened waiting other connections

			// Get the remote address
			if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd))) {
				// Print the address, converting in the host format
				std::cout << "Host connected from " << SDLNet_Read32(&remoteIP->host) << " on port" << SDLNet_Read16(&remoteIP->port) << "\r\n";

				std::string greeting = "Welcome to AutoServer for AutoRPG (http://autorpg.googlecode.com/)\r\n";
				SDLNet_TCP_Send(csd, greeting.c_str(), greeting.length() + 1);
			}
			else {
				fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
			}

			quit2 = 0;
			std::string messageBuffer = "";
			while (!quit2)
			{

				std::cout << "Buffer: " << messageBuffer << "\r\n";
				if (SDLNet_TCP_Recv(csd, buffer, 512) > 0)
				{
				    if ((int)buffer[0] == 13) {
                        if(messageBuffer == "exit")	// Terminate this connection
                        {
                            quit2 = 1;
                            std::cout << "Terminate connection\n";
                        }
                        if(messageBuffer == "quit") // Quit the program
                        {
                            quit2 = 1;
                            quit = 1;
                            std::cout << "Quit program\n";
                        }
                        messageBuffer = "";
                        std::cout << "Got newline\n";
                    }
                    else {
                        messageBuffer = messageBuffer + buffer[0];
                    }
				}
			}

			// Close the client socket
			SDLNet_TCP_Close(csd);
		}
	}

	SDLNet_TCP_Close(sd);
	SDLNet_Quit();

	return EXIT_SUCCESS;





    // all is well ;)
    printf("Exited cleanly\n");
    return 0;

}
