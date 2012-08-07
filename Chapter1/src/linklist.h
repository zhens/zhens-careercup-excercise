/*
 * linklist.h
 *
 *  Created on: Dec 24, 2010
 *      Author: zhenshao
 */

#ifndef LINKLIST_H_
#define LINKLIST_H_


typedef struct Node{
	Node* next;
	double factor;
	Node(Node* _next, double _factor= 0){
		next = _next;
		factor = _factor;
	}
}*pNode;

class Linklist{
	pNode	head;
public:
	Linklist(){
		head = new Node(NULL, -1);
	}
	~Linklist(){
		_DeleteNode(head);
	}

	void _DeleteNode( pNode p ){
		if(p->next == NULL)
			delete(p);
		else{
			_DeleteNode(p->next);
			delete(p);
		}
	}

	void InsertNodeAfter( pNode pre, pNode newNode){
		newNode->next = pre->next;
		pre->next = newNode;
	}

	void DeleteNodeAfter( pNode pre){
		if( pre->next == NULL){
			cout << "Error, node to delete does not exist.\n";
			return;
		}
		pNode temp = pre->next;
		pre->next = temp->next;
		delete(temp);
	}

	bool ifEmpty(){
		return head->next == NULL;
	}

	void Clear(){
		if(!ifEmpty())
			_DeleteNode(head->next);
		head->next = NULL;
		head->factor = -1;
	}

	pNode GetHeader(){ return head;}
};


#endif /* LINKLIST_H_ */
