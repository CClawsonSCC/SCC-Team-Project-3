#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "BTNode.h"

#include <cstddef>
#include <algorithm>
#include <vector>

using std::vector;
using std::istream;
using std::istringstream;

/** A binary tree class */
template<typename T>
class Binary_Tree {
public:
	void set_root(BTNode<T>* new_root);
	BTNode<T>* get_root();
	// Constructors and Functions

	/** Construct an empty Binary_Tree. */
	Binary_Tree() : root(NULL) {}

	/** Construct a Binary_Tree with two subtrees.
	@param the_data The data at the root
	@param left_child The left subtree
	@param right_child The right subtree
	*/
	Binary_Tree(const T& the_data,
		const Binary_Tree<T>& left_child
		= Binary_Tree(),
		const Binary_Tree<T>& right_child
		= Binary_Tree()) :
		root(new BTNode<T>(the_data, left_child.root,
			right_child.root)) {}

	/** Virtual destructor to avoid warnings */
	virtual ~Binary_Tree() {} // Do nothing.

	/** Return the left subtree. */
	Binary_Tree<T> get_left_subtree() const;

	/** Return the right subtree. */
	Binary_Tree<T> get_right_subtree() const;

	bool is_binary_search();

	/** Return the data field of the root.*/
	const T& get_data() const;

	/** Indicate that this is the empty tree. */
	bool is_null() const;

	/** Indicate that this tree is a leaf. */
	bool is_leaf() const;

	/** Return a string representation of this tree. */
	virtual string to_string() const;

	/** Read a binary tree */
	static Binary_Tree<T> read_binary_tree(istream& in);

	void read_tree(vector<string>& text);

	Binary_Tree<T> read_binary_tree(vector<string>& text, int& i);

	/** Return a string representation of the root */
	string root_to_string() const {
		return root->to_string();
	}

	/** Return a pre-order traversal of the tree */
	string pre_order() const {
		return pre_order(root);
	}

	/** Return a post-order traversal of the tree */
	string post_order() const {
		return post_order(root);
	}

	string in_order() const {
		return in_order(root);
	}

	int height() const {
		if (is_null()) { return 0; }
		return 1 + std::max(get_left_subtree().height(), get_right_subtree().height());
	}
	int number_of_nodes() const {
		if (is_null()) { return 0; }
		return 1 + get_left_subtree().number_of_nodes() + get_right_subtree().number_of_nodes();
	}

protected:

	// Protected constructor
	/** Construct a Binary_Tree with a given node as the root */
	Binary_Tree(BTNode<T>* new_root) : root(new_root) {}

	// Data Field
	BTNode<T>* root;

private:
	std::string pre_order(const BTNode<T>* local_root) const;
	std::string post_order(const BTNode<T>* local_root) const;
	std::string in_order(const BTNode<T>* local_root) const;
}; 

template<typename T>
bool Binary_Tree<T>::is_binary_search(){
	bool result=true;
	is_binary_search(this->root, result);
	return result;
}

template<typename T>
void Binary_Tree<T>::set_root(BTNode<T>* new_root) { root = new_root; }

template<typename T>
BTNode<T>* Binary_Tree<T>::get_root() {
	return root;
}

// Overloading the ostream insertion operator.
template<typename T>
ostream& operator<<(ostream& out, const Binary_Tree<T>& tree) { return out << tree.to_string(); }

// Overloading the istream extraction operator
template<typename T>
istream& operator>>(istream& in, Binary_Tree<T>& tree) {
	tree = Binary_Tree<T>::read_binary_tree(in);
	return in;
}

// Implementation of member functions

// Accessors
/** Return the left-subtree. */
template<typename T>
Binary_Tree<T>
Binary_Tree<T>::get_left_subtree() const {
	if (root == NULL) {
		throw std::invalid_argument("get_left_subtree on empty tree");
	}
	return Binary_Tree<T>(root->left);
}


/** Return the right-subtree */
template<typename T>
Binary_Tree<T>
Binary_Tree<T>::get_right_subtree() const {
	if (root == NULL) {
		throw std::invalid_argument("get_right_subtree on empty tree");
	}
	return Binary_Tree<T>(root->right);
}

/** Return the data field of the root
@throws std::invalid_argument if null tree
*/
template<typename T>
const T& Binary_Tree<T>::get_data() const {
	if (root == NULL) {
		throw std::invalid_argument("get_data on null tree");
	}
	return root->data;
}

template<typename T>
bool Binary_Tree<T>::is_null() const {
	return root == NULL;
}

/** Indicate that this tree is a leaf. */
template<typename T>
bool Binary_Tree<T>::is_leaf() const {
	if (root != NULL) {
		return root->left == NULL && root->right == NULL;
	}
	else
		return true;
}

/** Return a string representation of this tree */
template<typename T>
string Binary_Tree<T>::to_string() const {
	ostringstream oss;
	if (is_null()) { oss << "NULL\n"; }
	else {
		oss << *root << '\n';
		oss << get_left_subtree().to_string();
		oss << get_right_subtree().to_string();
	}
	return oss.str();
}

template<typename T>
void Binary_Tree<T>::read_tree(vector<string>& text) {
	int i = 0;
	Binary_Tree<T> newTree = read_binary_tree(text, i);
	setRoot(newTree.getRoot());
}

template<typename T>
Binary_Tree<T> Binary_Tree<T>::read_binary_tree(vector<string>& text, int& i) {
	if (i > text.size() - 1 || text[i] == "NULL") {
		return Binary_Tree<T>();
	}
	else {
		string txt = text[i];
		Binary_Tree<T> left = read_binary_tree(text, ++i);
		Binary_Tree<T> right = read_binary_tree(text, ++i);
		return Binary_Tree<T>(txt, left, right);
	}
}

template<typename T>
Binary_Tree<T> Binary_Tree<T>::read_binary_tree(istream& in) {
	string next_line;
	getline(in, next_line);
	if (next_line == "NULL") {
		return Binary_Tree<T>();
	}
	else {
		T the_data;
		istringstream ins(next_line);
		ins >> the_data;
		Binary_Tree<T> left = read_binary_tree(in);
		Binary_Tree<T> right = read_binary_tree(in);
		return Binary_Tree<T>(the_data, left, right);
	}
}

/** Return a pre-order traversal of the tree */
template<typename T>
string Binary_Tree<T>::pre_order(const BTNode<T>* local_root) const {
	string result;
	if (local_root != NULL) {
		result += local_root->to_string();
		if (local_root->left != NULL) {
			result += " ";
			result += pre_order(local_root->left);
		}
		if (local_root->right != NULL) {
			result += " ";
			result += pre_order(local_root->right);
		}
	}
	return result;
}

/** Return a post-order traversal of the tree */
template<typename T>
string Binary_Tree<T>::post_order(const BTNode<T>* local_root) const {
	string result;
	if (local_root != NULL) {
		if (local_root->left != NULL) {
			result += post_order(local_root->left);
			result += " ";
		}
		if (local_root->right != NULL) {
			result += post_order(local_root->right);
			result += " ";
		}
		result += local_root->to_string();
	}
	return result;
}

/** Return an in-order traversal of the tree */
template<typename T>
string Binary_Tree<T>::in_order(const BTNode<T>* local_root) const {
	string result;
	if (local_root != NULL) {
		result += "(";
		if (local_root->left != NULL) {
			result += in_order(local_root->left);
			result += " ";
		}
		result += local_root->to_string();
		if (local_root->right != NULL) {
			result += " ";
			result += in_order(local_root->right);
		}
		result += ")";
	}
	return result;
}

#endif
// !BINARY_TREE_H

