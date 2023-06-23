#include "server_rules.h"
#include "server.h"

//default relay style communication
// waits for each player to respond
// sends player one's response to player two and vice versa
int relay( int playerOne, int playerTwo) {
	const int MAXBUFFERSIZE = 100;
	char p1Buff[MAXBUFFERSIZE + 1];
	p1Buff[MAXBUFFERSIZE] = '\0';
	char p2Buff[MAXBUFFERSIZE + 1];
	p2Buff[MAXBUFFERSIZE] = '\0';
	//TODO: change to an end condition
	int end = 0;
	while (!end) {
		int p1Read = read(playerOne, p1Buff, MAXBUFFERSIZE);
		if (p1Read <= 0) { //connection failed
			write(playerTwo, "ERROR: Player Disconnected", 26);
			//Thought : set an error bit and do all error writing in a dff function?
			break;
		}
		p1Buff[p1Read] = '\0';

		int p2Read = read(playerTwo, p2Buff, MAXBUFFERSIZE);
		if (p2Read <= 0) { //connection failed
			write(playerOne, "ERROR: Player Disconnected", 26);
			//Thought : set an error bit and do all error writing in a dff function?
			break;
		}
		p2Buff[p2Read] = '\0';

		int p1Write = write(playerOne, p2Buff, p2Read);
		if (p1Write <= 0) { //connection failed
			write(playerTwo, "ERROR: Player Disconnected", 26);
			//Thought : set an error bit and do all error writing in a dff function?
			break;
		}

		int p2Write = write(playerTwo, p1Buff, p1Read);
		if (p2Write <= 0) { //connection failed
			write(playerOne, "ERROR: Player Disconnected", 26);
			//Thought : set an error bit and do all error writing in a dff function?
			break;
		}

		if ( strncmp(p1Buff, "exit", 4) == 0 ||
				 strncmp(p2Buff, "exit", 4) == 0 ) {
			end = 1;
		}

	}

	return 1;	
}

int loganTest( int playerOne, int playerTwo) {
	return 1;
}
