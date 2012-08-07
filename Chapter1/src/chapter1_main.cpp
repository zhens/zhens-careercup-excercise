//============================================================================
// Name        : chapter1_main.cpp
// Author      : Zhen Shao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void	test1_1(int n){//generate the n-th fib number
	//validation
	if(n<0){
		cout << "Error input. Should be Non-Negative.\n";
		return;
	}
	//init
	int fibpre = 1;
	int fibnow = 1;
	int index = 2;
	//iteration
	while( index < n )
	{
		int fib = fibpre + fibnow;
		if( fib < fibnow )
		{
			cout << "Error input. Too large N.\n";
			return;
		}
		fibpre = fibnow;
		fibnow = fib;
		index++;
	}
	//output
	cout << fibnow << endl;
}


//void	test1_2(int n){//count 2s in 1 ~ n
//	//validation
//	if(n<0){
//		cout << "Error input. Should be Non-Negative.\n";
//		return;
//	}
//	//init
//	int counter = 0;
//	int step = 0;
//	//iteration
//	while(step<=n)
//	{
//		int num = step;
//		while( num > 0)
//		{
//			if( num % 10 == 2)
//				counter++;
//			num /= 10;
//		}
//		step++;
//	}
//	//output
//	cout << counter << endl;
//}


void	test1_2(int n){//count 2s in 1 ~ n: method O( log(n) );
	//validation
	if(n<0){
		cout << "Error input. Should be Non-Negative.\n";
		return;
	}
	//init
	int	counter = 0;
	int mul = 1;
	//iteration
	while(n>0)
	{
		if( n % 10 >= 2)
			counter+= mul;
		n /= 10;
		counter += n*mul;
		mul*= 10;
	}
	//output
	cout << counter << endl;
}


#define EPS 1e-6
#define ZERO(x) (-EPS < x && x < EPS)
typedef struct Line{//define the struct
	double	p1x,p1y,p2x,p2y;
	Line(double x1,double y1,double x2,double y2){//generate an instance
		p1x = x1; p1y = y1; p2x = x2; p2y = y2;
	}
};

bool validate(Line l){//test if it is a line or overlapped points.
	if( ZERO(l.p1x-l.p2x) && ZERO(l.p1y-l.p2y) )
		return false;
	else
		return true;
}


void	test1_3(Line l1, Line l2){//line if intersected?
	//validation
	if( !validate(l1) || !validate(l2)){
		cout<<"Error, one of the line is not-valid.\n";
		return;
	}
	//determinate
	double v1x = l1.p2x - l1.p1x;
	double v2x = l2.p2x - l2.p1x;
	double v1y = l1.p2y - l1.p1y;
	double v2y = l2.p2y - l2.p1y;

	double delta = v1x*v2y - v2x*v1y;

	//output case 1
	if( ! ZERO(delta) )
		cout << "Intersecting!\n";//intersected.
	else
	{
		//possible parallel or overlapping;
		//determinate
		v1x = l1.p2x - l2.p1x;
		v2x = l2.p2x - l2.p1x;
		v1y = l1.p2y - l2.p1y;
		v2y = l2.p2y - l2.p1y;

		delta = v1x*v2y - v2x*v1y;

		//output case 2
		if( ZERO(delta) )
			cout << "Overlapping!\n";//overlapping.
		else
			cout << "Not Intersecting!\n";
	}
}


void test1_5(int n){ //count the ending zeros of n!
	//validation
	if( n < 0)
	{
		cout << "Error input.\n";
		return;
	}
	//count only 2 and 5s.
	//init
	int counter2 = 0;
	int counter5 = 0;
	int step = 1;
	//iteration
	while( step <= n)
	{
		int num = step;
		while( num%2 == 0)
		{
			num /= 2;
			counter2++;
		}
		while( num%5 == 0)
		{
			num /= 5;
			counter5++;
		}
		step++;
	}
	//output
	cout << (counter2>counter5? counter5 : counter2) << endl;

}


#include "BitOperator.h"
void test1_6(){ //write your own + using &^|~!
	BitInt x(1);
	BitInt y(~(-63));
	cout << x+y << endl;
}

void test1_7(){ //write your own -*/ using + and &^!~|
	BitInt x(-1);
	BitInt y(5);
	cout << x-y << endl;
	cout << x*y << endl;
	cout << x/y << endl;
}



#include "heap.h"
void test1_8(int k){ //calc the k-th number having 3,5,7 as only factors.
	if( k< 1){
		cout << "Error input. K should be positive.\n";
		return;
	}
	Heap	heap;
	//heap.Debug();
	heap.insertNode(3);
	heap.insertNode(5);
	heap.insertNode(7);
	int min = 0;
	int lastmin = 0;
	for( int i = 0 ; i < k ; i++)
	{
		min = heap.GetPopMin();
		while( min == lastmin)
			min = heap.GetPopMin();
		heap.insertNode(min*3);
		heap.insertNode(min*5);
		heap.insertNode(min*7);
		lastmin = min;
		cout << min <<" ";
	}
	cout << "min:" << min << endl;
}




#include <algorithm>

typedef struct Pair{
	int	w;
	int h;
	Pair(int _w, int _h){
		w = _w; h = _h;
	}
};

bool operator<(Pair p1, Pair p2){
	return (p1.w < p2.w)||((p1.w==p2.w)&&(p1.h<p2.h) );
}

