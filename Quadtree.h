#ifndef QUADTREE_H
#define QUADTREE_H

/***************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ***************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
	private:
		Quadtree_node<T> *tree_root;
		int count;

	public:
		Quadtree();
		~Quadtree();

		// Accessors

		int size() const;
		bool empty() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		Quadtree_node<T> *root() const;
		bool member( T const &, T const & ) const;

		// Mutators

		void insert( T const &, T const & );
		void clear();
};

template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
	// empty constructor
}

template <typename T>
Quadtree<T>::~Quadtree() {
    clear();
}

template <typename T>
int Quadtree<T>::size() const {
	return count;					// returns current number of nodes in tree
}

template <typename T>
bool Quadtree<T>::empty() const {
	return (count == 0);			// returns true iff count = 0
}

template <typename T>
T Quadtree<T>::min_x() const {
	return tree_root -> min_x();	// calls min_x() on tree_root
}

template <typename T>
T Quadtree<T>::min_y() const {
	return tree_root -> min_y();	// calls min_y() on tree_root
}

template <typename T>
T Quadtree<T>::max_x() const {
	return tree_root -> max_x(); 	// calls max_x() on tree_root
}

template <typename T>
T Quadtree<T>::max_y() const {
	return tree_root -> max_y();	// calls max_y() on tree_root
}

template <typename T>
T Quadtree<T>::sum_x() const {
	return this -> tree_root -> sum_x();	// calls sum_x() on tree_root
}

template <typename T>
T Quadtree<T>::sum_y() const {
	return this -> tree_root -> sum_y();	// calls sum_y() on tree_root
}

template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
	if (this -> empty()){
		return 0;
	}
	return tree_root;
}

template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
	if(tree_root == 0){
		return false;
	}
	return tree_root -> member(x,y);
}

template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {
	if(tree_root == 0){
		tree_root = new Quadtree_node<T>(x,y);
	}
	else if(this -> member(x,y)){
		return;
	}
	else{
		tree_root -> insert(x,y);
	}
	count++;
}

template <typename T>
void Quadtree<T>::clear(){
	if(tree_root != 0){
		tree_root -> clear();
		delete tree_root;
		tree_root = 0;
	}
	count = 0;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
