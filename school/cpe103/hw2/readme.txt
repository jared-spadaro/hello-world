Program Notes / Observations   --    Jared Spadaro

NOTE: Binary Search remains incomplete. Had some bugs that I couldn't figure out. 
However, the binary sort leaves the list "mostly sorted".

Regarding the times:

[ORDER]
In order times were very small, followed by random order, and then reverse order.
The difference between in order and the others was very large.
The difference between random and reverse order was roughly 2:1. 

[SIZE]
The difference between 100k objects and 10k objects was MUCH larger than
the difference between 10k objects and 1k objects.
This is to be expected, because the behavior of n^2 and nlog(n) is as such.

[SORT METHOD]
Binary search showed an improvement in efficiency over linear search, although
the difference was not monumental. Binary search proved to take roughly half as
much time as linear search.

    