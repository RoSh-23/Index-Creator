/**	- Program to create an index of key words(like a textbook index)
 * 	  for a text with page numbers defined.
 * 	- The key words are also called as terms and are assumed to be in small letters
 * 	- Input:
 *		File 1: - Contains terms each new line which needs to be indexed.
 * 		File 2: - Contains the text to be processed.
 *				- New pages are indicated by 10 '@' in a row (on a new line)
 *	- Output:
 *		File 1: - The file in which the index is to be saved.
 *				- Organized as (on each new line)
 *					- Terms followed by their comma separated page numbers.
 *					- Terms and page numbers are alphabetically arranged.
 **/

/*
	IMP. NOTE: The code for AVL Trees was written by referring to the book -- "Data Structures Using C & C++, 2nd Ed."
	IMP. NOTE: The code for Tries was written by referring to Internet resources" 
*/

/**
 * 	Author: Rohan Shah
 * 	Start Date: 07th February 2023
 * 	End Date: 10th February 2023
 **/

/**
 *	- USE
 * 		- On Windows command prompt
 * 			name_of_executable_file inpt_file_1.txt inpt_file_2.txt output_file_1.txt
 * 		- On Linux terminal
 * 			./object_file_name inpt_file_1.txt inpt_file_2.txt output_file_1.txt
 **/

