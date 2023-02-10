# Index-Creator :orange_book:

+ This project creates an index that is similar to a **text book index :bookmark_tabs: in that it contains terms and page numbers**. :open_book: 
+ It uses a text and a list of terms that need to be indexed to produce an **alphabetical index** :capital_abcd:. 
+ This project was inspired by problem 5.2.11 from the book :blue_book: *"Data Structures using C and C++" by Langsam, Augenstein, and Tenenbaum*. 
+ I've used and implemented :palm_tree:**AVL trees and Tries**:deciduous_tree: as my data structures.
+ To create this project, I drew on concepts from both generic programming and object-oriented programming. 
+ The **process** for creating the index is as follows :arrow_heading_down:
    1. All *special characters* from the text, including $,%,!, and others, were removed using simple tests of ASCII values.
    2. All *stop words* like and, or, not, why, if, … were eliminated. While traversing each word from the file acquired in the output of step one, if a word was found in a trie of stop words, it was discarded.
    3. The output file from phase 2 is the file being processed in this step. Every word is scanned, and if it is discovered in a trie of terms, it is added to one AVL tree, and the its page number is added to another. The *AVL tree of terms and page numbers* are connected.
    4. The resultant AVL trees are *traversed in-order* to produce the index.  

## Usage 
<br> **Note**: Prerequisite: GCC compiler should be downloaded on your machine <br> 
+ On Windows 
    1. Save the source code for this project & compile it. 
    2. Open the command prompt and type <br>
        name_of_executable_file inpt_file_1.txt inpt_file_2.txt output_file_1.txt
+ On Linux
    1. Save the source code for this project & compile it. 
    2. Open the linux terminal and type <br>
        ./object_file_name inpt_file_1.txt inpt_file_2.txt output_file_1.txt 
+ Where 
    1. inpt_file_1.txt: contains all the terms which need to be indexed from the text. Each term on a new line. 
    2. inpt_file_2.txt: contains the text on which index has to be created. 
    3. output_file_1.txt: file where the resultant index will be saved. 
## Example
