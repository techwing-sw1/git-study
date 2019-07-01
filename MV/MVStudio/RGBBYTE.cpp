// RGBBYTE.cpp: implementation of the RGBBYTE class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MVStudio.h"
#include "RGBBYTE.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RGBBYTE::RGBBYTE(const BYTE& value/*=255*/) 
: r(value), g(value), b(value)
{

}

RGBBYTE::RGBBYTE(const BYTE& _r, const BYTE& _g, const BYTE& _b)
: r(_r), g(_g), b(_b)
{
}
// 0x00BBGGRR
RGBBYTE::RGBBYTE(const RGBBYTE& value)
: r(value.r), g(value.g), b(value.b)
{
}


RGBBYTE::~RGBBYTE()
{
}


RGBBYTE& RGBBYTE::operator = (const RGBBYTE& value)
{
	if( this == &value){
		return *this;
	}
	
	r = value.r;
	g = value.g;
	b = value.b;

	return *this;
}

RGBBYTE& RGBBYTE::operator = (const COLORREF& value)
{
	r = (BYTE)(value&0x000000FF);
	g = (BYTE)((value&0x0000FF00)>>8);
	b = (BYTE)((value&0x00FF0000)>>16);
	return *this;
}

RGBBYTE& RGBBYTE::operator = (const BYTE& value)
{
	r = value;
	g = value;
	b = value;
	return *this;
}

BOOL RGBBYTE::operator == (const RGBBYTE& value)
{
	if( r != value.r ) return FALSE;	
	if( g != value.g ) return FALSE;	
	if( b != value.b ) return FALSE;	
	return TRUE;
}

BOOL RGBBYTE::operator != (const RGBBYTE& value)
{
	if( r == value.r ) return FALSE;	
	if( g == value.g ) return FALSE;	
	if( b == value.b ) return FALSE;	
	return TRUE;
}

/*=====================================================================
* 산술 연산자 오버로딩 '+'
=====================================================================*/
RGBBYTE& RGBBYTE::operator + (const RGBBYTE& value)
{
	r = (BYTE)limit(r + value.r);
	g = (BYTE)limit(g + value.g);
	b = (BYTE)limit(b + value.b);
	return *this;
}

RGBBYTE& RGBBYTE::operator + (const COLORREF& value)
{
	r = (BYTE)limit(r +(BYTE)(value&0x000000FF));
	g = (BYTE)limit(g +(BYTE)((value&0x0000FF00)>>8));
	b = (BYTE)limit(b +(BYTE)((value&0x00FF0000)>>16));
	return *this;
}

RGBBYTE& RGBBYTE::operator + (const BYTE& value)
{
	r = (BYTE)limit(r +value);
	g = (BYTE)limit(g +value);
	b = (BYTE)limit(b +value);
	return *this;
}

/*=====================================================================
* 산술 연산자 오버로딩 '-'
=====================================================================*/
RGBBYTE& RGBBYTE::operator - (const RGBBYTE& value)
{
	r = (BYTE)limit(r - value.r);
	g = (BYTE)limit(g - value.g);
	b = (BYTE)limit(b - value.b);
	return *this;
}

RGBBYTE& RGBBYTE::operator - (const COLORREF& value)
{
	r = (BYTE)limit(r - (BYTE)(value&0x000000FF));
	g = (BYTE)limit(g - (BYTE)((value&0x0000FF00)>>8));
	b = (BYTE)limit(b - (BYTE)((value&0x00FF0000)>>16));
	return *this;
}

RGBBYTE& RGBBYTE::operator - (const BYTE& value)
{
	r = (BYTE)limit(r - value);
	g = (BYTE)limit(g - value);
	b = (BYTE)limit(b - value);
	return *this;
}



/*=====================================================================
* 산술 연산자 오버로딩 '*'
=====================================================================*/
RGBBYTE& RGBBYTE::operator * (const BYTE& value)
{
	r = (BYTE)limit(r * value);
	g = (BYTE)limit(g * value);
	b = (BYTE)limit(b * value);
	return *this;
}

/*=====================================================================
* 산술 연산자 오버로딩 '/'
=====================================================================*/
RGBBYTE& RGBBYTE::operator / (const BYTE& value)
{
	r = (BYTE)limit(r / value);
	g = (BYTE)limit(g / value);
	b = (BYTE)limit(b / value);
	return *this;
}


/*=====================================================================
* 논리 연산자 오버로딩 'AND'
=====================================================================*/
RGBBYTE& RGBBYTE::operator & (const RGBBYTE& value)
{
	return *this;
}
RGBBYTE& RGBBYTE::operator & (const COLORREF& value)
{
	return *this;
}
RGBBYTE& RGBBYTE::operator & (const BYTE& value)
{
	return *this;
}

/*=====================================================================
* 논리 연산자 오버로딩 'OR'
=====================================================================*/
RGBBYTE& RGBBYTE::operator | (const RGBBYTE& value)
{
	return *this;
}
RGBBYTE& RGBBYTE::operator | (const COLORREF& value)
{
	return *this;
}
RGBBYTE& RGBBYTE::operator | (const BYTE& value)
{
	return *this;
}