/**
 * 	The idea for this program came from question 5.2.11 on page number 283 of the book
 * 	"Data Structures Using C and C++, Second Edition" written by Lansman, Augenstein and
 * 	Tenenbaum
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

const int NUM_OF_LETTERS = 26;

// a class to represent node of a trie
class NodeOfTrie
{
protected:
	NodeOfTrie *arrOfChildNodesPtrs[NUM_OF_LETTERS]; // an array of pointers to the child nodes of a trie node
	bool endOfKeyFlag;	// a flag that shows whether the current character is end of the key or not

public:
	NodeOfTrie()
	{
		for(int i = 0; i < NUM_OF_LETTERS; i++)
		{
			arrOfChildNodesPtrs[i] = NULL;
		}
		endOfKeyFlag = false;
	}
	~NodeOfTrie()
	{
		for(int i = 0; i < NUM_OF_LETTERS; i++)
		{
			delete(arrOfChildNodesPtrs[i]);
			arrOfChildNodesPtrs[i] = NULL;
		}
		delete(this);
	}

	friend class Trie;
};

// a class that encapsulates the trie data structure
class Trie
{
	NodeOfTrie *root;	// pointer to the root of the trie
public:
	Trie()
	{
		NodeOfTrie *temp = new NodeOfTrie();
		root = temp;
	}

    // a function to check is a key is in correct format or not
    bool isKeyValid(string key)
    {
        bool isValid = true;
        for(int i = 0; i < key.length(); i++)
        {
            if(key[i] > 'z')
                isValid = false;
            if(key[i] < 'a')
                isValid = false;
        }
        return isValid;
    }

	// a function to insert a key into the trie
	void insertKey(string insertKey)
	{
		NodeOfTrie *travNode = root;

		for(unsigned int i = 0; i < insertKey.length(); i++)
		{
			int idxOfInsertion = insertKey[i] - 'a'; // index is determined by subtracting the from
													 // ASCII code of current character the ASCII of 'a'
			// only insert if that character does not already exist
			if(travNode->arrOfChildNodesPtrs[idxOfInsertion] == NULL)
			{
				NodeOfTrie *myNode = new NodeOfTrie();
				travNode->arrOfChildNodesPtrs[idxOfInsertion] = myNode;
			}
			// go to the next level in the trie
			travNode = travNode->arrOfChildNodesPtrs[idxOfInsertion];
		}

		travNode->endOfKeyFlag = true;
	}

	// a function to search a key
	// input: key --> string
	// output: true if found, false otherwise
	bool searchKey(string serKey)
	{
        if(isKeyValid(serKey) == false)
        {
            return false;
        }

		NodeOfTrie *travNode = root;

		// traverse the key
		for(unsigned int i = 0; i < serKey.length(); i++)
		{
			int idxOfSer = serKey[i] - 'a';
			// if pointer for that index does not exist it implies that no key exists from that point
			if(travNode->arrOfChildNodesPtrs[idxOfSer] == NULL)
			{
				return false;
			}

			travNode = travNode->arrOfChildNodesPtrs[idxOfSer];
		}

		// after traversal at end
		// if endOfKeyFlag is true it implies that a key has been matched
		if(travNode->endOfKeyFlag == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

// forward declaration for class AVLTree
template<typename K, typename D>
class AVLTree;

// a class that represents the node of a AVL Tree
// it is a generic node --> can be of any type
template<typename K, typename D = void>
class AVLTreeNode
{
protected:
    K key;
    D *dataNode;
    AVLTreeNode<K, D> *left;
    AVLTreeNode<K, D> *right;
    int bal;    // balance of any node is defined as the difference between the height of LST and RST
   	            // valid values for an AVL tree is -1, 0 and 1
public:
    AVLTreeNode(K insKey, D *dataNodePtr)
    {
        key = insKey;
        dataNode = dataNodePtr;
        left = NULL;
        right = NULL;
        bal = 0;
    }

    ~AVLTreeNode()
    {
        delete(this);
    }

    friend class AVLTree<K, D>;
    friend class IndexCreator;
};

// a class to encapsulate the functionality of an AVL Tree
// it is a generic class
template<typename K, typename D = void>
class AVLTree
{
    AVLTreeNode<K, D> *root;

    // function to perform left rotation on a tree rooted at rootPtr
    void performLeftRotation(AVLTreeNode<K, D> *rootPtr)
    {
        AVLTreeNode<K, D> *tempPtr1 = rootPtr->right;
        AVLTreeNode<K, D> *tempPtr2 = tempPtr1->left;
        tempPtr1->left = rootPtr;
        rootPtr->right = tempPtr2;
    }

    // function to perform right rotation on a tree rooted at rootPtr
    void performRightRotation(AVLTreeNode<K, D> *rootPtr)
    {
        AVLTreeNode<K, D> *tempPtr1 = rootPtr->left;
        AVLTreeNode<K, D> *tempPtr2 = tempPtr1->right;
        tempPtr1->right = rootPtr;
        rootPtr->left = tempPtr2;
    }

public:
    AVLTree()
    {
        root = NULL;
    }

    ~AVLTree()
    {
        delete(this);
    }

    // function to insert an key into the AVL tree
    void insertKey(K key, D *dataPtr = NULL)
    {
        AVLTreeNode<K, D> *nodeToBeInsertedPtr = new AVLTreeNode<K, D>(key, dataPtr);
        // tree is empty
        if(root == NULL)
        {
            root = nodeToBeInsertedPtr;
            return;
        }

        // if the tree is non empty
        /** PART I: search and insert into the binary tree **/
        AVLTreeNode<K, D> *travPtr = root;
        AVLTreeNode<K, D> *travPtrFather = NULL;  // initially no father of the root
        // youngest ancestor implies that node that ancestor node of the node to be inserted
        // that will get unbalanced if we do the insertion
        AVLTreeNode<K, D> *youngestAncestorPtr = travPtr;
        AVLTreeNode<K, D> *youngestAncestorPtrFather = NULL; // initially no father of the root

        AVLTreeNode<K, D> *travPtr2 = NULL;
        AVLTreeNode<K, D> *sonOfYAInDirOfImbalPtr = NULL;

        /* find the correct location to insert the new node */
        while(travPtr != NULL)
        {
            if(key == travPtr->key)
            {
                cout << "\nKEY ALREADY PRESENT\n";
                return;
            }
            travPtr2 = (key < travPtr->key)? travPtr->left : travPtr->right;
            if(travPtr2 != NULL)
            {
                if(travPtr2->bal != 0)
                {
                    youngestAncestorPtrFather = travPtr;
                    youngestAncestorPtr = travPtr2;
                }
            }
            travPtrFather = travPtr;
            travPtr = travPtr2;
        }

        /* now insert the new node as if no balancing is required */
        travPtr2 = nodeToBeInsertedPtr;
        if(key < travPtrFather->key)
        {
            travPtrFather->left = travPtr2;
        }
        else
        {
            travPtrFather->right = travPtr2;
        }
        /*
            the balance of all the nodes in the path between youngest ancestor node
            and node being inserted is changed with these two not included.
        */
        travPtr = (key < youngestAncestorPtr->key) ? youngestAncestorPtr->left : youngestAncestorPtr->right;
        sonOfYAInDirOfImbalPtr = travPtr;
        while(travPtr != travPtr2)
        {
            if(key < travPtr->key)
            {
                travPtr->bal = 1;
                travPtr = travPtr->left;
            }
            else
            {
                travPtr->bal = -1;
                travPtr = travPtr->right;
            }
        }
        /** PART I END **/

        /** PART II: find out if the tree is unbalanced or not **/
        // if key is smaller than the youngest ancestor key than
        // an imbalance of 1 will be created or -1 otherwise
        int imbal = (key < youngestAncestorPtr->key) ? 1 : -1;
        if(youngestAncestorPtr->bal == 0)
        {
            // new level has been added to the tree and tree continues to be balanced
            youngestAncestorPtr->bal = imbal;
            return; // no need of further processing, node has been inserted
        }

        if(youngestAncestorPtr->bal != imbal)
        {
            // new node has been added to the opposite direction of imbalance
            // therefore tree continues to be balanced
            youngestAncestorPtr->bal = 0; // height of both LST & RST becomes same
            return; // no need of further processing, node has been inserted
        }
        /** PART II END **/

        /**
            PART III: the newly inserted node has unbalanced the tree,
            re-balancing it by performing rotations and setting the
            changed balance of the nodes involved
        **/
        if(sonOfYAInDirOfImbalPtr->bal == imbal)
        {
            /// youngest ancestor and its son have been unbalanced in the same direction
            travPtr = sonOfYAInDirOfImbalPtr;
            if(imbal == 1)  // node inserted is a left descendant of youngest ancestor
            {
                performRightRotation(youngestAncestorPtr);
            }
            else // node inserted is a left descendant of youngest ancestor
            {
                performLeftRotation(youngestAncestorPtr);
            }
            youngestAncestorPtr->bal = 0;
            sonOfYAInDirOfImbalPtr->bal = 0;
        }
        else
        {
            /// youngest ancestor and its son are unbalanced in opposite directions ///
            if(imbal == 1)  // node inserted is a left descendant of youngest ancestor
            {
                travPtr = sonOfYAInDirOfImbalPtr->right;
                performLeftRotation(sonOfYAInDirOfImbalPtr);
                youngestAncestorPtr->left = travPtr;
                performRightRotation(youngestAncestorPtr);
            }
            else  // node inserted is a right descendant of youngest ancestor
            {
                travPtr = sonOfYAInDirOfImbalPtr->left;
                youngestAncestorPtr->right = travPtr;
                performRightRotation(sonOfYAInDirOfImbalPtr);
                performLeftRotation(youngestAncestorPtr);
            }

            /* adjusting the balance fields of the nodes involved in rotations */
            if(travPtr->bal == 0)
            {
                youngestAncestorPtr->bal = 0;
                sonOfYAInDirOfImbalPtr->bal = 0;
            }
            else
            {
                if(travPtr->bal == imbal)
                {
                    youngestAncestorPtr->bal =  -1 * imbal;
                    sonOfYAInDirOfImbalPtr->bal = 0;
                }
                else
                {
                    youngestAncestorPtr->bal = 0;
                    sonOfYAInDirOfImbalPtr->bal = imbal;
                }
                travPtr->bal = 0;
            }
        }
        /// adjusting the pointer to the rotated subtree
        if(youngestAncestorPtrFather == NULL)
        {
            root = travPtr;
        }
        else
        {
            if(youngestAncestorPtr == youngestAncestorPtrFather->right)
            {
                youngestAncestorPtrFather->right = travPtr;
            }
            else
            {
                youngestAncestorPtrFather->left = travPtr;
            }
        }
    }

    void inorderTravCaller()
    {
        AVLTreeNode<K, D> *tempPtr = root;
        inorderTrav(tempPtr);
    }

    // function to traverse the tree in in-order fashion on the console
    void inorderTrav(AVLTreeNode<K, D> *travPtr)
    {
        if(travPtr == NULL)
        {
            return;
        }

        if(travPtr->left != NULL)
        {
            inorderTrav(travPtr->left);
        }

        cout << travPtr->key << " ";

        if(travPtr->right != NULL)
        {
            inorderTrav(travPtr->right);
        }
    }

    AVLTreeNode<K, D>* searchKeyCaller(K key)
    {
        AVLTreeNode<K, D> *tempPtr = root;
        AVLTreeNode<K, D> *result = searchKeyAVL(key, tempPtr);
        return result;
    }

    // function to search a key in the AVL tree
    AVLTreeNode<K, D>* searchKeyAVL(K key, AVLTreeNode<K, D> *travPtr)
    {
        if(travPtr == NULL)
        {
            return NULL;
        }

        if(key == travPtr->key)
        {
            return travPtr;
        }

        if(travPtr->left != NULL && key < travPtr->key)
        {
            return searchKeyAVL(key, travPtr->left);
        }

        if(travPtr->right != NULL && key > travPtr->key)
        {
            return searchKeyAVL(key, travPtr->right);
        }
        return NULL;
    }

    friend class IndexCreator;
};

