In this Repository,I took advantage of C programming and its characteristics like pointers, dynamic programming and more to implement the Data structures. 

a.) In the HashTable data structure, we try to add,search, dleet elements which happen in O(n) time.
Also, to avoid hashing of keys to same index. We created OverflowBuckets (which is nothing the representation of a LinkedList) to chain the elements which point to same index, in this way we can avoid hash collission.

b.) The next files I added are Linked List implementation using pointers. Here, I have implemented the Linked Lists in two different ways: One where I allocate a LinkedList and add nodes within the list struct; and the second was where we can can make nodes and chain them.

c.) I had a course called Signals and Systems where we learnt one of the most important topics which was "Convolution". I tried to create an alogrithm/program to take in 2 arrays from user and then yield the new array which has the convoled elements in it. At first, I had made the program which had the complexity of: O(n^3). However, this might not be feasible for large arrays. So, I tried to make the algorithm have the complexity of: O(n^2) which would save the computer lot of energy and computation.
