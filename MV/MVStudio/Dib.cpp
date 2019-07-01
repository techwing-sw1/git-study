// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MVStudio.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
	m_nWidth	= 0;
	m_nHeight	= 0;
	m_nBitCount = 0;
	m_nDibSize	= 0;
	
	m_pDib		= NULL;	
	m_pGrayPtr	= NULL;
	m_pRgbPtr	= NULL;
}

CDib::CDib(const CDib& Dib)
{
	m_nWidth	= 0;
	m_nHeight	= 0;
	m_nBitCount = 0;
	m_nDibSize	= 0;
	
	m_pDib		= NULL;	
	m_pGrayPtr	= NULL;
	m_pRgbPtr	= NULL;

	if( Dib.m_pDib ){
		m_pDib = new BYTE [Dib.m_nDibSize];
		memcpy(m_pDib, Dib.m_pDib, Dib.m_nDibSize);
		m_fnInitDib();
	}
}

CDib::~CDib()
{
	m_fnDestroy();
}

BOOL CDib::m_fnInitDib()
{
	LPBITMAPINFOHEADER bmi = (LPBITMAPINFOHEADER)m_pDib;

	m_nWidth	= bmi->biWidth;
	m_nHeight	= bmi->biHeight;
	m_nBitCount = bmi->biBitCount;

	DWORD dwImageSize = m_nHeight*(DWORD)((m_nWidth*m_nBitCount/8+3)&~3);

	m_nDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*m_fnGetPaletteNums() + dwImageSize;

	if( !m_fnAllocPtr() ){
		return FALSE;
	}

	return TRUE;
}

void CDib::m_fnDestroy()
{
	if( m_pDib ){
		delete [] m_pDib;
		m_pDib = NULL;
	}

	m_fnFreePtr();

	m_nWidth	= 0;
	m_nHeight	= 0;
	m_nBitCount = 0;
	m_nDibSize	= 0;
}

BOOL CDib::m_fnAllocPtr()
{
	register int i;
	if( m_nBitCount == 8 ){
		if( m_pGrayPtr ) m_fnFreePtr();
		m_pGrayPtr = new BYTE* [m_nHeight];
		if( m_pGrayPtr == NULL ) return FALSE;

		DWORD nRWidth = (DWORD)((m_nWidth*m_nBitCount/8+3)&~3);
		BYTE* pData = (BYTE*)m_fnGetDibBitsAddr();
		for( i=0; i<m_nHeight; i++){
			m_pGrayPtr[i] = (BYTE*)(pData+(m_nHeight-1-i)*nRWidth);
		}
	}
	else if( m_nBitCount == 24 ){
		if(m_pRgbPtr) m_fnFreePtr();
		m_pRgbPtr = new RGBBYTE* [m_nHeight];
		if( m_pRgbPtr == NULL ) return FALSE;

		DWORD nRWidth = (DWORD)((m_nWidth*m_nBitCount/8+3)&~3);
		BYTE* pData = (BYTE*)m_fnGetDibBitsAddr();
		for( i=0; i<m_nHeight; i++){
			m_pRgbPtr[i] = (RGBBYTE*)(pData+(m_nHeight-1-i)*nRWidth);
		}
	}
	else{
		return FALSE;
	}

	return TRUE;
}

void CDib::m_fnFreePtr()
{
	if( m_pGrayPtr ){
		delete [] m_pGrayPtr;
		m_pGrayPtr = NULL;
	}

	if( m_pRgbPtr ){
		delete [] m_pRgbPtr;
		m_pRgbPtr = NULL;
	}
}

int CDib::m_fnGetPaletteNums()
{
	switch( m_nBitCount )
	{
	case 1:
	case 4:
	case 8:
		return 1<<m_nBitCount;
	}
	return 0;
}

BOOL CDib::m_fnIsValid()
{
	return (m_pDib == NULL) ? FALSE : TRUE;
}

