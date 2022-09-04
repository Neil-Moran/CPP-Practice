# Linked List
A basic implementation of a single-linked list, another recreation of a program I wrote in college. I've still never seen one actually implemented in the wild but I'm sure I will some day. A good opportunity to play with pointers again, didn't have too many issues/null-pointer exceptions thankfully! Enjoyed this a lot, quick to get up and running but lots of extra features to add and decisions to make. Had to think about the possible data states a lot while developing, e.g. "what if we remove the head or tail?", or "what if the list is empty?". I might start over and try a double-linked list in the future.

## Add and Insert
User has the option to add a node to the end of the list (maybe should have called this append?) or insert it into the list in ascending numerical order. Made a + operator overload for add() as practice, I find the syntax hard to remember. Discussed with [Kevin](https://github.com/kevinmoran) and he mentioned that operator overloads can sometimes be obfuscating as another developer might not agree on what "list += x" is supposed to mean, and in this instance I definitely agree that it would be clearer without. Left it in as it's just a practice program. 

I never added sorting, one way to achieve this would be to remove all nodes and then insert them again. Honestly I think you should probably know if the list should be sorted or not when creating it but you never know I suppose! Didn't feel like tackling in-place sorting this time around, see [Sorting Algorithms](https://github.com/Neil-Moran/CPP-Practice/tree/main/Sorting%20Algorithms) project for that!

## Reverse
Ah yes, the classic interview question (part of the motivation of this repository is to be able point to my GitHub in interviews :P). Was very straightforward, there's surely many ways you could write this and I might even do it differently in the future.

## Find and Remove
I was pleasantly surprised at how easy these were to get working, it was just important to consider removing the head or tail. The remove() method could have used the find() method to locate the node and another helper method to remove it, but that seemed like over-engineering to me for such a simple project.

## Recursion
If recursion is a new concept to you then check out the ~Node() and print() methods for a very simple example! Kind of quirky to get your head around at first but the golden rule I was taught was to keep it as simple as you possibly can, at least when starting out. Note that recursive code will sometimes be slower than the non-recursive alternative, write both and profile them if performance is a concern (I promise to do that next time, recursion is so pretty though :D)!