void test1_9(){//longest non-dicreasing sequence
	Pair	pairs[7] = {Pair(65,100), Pair(70,150), Pair(56,90), Pair(75,190), Pair(60,95), Pair(68,110), Pair(30,120)};
	sort(pairs, pairs + 7);
	int f[7], r[7];
	for(int i = 0; i < 7; i++)
		f[i] = 1;
	r[0] = 0;
	for(int i = 1 ; i < 7; i++)
	{
		for(int j = 0 ; j < i ; j++)
		{
			if( pairs[i].h > pairs[j].h)
				if( f[j] +1 > f[i])
				{
					f[i] = f[j]+1;
					r[i] = j;
				}
		}
	}
	int maxi = 0;
	for(int i = 0; i < 7; i++)
	{
		if(f[maxi] < f[i])
			maxi = i;
	}
	//output the max length
	//cout << maxi << endl;
	int maxL = f[maxi];
	f[0] = maxi;
	for(int i = 1; i < maxL; i++)
		f[i] = r[f[i-1]];
	for(int i = maxL-1; i >= 0; i--)//output the max length details.
		cout << "(" << pairs[f[i]].w << "," << pairs[f[i]].h << ") ";
	cout << endl;

}


//test 1_10

typedef struct Point{
	double x,y;
	Point(){}
	Point(double _x, double _y){
		x = _x; y = _y;
	}
};

typedef struct Line2P{
	Point a;
	Point b;
	Line2P(){}
	Line2P( Point _a, Point _b){
		a = _a; b= _b;
	}
};

typedef struct LinePS{
	double yintersection;
	double slope;
};

LinePS convert(Line2P l2p){
	LinePS lps;
	if( !ZERO(l2p.a.x - l2p.b.x) )
	{
		lps.slope = (l2p.a.y - l2p.b.y)/(l2p.a.x - l2p.b.x);
		lps.yintersection = l2p.a.y - l2p.a.x * lps.slope;
		return lps;
	}
	return lps;
}

typedef struct Counter2P{
	Line2P	data;
	int counter;
	Counter2P(Line2P _data){
		data = _data; counter = 1;
	}
};

bool operator==(Counter2P c1, Counter2P c2){
	return (ZERO(c1.data.a.x - c2.data.a.x) );
}

bool operator<(Counter2P c1, Counter2P c2){
	return (c1.counter > c2.counter );
}

typedef struct CounterPS{
	LinePS	data;
	int counter;
	CounterPS(LinePS _data){
		data = _data; counter = 1;
	}
};

bool operator==(CounterPS c1, CounterPS c2){
	return (ZERO(c1.data.slope - c2.data.slope) && ZERO(c1.data.yintersection - c2.data.yintersection) );
}

bool operator<(CounterPS c1, CounterPS c2){
	return (c1.counter > c2.counter );
}

void test1_10(){
	Point points[17] = {Point(1,10),Point(2,12),Point(3,14),Point(4,16),Point(2,-1),Point(1,-2),\
			Point(10000,1),Point(0.005,3),Point(30,40),Point(1,1.3),Point(0,2.2),Point(0,2.3),Point(2.2,2.3),\
			Point(-4,-23.9),Point(-12,2),Point(3,.232),Point(32,12)};
	vector<  CounterPS >	lineList;
	vector<  Counter2P >	verLineList;
	lineList.clear();
	verLineList.clear();
	for(int i = 1 ; i < 17 ; i++)
		for(int j = 0; j < i; j++)
		{
			Line2P l2p(points[i], points[j]);
			if( ZERO( points[i].x - points[j].x ) ){
				vector<Counter2P>::iterator	it;
				Counter2P c2p(l2p);
				it = find( verLineList.begin(), verLineList.end(), c2p );
				if( it == verLineList.end() )
					verLineList.push_back( c2p  );
				else
					it->counter++;
			}
			else{
				vector<CounterPS>::iterator	it;
				CounterPS cps(convert(l2p));
				it = find( lineList.begin(), lineList.end(), cps );
				if( it == lineList.end() )
					lineList.push_back( cps  );
				else
					it->counter++;
			}
		}
	sort( verLineList.begin(), verLineList.end());
	sort( lineList.begin(), lineList.end());
	if( verLineList.begin()->counter > lineList.begin()->counter ){
		double res = verLineList.begin()->data.a.x;
		cout << "Max Point (" << verLineList.begin()->counter << ") Line: x = " << res << endl;
	}
	else{
		double slope = lineList.begin()->data.slope;
		double y = lineList.begin()->data.yintersection;
		cout << "Max Point (" << lineList.begin()->counter << ") Line: y = ";
		if( slope != 1)	cout << slope << " * ";
		cout << "x";
		if( y != 0 ) cout << " + " << y;
		cout << endl;
	}
}



int main() {
	test1_1(2);//no parameter validation 1st time.
	test1_2(3540);//no step++ 1st time.//no efficient algo 1st time.
	test1_3(Line(0,0,1,1), Line(0,1,1,2));//don't know the grammar of typedef 1st time.//ignore overlapping
	test1_5(26);//ac at 1st time.//there is a better solution, minor better.
	test1_6();//learned 1st time.
	test1_7();//should care for sig;
	test1_8(30);//forget to ignore the duplicated.
	test1_9();//heap index starts from 1;
	test1_10();//err..... test several vector functions.
}
