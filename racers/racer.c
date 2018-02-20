// 
// File: racer.c 
// TODO_DOCS_ racer.c
// @author Connor Egbert <cje5361>
// // // // // // // // // // // // // // // // // // // // // // // 

#define _BSD_SOURCE

#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "racer.h"
#include "display.h"

long int ms;
pthread_mutex_t ilock;

void initRacers(long miliseconds) {
	ms = miliseconds;
}

Racer* makeRacer(char *name, int position) {
	Racer* r = malloc(sizeof(Racer));
	r->dist = 0;
	r->row = position;
	r->graphic = malloc(strlen(name) + 1);
	strncpy(r->graphic, name, strlen(name));
	return r;
}

void destroyRacer(Racer* racer) {
	free(racer->graphic);
	free(racer);
}

void* run(void* racer) {
	Racer* car = (Racer*) racer;
	set_cur_pos(car->row + 1, 0);
	srand(time(NULL));
	int r;
	while(car->dist < FINISH_LINE) {
		r = rand() % ms;
		if(r <= 3) {
			car->graphic[1] = 'X';
			for(unsigned int i = 0; i < strlen(car->graphic); i++) {
				set_cur_pos(car->row, car->dist + i);
				put(car->graphic[i]);
			}
			break;
		}
		pthread_mutex_lock(&ilock);
		set_cur_pos(car->row + 1, car->dist);
		put(' ');
		car->dist++;
		for(unsigned int i = 0; i < strlen(car->graphic); i++) {
			set_cur_pos(car->row, car->dist + i);
			put(car->graphic[i]);
		}
		pthread_mutex_unlock(&ilock);
		usleep(r * 1000);
	}
	return NULL;
}
