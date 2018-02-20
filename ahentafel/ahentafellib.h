// 
// File: ahentafellib.h 
// @author Connor Egbert <cje5361>
// // // // // // // // // // // // // // // // // // // // // // // 

#ifndef AHENTAFEL_H
#define AHENTAFEL_H

/**
 * Converts an integer to char array binary format.
 */
char * tobinary(int num, char * output);

/**
 * Verifies that a char array binary input if formatted correctly.
 * inputtype determines where the input comes from
 * 	0 comes from the menu
 * 	1 comes from the terminal
 */
bool isbinary(char * input, int inputtype);

/**
 * Verifies a relation input
 */
bool isrelation(char * input);

/**
 * Takes a base 10 number and displays ahnentfel information and binary translation.
 */
void base10input(char * input);

/**
 * Takes a binary input and displays ahnentafel information and base 10 translation.
 */
void binaryinput(char * input);

/**
 * Takes a relation input and displays the binary and base 10 translation.
 */
void relationinput(char * input);

#endif
