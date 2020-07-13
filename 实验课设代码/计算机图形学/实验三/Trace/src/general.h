#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <string>
#include <iostream>

class Exception
{
public:
	Exception( const string& m ) 
		: msg( m ) {}
	
	string getMsg() const { return msg; }

private:
	string msg;
};

inline ostream& operator <<( ostream& os, const Exception& x )
{
	return os << x.getMsg();
}

#endif // __GENERAL_H__
