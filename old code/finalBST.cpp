#include <iostream>
#include "BSTComplete.h"
#include "BSTOps.h"

using namespace std;




int main(int argc, const char * argv[]) {

    Node* tree = NULL;
    
    tree = insert(tree, 6);
    tree = insert(tree, 2);
    tree = insert(tree, 7);
    tree = insert(tree, 6);
    tree = insert(tree, 6);
    tree = insert(tree, 6);
    tree = insert(tree, 7);
    
    cout << occurrences(tree, 7) << endl;
    
    return 0;
}
