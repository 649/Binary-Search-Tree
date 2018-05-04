#ifndef BST_h
#define BST_h

#include <iostream>

// The struct representing a Binary Search Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Inserting a value into an existing tree
Node* insert(Node* root, int value){
    // If we have an empty root, make a new node
    if (root == NULL){
        root = new Node();
        root->data = value;
        root->left = NULL;
        root->right = NULL;
    }
    else{
        if (value < root->data){
            // If value is less than the root,
            // insert it in the left subtree
            // If only there was a function that can insert into trees
            // Oh, wait. There is one...
            root->left = insert(root->left, value);
        }
        else {
            // Same thing here. If we are inserting
            // a number bigger than the root, then
            // insert it in the right subtree
            root->right= insert(root->right, value);
        }
    }
    // After the new node has been inserted in the right place
    // Just return the root pointer
    return root;
}

// In-order traversal of tree, produces the elements in sorted order
void traverse (Node* root){
    if (root != NULL){
        traverse(root->left);
        std::cout  << root->data << " ";
        traverse(root->right);
    }
}

// Call the traverse function and leave a line aftrewards
void displayInOrder(Node* root){
    traverse(root);
    std::cout << std::endl;
}

// A function to display the tree graphically
void displayTree(Node* root, int level, int direction){
    // Don't worry about this function, just use it
    if (root != NULL){
        displayTree(root->right, level+1, 1);
        
        for (int i = 0; i < level-1; i++) {
            std::cout << "   ";
        }
        if (level > 0 ){
            if (direction == 1){
                std::cout << " /--";
            }
            else{
                std::cout << " \\--";
            }
        }
        std::cout << root->data;
        std::cout << std::endl;
        level++;
        
        displayTree(root->left, level, -1);
    }
}

// Call the function to display the tree and leave some space afterwards
void drawTree(Node* root){
    displayTree(root, 0, 0);
    std::cout << std::endl << std::endl;
}

bool search(Node* root, int value){
    // If we landed on a NULL node
    // then whatever we are searching for
    // can not possibly be in the tree
    if (root == NULL){
        return false;
    }
    else{
        // If the current node is not NULL,
        // then there is still a chance we
        // may be able to find what we seek
        if (root->data == value){
            // If we see the value we want, we're all set
            return true;
        }
        else if (value < root->data) {
            // If the value we want is smaller
            // we search for it on the left
            return search(root->left, value);
        }
        else{
            // Otherwise search for it on the right
            return search(root->right, value);
        }
    }
}

// A little function to check if a given tree
// meets all requirements to be a Binary Search Tree
bool isBST(Node* root){
    if (root == NULL) {
        return true;
    }
    else{
        bool levelOK = true;
        if (root->left != NULL && root->left->data > root->data){
            levelOK = false;
        }
        if (root->right != NULL && root->right->data <= root->data){
            levelOK = false;
        }
        return levelOK && isBST(root->left) && isBST(root->right);
    }
}

// Find a node in the tree that has a specific value
Node* findNode(Node* root, int value){
    // If we land on a NULL node, then the
    // value we want to find is not in the tree
    if (root == NULL){
        return NULL;
    }
    else{
        if (root->data == value){
            // We have found what we are looking for
            return root;
        }
        else if (value < root->data){
            // What we need must be to the left
            return findNode(root->left, value);
        }
        else {
            // What we need must be to the right
            return findNode(root->right, value);
        }
    }
}

// A function to find the minimum value in a tree
Node* findMin(Node* root){
    // If the current node has no left
    // Then there can't be anything in
    // the tree smaller than it
    if (root->left == NULL){
        return root;
    }
    else {
        // If on the other hand it has a left,
        // then we have not seen the smallest
        // value yet, because there are still
        // unexplored nodes to the left, and
        // we know they all have smaller values
        // than the one we are currently on
        return findMin(root->left);
    }
}
// A function to find the successor of the root element
// A successor of a node Q is defined as the node with the
// smallest value that is greater than or equal to the data in Q
Node* findSucc(Node* root){
    // First, if we are asked to find the successor the
    // root element of an empty tree, just return NULL
    
    if (root == NULL){
        return NULL;
    }
    
    // Second, make sure there is something on the right of the root
    // That's the only place you will find values greater than the
    // one in the root
    
    if (root->right == NULL){
        // The root is its own successor
        return root;
    }
    else{
        // Find the smallest value to the right of you
        return findMin(root->right);
    }
}

