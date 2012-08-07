//============================================================================
// Name        : Chapter6.cpp
// Author      : Zhen Shao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <vector>


#include "SZTools.h"
using namespace SZTools;

//test6_2

char	map[8];

void	create_map(){
	InitRand();
	for(int i = 0 ; i < 7; i++){
		map[i] = (char)IntRand(128,256);
		printBin(map[i], 8);
	}
	map[7] = (char)255;
	printBin(map[7], 8);
}

bool	is_free(int i, int j){
	return (map[i] & (1<<(7-j)));
}

void	search(int x, int y, string path){
	if( is_free(x,y) ){
		if( x==7 && y==7){
			path += "->(7,7)\n";
			cout << path;
			return;
		}
		else{
			path += "->(";
			path += (char)(x + '0');
			path += ",";
			path += (char)(y + '0');
			path += ")";
			if( x+1 < 8) search( x+1, y, path);
			if( y+1 < 8) search( x, y+1, path);
		}
	}
}

void	test6_2(){
	create_map();
	//finish generating a 8*8 map, guarantee at least one solution
	search(0,0,"(0,0)");
}



//test6_3


string	generate_string( int len, int difc){
	if( difc >= 26) return "";
	string str = "";
	InitRand();
	for(int i = 0; i < len; i++){
		char c = (char)IntRand('a', 'a'+difc);
		str += c;
	}
	cout << "Generated:" << str << endl;
	return str;
}

void	generate_permutation( string ori, string gen){
	if( ori.size() == 0){
		cout << gen << endl;
		return;
	}
	for(int i = 0 ; i < (int)ori.size(); i++){
		string ori_new = ori;
		string gen_new;
		if( i && i<(int)ori.size() && ori[i]==ori[i-1])
			continue;
		gen_new= gen + ori[i];
		ori_new.erase(i, 1);
		generate_permutation( ori_new, gen_new);
	}
}

#include <algorithm>
void	test6_3(){
	string ori = generate_string( 8, 4);
	char* temp = new char[ori.size()];
	for(int i = 0; i < (int)ori.size(); i++)
		*(temp+i) = ori[i];
	sort( temp, temp+ori.size());
	for(int i = 0; i < (int)ori.size(); i++)
		ori[i] = *(temp+i);

	generate_permutation( ori, "");
}



//test6_4

#include <assert.h>
void	generate_parentheses( string pre, int left, int tail){
	assert(left>=0);
	if( tail == 0){
		assert( left == 0);
		cout << pre << endl;
		return;
	}
	assert((tail+left)%2==0);
	if( left < tail )	generate_parentheses( pre + "(", left+1, tail-1);
	if( left > 0 )	generate_parentheses( pre+")", left-1, tail-1);
}

void	test6_4(){
	int n = 3;
	generate_parentheses("", 0, 2*n);
}


//test6_5
void	generate_subset( string subset, int count, string set[], int total, bool write ){
	if( write){
		if(subset[subset.size()-1] == ','){
			cout << subset.substr(0,subset.size()-1) << ")" << endl;
		}else
			cout << subset << ')' << endl;
	}
	if( count < total ){
		generate_subset( subset+set[count]+",", count+1, set, total, 1);
		generate_subset( subset, count+1, set, total, 0);
	}
}

void	test6_5(){
	string set[5] = {"a", "good","boy", "sucks", "!"};
	generate_subset("(", 0, set, 5, 1);
}


int main() {
	test6_2();
	test6_3();
	test6_4();
	test6_5();
	return 0;
}