class TermDataNode
{
public:
    AVLTree<int> *setOfPageNumbersTree;
	TermDataNode()
	{
		setOfPageNumbersTree = NULL;
	}

	~TermDataNode()
	{
		delete(this);
	}

	friend class AVLTreeNode<string, TermDataNode>;
	friend class AVLTree<string, TermDataNode>;
};

class IndexCreator
{
	string termsFileName;
	string textToBeProcFileName;
	string optFileName;

	Trie* createTrieFromFile(string fn)
	{
		Trie* frmFileTrie = new Trie();
		ifstream fin;
		fin.open(fn);
		if(fin.fail())
		{
			cout << "\n\nCould not open the file " << fn << endl;
			exit(1);
		}

		string extrWord;
		while(fin.eof() != true)
		{
			getline(fin, extrWord);
			frmFileTrie->insertKey(extrWord);
		}
		fin.close();

		return frmFileTrie;
	}

public:
	IndexCreator(string termsFN, string textFN, string optFN)
	{
		termsFileName = termsFN;
		textToBeProcFileName = textFN;
		optFileName = optFN;
	}

	void saveIdxFilePN(ofstream* fosPtr, AVLTreeNode<int> *travPtr)
    {
        if(travPtr == NULL)
        {
            return;
        }

        if(travPtr->left != NULL)
        {
            saveIdxFilePN(fosPtr ,travPtr->left);
        }

        (*fosPtr) << travPtr->key;
        (*fosPtr) << ", ";

        if(travPtr->right != NULL)
        {
            saveIdxFilePN(fosPtr, travPtr->right);
        }
    }

