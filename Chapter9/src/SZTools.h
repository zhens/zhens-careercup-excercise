/*
 * SZTools.h
 *
 *  Created on: Dec 25, 2010
 *      Author: zhenshao
 */

#ifndef SZTOOLS_H_
#define SZTOOLS_H_

#include <time.h>
#include <iostream>
using namespace std;

namespace SZTools{

	void ListRand();

	void InitRand();
	int IntRand(int from, int to);
	int IntRand(int to);
	void IntArrayRand( int* a, int len, int from, int to);
	void IntArrayRand( int* a, int len, int to);

	double DoubleRand(double from, double to);
	double DoubleRand(double to);
	void DoubleArrayRand( double* a, int len, double from, double to);
	void DoubleArrayRand( double* a, int len, double to);
	void SetPrecision(int prec);


	/*example: #include "SZTools.h"
	 *
	double a[9];
	SZTools::InitRand();
	SZTools::SetPrecision(3);
	SZTools::DoubleArrayRand(a,9,-100.0, 100.0);
	 *
	 */

	void printBin(int a, int len);

}

#endif /* SZTOOLS_H_ */
