# Index-Creator :orange_book:

+ This project creates an index that is similar to a **text book index :bookmark_tabs: in that it contains terms and page numbers**. :open_book: 
+ It uses a text and a list of terms that need to be indexed to produce an **alphabetical index** :capital_abcd:. 
+ This project was inspired by problem 5.2.11 from the book :blue_book: *"Data Structures using C and C++" by Langsam, Augenstein, and Tenenbaum*. 
+ I've used and implemented :palm_tree:**AVL trees and Tries**:deciduous_tree: as my data structures.
+ To create this project, I drew on concepts from both generic programming and object-oriented programming. 
+ The **process** for creating the index is as follows 
    1. All *special characters* from the text, including $,%,!, and others, were removed using simple tests of ASCII values.
    2. All *stop words* like and, or, not, why, if, … were eliminated. While traversing each word from the file acquired in the output of step one, if a word was found in a trie of stop words, it was discarded.
    3. The output file from phase 2 is the file being processed in this step. Every word is scanned, and if it is discovered in a trie of terms, it is added to one AVL tree, and the its page number is added to another. The *AVL tree of terms and page numbers* are connected.
    4. The resultant AVL trees are *traversed in-order* to produce the index.  

## How to run it?

## The example that I used
