// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__BFDD6CA5_526E_4A73_BEBD_ACD8349C3F0E__INCLUDED_)
#define AFX_DIB_H__BFDD6CA5_526E_4A73_BEBD_ACD8349C3F0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RGBBYTE.h"

#define DIB_HEADER_MARKER ((WORD) 'M'<<8 | 'B')

class CDib  
{
public:
	CDib();
	CDib(const CDib& Dib);
	virtual ~CDib();

protected:
	BOOL m_fnInitDib();
	void m_fnDestroy();
	BOOL m_fnAllocPtr();
	void m_fnFreePtr();

public:
	// BMP File save/load
	BOOL m_fnLoad(LPCTSTR lpszFileName);
	BOOL m_fnSave(LPCTSTR lpszFileName);

	// DIB Info I/F
	LONG m_fnGetWidth()		{ return m_nWidth;		};
	LONG m_fnGetHeight()	{ return m_nHeight;		};
	WORD m_fnGetBitCount()	{ return m_nBitCount;	};
	DWORD m_fnGetDibSize()	{ return m_nDibSize;	};
	BOOL m_fnIsValid();
	LPBITMAPINFO m_fnGetBitmapInfoAddr();
	LPVOID m_fnGetDibBitsAddr();
	int m_fnGetPaletteNums();

	// Draw
	void m_fnDraw(HDC hDC);
	void m_fnDraw(HDC hDC, int dx, int dy);
	void m_fnDraw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop=SRCCOPY);
	void m_fnDraw(HDC hDC, int dx, int dy, int dw, int dh,
						   int sx, int sy, int sw, int sh, DWORD dwRop=SRCCOPY);

	// Crate
	BOOL m_fnCreateGrayImage(LONG nWidth, LONG nHeight, BYTE value=255);
	BOOL m_fnCreateRGBImage(LONG nWidth, LONG nHeight, COLORREF value=0x00FFFFFF);

	// Object Copy
	BOOL m_fnCopy(CDib* pDib);
	CDib& operator = (const CDib& Dib);

	// Pixel Control
	BYTE** m_fnGetGrayPtr();
	RGBBYTE** m_fnGetRgbPtr();

	// Clipboard Control
	BOOL m_fnCopyToClipboard();
	BOOL m_fnPasteFromClipboard();

protected:
	BOOL m_fnLoadBMP(LPCTSTR lpszFileName);
	BOOL m_fnSaveBMP(LPCTSTR lpszFileName);


protected:
	LONG m_nWidth;
	LONG m_nHeight;
	WORD m_nBitCount;
	DWORD m_nDibSize;

	BYTE* m_pDib;

	BYTE** m_pGrayPtr;
	RGBBYTE** m_pRgbPtr;
};

///////////////////////////////////////////////////////////////////////////
// 템플릿 전역 함수 정의
///////////////////////////////////////////////////////////////////////////

/*************************************************************************
* 
* 이름 : limit(const T& value)
* 인자 : value - 정수 혹은 실수.
* 반환 : 0~255 사이의 값.
* 설명 : value 값이 0보다 작으면 0으로, 255보다 크면 255로 변경한다.
* 
*************************************************************************/

template<typename T>
inline T limit(const T& value)
{
	return ( (value > 255) ? 255 : ((value < 0) ? 0 : value) );
}

/*************************************************************************
* 
* 이름 : limit(const T& value, const T& lower, const T& upper)
* 인자 : value - 정수 혹은 실수.
* 반환 : lower ~ upper 사이의 값.
* 설명 : value 값이 lower보다 작으면 lower으로, 
*        upper보다 크면 upper로 변경한다.
* 
*************************************************************************/

template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
	return ((value > upper) ? upper : ((value < lower) ? lower : value));
}

/*************************************************************************
* 
* 이름 : swap(T& lha, T& rha)
* 인자 : lha - Left hand argument, rha - Right hand argument.
* 반환 : 없음.
* 설명 : rha와 lha의 값을 서로 바꾼다.
* 
*************************************************************************/

template<typename T> 
inline void swap(T& lha, T& rha)
{
	T tmp = lha;
	lha = rha;
	rha = tmp;
}



#endif // !defined(AFX_DIB_H__BFDD6CA5_526E_4A73_BEBD_ACD8349C3F0E__INCLUDED_)
