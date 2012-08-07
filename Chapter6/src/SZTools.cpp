/*
 * SZTools.cpp
 *
 *  Created on: Dec 25, 2010
 *      Author: zhenshao
 */

#include "SZTools.h"
#include <vector>

vector<int>	recInt;
vector<double> recDouble;

void	initVector(){
	recInt.clear();
	recDouble.clear();
}

void SZTools::ListRand(){
	if( recInt.size() > 0){
		cout << "Rand Generated:";
		for( int i  = 0 ; i < (int)recInt.size(); i++)
			cout << recInt[i] << " ";
		cout << endl;
	}else if( recDouble.size() > 0){
		cout << "Rand Generated:";
		for( int i  = 0 ; i < (int)recDouble.size(); i++)
			cout << recDouble[i] << " ";
		cout << endl;
	}else
		cout << "Nothing Generated.\n";
}

void SZTools::InitRand(){
	srand ( time(NULL) );
}

int SZTools::IntRand(int from, int to){
	if( from >= to ) return -1;
	initVector();
	int rec = (rand()%(to-from)+from );
	recInt.push_back(rec);
	return rec;
}

int SZTools::IntRand(int to){
	if( to <= 0 ) return -1;
	initVector();
	int rec = (rand()%to);
	recInt.push_back(rec);
	return rec;
}

void SZTools::IntArrayRand( int* a, int len, int from, int to){
	if( from >= to ) return;
	initVector();
	for(int i = 0; i < len; i++){
		int rec = (rand()%(to-from)+from );
		recInt.push_back(rec);
		*(a+i) = rec;
	}
}

void SZTools::IntArrayRand( int* a, int len, int to){
	if( to <= 0 ) return;
	initVector();
	for(int i = 0; i < len; i++){
		int rec = (rand()%to);
		recInt.push_back(rec);
		*(a+i) = rec;
	}
}

int precision = 8;

int prec[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

double SZTools::DoubleRand(double from, double to){
	if( from >= to ) return -1;
	initVector();
	double rec = (rand()%prec[precision])*1.0/prec[precision]*(to-from)+from;
	recDouble.push_back(rec);
	return rec;
}

double SZTools::DoubleRand(double to){
	if( to <= 0 ) return -1;
	initVector();
	double rec = (rand()%prec[precision])*1.0/prec[precision]*to;
	recDouble.push_back(rec);
	return rec;
}

void SZTools::DoubleArrayRand( double* a, int len, double from, double to){
	if( from >= to ) return;
	initVector();
	for(int i = 0; i < len; i++){
		double rec = (rand()%prec[precision])*1.0/prec[precision]*to;
		recDouble.push_back(rec);
		*(a+i) = rec;
	}
}

void SZTools::DoubleArrayRand( double* a, int len, double to){
	if( to <= 0 ) return;
	initVector();
	for(int i = 0; i < len; i++){
		double rec = (rand()%prec[precision])*1.0/prec[precision]*to;
		recDouble.push_back(rec);
		*(a+i) = rec;
	}
}

void SZTools::SetPrecision(int prec){
	if( prec >= 0 && prec <= 8 )
		precision = prec;
}


void SZTools::printBin(int a, int len = 32){
	a <<= (32 - len);
	for(int i = 0; i < len;i++,a<<=1){
		cout << (int)(bool)(a & 0x80000000);
	}
	cout << endl;
}
