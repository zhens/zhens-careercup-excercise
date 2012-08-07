/*
 * SmartPointer.h
 *
 *  Created on: Dec 28, 2010
 *      Author: zhenshao
 */

#ifndef SMARTPOINTER_H_
#define SMARTPOINTER_H_

template<class T>
class	SmartPointer{
	T*	_ptr;
	unsigned int*	_count;
public:
	SmartPointer(T* t){
		_count = new unsigned int;
		*_count = 1;
		_ptr = t;

	}
	SmartPointer( SmartPointer<T>& other){
		if( !(this== &other)){
			this->_ptr = other._ptr;
			this->_count = other._count;
			(*this->_count)++;
		}
	}
	SmartPointer<T>& operator=(SmartPointer<T>& other){
		if( !(this==&other)){
			this->_ptr = other._ptr;
			this->_count = other._count;
			(*this->_count)++;
		}
		return (*this);
	}
	T*	operator->(){
		return _ptr;
	}
	T&	operator*(){
		return *_ptr;
	}
	~SmartPointer(){
		--*_count;
		if( *_count==0){
			delete _count;
			delete _ptr;
		}
	}
};


#endif /* SMARTPOINTER_H_ */
