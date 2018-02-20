// 
// File: bst.c 
// TODO_DOCS_ bst.c
// @author Connor Egbert <cje5361>
// // // // // // // // // // // // // // // // // // // // // // // 

#define _GNU_SOURCE
#define DELIM " "

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "bst.h"

/// Trims words to meet today's high standards

void makewordsgreatagain(char * word, char * newword) {
	int j = 0;
	for (unsigned int i = 0; i < strlen(word) + 1; i++) {
		if (isalpha(word[i])) {
			newword[j] = word[i];
			j++;
		}
		else if (isdigit(word[i])) {
			newword[j] = word[i];
			j++;
		}
		else if (word[i] == '\'' || word[i] == '-') {
			newword[j] = word[i];
			j++;
		}
		else if (word[i] == '\0') {
			newword[j] = word[i];
			j++;
		}
	}
	newword[j] = '\0';
}

void insert_word( TreeNode** root, const char *word ) {
	if ((*root) == NULL) {
		TreeNode * node = malloc(sizeof(TreeNode));
		node->word = malloc(strlen(word) + 1);
		strncpy(node->word, word, strlen(word) + 1);
		node->frequency = 1;
		node->left = NULL;
		node->right = NULL;
		(*root) = node;
	}
	else {
		int i = strcasecmp((*root)->word, word);
		if (i == 0) {
			(*root)->frequency++;
		}
		else if (i < 0) {
			insert_word(&((*root)->left), word);
		}
		else if (i > 0) {
			insert_word(&((*root)->right), word);
		}
	}
}

void traverse_tree( const TreeNode* root ) {
	if (root == NULL) {
		return;
	}
	traverse_tree(root->right);
	printf("%s %d\n", root->word, root->frequency);
	traverse_tree(root->left);
}

void cleanup_tree(TreeNode *root) {
	if (root == NULL) {
		return;
	}
	cleanup_tree(root->left);
	cleanup_tree(root->right);
	free(root->word);
	free(root);
}

/// Used to take input from stdin and count word frequency.

int main( int argc, char* argv[] ) {
	(void) argv;
	if (argc != 1) {
		fprintf(stderr, "Usage:  bst\n");
		return EXIT_FAILURE;
	}
	char *buf = NULL;  // important: must initially be NULL
	size_t len = 0;    // should initially be 0
	char *token;
	char dyword[500];
	TreeNode *root = NULL;
	while (getline(&buf, &len, stdin) >= 0) {
		token = strtok(buf, DELIM);
		while( token != NULL ) { 
			makewordsgreatagain(token, dyword);
			insert_word(&root, dyword);
			token = strtok(NULL, DELIM);
		}
	}
	traverse_tree(root);
	cleanup_tree(root);
	if( buf != NULL ) {
		free(buf);  // must deallocate this space!
	}
    	return EXIT_SUCCESS;
}
