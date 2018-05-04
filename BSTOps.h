#ifndef BSTOps_h
#define BSTOps_h

#include "BSTComplete.h"

int occurrences(Node* root, int value){
	if (!root)
		return 0;
	if (root->data == value)
		return 1 + occurrences(root->right, value) + occurrences(root->left, value);
	else if (value < root->data)
		return occurrences(root->left, value);
	else
		return occurrences(root->right, value);
}
#endif