LPVOID CDib::m_fnGetDibBitsAddr()
{
	LPVOID pDibBits = NULL;
	pDibBits = (LPVOID)(m_pDib	+ sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*m_fnGetPaletteNums());
	return pDibBits;
}

LPBITMAPINFO CDib::m_fnGetBitmapInfoAddr()
{
	return (LPBITMAPINFO)m_pDib;
}

// Image Load/Save
BOOL CDib::m_fnLoad(LPCTSTR lpszFileName)
{
	BOOL bRet = FALSE;
	CString strFmt="";
	strFmt = lpszFileName;
	strFmt.MakeUpper();

	if( strFmt.Right(4) == ".BMP"){
		bRet = m_fnLoadBMP(lpszFileName);
	}else{
		return FALSE;
	}
	return bRet;
}

BOOL CDib::m_fnSave(LPCTSTR lpszFileName)
{
	BOOL bRet = FALSE;
	CString strFmt="";
	strFmt = lpszFileName;
	strFmt.MakeUpper();

	if( strFmt.Right(4) == ".BMP"){
		bRet = m_fnSaveBMP(lpszFileName);
	}else{
		return FALSE;
	}
	return bRet;
}

// Image Draw
void CDib::m_fnDraw(HDC hDC)
{
	m_fnDraw(hDC, 0, 0);
}

void CDib::m_fnDraw(HDC hDC, int dx, int dy)
{
	if( m_pDib == NULL ) return;

	LPVOID lpDibBits = m_fnGetDibBitsAddr();
	LPBITMAPINFO lpBitmapInfo = m_fnGetBitmapInfoAddr();

	::SetDIBitsToDevice(
		hDC,
		dx,
		dy,
		m_nWidth,
		m_nHeight,
		0,
		0,
		0,
		m_nHeight,
		lpDibBits,
		lpBitmapInfo,
		DIB_RGB_COLORS);
}

void CDib::m_fnDraw(HDC hDC, int dx, int dy, int dw, int dh, DWORD Rop/*=SRCCOPY*/)
{
	if( m_pDib == NULL ) return;

	LPVOID lpDibBits = m_fnGetDibBitsAddr();
	LPBITMAPINFO lpBitmapInfo = m_fnGetBitmapInfoAddr();

	::StretchDIBits(
		hDC,
		dx,
		dy,
		dw,
		dh,
		0,
		0,
		m_nWidth,
		m_nHeight,
		lpDibBits,
		lpBitmapInfo,
		DIB_RGB_COLORS,
		Rop);
}

void CDib::m_fnDraw(HDC hDC, int dx, int dy, int dw, int dh,
						int sx, int sy, int sw, int sh, DWORD Rop/* = SRCCOPY*/)
{
	if( m_pDib == NULL ) return;

	LPVOID lpDibBits = m_fnGetDibBitsAddr();
	LPBITMAPINFO lpBitmapInfo = m_fnGetBitmapInfoAddr();

	::StretchDIBits(
		hDC,
		dx,
		dy,
		dw,
		dh,
		sx,
		sy,
		sw,
		sh,
		lpDibBits,
		lpBitmapInfo,
		DIB_RGB_COLORS,
		Rop);
}

