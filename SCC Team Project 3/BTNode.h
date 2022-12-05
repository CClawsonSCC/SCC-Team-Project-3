#ifndef BTNODE_H
#define BTNODE_H

#include <iostream>
#include <sstream>
#include <string>

using std::ostream;
using std::ostringstream;
using std::string;

/** A binary tree node */
template<class T>
struct BTNode {
	// Data Fields
	T data; // Stores some data in the node.
	BTNode<T>* left, * right; // Stores pointers to the left and right child.

	// Constructor
	BTNode(const T&, BTNode<T>* = NULL, BTNode<T>* = NULL);

	// Destructor
	virtual ~BTNode(); // Avoid warning messages.

	// Class-member function
	virtual string to_string() const; // Returns a string containing the data stored in the node.
};

// Constructor
template<class T>
BTNode<T>::BTNode(const T& data, BTNode<T>* left, BTNode<T>* right) : data(data), left(left), right(right) {}

// Destructor
template<class T>
BTNode<T>::~BTNode() {} // Avoid warning messages.

/** Returns a string containing the data stored in the node.
	@return: a string containing the data stored in the node
*/
template<class T>
string BTNode<T>::to_string() const {
	ostringstream oss;
	oss << data;
	return oss.str();
}
// Overloading the ostream insertion operator
template<class T>
ostream& operator << (ostream& out, const BTNode<T>& node) { return out << node.to_string(); }
#endif // !BTNODE_H

