#include "bst.h"
using namespace std;
// checks if a word exists in a tree, takes in a root of the tree that it will look through, and the word that is being searched for
bool wordexists(Node *tree, string word)
{	
	//loops around the entire of the tree until it finds the word or reaches the end of the tree
	while(tree != nullptr)
	{
		//breaks out of the tree if the word is the same as the word in the current node
		if(tree->data ==word)
		{
			break;
		}
		if (word > tree->data)
		{
			//goes down to the right if the word is larger than the node
			tree = tree->right; 
		}
		else
		{
			if (word < tree->data)
			{
				//goes down to the left if the word is smaller than the node
				tree = tree->left; 
			}	
		}
	}
	//returns false if it reached the end of the tree without finding the word, if it does find the word it will return true.
	if (tree == nullptr)
	{
		return false;
	}
	if(tree->data ==word)
	{
		return true;
	}
}

//takes a word and inserts it into the tree
Node* insertword(Node *tree, string words)
{
	//if the current node is a nullptr(ie the tree is empty) a new node is created and the data placed in it, if the tree exists it will figure out if the word is larger or smaller and place it in the node that it fits in, if the word already exists in the tree it will not be placed in the tree
	if(tree == nullptr)
	{
		//sets up the node
		tree = new Node;
		tree->data = words;
		tree->left = nullptr;
		tree->right = nullptr;
	}else
	{
		//if the word is smaller than the data it will go to the left, if it is larger it goes right
		if(words < tree->data)
		{
			tree->left=insertword(tree->left,words);
		}
		else if(words > tree->data)
		{
			tree->right=insertword(tree->right,words);
		}
	}
	return tree;
}

//sets up the output of all the words in the tree inorder
string inorderoutput(Node *tree,string output)
{
	//checks to make the tree exists
	if(tree != nullptr)
	{
		//goes down the tree in order and adds it to the output
		output=inorderoutput(tree->left,output);
		output=output+tree->data+" ";
		output=inorderoutput(tree->right,output);
	
	}
	return output;
}

string preorderoutput(Node *tree,string output)
{
	//checks to make the tree exists
	if(tree != nullptr)
	{
		//goes down the tree in order and adds it to the output
		output=output=output+tree->data+" ";
		output=preorderoutput(tree->left,output);
		output=preorderoutput(tree->right,output);	
	}
	return output;
}

string postorderoutput(Node *tree,string output)
{
	//checks to make the tree exists
	if(tree != nullptr)
	{
		//goes down the tree in order and adds it to the output
		output=postorderoutput(tree->left,output);
		output=postorderoutput(tree->right,output);	
		output=output=output+tree->data+" ";
	}
	return output;
}

//helps find what would be the next smaller word in the tree
Node* removehelpershelper(Node* tree)
{
	if(tree==nullptr)
	{
		return nullptr;
	}
	while(tree->right != nullptr)
	{
		tree=tree->right;
	}
	return tree;
}

//removes a word from the tree by searching through for it
Node* removehelper(Node *tree, string word)
{
	//checks if the tree exists
	if(tree == nullptr)
	{
		return tree;
	}
	//searchs if the word is larger or smaller and moves through the tree appropriately
	else if(word < tree->data)
	{
		tree->left = removehelper(tree->left, word);
		
	}
	else if(word > tree->data)
	{
		tree->right = removehelper(tree->right, word);
	}
	else
	{
		//decides how it will have to delete the node
		if(tree->left == nullptr && tree->right == nullptr)
		{
			//no child Node
			delete tree;
			tree=nullptr;	
		}else if(tree->left == nullptr)
		{
			//left child node
			//replaces the left tree with the one on the right
			tree=tree->right;
		}
		else if(tree->right==nullptr)
		{
			//right child node
			//replaces the right tree with the one on the left
			tree=tree->left;
		}
		else
		{
			//two child nodes
			
			//sets the temperory node to what would be the next smaller node and places that into the tree
			Node *temperory = removehelpershelper(tree->left);
			tree->data= temperory->data;
			//goes back the the left of the tree and removes the value that would now be duplicated.
			tree->left = removehelper(tree->left, temperory->data);
		}

	}
	return tree;
	
}
//copy's the entire of one tree into the other tree, takes in tree which was a blank tree, and rhstree which contains all of teh data from the other tree.
Node* copytree(Node *tree, Node *rhstree)
{
	//checks if the tree it is copying from has reached the end(or doesnt exist)
	if (rhstree != nullptr)
	{	
		//creates a new node for the tree, adds the data from the other tree into a string , and then places that string into the new tree, goes through all of the tree and copys everything
		tree = new Node;
		string word;
		word = rhstree->data;
		tree->data = word;
		tree->left=copytree(tree->left,rhstree->left);
		tree->right=copytree(tree->right,rhstree->right);
	}
	return tree;
}
//will free up memory from the nodes by deleting all of them from the tree.
void delete_tree(Node *root)
{
	//checks if the tree is empty
	if(root == nullptr)
	{
		return;
	}
	//calls to delete the tree using a helper function
	delete_tree(root->left);
	delete_tree(root->right);

	delete(root);
	
}

