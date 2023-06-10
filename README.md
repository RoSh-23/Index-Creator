# Index-Creator :orange_book:
**Note** :triangular_flag_on_post: This project has been made as a practice project to showcase DS skills. It has not gone through rigorus testing process and should not be used in production.
+ This project creates an index that is similar to a **text book index :bookmark_tabs: in that it contains terms (words) and corresponding page numbers on which these terms are present.** :open_book: 
+ It uses a text and a list of terms that need to be indexed to produce an **alphabetical index** :capital_abcd:. 
+ This project was inspired by problem 5.2.11 from the book :blue_book: *"Data Structures using C and C++, 2<sup>nd</sup> edition* by Langsam, Augenstein, and Tenenbaum. 
+ I've used and implemented :palm_tree:**AVL trees and Tries**:deciduous_tree: as my data structures.
    <br>**Note** :triangular_flag_on_post: I have referred to the book "Data Structures using C & C++ , 2<sup>nd</sup> ed." to write code for AVL Trees and referred to internet resources to write code for Tries. 
+ To create this project, I drew on concepts from both generic programming and object-oriented programming. 
+ The **process** for creating the index is as follows :arrow_heading_down:
    1. All *special characters* from the text, including $,%,!, and others, were removed using simple tests of ASCII values.
    2. All *stop words* like and, or, not, why, if, … were eliminated. While traversing each word from the file acquired in the output of step one, if a word was found in a trie of stop words, it was discarded.
    3. The output file from phase 2 is the file being processed in this step. Every word is scanned, and if it is discovered in a trie of terms, it is added to one AVL tree, and the its page number is added to another. The *AVL tree of terms and page numbers* are connected.
    4. The resultant AVL trees are *traversed in-order* to produce the index.  

## Usage :hammer_and_wrench:
<br> **Note** :triangular_flag_on_post: - **GCC compiler for C++ i.e. g++** should be downloaded on your machine. <br> 
<br> **Note** :triangular_flag_on_post: - **Works fine only if words to be indexed are expressed as lowercase alphabets (no special symbols)** <br> 
+ On **Windows** 
    1. Save the source code for this project & compile it using g++. 
    2. Open the command prompt and type <br>
        name_of_executable_file inpt_file_1.txt inpt_file_2.txt output_file_1.txt
+ On **Linux**
    1. Save the source code for this project & compile it using g++.
    2. Open the linux terminal and type <br>
        ./program_name inpt_file_1.txt inpt_file_2.txt output_file_1.txt 
+ **Where** 
    1. *inpt_file_1.txt*: contains all the words which need to be indexed from the text. Each term on a new line. 
    2. *inpt_file_2.txt*: contains the text on which index has to be created with each new page delimited by *10 '@'* symbols.  
    3. *output_file_1.txt*: file where the resultant index will be saved. 
## Example
+ I have run this program on the book *"Software Engineering, 10<sup>th</sup> edition"* written by Ian Somerville. 
+ The **text.txt** file in this repository contains the same book in text format. 
+ The **terms.txt** file in this repository contains the list of words on which I have created the index. 
+ The **opt.txt** file in this repository contains the index which is alphabetically sorted. 
+ Some Screenshots: :arrow_heading_down:
    ![image of terms to be indexed](/assets/images/terms.JPG)
    ![image of text on which index is created](/assets/images/text.JPG)
    ![image of output index](/assets/images/output.JPG)
    ![image of book section for verification](/assets/images/somerVBook.JPG)
