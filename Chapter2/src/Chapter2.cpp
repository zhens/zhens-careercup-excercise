//============================================================================
// Name        : Chapter2.cpp
// Author      : Zhen Shao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "SZTools.h"

//test2_1;

void	swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

void	shift(int a[], int id1, int id2, int k){
	for(int i = 0 ; i < k ; i++)
		swap(a[id1+i], a[id2+i]);
}

void	test2_1(){
	int	a[20] = {1,2,3,4,5,6,7,8,9,10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
	int n = 10;
	for(int k = n-1; k > 0; k--){
		shift(a, n-k, n, k);
	}
	for(int i = 0 ; i < 20; i++)
		cout << a[i] << " ";
	cout << endl;
}


//test2_1_2;

void	swapArea(int a[], int from1, int to1, int from2, int to2){
	if( to1-from1 > to2-from2){//longer first part;
		int sep1 = to1 - ( (to1-from1) - (to2-from2) );
		swapArea(a, from1, sep1, from2, to2);
		swapArea(a, sep1+1, to2, from2, to2);
	}
	else if( to1-from1 < to2-from2){//longer second part;
		int sep2 = to2 - ( (to2-from2) - (to1-from1) );
		swapArea(a, from1, to1, from2, sep2);
		swapArea(a, from2, sep2, sep2+1, to2);
	}
	else{
		for(int i = 0; i<= to1-from1; i++)
			swap(a[from1+i], a[from2+i]);
	}
}

void 	Rearrange( int a[], int from, int to){
	if(from >= to-1) return;
	else{
		int mid = (from+to)/2;
		int midmid1 = (from+mid)/2;
		int midmid2 = mid+1+(midmid1-from);
		swapArea(a,midmid1+1, mid, mid+1, midmid2 );
		Rearrange(a, from, from+(midmid1-from)*2+1);
		Rearrange(a, from+(midmid1-from)*2+2, to);
	}
}

void	test2_1_2(){
	int	a[20] = {1,2,3,4,5,6,7,8,9,10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
	Rearrange(a, 0, 19);
	for(int i = 0 ; i < 20; i++)
		cout << a[i] << " ";
	cout << endl;
}


//test2_2;

void	test2_2(string str){//assume that there is a 256 buffer available

	bool	already[255];
	memset(already, 0, sizeof(already));
	for(int p = 0; p < (int)str.length(); p++){
		if( already[p])	continue;
		int i = p+1;
		int j = i;
		while( j < (int)str.length() ){
			if( str[j] == str[p] ) j++;
			if( str[j] != str[p] ){
				str[i] = str[j];
				i++;
				j++;
			}
		}
		str = str.substr(0,i);
		already[p] = true;
	}
	cout << str << endl;
}

void	test2_3(){//max sum consecutive sequence
	double a[9];
	SZTools::InitRand();
	SZTools::SetPrecision(3);
	SZTools::DoubleArrayRand(a,9,-100.0, 100.0);
	double f[9];
	f[0] = a[0];
	int max = -10000000;
	for(int i = 1; i < 9 ; i++){
		cout << a[i] << " ";
		if(f[i-1] > 0)
			f[i] = f[i-1]+a[i];
		else
			f[i] = a[i];
		if( f[i] > max) max = f[i];
	}
	cout << "Max:" << max << endl;
}

void	test2_4(){//find all pairs sum to a certain value;
	int value = 30;
	int n = 40;
	int a[40];
	SZTools::InitRand();
	SZTools::IntArrayRand(a, n, -60, 60);
	for(int i = 0 ; i < n-1; i++) cout << a[i] << " ";
	cout << endl;
	int front = 0;
	int rear = n-1;
	sort(a, a+n);
	while( front < rear ){
		if( a[front] + a[rear] == value){
			cout << a[front] << " + " << a[rear] << " = " << value << endl;
			front++;
		}
		else if( a[front] + a[rear] < value){
			front++;
		}
		else{
			rear--;
		}
	}
}


#include <tr1/unordered_map>
void	test2_4_2(){//using hash
	int value = 30;
	int n = 40;
	int a[40];
	SZTools::InitRand();
	SZTools::IntArrayRand(a, n, -60, 60);
	for(int i = 0 ; i < n-1; i++) cout << a[i] << " ";cout << endl;
	tr1::unordered_map<int, bool>	ht;
	ht.clear();

	for(int i = 0 ; i < n; i++){
		if(ht[value-a[i]])
			cout << a[i] << " + " << value - a[i] << " = " << value << endl;
		ht[a[i]] = true;
	}

}

//test2_5, simulating the given function

int	fetch(int* a, int i, int j){
	int num = *(a+i);
	unsigned int bit = 1;
	if(num & ( bit << j) )	return 1;
	else	return 0;
}

void	test2_5(){//find missing number using bit test.
	int n = 600;
	SZTools::InitRand();
	int missing = SZTools::IntRand(n+1);
	cout << "Rand Test: missing:" << missing << endl;
	int a[600];
	for(int i = 0; i < n; i++)
		if( i < missing) a[i]= i;
		else a[i] = i+1;
	//finish preparing for test case.

	unsigned int res = 0;
	int bit = 0;
	while(n){
		int odd = (n*(n+1)/2)%2;
		int sum = 0;
		for(int i = 0 ; i < n; i++)
			sum += fetch( a, i, bit);
		sum = sum%2;
		sum = sum^odd;
		if( sum )//missing is odd;
			res |= 1 << bit;
		int index = 0;
		for(int i = 0; i < n ; i++)
			if( fetch(a,i,bit) == sum )
				a[index++] = a[i];
		bit++;
		n = index;
		//cout << index << " ";
	}
	cout <<  "Ans: " << res << endl;

}



int main() {
	test2_1();//have better solution
	test2_1_2();//this is the better one.
	test2_2("give me enough money to make a lisktksdj");//wrong use of while....
	test2_3();
	test2_4();test2_4_2();
	test2_5();

	return 0;
}
