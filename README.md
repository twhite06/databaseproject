 # Database - Word - Search
 
 README
 *
 * Author: Tim White 
 * Date: 11/15/2019


Program Purpose:

	
	This program works very similar to the Grep Linux command indexes all words in a given root directory file through
	hashing and allows you to query them.


Files:

--> design.txt:

    	Explains my plan for the project and what I should be doing. Though my plan
    in the beginning stayed the same for the most part throughout the project,
    a few things changed as I optimized the project. During my implementation
    I actually decided to change my structure from a array of vectors which
    contained wordContents to an array of vectors which contained the lowercase 
    version of a word and another vector of word contents.

--> DirNode.h:

    	Used to create nodes on the tree I am using.

--> FSTree.h:

    	Used to create tree with the DirNode file.

--> main.cpp:

    	This file was originally FSTreeTraversal, but I ended up making it become 
    my main driver. I run the main starter commands through this file and also 
    have teo functions in this file that traverses and hashes the tree as well
    as search query and search the tree. Main is very useful for me to be able 
    to store the paths that I needed to print out from the query search.

--> stringProcessing.cpp:

    	Does the string stripping for the query searching to take off any 
    leading or trailing non-alphaNum characters the user types.

--> stringProcessing.h:

    	Declaration for the string strip function

--> Makefile:

    	Creates the commands for compilation

--> HashClass.cpp:

    	Contains the function for doing the hashing of each word from the file and 
    placing it in the hash table structure. Once each word has been hashed, the
    class also is able to do the searching and printing to outfile (cout or 
    file output).




Data Structures:

	Hash Table with array of vectors. Each vector has in it a string lowercase word and a Vector of 
	word contents (every instance of that word). 
	
	4 structs for information needed to be stored. Linecontent stores the string of
	the line and int of the line number. Indexes stores the index of the line and
	path vector that holds the information needed. WordContent stores the word read 
	in and a vector of indexes for my line and path vectors. Bucketdata stores the 
	lower case version of a word and a vector of wordContents 


Testing:

	Instead of a testing main this time I tested each step as I was building my 
	hash class. Once I declared my initial hash structure, I pushed test values 
	onto the vectors at each index and printed our that information to make sure 
	the main structure was working well. Then when I created an instance of my
	wordContent struct I printed out the information stored inside of the string
	and vector of the Wordcontent. After this, I made surer that the information
	inside of my auxilarry vectors was being correctly pushed and I printed out 
	all of the line and path info in these vectors. I also had a test printing
	function that printed out the current index of the main structure (array), the
	index of the vector in which I am currently in (within same bucket), and the
	word content inside of my word content vector. I used this test function for
	many things throughout my project to make sure the words that I was storing
	were correct. I encountered a seg fault that I was stuck on for over a week, but
	knowing the exact index of the main array, word, and line/path content was very helpful
	in finding this error. I also used 44 cerr statements in trying to find all 
	of my bugs, mainly the ones caused by the seg fault. I have attached the main 
	testing functions below:

// Tests I Conducted little by little while building my HashClass

    --> test main array of vectors to make sure it is functioning
    ---> test 1: push_back 1 element and two elements in second while
    --> test 2 for expand: push back 8 elements to trigger expand
     wordContent w1, w2, w3, w4;
     w1.word = "test word";
     w1.indexes.push_back(1);
     w1.indexes.push_back(2);
     w2.word = "test word 2 ;)";
     w2.indexes.push_back(3);
     w2.indexes.push_back(4);
    // added to test expand
     w3.word = "test word 3 :O";
     w3.indexes.push_back(1);
     w3.indexes.push_back(2);
     w4.word = "test word 4 ;-[";
     w4.indexes.push_back(3);
     w4.indexes.push_back(4); 
     int i = 0;
     while (i < 5){
         data[i].push_back(w1);
         data[i].push_back(w2);
         data[i].push_back(w4);
         data[i].push_back(w3);
         wordsStored += 4;
         i++;
     }
     while (i < 10){
          data[i].push_back(w2);
          data[i].push_back(w1);
          data[i].push_back(w3);
          data[i].push_back(w4);
          wordsStored += 4;
          i++;  
     }
     for (int i = 0; i < 10; i++){
          for (size_t j = 0; j < data[i].size(); j++){
              cout << data[i][j].word << endl;
              cout << data[i][j].indexes[0] << endl;
              cout << data[i][j].indexes[1] << endl;         
          }
     }

    --> test to make sure expand works
         for (int i = 0; i < 3; i++){
             cout << "Main array index: " << i << endl;
             for (size_t j = 0; j < data[i].size(); j++){
                 cout << data[i][j].word << endl;
                 cout << data[i][j].indexes[0] << endl;
                 cout << data[i][j].indexes[1] << endl;         
             }
             cout << " " << endl;
         }


    --> test that hashing returns a valid slot
     cout << "Put in " << bucket << "slot." << endl;

    --> test to make sure main data array has right elements
     for (int i = 0; i < capacity; i++){
         cout << "Main array index: " << i << endl;
         for (size_t j= 0; j < data[i].size(); j++){
             cout << data[i][j].word << endl;
             for (size_t k = 0; k < data[i][j].LPInfo.size(); k++){
                 cout << "line index: " << data[i][j].LPInfo[k].line << endl;
                 cout << "path index: " << data[i][j].LPInfo[k].path << endl;
             }
         }
         cout << " " << endl;
     }
    
    --> test to make sure that the lineStuff vector has all of the correct stuff
     for (size_t i = 0; i < lineStuff.size(); i++){
         cout << lineStuff[i].line  + ": ";
         cout << lineStuff[i].lineNum << endl;
     }
     
    ---> test to make sure that the paths vector has all of the correct stuff
     for (size_t i = 0; i < paths.size(); i++){
         cout << paths[i] << endl;
    }
    
    --> debugging function to try and print the exact indexes where my program was
    seg faulting for over a week (index 5 for large Gutenberg and index 7 for 
    small Gutenberg)

	void HashClass:: printForTest(){;
	    for (size_t i = 0; i < data[5].size(); i++){
		for (size_t j = 0; j < data[5][i].WCVec.size(); j++){
		    for (size_t k = 0; k < data[5][i].WCVec[j].LPInfo.size(); k++){
		    }
		}
	    }
	}

Error:
My words are being stored and printing twice
