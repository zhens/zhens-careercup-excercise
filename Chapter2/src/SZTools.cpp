/*
 * SZTools.cpp
 *
 *  Created on: Dec 25, 2010
 *      Author: zhenshao
 */

#include "SZTools.h"

void SZTools::InitRand(){
	srand ( time(NULL) );
}

int SZTools::IntRand(int from, int to){
	if( from >= to ) return -1;
	return (rand()%(to-from)+from );
}

int SZTools::IntRand(int to){
	if( to <= 0 ) return -1;
	return (rand()%to );
}

void SZTools::IntArrayRand( int* a, int len, int from, int to){
	if( from >= to ) return;
	for(int i = 0; i < len; i++){
		*(a+i) = IntRand(from, to);
	}
}

void SZTools::IntArrayRand( int* a, int len, int to){
	if( to <= 0 ) return;
	for(int i = 0; i < len; i++){
		*(a+i) = IntRand(to);
	}
}

int precision = 8;

int prec[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

double SZTools::DoubleRand(double from, double to){
	if( from >= to ) return -1;
	double t1 = (rand()%prec[precision])*1.0;
	t1 /= prec[precision];
	t1 *= to-from;
	t1 += from;
	return t1;
}

double SZTools::DoubleRand(double to){
	if( to <= 0 ) return -1;
	return (rand()%prec[precision])*1.0/prec[precision]*to;
}

void SZTools::DoubleArrayRand( double* a, int len, double from, double to){
	if( from >= to ) return;
	for(int i = 0; i < len; i++){
		*(a+i) = DoubleRand(from, to);
	}
}

void SZTools::DoubleArrayRand( double* a, int len, double to){
	if( to <= 0 ) return;
	for(int i = 0; i < len; i++){
		*(a+i) = DoubleRand(to);
	}
}

void SZTools::SetPrecision(int prec){
	if( prec >= 0 && prec <= 8 )
		precision = prec;
}
