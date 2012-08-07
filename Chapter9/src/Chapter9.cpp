//============================================================================
// Name        : Chapter9.cpp
// Author      : Zhen Shao
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "SZTools.h"
using namespace SZTools;

void	printInt(int i){
	cout << i << " ";
}

enum Chess{_X, _O, empty};

void	DrawChessBoard( Chess** ChessBoard, int n){
	for(int i = 0 ; i < n ; i++, cout << "|" << endl)
		for(int j = 0 ; j < n ; j++ )
		{
			Chess chess = *(*(ChessBoard+i)+j);
			if( chess == empty)
				cout << ".";
			else if( chess == _X)
				cout << "X";
			else
				cout << "O";
		}
}

void	GenerateChessBoard( Chess** ChessBoard, int n){
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			*(*(ChessBoard+i)+j) = (Chess)IntRand(3);
	DrawChessBoard( ChessBoard, n);
}

void	test_win( Chess** ChessBoard, int n ){

	int* h = new int[5];
	int* v = new int[5];
	int d1, d2;
	d1 = 0; d2 = 0; memset(h, 0, n*sizeof(int)); memset(v, 0, n*sizeof(int));
	int chess;

	for(int i = 0 ; i < n; i++)
		for(int j = 0 ; j < n ; j++){
			switch (*(*(ChessBoard+i)+j)){
				case	_X:	chess = 1; break;
				case	_O:	chess = 1<<16;	break;
				case	empty: continue;
			}
			if( i==j)	d1 += chess;
			if( i+j == n-1)	d2 += chess;
			*(h+i) += chess;
			*(v+j) += chess;
		}
	Chess win = empty;
	for(int i = 0 ; i < n; i++){
		if( ((*(h+i)) & 0x0000ffff) == n)
			win = _X;
		if( ((*(h+i)) >> 16) == n )
			win = _O;
		if( ((*(v+i)) & 0x0000ffff) == n)
			win = _X;
		if( ((*(v+i)) >> 16) == n )
			win = _O;
	}
	if( (d1 & 0x0000ffff) == n)
		win = _X;
	if( (d1 >> 16) == n )
		win = _O;
	if( (d2 & 0x0000ffff) == n)
		win = _X;
	if( (d2 >> 16) == n )
		win = _O;
	if( win == _X) cout << "X wins.\n";
	else if( win == _O) cout << "O wins.\n";
	else	cout << "No one wins.\n";
}

void	test9_1(int n){
	Chess**	chessBoard = new Chess*[n];
	for(int i = 0; i < n ; i++){
		chessBoard[i] = new Chess[n];
	}
	GenerateChessBoard( chessBoard, n);
	test_win( chessBoard, n);
}


//test9_2


void	test9_2( string guess, string solution, int digits){
	if( guess.size() != digits || solution.size() != digits){
		cout << "Error Input!\n";
		return;
	}
	int count[256];
	memset( count, 0 , sizeof(count));
	for(int i = 0 ; i < digits; i++){
		count[solution[i]]++;
		count[guess[i]]--;
	}
	int B = 0;
	for(int i = 0 ; i < digits; i++){
		if( count[guess[i]] < 0) B += -count[guess[i]];
		count[guess[i]] = 0;
	}
	B = digits - B;
	int A = 0;
	for(int i = 0 ; i < digits ; i++)
		if( guess[i]==solution[i])
			A++;//number of hits
	B = B - A; // number of pseudo-Hits
	cout << A << " hits, " << B << " pseudo hits\n";
}


string GenerateString( int digits, int len){
	string str = "";
	for(int i = 0 ; i < len; i++)
		str += (char)('A'+IntRand(digits));
	cout << str << endl;
	return str;
}

//answer is totally wrong......
// Use a bit mask for hash_mapping
struct result {
	int hits;
	int pseudoHits;
};

result estimate(const string& guess, const string& solution) {
	result res;
	res.hits = res.pseudoHits = 0;
	int solution_mask = 0;
	for (int i = 0; i < 4; ++i) {
		solution_mask |= 1 << (1 + solution[i] - 'A');
	}
	for (int i = 0; i < 4; ++i) {
		if (guess[i] == solution[i]) {
			++res.hits;
		}else if (solution_mask && ( 1 << (1 + guess[i] - 'A'))) {
			++res.pseudoHits;
		}
	}
	cout << res.hits << " hits, " << res.pseudoHits << " pseudo hits\n";
	return res;
}


//test9_4
#include <vector>



bool	searchNQueen(vector<int>& queenPos, int n, bool d1[], bool d2[], bool r[]){
	if( queenPos.size() == n){
		for(int i = 0 ; i < n ; i++, cout << endl)
			for(int j = 0 ; j < n; j++)
				if( queenPos[i] == j) cout << "Q";
				else	cout << ".";
		return true;
	}
	int j = queenPos.size();
	for( int i = 0 ; i < n ; i++)
		if( d1[(i-j+n)%(2*n)] && d2[i+j] && r[i] ){
			d1[(i-j+n)%(2*n)] = d2[i+j] = r[i] = false;
			queenPos.push_back(i);
			if( searchNQueen( queenPos, n, d1, d2, r) )	return true;
			d1[(i-j+n)%(2*n)] = d2[i+j] = r[i] = true;
			queenPos.pop_back();
		}
	return false;
}

