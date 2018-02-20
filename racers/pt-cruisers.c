// 
// File: pt-cruisers.c 
// Multithreaded race program
// @author Connor Egbert <cje5361>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "racer.h"
#include "display.h"

#define USAGE "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n"

int main( int argc, char* argv[] ) {
	if(argc < 3) {
		fprintf(stderr, USAGE);
		return EXIT_FAILURE;
	}
	int index = 1; //Position of the first name
	long f;
	if(sscanf(argv[index], "%ld", &f) != 0) {
		index = 2;
		initRacers(f);
	} //It's a floaty.
	else {
		initRacers(DEFAULT_WAIT);
	}
	if(argc - index < 2) {
		fprintf(stderr, USAGE);
		return EXIT_FAILURE;
	}
	Racer* racers[sizeof(Racer*) * argc];
	int i = 0;

	char name[MAX_NAME_LEN + 6];
	for(int x = index; x < argc; x++) {
		if(strlen(argv[x]) > MAX_NAME_LEN) {
			fprintf(stderr, "Error: racer names must not exceed length %d.\n", MAX_NAME_LEN);
			return EXIT_FAILURE;
		}
		else {
			sprintf(name, "~O=%-*so>", MAX_CAR_LEN - 5, argv[x]);
			for(unsigned int y = 0; y < strlen(name); y++) {
				if (name[y] == ' ') {
					name[y] = '-';
				}
			}
			racers[i] = makeRacer(name, x);
			i++;
		}
	}
	clear();

	//Create threads
	pthread_t threads[i];
	void *retval;
	int rc;
	long t;
	for(t = 0; t < i; ++t) {
		rc = pthread_create(&threads[t], NULL, run, (void *)racers[t]);
		if(rc) { //Error checking
			fprintf(stderr,"ERROR; pthread_create() returned %d\n",rc );
			return EXIT_FAILURE;
		}
	}

	for( t = 0; t < i; ++t ) {
		pthread_join(threads[t], &retval);
	}

	//Kill everything
	for(int a = 0; a < i; a++) {
		destroyRacer(racers[a]);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
