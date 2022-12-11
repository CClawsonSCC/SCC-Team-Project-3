#ifndef MORSE_TREE_H
#define MORSE_TREE_H

#include "Binary_Tree.h"
#include <fstream>
#include <algorithm>

using namespace std;

template<typename T>
class Morse_Tree : public Binary_Tree<T> {
public:
	// Constructor
	Morse_Tree() : Binary_Tree<T>() {}

	// Member functions
	virtual bool insert(const T&, const string&);
	string decode(const string&);
	string encode(const string&);

private:

	// Member functions
	virtual bool insert(BTNode<T>*&, const T&, const string&);
	string decode(BTNode<T>*&, const string&);
	char find_letter(BTNode<T>*&, string&);
	bool encode_letter(BTNode<T>*&, const char, string&);
};

/* Member Functions */

/** Insert character to tree.
	@param item - Alhabet chracter.
	@param path - Dot and dash code.
	@return {true} when successful, {false} otherwise. 
	*/
template<typename T>
bool Morse_Tree<T>::insert(const T& item, const string& path) {

	return insert(this->root, item, path);
}

/**
 * @brief Inserts a character into a binary tree to a node based on its morse code pattern.
 * @param local_root - The current node in the morse code tree.
 * @param item - The character to be inserted.
 * @param path - Morse code string representing {item}.
 * @return {true} if the character was inserted successfully, {false} otherwise.
*/
template<typename T>
bool Morse_Tree<T>::insert(BTNode<T>*& local_root, const T& item, const string& path) {

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

/**
 * @brief Translates code into Alphabet.
 * @param code - Morse code that need to translate.
 * @return The message which is in alphabet format. 
*/ 
template<typename T>
string Morse_Tree<T>::decode(const string& code) {
	return decode(this->root, code);
}

/**
 * @brief Translates a string into morse code.
 * @param input - The string to me encoded.
 * @return A morse code string.
*/
template<typename T>
string Morse_Tree<T>::encode(const string& input)
{
	string morse = "";
	for (size_t i = 0; i < input.size(); i++)
	{
		encode_letter(this->root, input.at(i), morse);
		morse += " ";
	}
	reverse(morse.begin(), morse.end());
	return morse;
}

/* Private functions below. */

/**
 * @brief Decodes a morse code string into its alphabetic form.
 * @param local_root - The current node in the morse code tree.
 * @param code - The morse code string.
 * @return the decoded word.
*/
template<typename T>
string Morse_Tree<T>::decode(BTNode<T>*& local_root, const string& code) {

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

/**
 * @brief Finds a letter in the tree based on a morse code path - Only called within decode().
 * @param local_root - The current node in the tree.
 * @param path - A morse code string that will direct the path to the letter.
 * @return The letter the morse code represents.
*/
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

/**
 * @brief Creates a string of '.' and '_' characters to represent the morse code of a letter.
 * @param local_root - The current node in the tree.
 * @param letter - The letter to be encoded.
 * @param morse - String of dots and dashes of the letter
 * @return The morse string.
*/
template<typename T>
bool Morse_Tree<T>::encode_letter(BTNode<T>*& local_root, const char letter, string& morse)
{
	if (!local_root) { return false; }
	if (local_root->data == letter) { return true; }
	if (encode_letter(local_root->left, letter, morse))
	{
		morse += ".";
		return true;
	}
	if (encode_letter(local_root->right, letter, morse))
	{
		morse += "_";
		return true;
	}
	return false;
}

#endif // !MORSE_H