// New Image Create
BOOL CDib::m_fnCreateGrayImage(LONG nWidth, LONG nHeight, BYTE value/*=255*/)
{
	if( m_pDib ) m_fnDestroy();

	WORD nBitCount=8;
	DWORD dwImageSize = nHeight*((nWidth*nBitCount/8+3)&~3);
	DWORD dwDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*(1<<nBitCount) + dwImageSize;
	
	m_pDib = new BYTE [dwDibSize];

	LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER)m_pDib;
	lpBitmapInfo->biBitCount		= nBitCount;
	lpBitmapInfo->biWidth			= nWidth;
	lpBitmapInfo->biHeight			= nHeight;
	lpBitmapInfo->biCompression		= BI_RGB;
	lpBitmapInfo->biPlanes			= 1;
	lpBitmapInfo->biSize			= sizeof(BITMAPINFOHEADER);
	lpBitmapInfo->biSizeImage		= dwImageSize;
	lpBitmapInfo->biClrUsed			= 0;
	lpBitmapInfo->biClrImportant	= 0;
	lpBitmapInfo->biXPelsPerMeter	= 0;
	lpBitmapInfo->biYPelsPerMeter	= 0;

	LPRGBQUAD pPal = NULL;
	pPal = LPRGBQUAD(m_pDib+sizeof(BITMAPINFOHEADER));

	for( int i=0; i<256; i++){
		(pPal+i)->rgbRed		= (BYTE)i;
		(pPal+i)->rgbGreen		= (BYTE)i;
		(pPal+i)->rgbBlue		= (BYTE)i;
		(pPal+i)->rgbReserved	= 0;
	}

	if( !m_fnInitDib() ){
		return FALSE;
	}

	BYTE* pImage = (BYTE*)m_fnGetDibBitsAddr();
	memset(pImage, value, dwImageSize);

	return TRUE;
}

BOOL CDib::m_fnCreateRGBImage(LONG nWidth, LONG nHeight, COLORREF value/*=0x00FFFFFF*/)
{
	WORD nBitCount = 24;

	DWORD dwImageSize = nHeight*((nWidth*nBitCount/8+3)&~3);
	DWORD dwDibSize = sizeof(BITMAPINFOHEADER) + dwImageSize;

	if( m_pDib ) m_fnDestroy();
	m_pDib = new BYTE [dwDibSize];
	
	LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER)m_pDib;
	lpBitmapInfo->biBitCount		= nBitCount;
	lpBitmapInfo->biWidth			= nWidth;
	lpBitmapInfo->biHeight			= nHeight;
	lpBitmapInfo->biCompression		= BI_RGB;
	lpBitmapInfo->biPlanes			= 1;
	lpBitmapInfo->biSize			= sizeof(BITMAPINFOHEADER);
	lpBitmapInfo->biSizeImage		= dwImageSize;
	lpBitmapInfo->biClrUsed			= 0;
	lpBitmapInfo->biClrImportant	= 0;
	lpBitmapInfo->biXPelsPerMeter	= 0;
	lpBitmapInfo->biYPelsPerMeter	= 0;

	if( !m_fnInitDib() ){
		return FALSE;
	}

	RGBBYTE** pImage = m_fnGetRgbPtr();
	register int y=0,x=0;
	for(y=0; y<nHeight; y++){
		for(x=0; x<nWidth; x++){
			pImage[y][x] = value;
		}
	}
	return TRUE;
}

// copy
CDib& CDib::operator = (const CDib& Dib)
{
	if( this == &Dib ){
		return *this;
	}

	if( m_pDib ) m_fnDestroy();

	m_pDib = new BYTE [Dib.m_nDibSize];
	memcpy(m_pDib, Dib.m_pDib, Dib.m_nDibSize);

	m_fnInitDib();

	return *this;
}

BOOL CDib::m_fnCopy(CDib* pDib)
{
	if( pDib == NULL ) return FALSE;
	if( pDib->m_pDib == NULL ) return FALSE;

	if( m_pDib ) m_fnDestroy();
	
	m_pDib = new BYTE [pDib->m_nDibSize];
	memcpy(m_pDib, pDib->m_pDib, pDib->m_nDibSize);

	m_fnInitDib();

	return TRUE;
}

// pixel control
BYTE** CDib::m_fnGetGrayPtr()
{
	ASSERT( m_nBitCount == 8 );
	ASSERT( m_pDib != NULL );
	return m_pGrayPtr;
}

RGBBYTE** CDib::m_fnGetRgbPtr()
{
	ASSERT( m_nBitCount == 24 );
	ASSERT( m_pDib != NULL );
	return m_pRgbPtr;
}