void	test9_4(int n ){//n queens
	vector<int> queenPos;
	queenPos.clear();
	bool d1[100], d2[100], r[100];
	for(int i = 0 ; i < 100; i++)
		d1[i] = d2[i] = r[i] = true;
	searchNQueen( queenPos, n, d1,d2,r);
}


//test9_5

#include <assert.h>

enum	OChess{O, B, W};
string	NameOChess[3] = {"O", "B", "W"};
int		dx[8] = { 1,1,1,0,0,-1,-1,-1};
int		dy[8] = { 1,0,-1,1,-1,1,0,-1};

template<int w = 8, int h = 8>
class	Othello{
	OChess	board[w][h];
	OChess	playerNow;
	bool	started;
	OChess	winner;
	int		flip[8];
public:
	Othello(OChess player = W ){
		memset( board, 0, sizeof( board));
		playerNow = player;
		started = false;
	}

	~Othello(){};

	void	GameStart(){
		if( started ) return;
		started = true;
		board[w/2][h/2] = board[w/2-1][h/2-1] = W;
		board[w/2-1][h/2] = board[w/2][h/2-1] = B;
		printChessBoard();
		while( !checkWin() ){
			cout << "Player " << NameOChess[playerNow] << ", please put chess:";
			int x,y;
			cin >> x >> y;
			cout << "\nPut Chess " << NameOChess[playerNow] << " at (" << x <<"," <<y<<")\n";
			if( PutChess( y, x , playerNow) )
				playerNow = (OChess)(3 - (int)playerNow);
			else
				cout << "Not valid position. Retry.\n";
			printChessBoard();
		}
		cout << "Winner is " << NameOChess[winner] << endl;
	}

	bool	PutChess( int x, int y, OChess chess){
		if( !started) return false;
		if(_checkValidation(x,y, chess)){
			for(int i = 0; i < 8 ; i++)
				for(int j = 1 ; j < flip[i]; j++ ){
					assert( chess != board[x+dx[i]*j][y+dy[i]*j]);
					board[x+dx[i]*j][y+dy[i]*j] = chess;
				}
			board[x][y] = chess;
			return true;
		}
		return false;
	}

	bool	checkWin(){
		int white=0;
		int black=0;
		for(int i=0;i<w;i++)
			for(int j = 0; j < h ; j++)
				if(board[i][j]==W) white++;
				else if(board[i][j]==B) black++;
				else{
					bool deadBoard = true;
					for(int i = 0 ; i < w ; i++)
						for(int j = 0 ; j < h ; j++)
							if( _checkValidation(x,y, playerNow) )
							{
								deadBoard = false;
								winner = (OChess)(3 - (int)playerNow);
								return true;
							}
					return false;
				}
		if( white > black)	winner = W;
		else if( white < black) winner = B;
		else winner = O;

		return true;
	}

	void	printChessBoard(){
		cout << endl;
		for(int i = 0; i < h; i++)
			cout << i%10;
		cout << endl;
		for(int i = 0 ; i < w; i++,cout << (i-1)%10 << endl)
			for(int j = 0 ; j < h; j++)
				if( board[i][j] == W) cout << "W";
				else if( board[i][j] == B) cout << "B";
				else cout << ".";
		cout << endl;
	}

private:

	bool	_checkValidation(int x, int y, OChess toPut){
		if( x < 0 || x >= w || y < 0 || y >= h ) return false;
		if( board[x][y] != O) return false;
		bool valid = false;
		for(int i = 0 ; i < 8; i++){
			int step = 1;
			while( x+dx[i]*step >= 0 &&
					x+dx[i]*step < w &&
					y+dy[i]*step >= 0 &&
					y+dy[i]*step < h &&
					board[x+dx[i]*step][y+dy[i]*step] != toPut &&
					board[x+dx[i]*step][y+dy[i]*step] != O)
				{
					//cout << "testing (" <<  y+dy[i]*step << "," << x+dx[i]*step << "):";
					//cout << NameOChess[board[x+dx[i]*step][y+dy[i]*step]] << endl;
					step++;
				}
			if( step > 1 && board[x+dx[i]*step][y+dy[i]*step] == toPut ){
				valid = true;
				flip[i] = step;
			}else
				flip[i] = 1;
		}
		//for_each(flip, flip+8, printInt);
		return valid;
	}
};


void	test9_5(){
	Othello<8,8>	game;
	game.GameStart();
}


int main() {
	InitRand();
	test9_1(6);
	test9_2(GenerateString(5,7), GenerateString(5,7), 7);
	//estimate("YGBA", "AAAA");// this answer is totally wrong.
	test9_4(8);
	test9_5();
	return 0;
}
