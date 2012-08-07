/*
 * virtual.cpp
 *
 *  Created on: Dec 28, 2010
 *      Author: zhenshao
 */

#include <iostream>
using namespace std;
#include "virtual.h"

void	PrintableInt::print(){
	cout << "Print:" << _x << endl;
}


void	PrintableSmallInt::print(){
	if( _x > _limit){
		cout << "Out of Range.\n";
	}
	else{
		cout << "Print:" << _x << endl;
	}
}
