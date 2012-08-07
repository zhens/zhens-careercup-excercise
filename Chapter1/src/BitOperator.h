/*
 * BitOperator.h
 *
 *  Created on: Dec 24, 2010
 *      Author: zhenshao
 */

#ifndef BITOPERATOR_H_
#define BITOPERATOR_H_


class	BitInt{
private:
	int x;
public:
	BitInt(int x):x(x){};
	const BitInt operator +( const BitInt& a){
		int R = 0;
		int A = this->x;
		int B = a.x;
		int C = 0;
		int Bit = 1;
		while( (A || B || C ) && Bit){
			int Al = A & 1;
			int Bl = B & 1;
			if(Al & Bl){
				if(C) R |= Bit;
				else R &= ~Bit;
				C = 1;
			}
			else
			if(!Al && !Bl){
				if(C)
					R |= Bit;
				else
					R &= ~Bit;
				C = 0;
			}
			else if(!C) R |= Bit;

			Bit <<= 1;
			A >>= 1;
			B >>= 1;
		}
		return BitInt(R);
	}

	const BitInt operator -( const BitInt& a){
		return BitInt(~(a.x))+ (BitInt(1)+ (*this));
	}


	const BitInt operator*( const BitInt& a){
		BitInt R(0);
		int A = this->x;
		int B = a.x;
		int sig = 0;
		if( B < 0){
			B = (BitInt(0)-BitInt(a)).x;
			sig = !sig;
		}
		if( A < 0){
			A = (BitInt(0)-(*this)).x;
			sig = !sig;
		}
		unsigned int Bit = 0x80000000;
		while( A  && (Bit>>1) ){
			int Al = A & 1;
			if( Al )
				R = R + BitInt(B);
			B <<= 1;
			A >>= 1;
		}
		if(sig) R = BitInt(0) - R;
		return R;
	}

	const BitInt operator/( const BitInt& a){
		BitInt R(0);
		int A = this->x;
		int B = a.x;
		int sig = 0;
		if( !B ){
			cout << "Error input. Divider should be non-zero.\n";
			return NULL;
		}
		if( B < 0){
			B = (BitInt(0)-BitInt(a)).x;
			sig = !sig;
		}
		if( A < 0){
			A = (BitInt(0)-(*this)).x;
			sig = !sig;
		}
		if( A < B){
			return BitInt(0);
		}
		int Bit = 1;
		while( !(B & 0x40000000) && (A>=(B<<1)) ){
			B <<= 1;
			Bit <<= 1;
		}
		while(Bit){
			if(A>=B){
				A = (BitInt(A)-BitInt(B)).x;
				R = R + BitInt(Bit);
			}
			B >>= 1;
			Bit >>= 1;
		}
		if(sig) R = BitInt(0) - R;
		return R;
	}

	BitInt& operator =( const BitInt& a){
		if( this == &a){//self-assignment check
			return *this;
		}
		this->x = a.x;
		return *this;
	}
	friend ostream & operator <<( ostream & stream, BitInt a);
	friend istream & operator >>( istream & stream, BitInt &a);
};

ostream& operator<<(ostream &stream, BitInt a){
	stream << a.x;
	return stream;
}

istream& operator>>(istream &stream, BitInt &a){
	stream >> a.x;
	return stream;
}



#endif /* BITOPERATOR_H_ */