// clipboard
BOOL CDib::m_fnCopyToClipboard()
{
	int     dwSizeDib;
	HANDLE  hMem;
	
	if( !::OpenClipboard( NULL ) )	return FALSE;
	
	// DIB 전체를 전역 메모리 블럭에 복사
	
	dwSizeDib = m_fnGetDibSize();
	hMem = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE, dwSizeDib);
	if( hMem == NULL )	
	{
		::CloseClipboard();
		return FALSE;
	}
	
	void* lpDib = ::GlobalLock((HGLOBAL)hMem);
	memcpy(lpDib, m_fnGetBitmapInfoAddr(), dwSizeDib);
	::GlobalUnlock(hMem);
	
	// 클립보드에 데이터 입력
	
	::EmptyClipboard();
	::SetClipboardData(CF_DIB, hMem);
	::CloseClipboard();
	
	return TRUE;
}

BOOL CDib::m_fnPasteFromClipboard()
{
	if( !::IsClipboardFormatAvailable(CF_DIB) ){
		return FALSE;
	}

	if( !::OpenClipboard( NULL ) ){
		return FALSE;
	}

	HANDLE hMem=NULL;
	hMem = ::GetClipboardData(CF_DIB);
	::CloseClipboard();
	if( hMem == NULL ){
		return FALSE;
	}

	LPVOID pData = NULL;
	pData = ::GlobalLock( hMem );
	if( pData == NULL ){
		return FALSE;
	}

	LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER)pData;
	LONG nWidth		= lpBitmapInfo->biWidth;
	LONG nHeight	= lpBitmapInfo->biHeight;
	WORD nBitCount	= lpBitmapInfo->biBitCount;

	DWORD dwImageSize = nHeight*((nWidth*nBitCount/8+3)&~3);
	DWORD dwDibSize = 0;
	if( nBitCount == 8 ){
		dwDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*(1<<nBitCount) + dwImageSize;
	}
	else if( nBitCount == 24 ){
		dwDibSize = sizeof(BITMAPINFOHEADER) + dwImageSize;
	}else{
		return FALSE;
	}

	if( m_pDib ) m_fnDestroy();
	m_pDib = new BYTE [dwDibSize];	
	memcpy(m_pDib, pData, dwDibSize);
	::GlobalUnlock( hMem );

	m_fnInitDib();

	return TRUE;
}

BOOL CDib::m_fnLoadBMP(LPCTSTR lpszFileName)
{
	CFile file;
	if( !file.Open(lpszFileName, CFile::modeRead|CFile::shareDenyRead) ){
		return FALSE;
	}

	BITMAPFILEHEADER bmfh;
	file.Read(&bmfh, sizeof(BITMAPFILEHEADER));

	if( bmfh.bfType != DIB_HEADER_MARKER ){
		file.Close();
		return FALSE;
	}

	DWORD dwDibSize = bmfh.bfSize - sizeof(BITMAPFILEHEADER);

	if( m_pDib ) m_fnDestroy();
	m_pDib = new BYTE [dwDibSize];

	file.Read(m_pDib, dwDibSize);

	file.Close();

	m_fnInitDib();

	return TRUE;
}

BOOL CDib::m_fnSaveBMP(LPCTSTR lpszFileName)
{
	CFile file;

	file.Open(lpszFileName, CFile::modeWrite|CFile::modeCreate );

	// set BITMAPFILEHEADER
	BITMAPFILEHEADER bmfh;
	bmfh.bfType		= DIB_HEADER_MARKER;
	bmfh.bfSize		= sizeof(BITMAPFILEHEADER)+m_nDibSize;
	bmfh.bfOffBits	= sizeof(BITMAPFILEHEADER)
					+ sizeof(BITMAPINFOHEADER)
					+ sizeof(RGBQUAD)*m_fnGetPaletteNums();
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;

	file.Write(&bmfh, sizeof(BITMAPFILEHEADER));

	file.Write(m_pDib, m_nDibSize);

	file.Close();

	return TRUE;
}
