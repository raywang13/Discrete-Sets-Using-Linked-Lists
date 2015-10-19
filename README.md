A C program that implements a set abstract data type with operations union, intersection and set difference. 
Input to the program will be a sequence of single characters separated by white space. These indicate which 
operations should be carried out:
   ’u’ or ’U’:  Find the union of two sets,
   ’i’ or ’I’:  Find the intersection of two sets, and
   ’d’ or ’D’:  Find the difference of two sets.
   ’q’ or ’Q’:  Quit (freeing any allocated memory),
For the union, intersection, or difference, the user will enter two sets A and B, and your program should output 
the result of the operation on the sets. The elements of the sets will be nonnegative ints, listed in increasing order, 
without repetitions. The last element in an input set will be followed by a negative value.
