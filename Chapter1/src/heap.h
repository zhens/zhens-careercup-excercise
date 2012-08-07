/*
 * heap.h
 *
 *  Created on: Dec 24, 2010
 *      Author: zhenshao
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <vector>

class	Heap{

	vector<int>	arr;
	bool	debug;

public:
	Heap(){
		arr.clear();
		arr.push_back(0);
		debug = false;
	}

	int size(){
		return arr.size();
	}

	void Debug(){
		debug = !debug;
	}

	void MakeHeapUp( int child ){//given one of the child's index, make heap
		int index = child/2;//index = root index;
		int key = arr[index];
		int keyL, keyR;
		if(index * 2 < (int)arr.size() ) keyL = arr[index*2];else keyL = 0x4FFFFFFF;
		if(index * 2+1 < (int)arr.size() ) keyR = arr[index*2+1];else keyR = 0x4FFFFFFF;

		if(key <= keyL && key <= keyR) return;//no swap
		if((key > keyL && key <= keyR) || (key > keyR && keyR > keyL) ){
			//swap root and left;
			arr[index] = keyL;
			arr[index*2] = key;
		}else{
		//swap root and right;
		arr[index] = keyR;
		arr[index*2+1] = key;
		}
		if( index >0 ) MakeHeapUp(index);
	}

	void MakeHeapDown( int index ){
		int key = arr[index];
		int keyL, keyR;
		if(index * 2 < (int)arr.size() ) keyL = arr[index*2];else keyL = 0x4FFFFFFF;
		if(index * 2+1 < (int)arr.size() ) keyR = arr[index*2+1];else keyR = 0x4FFFFFFF;

		if(key <= keyL && key <= keyR) return;//no swap
		if((key > keyL && key <= keyR) || (key > keyR && keyR > keyL) ){
			//swap root and left;
			arr[index] = keyL;
			arr[index*2] = key;
			MakeHeapDown( index*2);
		}else{
		//swap root and right;
		arr[index] = keyR;
		arr[index*2+1] = key;
		MakeHeapDown( index*2+1);
		}
	}

	void insertNode( int data ){
		arr.push_back(data);
		MakeHeapUp(arr.size()-1);
		if(debug){
			for( int i = 0 ; i < (int)arr.size(); i++) cout << arr[i] << " ";
			cout << endl;
		}
	}

	int GetPopMin(){
		int min = arr[1];
		arr[1] = arr[arr.size()-1];
		arr.pop_back();
		MakeHeapDown(1);
		return min;
	}

};

#endif /* HEAP_H_ */
