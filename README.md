# Topological_Sort
This Program Generates all possible topological sorting arrangements. 
The principle idea is taken from "A structured program to generate all topological sorting 
arrangements" by Donald E. Knuth and  Jayme L. Szwarcfiter.   This program implements the recursive
version outlined in the paper. Alternatively a non recursive version can  be implemented using the same
data structures as outlined in the original article.

The linear List D (the 'BAG') described in the paper is implemented as a linked list where insertion is possible
both in head and in tail. This mechanism is equivalent to taking an element from right and putting it to
left of the list until base case is found (please refer to the original paper).

The successor list is implemented as an array of linked lists.

The predecessor count is a simple array.
----------------------------------------

Apart from the needed functionalities of each data structures, several redundant functions is also
implemented and provided in the program which can be used for debugging purposes.


Author: Aniruddha Maiti
Date: 6th September, 2015