// Creates an empty binary tree
BinarySearchTree::BinarySearchTree()
{
	//creates a new tree
	Node *tree = new Node;
	tree->left = nullptr;
	tree->right = nullptr;
}


// Creates a binary tree with an initial value to store
BinarySearchTree::BinarySearchTree(string word)
{
	//places the word in the tree
	root=insertword(root,word);
}


// Creates a binary tree by copying an existing tree
BinarySearchTree::BinarySearchTree(const BinarySearchTree &rhs)
{
	//creates a node with pointers based on the root of a second tree and uses the copytree function to create a full copy(that doesnt use the pointers from the other tree)
	Node *oldroot= rhs.root;
	root=copytree(root,oldroot);
}

// Destroys (cleans up) the tree
BinarySearchTree::~BinarySearchTree()
{
	//deletes the tree then sets it to a nullptr so that tests that run later cna show that the tree is empty
	delete_tree(root);
	root=nullptr;
}

// Adds a word to the tree
void BinarySearchTree::insert(string word)
{
	
	root=insertword(root,word);
}

// Removes a word from the tree
void BinarySearchTree::remove(string word)
{
	
	root=removehelper(root,word);
}

// Checks if a word is in the tree
bool BinarySearchTree::exists(string word) const
{
	//returns if the word exists in the tree(returns as a bool)
  return wordexists(root,word);
}

// Prints the tree to standard out in numerical order
std::string BinarySearchTree::inorder() const
{
	//creates a string and gets the output inorder, then removes the extra space that will be at the end(if there is a data put in) and then outputs it to the screen but also returns it to output
	string output="";
	output= inorderoutput(root,output);
	if (output.size () > 0)  
	{
		output.resize (output.size () - 1);
	}
	cout<<"this is the output for inorder " + output<<endl;
    return output;
}

// Prints the tree in pre-order
std::string BinarySearchTree::preorder() const
{
	//creates a string and gets the output preorder, then removes the extra space that will be at the end(if there is a data put in) and then outputs it to the screen but also returns it to output
	string output="";
	output= preorderoutput(root,output);
	if (output.size () > 0)  
	{
		output.resize (output.size () - 1);
	}
	cout<<"this is the output for preorder " + output<<endl;
    return output;
}

// Prints the tree in post-order
std::string BinarySearchTree::postorder() const
{
	//creates a string and gets the output postorder, then removes the extra space that will be at the end(if there is a data put in) and then outputs it to the screen but also returns it to output
   	string output="";
	output=postorderoutput(root,output);
	if (output.size () > 0)  
	{
		output.resize (output.size () - 1);
	}
	
	cout<<"this is the output for postorder " + output<<endl;
    return output;
}


// Checks if two trees are equal
bool BinarySearchTree::operator==(const BinarySearchTree &other) const
{
	//compares the output from two strings and if it is the same it returns true and if it doesnt it returns false
	string output= "";
	string outputothertree= "";
	Node *othertree = other.root;
	
	output = inorderoutput(root, output);
	outputothertree = inorderoutput(othertree, outputothertree);
	if (output == outputothertree)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

// Checks if two trees are not equal
bool BinarySearchTree::operator!=(const BinarySearchTree &other) const
{
	//compares the output from two strings and if it is the same it returns false and if it doesnt it returns true
	string output= "";
	string outputothertree= "";
	Node *othertree = other.root;
	output = inorderoutput(root, output);
	outputothertree = inorderoutput(othertree, outputothertree);
	if (output == outputothertree)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}


// Reads in words from an input stream into the tree
std::istream& operator>>(std::istream &in, BinarySearchTree &tree)
{
	//inserts the word into the tree that is specificied  
	Node *oldroot = tree.root;
	string words;
	while(in >> words)
	{
		Node *oldroot = tree.root;
		tree.insert(words);
	}
	return in;
}

// Writes the words, in-order, to an output stream
std::ostream& operator<<(std::ostream &out, const BinarySearchTree &tree)
{
	//puts the output into output stream
	Node *oldroot = tree.root;
	string output; 
	output = inorderoutput(oldroot, output);
	if (output.size () > 0)  
	{
		output.resize (output.size () - 1);
	}
	out << output;
    return out;
}

