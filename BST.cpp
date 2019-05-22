#include <iostream>
#include <stdlib.h>
using namespace std;
struct Node {
	int data;
	Node* left = NULL;
	Node* right = NULL;
	Node* parent = NULL;
};
struct Tree {
	Node* root = NULL;
};
void inorder(Node* x) {
	if (x != NULL) {
		inorder(x->left);
		cout << x->data << endl;
		inorder(x->right);
	}
}
void preorder(Node* x) {
	if (x != NULL) {
		cout << x->data << endl;
		preorder(x->left);
		preorder(x->right);
	}
}
void postorder(Node* x) {
	if (x != NULL) {
		postorder(x->left);
		postorder(x->right);
		cout << x->data << endl;
	}
}
void insert(Tree* T, Node* z) {
	Node* y = NULL;
	Node* x = T->root;
	while (x != NULL) {
		y = x;
		if (z->data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL)
		T->root = z;
	else if (z->data < y->data)
		y->left = z;
	else
		y->right = z;
}
Node* search(Node* x, int k) {
	if (x == NULL || k == x->data)
		return x;
	if (k < x->data)
		return search(x->left, k);
	else
		return search(x->right, k);
}
void transplant(Tree* T, Node* u, Node* v) {
	if (u->parent == NULL) {
		T->root = v;
	}else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}
Node* min(Node* x) {
	while (x->left != NULL)
		x = x->left;
	return x;
}
void del(Tree* T, Node* z) {
	if (z->left == NULL)
		transplant(T, z, z->right);
	else if (z->right == NULL)
		transplant(T, z, z->left);
	else {
		Node* y = min(z->right);
		if (y->parent != z) {
			transplant(T, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		} transplant(T, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
}

int main() {
	int key = 0; char c[1000];
	Tree* T = new Tree();
	while (c[0] != 'e') {
		cin >> c;
		key = atoi(c + 1);
		if (c[0] == 'i') {
			Node* z = new Node();
			z->data = key;
			insert(T, z);
		}
		else if (c[0] == 'd') {
			Node* query = search(T->root, key);
			if (query != NULL)
				del(T, query);
		}
		else if (c[0] == 'o') {
			if (c[1] == 'p') {
				if (c[2] == 'r' && c[3] == 'e') {
					preorder(T->root);
				} else if (c[2] == 'o' && c[3] == 's' && c[4] == 't'){
					postorder(T->root);
				}
			} else if (c[1] == 'i' && c[2] == 'n') {
				inorder(T->root);
			}
		}
	}
	return 0;
}