// 
// File: file-bitsets.c 
//
// Bit operators lab, the lab to learn bit operators,
// the lab designed specifically for bit operators.
//
// @author Connor Egbert <cje5361>
// // // // // // // // // // // // // // // // // // // // // // // 

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct set {
	uint64_t bits: 64;
};

/// Encode data from file
uint64_t file_set_encode( FILE * fp ) {
	uint64_t set = 0;
	void *v = malloc(sizeof(char));
	char decoder[] = "zyxwvutsrqponmlkjihgfedcba,9876543210.ZYXWVUTSRQPONMLKJIHGFEDCBA";
	for(unsigned int i = 0; i < strlen(decoder); i++) {
		while(fread(v, 1, 1, fp)) {
			if(*((char *) v) == decoder[i]) {
				set |= 1LL << i;
				break;
			}
		}
		rewind(fp);
	}
	free(v);
	return set;
}

/// Encode data from string
uint64_t set_encode( char * st ) {
	uint64_t set = 0;
	char decoder[] = "zyxwvutsrqponmlkjihgfedcba,9876543210.ZYXWVUTSRQPONMLKJIHGFEDCBA";
	for(unsigned int i = 0; i < strlen(decoder); i++) {
		for(unsigned int j = 0; j < strlen(st); j++) {
			if(st[j] == decoder[i]) {
				set |= 1LL << i;
				break;
			}
		}
	}
	return set;
}

/// Binary intersection between two sets
uint64_t set_intersect( uint64_t set1, uint64_t set2 ) {
	uint64_t set = set1 & set2;
	return set;
}

/// Binary union between two sets
uint64_t set_union( uint64_t set1, uint64_t set2 ) {
	uint64_t set = set1 | set2;
	return set;
}

/// Creates the two's compliment of the given set
uint64_t set_complement( uint64_t set1 ) {
	uint64_t set = ~set1;
	return set;
}

/// Binary difference between two sets
uint64_t set_difference( uint64_t set1, uint64_t set2 ) {
	uint64_t set = set1 & (~set2);
	return set;
}

/// Symmetric difference between two sets
uint64_t set_symdifference( uint64_t set1, uint64_t set2 ) {
	uint64_t set = set1 ^ set2;
	return set;
}

/// Returns the cardinality, or size, of a set
size_t set_cardinality( uint64_t set ) {
	size_t size = 0;
	for(unsigned int i = 0; i < sizeof(uint64_t) << 3; i++) {
		if((set & (1Lu << i)) == (1Lu << i)) {
			size++;
		}
	}
	return size;
}

/// Generate string from data set
char *set_decode( uint64_t set ) {
	int index = 0;
	char *s = malloc((sizeof(uint64_t) << 3) + 1); // plus one to garentee space for terminator
	char decoder[] = "zyxwvutsrqponmlkjihgfedcba,9876543210.ZYXWVUTSRQPONMLKJIHGFEDCBA";
	for(int i = (sizeof(uint64_t) << 3) - 1; i >= 0; i--) {
		if((set & (1Lu << i)) == (1Lu << i)) {
			s[index] = decoder[i];
			index++;
		}
	}
	s[index] = '\0';
	return s;
}

/// Main program
int main( int argc, char* argv[] ) {
	if(argc != 3) {
		fprintf(stderr, "Usage: file-bitsets string1 string2\n");
		return EXIT_FAILURE;
	}

	FILE *file1 = fopen(argv[1], "r");
	FILE *file2 = fopen(argv[2], "r");
	struct set set1;
	struct set set2;

	if(file1) {
		printf("string1:\t%s\tEncoding the file:\t%s\n", argv[1], argv[1]);
		set1.bits = file_set_encode(file1);
		fclose(file1);
	} else {
		printf("string1:\t%s\tEncoding the string:\t%s\n", argv[1], argv[1]);
		set1.bits = set_encode(argv[1]);
	}
	if(file2) {
		printf("string2:\t%s\tEncoding the file:\t%s\n\n", argv[2], argv[2]);
		set2.bits = file_set_encode(file2);
		fclose(file2);
	} else {
		printf("string2:\t%s\tEncoding the string:\t%s\n\n", argv[2], argv[2]);
		set2.bits = set_encode(argv[2]);
	}

	printf("set1:\t%#018lx\n", set1.bits);
	printf("set2:\t%#018lx\n\n", set2.bits);

	printf("set_intersect:\t%#018lx\n", set_intersect(set1.bits, set2.bits));
	printf("set_union:\t%#018lx\n\n", set_union(set1.bits, set2.bits));

	printf("set1 set_complement:\t%#018lx\n", set_complement(set1.bits));
	printf("set2 set_complement:\t%#018lx\n\n", set_complement(set2.bits));

	printf("set_difference:\t\t%#018lx\n", set_difference(set1.bits, set2.bits));
	printf("set_symdifference:\t%#018lx\n\n", set_symdifference(set1.bits, set2.bits));

	printf("set1 set_cardinality:\t%ld\n", set_cardinality(set1.bits));
	printf("set2 set_cardinality:\t%ld\n\n", set_cardinality(set2.bits));

	char *s1 = set_decode(set1.bits);
	char *s2 = set_decode(set2.bits);
	printf("members of set1:\t\'%s\'\n", s1);
	printf("members of set2:\t\'%s\'\n\n", s2);
	free(s1);
	free(s2);

	return EXIT_SUCCESS ;
}
