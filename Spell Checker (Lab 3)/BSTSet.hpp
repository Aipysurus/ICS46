// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"
#include <string>



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
	int bst_size;
	struct Node
	{
		T key;
		Node* left = nullptr;
		Node * right = nullptr;
	};
	Node* head;
public:
	void node_copy(Node &start, Node &end);
	void delete_node(Node* n);
	int compare_node(const T& first, const T& second) const;
};



template <typename T>
BSTSet<T>::BSTSet()
{
	bst_size = 0;
	head = nullptr;
}


template <typename T>
BSTSet<T>::~BSTSet()
{
	delete_node(this->head);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
	node_copy(head, s.head);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
	if (this != &s)
	{
		delete_node(head);
		head = nullptr;
		node_copy(head, s.head);
		bst_size = s.size();
	}
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
	Node** temp = &head;
	int cmp_val;
	if (*temp == nullptr)
	{
		*temp = new Node{element};
		this -> bst_size++;
	}
	else
		while (*temp != nullptr)
		{
			cmp_val = compare_node((*temp) -> key, element);
			if (cmp_val < 0)
			{
				temp = &((*temp) -> right);				
				/*if (*temp == nullptr)
				{
					*temp = new Node{element};
					this -> bst_size++;
					break;
				}*/
                //add(element);
			}
			else if(cmp_val > 0)
			{
				temp = &((*temp) -> left);
				/*if (*temp == nullptr)
				{
					*temp = new Node{element};
					this -> bst_size++;
					break;
				}*/
                //add(element);
			}
		}
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const 
{
	int cmpValue;
	Node* temp = head;
	while (true)
		if (temp == nullptr)
			break;
		else
		{
			if (element == temp -> key)
				return true;
			else
			{
				cmpValue = compare_node(temp -> key, element);
				if (cmpValue < 0)
				{
					temp = temp -> right;
					continue;
				}
				else if (cmpValue > 0)
				{
					temp = temp -> left;
					continue;
				}
				else
				{
					break;
				}
			}
		}
		return false;
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    return bst_size;
}

template <typename T>
int BSTSet<T>::compare_node(const T& first, const T& second) const
{
	std::string first_temp = first.c_str();
	std::string second_temp = second.c_str();
	return first_temp.compare(second_temp);
}

template <typename T>
void BSTSet<T>::node_copy(Node &first, Node& second)
{
	while (second != nullptr)
	{	this -> add(second.key);
		if (second.left != nullptr)
			node_copy(first.left, second.left);
		if (second.right != nullptr)
			node_copy(first.right, second.right);
	}
}

template <typename T>
void BSTSet<T>::delete_node(Node* n) 
{
	if (n -> left != nullptr)
		delete_node(n->left);
	if (n -> right != nullptr)
		delete_node(n ->right);
	if (n != nullptr)
		delete n;
}

#endif // BSTSET_HPP

