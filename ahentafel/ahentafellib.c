// 
// File: ahentafellib.c 
// @author Connor Egbert <cje5361>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXLINE 200

void reversestring(char * input) {
	if (input == 0 || *input == 0) {
		return;
	}
	char *start = input;
	char *end = start + strlen(input) - 1;
	char temp;
	while (end > start) {
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}

long int mathhpowerfunctionisstupid(int x, int n) {
	int number = 1;
	for (int i = 0; i < n; ++i) {
		number *= x;
	}
	return(number);
}

int todecimal(char * output) {
	int base10 = 0;
	for (int i = strlen(output) - 1; i >= 0; i--) {
		if (output[i] == '1') {
			base10 += mathhpowerfunctionisstupid(2, i);
		}
	}
	return base10;
}

char * tobinary(int num, char * output) {
	unsigned int i = 0;
	while (num > 1) {
		if (num % 2 == 0) {
			output[i] = '0';
		}
		else {
			output[i] = '1';
		}
		num /= 2;
		i++;	
	}
	if (num == 1) {
		output[i] = '1';
	}
	else {
		output[i] = '0';
	} 
	output[i + 1] = '\0';
	reversestring(output);
	return output;
}

char * fromrelation(char * relation, char * output) {
	output[0] = '1';
	output[1] = '\0';
	if (strcmp("self", relation) != 0) {
		return output;
	}
	int index = 1;
	for (unsigned int i = 0; i < strlen(relation); i++) {
		if (relation[i] == 'm') {
			output[index] = '0';
			index++;
		}
		if (relation[i] == 'f') {
			output[index] = '1';
			index++;
		}
	}
	output[index + 1] = '\0';
	return output;
}

char * torelation(char * binary, char * output) {
	int index = 0;
	for (unsigned int i = 0; i < strlen(binary); i++) {
		if (binary[i] == '0') {
			strncpy(&output[index], "mother\'s ", 9);
		}
		else {
			strncpy(&output[index], "father\'s ", 9);
		}
		index += 9;
	}
	output[index - 3] = '\0';
	return output;
}

bool isbinary(char * input, int inputtype) {
	if (inputtype) {
		if (input[strlen(input) - 1] != 'b') {
			return false;
		}
	}
	for (unsigned int i = 0; i < strlen(input); i++) {
		if (input[i] != '1' && input[i] != '0') {
			if (inputtype) {
				if (i != strlen(input) - 1) {
					fprintf(stderr, "Invalid binary input\n");
					exit(1);
				}
			}
			return false;
		}
	}
	return true;
}

bool isrelation(char * input) {
	if (strcmp(input, "self")) {
		return true;
	}
	if (strcmp(input, "mother\'s") != 0 || strcmp(input, "mother")) {
		return true;
	}
	if (strcmp(input, "father\'s") != 0 || strcmp(input, "father")) {
		return true;
	}
 	return false;
}

void base10input(char * input) {
	char * c = NULL;
	int base10 = 0;
	base10 = strtol(input, &c, 10);
	char bin[MAXLINE];
	char buffer[MAXLINE];
	tobinary(base10, bin);
	printf("Ahnentafel number in binary: %s\n", bin);
	if (base10 == 1) {
		printf("Family relation: self\n");
	}
	else {
		printf("Family relation: %s\n", torelation(&bin[1], buffer));
	}
	printf("Generations back: %ld\n\n", strlen(bin) - 1);
}

void binaryinput(char * input) {
	if (input[strlen(input) - 1] == 'b') {
		input[strlen(input) - 1] = '\0';
	}
	char * c = NULL;
	char buffer[MAXLINE];
	int base10 =  strtol(input, &c, 2);
	printf("Ahentafel number in base-10: %d\n", base10);
	if (base10 == 1) {
		printf("Family relation: self\n");
	}
	else {
		torelation(&input[1], buffer);
		printf("Family relation: %s\n", buffer);
	}
	printf("Generations back: %ld\n\n", strlen(input) - 2);
}

void relationinput(char * input) {
	char bin[MAXLINE];
	fromrelation(input, bin);
	int base10 = todecimal(bin);
	printf("Ahentafel number in base-10: %d\n", base10);
	printf("Ahentafel number in binary: %s\n", bin);
	printf("Generations back: %ld\n\n", strlen(bin) - 1);
}
