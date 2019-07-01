// RGBBYTE.h: interface for the RGBBYTE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGBBYTE_H__EABFD51D_9E9F_4AB5_8DD7_E434BE3CA319__INCLUDED_)
#define AFX_RGBBYTE_H__EABFD51D_9E9F_4AB5_8DD7_E434BE3CA319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class RGBBYTE  
{
public:
	RGBBYTE(const BYTE& value=255);
	RGBBYTE(const BYTE& _r, const BYTE& _g, const BYTE& _b);
	RGBBYTE(const RGBBYTE& value);
	~RGBBYTE();

	// 연산자 오버로딩
	// 대입 연산자 (=)
	/*
		RGBBYTE aPixel(255, 0, 0);
		RGBBYTE bPixel;
		bPixel = aPixel;
	*/
	RGBBYTE& operator = (const RGBBYTE& value);
	RGBBYTE& operator = (const COLORREF& value);
	RGBBYTE& operator = (const BYTE& value);

	// 관계 연산자(==, !=)
	/*
		RGBBYTE aPixel(255, 0, 0);
		RGBBYTE bPixel(255, 0, 0);
		if( aPixel == bPixel)
	*/
	BOOL operator == (const RGBBYTE& value);
	BOOL operator != (const RGBBYTE& value);

	// 산술 연산자 오버로딩
	RGBBYTE& operator + (const RGBBYTE& value);
	RGBBYTE& operator + (const COLORREF& value);
	RGBBYTE& operator + (const BYTE& value);

	RGBBYTE& operator - (const RGBBYTE& value);
	RGBBYTE& operator - (const COLORREF& value);
	RGBBYTE& operator - (const BYTE& value);

	RGBBYTE& operator * (const BYTE& value);

	RGBBYTE& operator / (const BYTE& value);
	
	// 논리 연산자 오버로딩
	RGBBYTE& operator & (const RGBBYTE& value);
	RGBBYTE& operator & (const COLORREF& value);
	RGBBYTE& operator & (const BYTE& value);

	RGBBYTE& operator | (const RGBBYTE& value);
	RGBBYTE& operator | (const COLORREF& value);
	RGBBYTE& operator | (const BYTE& value);

public:
	BYTE b;
	BYTE g;
	BYTE r;
};

#endif // !defined(AFX_RGBBYTE_H__EABFD51D_9E9F_4AB5_8DD7_E434BE3CA319__INCLUDED_)