	void saveIdxFile(ofstream* fosPtr, AVLTreeNode<string, TermDataNode> *travPtr)
    {
        if(travPtr == NULL)
        {
            return;
        }

        if(travPtr->left != NULL)
        {
            saveIdxFile(fosPtr ,travPtr->left);
        }

        (*fosPtr) << travPtr->key;
        (*fosPtr) << " ";
        saveIdxFilePN(fosPtr ,travPtr->dataNode->setOfPageNumbersTree->root);
        (*fosPtr) << "\n";

        if(travPtr->right != NULL)
        {
            saveIdxFile(fosPtr, travPtr->right);
        }
    }

	void createIdx()
	{
		ofstream fos;
		ifstream fin;
        int currPageNumInText = 0;
		char tempCh;
		/**
		 * 	STEP 1: Process the input text file and remove all special symbols from that file
		 * 	after removing the special symbols saving the result into another file.
		**/
        {
    		// creating a copy of input file and processing it.
    		fos.open("inptTextAfterProcess1.txt");
    		if(fos.fail())
    		{
    			cout << "\n\nCould not open the file inptTextAfterProcess1.txt" << endl;
    			exit(1);
    		}
    		fin.open(textToBeProcFileName);
    		if(fin.fail())
    		{
    			cout << "\n\nCould not open the file " << textToBeProcFileName << endl;
    			exit(1);
    		}
    		int charCnt = 0;
    		while(fin.eof() != true)
    		{
    		    charCnt++;
    			fin.get(tempCh);
    			int tempChInt = tempCh;
    			bool prevIsValidCh;
    			if((tempChInt >= 64 && tempChInt <= 90) || (tempChInt >= 97 && tempChInt <= 122))
    			{
    			    prevIsValidCh = true;
                    fos.put(tempCh);
    			}
    			else
    			{
    			    if(prevIsValidCh == true)
                        fos.put('\n');
    			    prevIsValidCh = false;
    			}
    		}
    		fos.close();
    		fin.close();

        }
        cout << "\n*** STEP 1 SUCESS ***\n";
		/****************************************** STEP 1 - END *********************************************/

		/**
		 * 	STEP 2: Process the text file from the previous step and remove stop words
		 *  from that file after removing the stop words saving the result into another file.
		**/
        {
    		// create a trie of stop words
    		Trie *trieOfStopWords = createTrieFromFile("listOfStopWords.txt");

    		// creating a copy of inptTextAfterProcess1 and processing it.
    		fin.open("inptTextAfterProcess1.txt");
    		if(fin.fail())
    		{
    			cout << "\n\nCould not open the file inptTextAfterProcess1.txt" << endl;
    			exit(1);
    		}
    		fos.open("inptTextAfterProcess2.txt");
    		if(fos.fail())
    		{
    			cout << "\n\nCould not open the file inptTextAfterProcess2.txt" << endl;
    			exit(1);
    		}

    		// traversing the file received after step 1,word by word
    		// if that word appears in the trie we do not add it to the new file
    		string tempStr;
    		string newPageMarker = "@@@@@@@@@@";
    		while(fin.eof() != true)
    		{
    			getline(fin, tempStr);
                string tempStrLower;
                for(unsigned int k = 0; k < tempStr.length(); k++)
                {
                    tempStrLower += tolower(tempStr[k]);
                }
                bool partOfStopWordsFlag = trieOfStopWords->searchKey(tempStrLower);
                if(partOfStopWordsFlag == false)
                {
                    fos << tempStr << "\n";
                    tempStr = "";
                }
    		}
    		fos.close();
    		fin.close();
        }
        cout << "\n*** STEP 2 SUCESS ***\n";
		/****************************************** STEP 2 - END *********************************************/

        /**
         *  STEP 3: create the index using a trie of terms
         *  and store the index and in AVL Trees to keep it sorted.
        **/
        {
            // Create a trie of terms
            Trie *trieOfTerms = createTrieFromFile(termsFileName);

            // creating an AVL Tree to store the index
            AVLTree<string, TermDataNode> *completeIndex = new AVLTree<string, TermDataNode>();

            // creating a copy of inptTextAfterProcess2 and processing it.
            fin.open("inptTextAfterProcess2.txt");
            if(fin.fail())
            {
                cout << "\n\nCould not open the file inptTextAfterProcess2.txt" << endl;
                exit(1);
            }

            // traversing the file received after step 2, word by word
            // if that word appears in the trie we add it to the AVL Tree
            string newPageMarker = "@@@@@@@@@@";
            string tempStr;
            currPageNumInText = 1;
            while(fin.eof() != true)
            {
                getline(fin, tempStr);
                if(tempStr == newPageMarker)
                {
                    currPageNumInText++;
                }
                string tempStrLower = "";
                for(unsigned int k = 0; k < tempStr.length(); k++)
                {
                    tempStrLower += tolower(tempStr[k]);
                }
                bool partOfTermsTrie = trieOfTerms->searchKey(tempStrLower);
                if(partOfTermsTrie == true)
                {
                    AVLTreeNode<string, TermDataNode> *serResPtr = completeIndex->searchKeyCaller(tempStrLower);
                    if(serResPtr == NULL)    // current term has not been added to the tree
                    {
                        // create a new node for terms
                        TermDataNode *termNodeTemp = new TermDataNode();
                        // create a new AVL tree for page numbers associated with this node
                        termNodeTemp->setOfPageNumbersTree = new AVLTree<int>();
                        // add the current page number to page number tree
                        termNodeTemp->setOfPageNumbersTree->insertKey(currPageNumInText, NULL);
                        // add the complete node to the complete index tree
                        completeIndex->insertKey(tempStrLower, termNodeTemp);
                    }
                    else
                    {
                        TermDataNode *tempTermPtr = serResPtr->dataNode;
                        if(tempTermPtr->setOfPageNumbersTree->searchKeyCaller(currPageNumInText) == NULL)
                            tempTermPtr->setOfPageNumbersTree->insertKey(currPageNumInText, NULL);
                    }
                    tempStr = "";
                }
            }
            fin.close();

            // saving the index in the opt.txt file by traversing the AVL trees in-order
            ofstream *fosPtr = new ofstream();
            fosPtr->open(optFileName);
            if(fosPtr->fail())
            {
                cout << "\n\nCould not open the file " << optFileName << endl;
                exit(1);
            }
            saveIdxFile(fosPtr, completeIndex->root);
            fosPtr->close();
        }
        cout << "\n*** STEP 3 SUCESS ***\n";
        /****************************************** STEP 3 - END *********************************************/
    }
};

