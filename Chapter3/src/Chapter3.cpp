//============================================================================
// Name        : Chapter3.cpp
// Author      : Zhen Shao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "SZTools.h"

int	count_ones( int a){
	int count = 0;
	while(a) {
		count++;
		a &= a-1;
	}
	return count;
}

void	test3_1(){
	SZTools::InitRand();
	int a = SZTools::IntRand(-32, 32);
	SZTools::ListRand();
	int b = SZTools::IntRand(-32, 32);
	SZTools::ListRand();
	//out << a <<"," << count_ones(a) << endl;
	cout << "a,b = (" << a << "," << b << "), count = " << count_ones(a^b) << endl;
}

//helper for testing
void	printBinary(int a){
	for(int i = 0; i < 32;i++,a<<=1){
		cout << (int)(bool)(a & 0x80000000);
	}
	cout << endl;
}

void	test3_2(){//swap odd and even digits
	SZTools::InitRand();
	int a = SZTools::IntRand(-32, 32);
	SZTools::ListRand();
	int odd = a & 0x55555555;
	odd <<= 1;
	int even = a & 0xaaaaaaaa;
	even >>= 1;
	int b = odd | even;
	cout << b << endl;

	//check:
	cout << "a="; printBinary(a);
	cout << "b="; printBinary(b);
}


void	test3_3(){//compare using bit
	SZTools::InitRand();
	int a = SZTools::IntRand(-32768, 32768);
	SZTools::ListRand();
	int b = SZTools::IntRand(-32768, 32768);
	SZTools::ListRand();

	//compare
	int c = a - b;
	int k = (int)(bool)(c & 0x80000000);
	int res = a - k*c;
	cout << res<< endl;
}



//test3_4;

int uadd( string a, string b, string& c){
	int im = a.size();
	int jm = b.size();
	int km = im>jm?im:jm;
	c.resize(km);
	int x = 0;
	for(int i = km-1 ; i >= 0; i--){
		c[i] = '0' + (a[i]-'0' + b[i]-'0' + x) % 10;
		x = a[i]-'0' + b[i] -'0' + x > 9;
	}
	return x;
}

string trimZero( string c){
	int pos = c.size()-1;
	while(pos && (c[pos]=='0')) pos--;
	return c.substr(0,pos+1);
}

int urshift( string a, string& c){
	int im = a.size();
	if( a[0] - '0' >= 2 ){
		int km = im;
		c.resize(km);
		int x = 0;
		for(int i = 0; i < km; i++){
			c[i] = ( x + a[i] - '0' )/2 + '0';
			x = ( x + a[i] -'0' )%2 * 10;
		}
		return x/10;
	}
	else{
		int km = im-1;
		if( km == 0){
			c.resize(1);
			c[0] = '0';
			return (a[0]-'0')%2;
		}
		c.resize(km);
		int x = 10;
		for(int i = 0; i < km; i++){
			c[i] = ( x + a[i+1] -'0' )/2 + '0';
			x = ( x + a[i+1] - '0')%2 * 10;
		}
		return x/10;
	}
}


#include <tr1/unordered_map>

void	test3_4(string decimal){//high resolution binary represented decimal
	int pos = decimal.find('.');
	string integer;
	if( pos > 0 ){
		integer = decimal.substr(0,pos);
		decimal = decimal.substr(pos+1);
	}else{
		integer = decimal;
		decimal = "0";
	}

	//for integer part;

	string bInt = "";
	while( true){
		string res;
		int bit = urshift( integer, res);
		integer = res;
		string temp = "";
		temp += (char)(bit+'0');
		temp += bInt;
		bInt = temp;
		if( integer[0] == '0') break;
	}

	decimal = trimZero( decimal );

	//cout << decimal << endl;

	if( decimal.size()==1 && decimal[0] == '0'){
		cout << bInt<< endl;
		return;
	}

	bInt += '.';

	//for decimal part;
	tr1::unordered_map<string, bool>	ht;
	ht.clear();
	while(true){
		if( !ht[decimal]) ht[decimal] = true;
		else{
			cout << "ERROR."<< endl;
			return;
		}
		string res;
		int bit = uadd( decimal, decimal, res);
		bInt += '0'+bit;
		decimal = trimZero(res);
		if( decimal.size()==1 && decimal[0] == '0')
			break;
	}

	cout << bInt << endl;
}



void	test3_5(){//set multiple bits.
	SZTools::InitRand();
	int n = SZTools::IntRand(-10000000, 10000000);
	int m = SZTools::IntRand(0x00000582, 0x00000a32);
	printBinary(n);
	printBinary(m);
	int i = 4;
	int j = 16;

	int mask1 = (-1)<<j;
	int mask2 = ~((-1)<<i);
	int mask3 = mask1 | mask2;
	int maskm = (-1)<<(j-i);

	if( m & maskm )
			cout << "ERROR M digits.\n";
	else{
		m = m<<i;
		n = n & mask3;
		n = n | m;
		printBinary(n);
	}
}


void	test3_6(){//swap
	int x = SZTools::IntRand(10);
	int y = SZTools::IntRand(10);
	x^=y; y^=x; x^=y;
	cout << x << "," << y << endl;
}


void	test3_7(unsigned int n, int debug){//smallest and largest number with same number of 1s
	int large;
	int small;
									cout << "n      =\n"; printBinary(n);
	int mask1 = n^(n-1);
									if( debug ) printBinary(mask1);
	int bitLow = mask1 & n;
									if( debug ) printBinary(bitLow);
	int n1 = n + bitLow;
									if( debug ) printBinary(n1);
	int n2 = (n^n1) - bitLow;
									if( debug ) printBinary(n2);
	int n3 = n2 / (bitLow<<2);
									if( debug ) printBinary(n3);
	large = n1 + n3;
									cout << "Bigger =\n"; printBinary(large);
	if(count_ones(n1) == 0){
		cout << "No Bigger." << endl;
	}else
		cout << "Bigger: " << (unsigned int)large << endl;

									cout << endl;

									cout << "n      =\n";

									printBinary(n);
	int mask2 = n^(n+1);
									if( debug ) printBinary(mask2);
	bitLow = (mask2 & n)+1;
									if( debug ) printBinary(bitLow);
	n1 = n - bitLow;
									if( debug ) printBinary(n1);
	n2 = ((n^n1) + bitLow)>>2;
									if( debug ) printBinary(n2);
	n3 = n - n2;
									if( debug ) printBinary(n3);
	int n4 = (mask2>>1) * (n2/bitLow);
									if( debug ) printBinary(n4);
	small = n4 | ( n3 & ~mask2);
									cout << "Smaller=\n"; printBinary(small);

	if( count_ones(n+1) == 1){
		cout << "No Smaller." << endl;
	}else
		cout << "Smaller: " << (unsigned int)small << endl;
}


int main() {
	test3_1();
	test3_2();
	test3_3();
	test3_4("123.1231");
	test3_5();
	test3_6();
	test3_7(0x0ffff0ff, 0);
	return 0;
}
