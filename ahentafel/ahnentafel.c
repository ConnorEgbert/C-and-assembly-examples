// 
// File: ahentafel.c 
// @author Connor Egbert <cje5361>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ahentafellib.h"

#define MAXLINE 200 // Max input size

/**
 * Main user interface for my ahentafel implementation
 * displays a menu if no parameters given
 * otherwise treats parameters as it would input inside the menu.
 * Does not use dynamic memory
 */
int main( int argc, char* argv[] ) {
	char * c = NULL;
	char buffer[MAXLINE]; 
	if (argc == 1) {
		long int switcher = 0;
		while (1) {
			switcher = 0;
			printf("1) description\n");
			printf("2) ahnentafel number (base 10)\n");
			printf("3) ahnentafel number (base 2)\n");
			printf("4) relation (e.g. mother's mother's father)\n");
			printf("5) exit\n\n> ");
			if (!feof(stdin)) { // If end of input reached (Ctrl-D)
				fgets(buffer, MAXLINE, stdin); // Get input from user
				switcher = strtol(buffer, &c, switcher); // Set input to an int
				switch(switcher) {
					case 1: // Description
						printf("The Ahnentafel number is used to determine the relation\n");
						printf("between an individual and each of his/her direct ancestors.\n\n");
						break;
					case 2: // Base 10
						printf("Enter the ahnentafel number in base-10: ");
						fgets(buffer, MAXLINE, stdin);
						base10input(buffer);
						break;
					case 3: // Base 2
						printf("Enter the ahnentafel number in binary: ");
						fgets(buffer, MAXLINE, stdin);
						binaryinput(buffer);
						break;
					case 4: // Relation string
						printf("Enter family relation (e.g.) \"father's mother\": ");
						fgets(buffer, MAXLINE, stdin);
						relationinput(buffer);
						break;
					case 5: // Quit
						printf("Goodbye.\n\n");
						return EXIT_SUCCESS;
						break;
					default:
						fprintf(stderr, "Invalid input. Try again.\n\n");
						break;
				}
			}
			else {
				printf("\n");
				break;
			}
		}
	}
	else { // Begin command line parameter processing
		strncpy(buffer, argv[1], MAXLINE);
		if (buffer[strlen(buffer) - 1] == 'b') { // If it starts with 'b' it is base 2
			isbinary(buffer, 1);
			binaryinput(buffer);
		}
		else if (buffer[0] == 'm' || buffer[0] == 'f') { // Starting with m or f is a relation string
			char relation[MAXLINE];
			int index = 0;
			for (int i = 1; i < argc; i++) {
				if (isrelation(argv[i])) {
					strncpy(&relation[index], argv[i], 9);
				}
				else {
					fprintf(stderr, "Invalid relation.");
				}
				index += 9;
			}
			relationinput(buffer);
		}
		else {
			base10input(buffer);
		}
	}
	return EXIT_SUCCESS;
}