int main(int argc, char *argv[])
{
	cout << "+-----------------+";
	cout << "\n| INDEX GENERATOR |\n";
	cout << "+-----------------+";

	if(argc < 4)
	{
		cout << "\n\nINSUFFCIENT ARGUMENTS PASSED !!!\n";
		cout << "\nUSE: name_of_executable_file file_1.txt file_2.txt file_3.txt\n\n";
		cout << "File 1: - Contains words to be indexed on each new line.(ensure no space after the word)\n";
  		cout << "File 2: - Contains the text to be processed.\n";
 		cout <<	"        - New pages are indicated by 10 hyphens in a row ('-')\n";
		cout << "File 3: - The file in which the index is to be saved.\n";
		exit(1);
	}

	string termsFileName = argv[1];
	string textToBeProcFileName = argv[2];
	string optFileName = argv[3];

	ifstream fin;
	fin.open(termsFileName);
	if(fin.fail())
	{
		cout << "\n\nCould not open the file " << termsFileName << endl;
		exit(1);
	}
	fin.close();


	fin.open(textToBeProcFileName);
	if(fin.fail())
	{
		cout << "\n\nCould not open the file " << textToBeProcFileName << endl;
		exit(1);
	}
	fin.close();

	fin.open(optFileName);
	if(fin.fail())
	{
		cout << "\n\nCould not open the file " << optFileName << endl;
		exit(1);
	}
	fin.close();

	IndexCreator idxCreatorObj = IndexCreator(termsFileName, textToBeProcFileName, optFileName);
	idxCreatorObj.createIdx();

	return 0;
}
