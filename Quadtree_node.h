#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "ece250.h"

template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {
	private:
		T       x_value;
		T       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;

	public:
		Quadtree_node( T const & = T(), T const & = T() );
		//~Quadtree_node();

		T retrieve_x() const;
		T retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		bool member( T const &, T const & ) const;

		bool insert( T const &, T const & );
		void clear();

	friend class Quadtree<T>;
};

template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}

/*template <typename T>
Quadtree_node<T>::~Quadtree_node() {
    delete this->north_east;
    delete this->north_west;
    delete this->south_east;
    delete this->south_west;
}*/

template <typename T>
T Quadtree_node<T>::retrieve_x() const {
	return x_value;
}

template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
}

template <typename T>
T Quadtree_node<T>::min_x() const {
	// you may use std::min

	using std::min;

	if ( north_west == 0 &&  south_west == 0){
		return  x_value;
	}
	else if ( north_west != 0 &&  south_west != 0){
		return min( north_west -> min_x(),  south_west -> min_x());
	}
	else if( north_west != 0){
		return  north_west -> min_x();
	}
	return  south_west -> min_x();
}

template <typename T>
T Quadtree_node<T>::min_y() const {
	// you may use std::min
	using std::min;

	if ( south_east == 0 &&  south_west == 0){
		return  y_value;
	}
	else if ( south_east != 0 &&  south_west != 0){
		return min( south_east -> min_y(),  south_west -> min_y());
	}
	else if ( south_east != 0){
		return  south_east -> min_y();
	}
	return  south_west -> min_y();
}

template <typename T>
T Quadtree_node<T>::max_x() const {
	// you may use std::max
	using std::max;

	if ( north_east == 0 &&  south_east == 0){
		return  x_value;
	}
	else if ( north_east != 0 &&  south_east != 0){
		return max( north_east -> max_x(),  south_east -> max_x());
	}
	else if( north_east != 0){
		return  north_east -> max_x();
	}
	return  south_east -> max_x();
}

template <typename T>
T Quadtree_node<T>::max_y() const {
	// you may use std::max
	using std::max;

	if ( north_east == 0 &&  north_west == 0){
		return  y_value;
	}
	else if ( north_east != 0 &&  north_west != 0){
		return max( north_east -> max_y(),  north_west -> max_y());
	}
	else if( north_east != 0){
		return  north_east -> max_y();
	}
	return  north_west -> max_y();
}

template <typename T>
T Quadtree_node<T>::sum_x() const {
	if ( this == 0 ) {
		// hint...
		return 0;
	} else {
		return  x_value +  north_east -> sum_x() +  north_west -> sum_x() +  south_east -> sum_x() +  south_west -> sum_x();
	}
}

template <typename T>
T Quadtree_node<T>::sum_y() const {
	if ( this == 0 ) {
		// hint...
		return 0;
	} else {
		return  y_value +  north_east -> sum_y() +  north_west -> sum_y() +  south_east -> sum_y() +  south_west -> sum_y();
	}
}

template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
	if ( this == 0 ) {
		return false;
	}
	else if ( x_value == x &&  y_value == y){
		return true;
	}
	else{
		if ( x_value > x &&  y_value > y){
			return  south_west -> member(x,y);
		}
		else if ( x_value > x &&  y_value <= y){
			return  north_west -> member(x,y);
		}
		else if ( x_value <= x &&  y_value > y){
			return  south_east -> member(x,y);
		}
		else if ( x_value <= x &&  y_value <= y){
			return  north_east -> member(x,y);
		}
	}
}

template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
	if ( x_value == x &&  y_value == y){
		return false;
	}

	if ( x_value > x){
		if( y_value > y){
			if( south_west == 0){
				 south_west = new Quadtree_node(x,y);
				return true;
			}
			return  south_west -> insert(x,y);
		}
		if( y_value <= y){
			if( north_west == 0){
				 north_west = new Quadtree_node(x,y);
				return true;
			}
			return  north_west -> insert(x,y);
		}
	}
	if ( x_value <= x){
		if( y_value > y){
			if( south_east == 0){
				 south_east = new Quadtree_node(x,y);
				return true;
			}
			return  south_east -> insert(x,y);
		}
		if( y_value <= y){
			if( north_east == 0){
				 north_east = new Quadtree_node(x,y);
				return true;
			}
			return  north_east -> insert(x,y);
		}
	}
}

template <typename T>
void Quadtree_node<T>::clear() {
	if (north_east != 0){
		north_east -> clear();
		delete north_east;
	}
	if (north_west != 0){
		north_west -> clear();
		delete north_west;
	}
	if (south_east != 0){
		south_east -> clear();
		delete south_east;
	}
	if (south_west != 0){
		south_west -> clear();
		delete south_west;
	}
    return;
}
// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
