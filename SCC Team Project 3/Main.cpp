#include "Morse_Tree.h"
#include <iostream>
#include <fstream>
#include <string>

void build_tree(Morse_Tree<char>& thetree)
{

	BTNode<char>* node;
	string line;

	node = new BTNode<char>('0'); // The data in the root of the tree should never be accessed
	thetree.set_root(node);
	ifstream fin("Morse_Code.txt");

	if (!fin) { cout << "[Error] None existent Morse_Code file" << endl; }
	else {
		while (getline(fin, line)) {
			char alphakey = line[0];
			string morsecode;
			for (size_t i = 1; i < line.size(); i++) { morsecode += line[i]; }
			thetree.insert(alphakey, morsecode);
		}
	}
}

int main()
{
	// Variable declaration
	string code_message;

	Morse_Tree<char> tree;

	build_tree(tree);

	cout << "Please enter a morse code message ( . and _ only, separate letters with spaces ): ";
	getline(cin, code_message);
	cout << endl << "The text for your Code Message is: " << tree.decode(code_message) << endl << endl;
	
	cout << "Please enter a word to encode (lowercase alphabet only): ";
	getline(cin, code_message);
	cout << endl << tree.encode(code_message) << endl << endl;

	system("pause");
	return 0;
}