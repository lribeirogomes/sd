/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ttt.h"


void
ttt_1(char *host)
{
	CLIENT *clnt;
	char * *result_1;
	char *currentboard_1_arg;
	int  *result_2;
	play_args  play_1_arg;
		play_1_arg.player = 0;
	int  *result_3;
	char *checkwinner_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, TTT, V1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	do {
		do {
			result_1 = currentboard_1((void*)&currentboard_1_arg, clnt);
			if (result_1 == (char **) NULL) {
				clnt_perror (clnt, "call failed");
			}
			else
				printf ("%s", *result_1);
			
			printf("\nPlayer %d, please enter the number of the square "
					"where you want to place your %c (0 to refresh the board, 10 to undo the last play): ", play_1_arg.player,(play_1_arg.player==1)?'X':'O');
			scanf(" %d", &go);
			if (go == 0){
				play_res = 0;
				continue;
			}
			else if (go == 10) {
				anular();
				continue;
			}
			
			play_1_arg.row = --go/3;		/* Get row index of square      */
			play_1_arg.column = go%3;		/* Get column index of square   */
			
			result_2 = play_1(&play_1_arg, clnt);
			/*if (result_2 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}*/
			if (result_2 != 0) {
			switch (play_res) {
				case 1:
				  printf("Position outside board.");
				  break;
				case 2:
				  printf("Square already taken.");
				  break;
				case 3:
				  printf("Not your turn.");
				  break;
				case 4:
				  printf("Game has finished.");
				  break;
				}
				printf(" Try again...\n");
			}
			
			result_3 = checkwinner_1((void*)&checkwinner_1_arg, clnt);
			if (result_3 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		}
		while (result_2 != 0);
		play_1_arg.player = (play_1_arg.player+1)%2
		printf("player %d\n", play_1_arg.player);
	}
	while (*result_3 == -1);
	
	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	ttt_1 (host);
exit (0);
}
