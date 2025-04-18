# Singleton LRU Cache

## Description
This project will implement an LRU cache data structure using the Singleton design principal. In this principal we initialize an give object only once. After initialization of such object, any new references to that object will be a pointer to the origional object.

## Implementation
An LRU Cache stands for Least Recently Used Cache. In this data structure we configure a maximum capacity. We can get or put to this structure and we pop the Least Recently Used value if our capacity is exceeded. 

This is typically implemented using a map and a doubly linked list. The map will store a <key, node pointer> for O(1) lookup times. The node pointer, points to a node in our double linked list where we track the most recent and least recent keys. This is done by shifting the pointers in the linked list where the left most node (begining of list) is the least recent and the right most node (end of list) is the most recent