// In "tree", find the parent of "node"
Node* findParent(Node* tree, Node* node){
    // If you are looking for the parent of the root,
    // just return NULL. The root has no parent
    if (node == tree){
        return NULL;
    }
    
    // Get a pointer to the root
    Node* copy = tree;
    
    // A boolean flag to indicate that we need to keep searching
    bool done = false;
    
    // We know we haven't found our goal yet because we have only
    // looked at the root. And if the root was our goal, we would
    // have returned in line 203 (the IF statement above)
    
    while (!done){
        if (copy->data <= node->data){
            // The node we want is to the right of the current one
            // So we should go right
            // But before we do, we should check if the next time
            // we go to the right, we would find our destination
            // If that is the case, then we should stop here,
            // because if the next node to the right is our destination
            // then we must now be standing at the parent of our
            // destination node
            if (copy->right->data != node->data){
                copy = copy->right;
            }
            else{
                done = true;
            }
        }
        else {
            // Same process if we go left. Again, if we find that
            // the next of the current node we are on is actually
            // our destination, then we must now be at the parent
            // of our destination node, so we stop here.
            if (copy->left->data != node->data){
                copy = copy->left;
            }
            else{
                done = true;
            }
        }
    }
    
    // At this point we know that copy points to the parent of node
    // So we return that pointer
    return copy;
}

// With all the helper functions above, we are finally ready to start
// implementing the remove function
Node* remove(Node* root, Node* node){
    // We take in two pointers, one to the root
    // and one to the node we want to remove
    
    // There are 3 (or 4) cases to handle (depending on how you count)
    
    // The first one is when we are asked to delete a leaf node
    // which is simple since leaf nodes have no children, removing
    // the node will not leave any detached nodes.
    
    if (node->right == NULL && node->left == NULL){
        // Deleting a leaf
        
        // All we have to do is inform the parent of the node
        // being deleted that its child node does not exist anymore
        
        // So we find the parent, and depending on whether the node
        // being deleted was a right child or a left child,
        // we update the parent accordingly
        Node* parent = findParent(root, node);
        if (parent->data <= node->data){
            parent->right = NULL;
        }
        else {
            parent->left = NULL;
        }
        // We then free the memory that was occupied by the deleted node
        delete node;
        
        // Finally return a pointer to the root of the modified tree
        return root;
    }
    
    // The second case is when the node being deleted has only a left
    // child but not a right child
    else if (node->left != NULL && node->right == NULL){
        // Again we find the parent of the node being deleted
        Node* parent = findParent(root, node);
        
        // This time we also get a pointer to the child
        // We know it's a left child because the node only has a left
        Node* child = node->left;
        
        // Now our job is to connect the child of the deleted node
        // to the parent of the deleted node, closing the gap left behind
        // by the removal of the node
        
        // Depending if the node being deleted was a left or a right child
        // we connect its child to its parent in the correct manner
        if (parent->data <= node->data){
            parent->right = child;
        }
        else {
            parent->left = child;
        }
        // Return a pointer to the root of the modified tree
        return root;
        
    }
    // Now we handle the case of a node that doesn't have a left
    // but it has a right
    else if (node->left == NULL && node->right != NULL){
        // Same as previous case, get the parent
        Node* parent = findParent(root, node);
        // Same as before, but this time we know the
        // node being deleted only has a right child
        Node* child = node->right;
        
        if (parent->data <= node->data){
            parent->right = child;
        }
        else {
            parent->left = child;
        }
        return root;
        
    }
    else {
        // We are deleting a node with 2 children
        Node* succ = findSucc(node);
        node->data = succ->data;
        node = remove(node, succ);
        return root;
    }
    return NULL;
}

#endif
