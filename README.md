# Binary Search Tree

> Author: [@037](https://twitter.com/037)

![alt text](https://raw.githubusercontent.com/649/Binary-Search-Tree/master/index.png)

### Compile
```
sudo g++ -std=c++11 -o BST.exe BST.cpp
```

### Input commands
In the input, each starts with 'e', 'i', 'd', 'oin','opre', or 'opost'. 
* i(key): Insert (key) into the BST. For example, i2 implies "Insert key 2 into the BST".
* d(key): delete (key) from the BST. For example, d2 implies "delete key 2 from the BST". Do nothing if the BST doesn't have the key.
* opre: output all keys via preorder walk.
* opost: output all keys via postorder walk.
* oin: output all keys via inorder walk.
* e: finish your program.

### Example

*Input*
```
i3
i1
i5
i7
oin
1
3
5
7
d7
oin
1
3
5
opre
3
1
5
opost
1
5
3
e
```
