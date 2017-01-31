// HashSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;
    void inputNode(const T& elemement);

private:
struct Nodes
    {
        T key;
        Nodes* next = nullptr;
    };
    HashFunction hashFunction;
    Nodes** hash;
    unsigned int hash_capacity;
    unsigned int hash_size;

};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    hash_capacity = DEFAULT_CAPACITY;
    hash = new Nodes*[hash_capacity];
    hash_size = 0;
}


template <typename T>
HashSet<T>::~HashSet()
{
    for (unsigned int i = 0; i < hash_capacity; ++i)
        delete hash[i];
    delete hash;
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}
{
    hash = s.hash;
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        hashFunction = s.hashFunction;
        hash = s.hash;
    }

    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
	inputNode(element);
    if ((hash_size / hash_capacity) > 0.8)
    {
    	Nodes** old_hash = hash;
    	unsigned int prev_amount = hash_capacity;
        hash_capacity = (hash_capacity * 2);
        hash = new Nodes*[hash_capacity];
        for (unsigned int i = 0; i < prev_amount; i++)
        {
        	Nodes* second_temp = old_hash[i];
        	while(second_temp != nullptr)
        	{
        		inputNode(element);
        		second_temp = second_temp -> next;
        	}
        }
        for (unsigned int x = 0; x < prev_amount; x++)
        {
        	if (old_hash[x] != nullptr)
        		delete old_hash[x];
        }
        delete[] old_hash;
    }
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{
   unsigned int index = static_cast<unsigned int>(hashFunction(element)) % hash_capacity;
   Nodes* test = hash[index];
   while(test != nullptr)
   {
   		if(test->key == element)
   			return true;
   		test = test -> next;
   }
   return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return hash_size;
}

template <typename T>
void HashSet<T>::inputNode(const T& element) 
{
    unsigned int index = static_cast<unsigned int>(hashFunction(element)) % hash_capacity;
	Nodes* alpha = hash[index];
	if (alpha == nullptr)
		hash[index] = new Nodes{element};
	else
	{
		while(alpha != nullptr)
			alpha = alpha -> next;
		alpha = new Nodes{element};
	}
}

#endif // HASHSET_HPP

