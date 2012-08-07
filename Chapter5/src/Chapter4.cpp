//============================================================================
// Name        : Chapter5.cpp
// Author      : Zhen Shao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <stdio.h>
#include <assert.h>

void	test5_2(){
	FILE	*fin;
	fin = fopen("input","r");
	assert(fin);
	char str[10][255];
	int index = 0;
	while( fgets(str[index], sizeof(str[index]), fin) != NULL){
		index = (index+1)%10;
	}
	for(int i = 0; i< 10; i++)
		printf("%s", str[(index+i)%10]);
	fclose(fin);
}



#include <iostream>
using namespace std;
#include "SZTools.h"
using namespace SZTools;

#include "virtual.h"


#include <fstream>
void	cppFileRead(){
	ifstream	fin("input");
	string str;
	while( fin >> str)
		cout << str;
	fin.close();
	ofstream	fout("output");
	str = "This is output.";
	fout << str << endl;
	fout.close();
}


//test5_10

#include <tr1/unordered_map>



typedef struct Node{
	Node* node1;
	Node* node2;
	int	  data[100];
};


Node* _Copy( Node* root, tr1::unordered_map<Node*, Node*>& rec){//!!!!show consider loop!
	if( root ){
		Node* p = new Node();
		if( rec[root] ) return rec[root]; else rec[root] = p;
		memcpy(p, root, sizeof(Node));
		if( root->node1) p->node1 = _Copy(root->node1, rec);
		if( root->node2) p->node2 = _Copy(root->node2, rec);
		return p;
	}else
		return NULL;
}

Node* Copy( Node* root){
	tr1::unordered_map<Node*, Node*> rec;
	rec.clear();
	return _Copy(root, rec);
}


//#define test1(k) k++
//#define test2(k) (*k)++


//int main() {
//	//test5_2();
//
//	//PrintableSmallInt	pi(5, 8);
//	//pi.print();
//
//	//cppFileRead();
//
//
//	return 0;
//}
