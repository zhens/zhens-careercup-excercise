/*
 * virtual.h
 *
 *  Created on: Dec 28, 2010
 *      Author: zhenshao
 */

#ifndef VIRTUAL_H_
#define VIRTUAL_H_


class	PrintableObject{
	virtual	void print() = 0;
	//virtual	void print();
};

class	PrintableInt: public PrintableObject{
protected:
	int _x;
public:
	PrintableInt(int x):_x(x){};
	void	print();
};

class	PrintableSmallInt:	public PrintableInt{
	int _limit;
public:
	PrintableSmallInt(int x, int limit):PrintableInt(x),_limit(limit){};
	void	print();
};



#endif /* VIRTUAL_H_ */
