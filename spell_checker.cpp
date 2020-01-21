#include <iostream>
#include <string>
#include <sstream>
#include<fstream>
#include <algorithm>
#include "bst.h"

using namespace std;

//checks to make sure that there is an input file and stores it in a string to be used for opening the file, uses argc and argv to check through argurments and inputFile to store the name of the file
string checkForInputFile(int argc,char **argv, string inputFile)
{
	for(int i = 0;i < argc ; i++)//loops for all arguements
	{
		if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-I") == 0 )// checks if the argument has either -i or -I, if true it returns 0, if false returns -1
		{	
			inputFile=argv[i+1];//sets the inputfile to the following arguement after -i or -I has been found
			return inputFile;
		}
		else
		{
			inputFile = "NULL";//if no file -i or -I is found inputfile is set to NULL
		}
	}
	return inputFile;
}

// opens a file and places all the words from it into a BinarySearchTree, only takes in the dictionaryTree as it is declared in main 
void inputFromDictionary(BinarySearchTree *dictionaryTree)
{
	//sets a ifstream and opens the file
	ifstream inputFileDictionary;
	inputFileDictionary.open("dictionary.txt");
	string words;
	//exits program if the file cant be openedW
	if(!inputFileDictionary)
	{
		cerr<<"there was a problem opening dictionary.txt"<<endl;
		exit(1);
	}
	//declares a string and reads through every word in the dictionary and uses the insert function in BinarySearchTree to place a word in the tree
	while(inputFileDictionary >> words)
	{
		//changes all letters to lower case
		transform(words.begin(), words.end(), words.begin(),::tolower);
		dictionaryTree->insert(words);
	}
	//closes the file as its no longer required.
	inputFileDictionary.close();
}

//opens a inputfile and checks through each word and checks if that word exists  in the tree
void inputFromFileAndCompare(int argc, char **argv,BinarySearchTree *dictionaryTree)
{
	
	string words;
	ifstream inputFileSpellChecked;
	string inputfile;
	//checks if there is a input file declared
	inputfile = checkForInputFile(argc,argv, inputfile);
	//opens the file
	inputFileSpellChecked.open(inputfile);
	//exits the program if there is a issue opening the file
	if(!inputFileSpellChecked)
	{
		cerr<<"there was a problem opening the file that should be checked"<<endl;
		exit(1);
	}
	
	bool wordexists;
	long index = 0;
	//checks through every word
	while(inputFileSpellChecked>>words)
	{
		//removes all puntucation
		words.erase (std::remove_if (words.begin (), words.end (), ispunct), words.end ());
		//changes all characters to lower case
		transform(words.begin(), words.end(), words.begin(),::tolower);
		//increases index by 1 showing that its another word
		index=index+1;
		//checks if the word is in the dictionary
		wordexists = dictionaryTree->exists(words);
		
		//if the word doesnt exist it prints out that the word is spelt wrong and where it is in the file
		if(wordexists == false)
		{
			cout<<"The word " << words <<" was spelt incorrectly in position " << index <<endl;
		}
	}
	
}

void deleteTree(BinarySearchTree *dictionaryTree)
{
	//deletes the tree and frees all the nodes
	delete dictionaryTree;
}

int main(int argc, char **argv)
{
	//creates a BinarySearchTree
	BinarySearchTree *dictionaryTree = new BinarySearchTree();
	inputFromDictionary(dictionaryTree);
	inputFromFileAndCompare(argc,argv,dictionaryTree);
	deleteTree(dictionaryTree);
}