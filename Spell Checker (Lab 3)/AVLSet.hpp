// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;



private:
    struct Node
    {
        T key;
        Node* left = nullptr;
        Node* right = nullptr;
        int height = 1;
    };
    Node* head;
    int avl_size;
    void avl_copy(Node &destination, Node& source);
    void avl_delete(Node* n);
    int avl_comp(const T& first, const T& second) const;
    int tree_height(Node* n);

};


template <typename T> //good
AVLSet<T>::AVLSet()
{
    avl_size = 0;
    head = nullptr;
}


template <typename T> //good
AVLSet<T>::~AVLSet()
{
    avl_delete(head);
}


template <typename T> //come back
AVLSet<T>::AVLSet(const AVLSet& s)
{
    avl_copy(head, s.head);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s) 
{
    if (this != &s)
    {
        avl_delete(head);
        head = nullptr;
        avl_copy(head, s.head);
        avl_size = s.size();
    }
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T> void AVLSet<T>::add(const T& element)
{
    Node** temp = &head;
    int cmp_val;
    if (*temp == nullptr)
    {
        *temp = new Node{element};
        this -> avl_size++;
    }
    else
    {
        while(temp != nullptr)
        {
            cmp_val = avl_comp((*temp) -> key, element);
            if (cmp_val < 0)
            {
                temp = &((*temp) -> right);             
               /* if (*temp == nullptr)
                {
                    *temp = new Node{element};
                    this -> avl_size++;
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
                    this -> avl_size++;
                    break;
                }*/
                //add(element;
             }
        }
    }
}


template <typename T> 
bool AVLSet<T>::contains(const T& element) const 
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
                cmpValue = avl_comp(temp -> key, element);
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
unsigned int AVLSet<T>::size() const
{
    return avl_size;
}

template <typename T>
int AVLSet<T>::avl_comp(const T& first, const T& second) const 
{
    std::string first_temp = first.c_str();
    std::string second_temp = second.c_str();
    return first_temp.compare(second_temp);
}

template <typename T>
void AVLSet<T>::avl_copy(Node &first, Node& second) 
{
    while (second != nullptr)
    {  
        first = new Node();
        first.key = second.key;
        first.height = second.height;
        first.parent = second.parent;
        if (second.left != nullptr)
            avl_copy(first.left, second.left);
        if (second.right != nullptr)
            avl_copy(first.right, second.right);
    }
}

template <typename T>
void AVLSet<T>::avl_delete(Node* n) 
{
    if (n -> left != nullptr)
        avl_delete(n->left);
    if (n -> right != nullptr)
        avl_delete(n ->right);
    if (n != nullptr)
        delete n;
}

template <typename T>
int AVLSet<T>::tree_height(Node* n)
{
    int l_height;
    int r_height;
    if (n == nullptr)
        return 0;
    l_height = tree_height(n -> left);
    l_height = tree_height(n -> right);
    if (l_height > r_height)
        return l_height + 1;
    else
        return r_height + 1;
}   

#endif // AVLSET_HPP

