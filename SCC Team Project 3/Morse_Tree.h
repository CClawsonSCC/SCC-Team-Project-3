#ifndef MORSE_TREE_H
#define MORSE_TREE_H

#include "Binary_Tree.h"
#include <fstream>

using namespace std;

template<typename T>
class Morse_Tree : public Binary_Tree<T> {
public:
	// Constructor
	Morse_Tree() : Binary_Tree<T>() {}

	// Memberfunction
	virtual bool insert(const T&, string&);
	string decode(string&);

private:
	virtual bool insert(BTNode<T>*& , const T& , string& );
	string decode(BTNode<T>*& , string& );
	char find_letter(BTNode<T>*& , string& );
};

/** Insert character to tree.
	@param item alhabet chracter
	@param path: dot and dash code
	@return {true} when successful, {false} otherwise. 
	*/
template<typename T>
bool Morse_Tree<T>::insert(const T& item, string& path) {

	return insert(this->root, item, path);
}

template<typename T>
bool Morse_Tree<T>::insert(BTNode<T>*& local_root, const T& item, string& path) {

	char travelkey;
	int i;
	string next_path;
	travelkey = path[0];

	// Traversing over empty nodes - ensures letters may be entered out of order
	if (local_root == NULL && !path.empty()) {
		local_root = new BTNode<T>('1'); // Temporarily set nodes so they may be access/changed later - Prevents data leak
	}

	// Build remaining code/path
	for (i = 1; i < path.size(); i++) { next_path += path[i]; }

	// At proper location temporarily occupied by '1'
	if (local_root != NULL && path.empty()) { local_root->data = item; }

	// At proper location, node empty
	if (local_root == NULL && path.empty()) {
		local_root = new BTNode<T>(item);
		return true;
	}
	// Traversal incomplete
	else {
		// '.' = left, '_' = right, otherwise the morse_code string is invalid and insertion will fail
		if (travelkey == '.') { return insert(local_root->left, item, next_path); }
		else if (travelkey == '_') { return insert(local_root->right, item, next_path); }
		else { return false; }
	}
}

/*Translate code into Alphabet.
	@param code morse code that need to translate
	@return the message which is in alphabet format. 
	*/ 
template<typename T>
string Morse_Tree<T>::decode(string& code) {
	return decode(this->root, code);
}

template<typename T>
string Morse_Tree<T>::decode(BTNode<T>*& local_root, string& code) {

	string letter_code;
	string message;
	char here;
	int i;
	// Read the morse code character by character (or code by code, dot by dot, w/e)
	for (i = 0; i < code.size(); i++) {
		here = code[i];

		// Rebuild the morse code for an individual letter. A space indicates a new letter
		if (here != ' ') {
			letter_code += here;
		}
		// If end of letter (or word), find the letter from the tree and append it to the decoded message
		if (here == ' ' || i == (code.size() - 1)) {
			message += find_letter(local_root, letter_code);
			letter_code = ""; // Resets letter_code to read next letter
		}
	}
	return message;
}

// Finds a letter in the tree based on a morse code path - Only called within decode()
template<typename T>
char Morse_Tree<T>::find_letter(BTNode<T>*& local_root, string& path) {

	char travelkey;
	int i;
	string next_path;

	travelkey = path[0];

	for (i = 1; i < path.size(); i++) { next_path += path[i]; }

	if (path.empty()) { return local_root->data; } // Finished traversing, you've arrived at your destination letter
	else {
		if (travelkey == '.') { return find_letter(local_root->left, next_path); }
		else if (travelkey == '_') { return find_letter(local_root->right, next_path); }
	}

	return 0;
}

#endif // !MORSE_H

