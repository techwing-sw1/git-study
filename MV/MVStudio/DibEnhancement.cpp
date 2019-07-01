#include <StdAfx.h>
#include "DibEnhancement.h"

#include <math.h>

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//  화장 향상
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

/*=====================================================================
*
*=====================================================================*/
int MV_Inverse(CDib& Src, CDib& Result)
{
	Result = Src;
	register int x=0, y=0;

	int w = Result.m_fnGetWidth();
	int h = Result.m_fnGetHeight();
	
	if( 8 == Result.m_fnGetBitCount() ){
		BYTE** ptr = NULL;
		ptr = Result.m_fnGetGrayPtr();
		if( ptr == NULL ) return -1;
		for( y = 0 ; y < h ; y++ ) {
			for( x = 0 ; x < w ; x++ ) {
				ptr[y][x] = 255 - ptr[y][x];
			}
		}
	}else if( 24 == Result.m_fnGetBitCount() ){
		RGBBYTE** ptr=NULL;
		ptr = Result.m_fnGetRgbPtr();
		if( ptr == NULL ) return -1;
		for( y = 0 ; y < h ; y++ ) {
			for( x = 0 ; x < w ; x++ ) {
				ptr[y][x].r = 255 - ptr[y][x].r;
				ptr[y][x].g = 255 - ptr[y][x].g;
				ptr[y][x].b = 255 - ptr[y][x].b;
			}
		}
	}else{
		return -2;
	}
	
	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_Brightness(CDib& Src, int nVal, CDib& Result)
{
	Result = Src;
	register int x=0, y=0;
	
	int w = Result.m_fnGetWidth();
	int h = Result.m_fnGetHeight();

	if( Result.m_fnGetBitCount() == 8 ){
		BYTE** ptr = NULL;
		ptr = Result.m_fnGetGrayPtr();
		if( ptr == NULL ) return -1;
		for( y=0; y<h; y++){
			for( x=0; x<w; x++){
				ptr[y][x] =	limit(ptr[y][x] + nVal);
			}
		}
	}else if( Result.m_fnGetBitCount() == 24 ){
		RGBBYTE** ptr = NULL;
		ptr = Result.m_fnGetRgbPtr();
		if( ptr == NULL ) return -1;
		for( y=0; y<Result.m_fnGetHeight(); y++){
			for( x=0; x<Result.m_fnGetWidth(); x++){
				ptr[y][x].r = limit(ptr[y][x].r + nVal);
				ptr[y][x].g = limit(ptr[y][x].g + nVal);
				ptr[y][x].b = limit(ptr[y][x].b + nVal);
			}
		}
		
	}else{
		return -2;
	}
	return 0;
}

/*=====================================================================
* ARGUMETN : nAlpha = 0~100 [%]
* RETURE   : 0 = OK, -1 = dib ptr err
*=====================================================================*/
int MV_Contrast(CDib& Src, int nAlpha, CDib& Result)
{
	Result = Src;
	register int x=0, y=0;
	
	int w = Result.m_fnGetWidth();
	int h = Result.m_fnGetHeight();

	if( Result.m_fnGetBitCount() == 8 )
	{
		BYTE** ptr = NULL;
		ptr = Result.m_fnGetGrayPtr();
		if( ptr == NULL ) return -1;
		for( y=0; y<h; y++){
			for( x=0; x<w; x++){
				ptr[y][x] =	limit(ptr[y][x] + ((ptr[y][x] - 128) * (nAlpha / 100)) );
			}
		}
	}
	else if( Result.m_fnGetBitCount() == 24 )
	{
		RGBBYTE** ptr = NULL;
		ptr = Result.m_fnGetRgbPtr();
		if( ptr == NULL ) return -1;
		for( y=0; y<h; y++){
			for( x=0; x<w; x++){
				ptr[y][x].r = limit(ptr[y][x].r + ((ptr[y][x].r - 128) * (nAlpha / 100)));
				ptr[y][x].g = limit(ptr[y][x].g + ((ptr[y][x].g - 128) * (nAlpha / 100)));
				ptr[y][x].b = limit(ptr[y][x].b + ((ptr[y][x].b - 128) * (nAlpha / 100)));
			}
		}		
	}else{
		return -2;
	}
	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_GammaCollection(CDib& Src, double dGamma, CDib& Result)
{
	Result = Src;
	register int x=0, y=0;
	double invgamm = 1.0f /dGamma;

	int w = Result.m_fnGetWidth();
	int h = Result.m_fnGetHeight();
	
	if( Result.m_fnGetBitCount() == 8 ) 
	{
		BYTE** ptr = NULL;
		ptr = Result.m_fnGetGrayPtr();
		if( ptr == NULL ) return -1;
		for( y = 0; y < h; y++) {
			for( x = 0; x < w; x++ ) {
				ptr[y][x] =	(BYTE) limit( pow(((float)ptr[y][x]/255.f), invgamm ) * 255.f + 0.5);
			}
		}
	}
	else if (Result.m_fnGetBitCount() == 24) 
	{
		RGBBYTE** ptr = NULL;
		ptr = Result.m_fnGetRgbPtr();
		if( ptr == NULL ) return -1;
		for( y = 0 ; y < h ; y++ ) {
			for( x = 0 ; x < w ; x++ ) {
				ptr[y][x].r =(BYTE) limit( pow(((float)ptr[y][x].r/255.f), invgamm ) * 255.f + 0.5);
				ptr[y][x].g =(BYTE) limit( pow(((float)ptr[y][x].g/255.f), invgamm ) * 255.f + 0.5);
				ptr[y][x].b =(BYTE) limit( pow(((float)ptr[y][x].b/255.f), invgamm ) * 255.f + 0.5);
			}
		}		
	}
	else
	{
		return -2;
	}
	return 0;
}

/*=====================================================================
* fHisto : 전체 픽셀에서 해당 Gray값을 갖는 픽셀의 비율
*=====================================================================*/
int MV_Histogram(CDib& Dib, float fHisto[256])
{
	float fTemp[256];
	register int x=0, y=0;
	int w = Dib.m_fnGetWidth();
	int h = Dib.m_fnGetHeight();

	if( Dib.m_fnGetBitCount() != 8 ) return -1;	

	memset(fTemp, 0x00, sizeof(float)*256);

	BYTE** ptr=NULL;
	ptr = Dib.m_fnGetGrayPtr();
	if( ptr == NULL ) return -3;
	for( y=0; y<h; y++){
		for( x=0; x<w; x++){
			if( ptr[y][x] < 0   ) ptr[y][x] = 0;
			if( ptr[y][x] > 255 ) ptr[y][x] = 255;
			fTemp[ptr[y][x]]++;		
		}
	}

	int area = w*h;
	for( x=0; x<256; x++){
		fHisto[x] = fTemp[x] / (float)area;
	}

	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_HistogramRGB(CDib& Dib, float fHistoR[256], float fHistoG[256], float fHistoB[256])
{
	float fTempR[256];
	float fTempG[256];
	float fTempB[256];
	register int x=0, y=0;
	int w = Dib.m_fnGetWidth();
	int h = Dib.m_fnGetHeight();

	if( Dib.m_fnGetBitCount() != 24 ) return -1;	

	memset(fTempR, 0x00, sizeof(float)*256);
	memset(fTempG, 0x00, sizeof(float)*256);
	memset(fTempB, 0x00, sizeof(float)*256);

	RGBBYTE** ptr=NULL;
	ptr = Dib.m_fnGetRgbPtr();
	if( ptr == NULL ) return -3;
	for( y=0; y<h; y++){
		for( x=0; x<w; x++){
			fTempR[ptr[y][x].r]++;		
			fTempG[ptr[y][x].g]++;		
			fTempB[ptr[y][x].b]++;		
		}
	}

	int area = w*h;
	for( x=0; x<256; x++){
		fHistoR[x] = fTempR[x] / (float)area;
		fHistoG[x] = fTempG[x] / (float)area;
		fHistoB[x] = fTempB[x] / (float)area;
	}

	return 0;
}


/*=====================================================================
*
*=====================================================================*/
int MV_HistoEqulization(CDib& Src, CDib& Result)
{
	int w,h;
	register int i,j;

	Result = Src;
	w = Result.m_fnGetWidth();
	h = Result.m_fnGetHeight();

	if( Src.m_fnGetBitCount() == 8 )
	{
		float fHisto[256];
		memset(fHisto, 0x00, sizeof(float)*256);

		MV_Histogram(Src, fHisto);

		float cdf[256];
		memset(cdf, 0x00, sizeof(float)*256);

		cdf[0] = fHisto[0];
		for(i=1; i<256; i++)
		{
			cdf[i] = cdf[i-1] + fHisto[i];
		}

		BYTE** ptr = NULL;
		ptr = Result.m_fnGetGrayPtr();
		if( ptr == NULL ) return -1;

		for( j=0; j<h; j++){
			for(i=0; i<w; i++){
				ptr[j][i] = (BYTE)limit( cdf[ptr[j][i]]*255 );
			}
		}
	}
	else if( Src.m_fnGetBitCount() == 24 )
	{
		float fHistoRGB[3][256];
		memset(fHistoRGB, 0x00, sizeof(float)*256*3);

		MV_HistogramRGB(Src, fHistoRGB[0], fHistoRGB[1], fHistoRGB[2]);

		float cdf_rgb[3][256];
		memset(cdf_rgb, 0x00, sizeof(float)*256*3);

		cdf_rgb[0][0] = fHistoRGB[0][0];
		cdf_rgb[1][0] = fHistoRGB[1][0];
		cdf_rgb[2][0] = fHistoRGB[2][0];

		for(i=1; i<256; i++)
		{
			cdf_rgb[0][i] = cdf_rgb[0][i-1] + fHistoRGB[0][i];
			cdf_rgb[1][i] = cdf_rgb[1][i-1] + fHistoRGB[1][i];
			cdf_rgb[2][i] = cdf_rgb[2][i-1] + fHistoRGB[2][i];
		}

		RGBBYTE** ptr = NULL;
		ptr = Result.m_fnGetRgbPtr();
		if( ptr == NULL ) return -2;
		for( j=0; j<h; j++)
		{
			for( i=0; i<w; i++)
			{
				ptr[j][i].r = (BYTE)limit( cdf_rgb[0][ptr[j][i].r]*255 );
				ptr[j][i].g = (BYTE)limit( cdf_rgb[1][ptr[j][i].g]*255 );
				ptr[j][i].b = (BYTE)limit( cdf_rgb[2][ptr[j][i].b]*255 );
			}
		}
	}
	else
	{
		return -2;
	}

	return 0;
}



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//  산술 및 논리 연산
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


/*=====================================================================
*
*=====================================================================*/
int MV_Add(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr)
{
	register int x,y;
	int w = Dib1.m_fnGetWidth();
	int h = Dib1.m_fnGetHeight();
	if( w != Dib2.m_fnGetWidth() || h != Dib2.m_fnGetHeight() ) {
		sprintf(szErr, "Image size is different!");
		return -1;
	}

	if( Dib1.m_fnGetBitCount() == 8 && Dib2.m_fnGetBitCount() == 8 )
	{
		Result.m_fnCreateGrayImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		BYTE** ptr1 = Dib1.m_fnGetGrayPtr();
		BYTE** ptr2 = Dib2.m_fnGetGrayPtr();
		BYTE** ptr_result = Result.m_fnGetGrayPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = (BYTE)limit(ptr1[y][x] + ptr2[y][x]);
			}
		}		
	}
	else if( Dib1.m_fnGetBitCount() == 24 && Dib2.m_fnGetBitCount() == 24 )
	{
		Result.m_fnCreateRGBImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		RGBBYTE** ptr1 = Dib1.m_fnGetRgbPtr();
		RGBBYTE** ptr2 = Dib2.m_fnGetRgbPtr();
		RGBBYTE** ptr_result = Result.m_fnGetRgbPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = ptr1[y][x] + ptr2[y][x];
			}
		}		
	}
	else{
		sprintf(szErr, "Bitcount is diffent!");
		return -2;
	}
	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_Sub(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr)
{
	register int x,y;
	int w = Dib1.m_fnGetWidth();
	int h = Dib1.m_fnGetHeight();
	if( w != Dib2.m_fnGetWidth() || h != Dib2.m_fnGetHeight() ) {
		sprintf(szErr, "Image size is different.");
		return -1;
	}
	if( Dib1.m_fnGetBitCount() == 8 && Dib2.m_fnGetBitCount() == 8 )
	{
		Result.m_fnCreateGrayImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		BYTE** ptr1 = Dib1.m_fnGetGrayPtr();
		BYTE** ptr2 = Dib2.m_fnGetGrayPtr();
		BYTE** ptr_result = Result.m_fnGetGrayPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = (BYTE)limit(ptr1[y][x] - ptr2[y][x]);
			}
		}		
	}
	else if( Dib1.m_fnGetBitCount() == 24 && Dib2.m_fnGetBitCount() == 24 )
	{
		Result.m_fnCreateRGBImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		RGBBYTE** ptr1 = Dib1.m_fnGetRgbPtr();
		RGBBYTE** ptr2 = Dib2.m_fnGetRgbPtr();
		RGBBYTE** ptr_result = Result.m_fnGetRgbPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = ptr1[y][x] - ptr2[y][x];
			}
		}		
	}
	else
	{
		sprintf(szErr, "Bitcount is different.");
		return -2;
	}
	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_Avr(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr)
{
	register int x,y;
	int w = Dib1.m_fnGetWidth();
	int h = Dib1.m_fnGetHeight();
	if( w != Dib2.m_fnGetWidth() || h != Dib2.m_fnGetHeight() ) {
		sprintf(szErr, "Image size is different.");
		return -1;
	}
	if( Dib1.m_fnGetBitCount() == 8 && Dib2.m_fnGetBitCount() == 8 )
	{
		Result.m_fnCreateGrayImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		BYTE** ptr1 = Dib1.m_fnGetGrayPtr();
		BYTE** ptr2 = Dib2.m_fnGetGrayPtr();
		BYTE** ptr_result = Result.m_fnGetGrayPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = (BYTE)limit((ptr1[y][x] + ptr2[y][x])/2);
			}
		}		
	}
	else if( Dib1.m_fnGetBitCount() == 24 && Dib2.m_fnGetBitCount() == 24 )
	{
		Result.m_fnCreateRGBImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		RGBBYTE** ptr1 = Dib1.m_fnGetRgbPtr();
		RGBBYTE** ptr2 = Dib2.m_fnGetRgbPtr();
		RGBBYTE** ptr_result = Result.m_fnGetRgbPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = (RGBBYTE)(ptr1[y][x] + ptr2[y][x])/2;
			}
		}		
	}
	else
	{
		sprintf(szErr, "Bitcount is different.");
		return -2;
	}
	return 0;
}

/*=====================================================================
* image process는 1D에서만 처리
*=====================================================================*/
int MV_Diff(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr)
{
	register int x,y;
	int w = Dib1.m_fnGetWidth();
	int h = Dib1.m_fnGetHeight();
	if( w != Dib2.m_fnGetWidth() || h != Dib2.m_fnGetHeight() ) {
		sprintf(szErr, "Image size is different.");
		return -1;
	}
	if( Dib1.m_fnGetBitCount() != 8 || Dib2.m_fnGetBitCount() != 8 ){
		sprintf(szErr, "Image is not gray.");
		return -3;
	}

	if( Dib1.m_fnGetBitCount() == 8 && Dib2.m_fnGetBitCount() == 8 )
	{
		Result.m_fnCreateGrayImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		BYTE** ptr1 = Dib1.m_fnGetGrayPtr();
		BYTE** ptr2 = Dib2.m_fnGetGrayPtr();
		BYTE** ptr_result = Result.m_fnGetGrayPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = (ptr1[y][x] > ptr2[y][x]) ? (BYTE)limit((ptr1[y][x] - ptr2[y][x])) : (BYTE)limit((ptr2[y][x] - ptr1[y][x]));
			}
		}		
	}
	else
	{
		sprintf(szErr, "Bitcount is different.");
		return -2;
	}
	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_AND(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr)
{
	register int x,y;
	int w = Dib1.m_fnGetWidth();
	int h = Dib1.m_fnGetHeight();
	if( w != Dib2.m_fnGetWidth() || h != Dib2.m_fnGetHeight() ) {
		sprintf(szErr, "Image size is diffenent.");
		return -1;
	}
	if( Dib1.m_fnGetBitCount() != 8 || Dib2.m_fnGetBitCount() != 8 ){
		sprintf(szErr, "Image is not gray.");
		return -3;
	}

	if( Dib1.m_fnGetBitCount() == 8 && Dib2.m_fnGetBitCount() == 8 )
	{
		Result.m_fnCreateGrayImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		BYTE** ptr1 = Dib1.m_fnGetGrayPtr();
		BYTE** ptr2 = Dib2.m_fnGetGrayPtr();
		BYTE** ptr_result = Result.m_fnGetGrayPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = (BYTE)limit((ptr1[y][x] & ptr2[y][x]));
			}
		}		
	}
	else
	{
		sprintf(szErr, "Bitcount is different.");
		return -2;
	}
	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_OR(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr)
{
	register int x,y;
	int w = Dib1.m_fnGetWidth();
	int h = Dib1.m_fnGetHeight();
	if( w != Dib2.m_fnGetWidth() || h != Dib2.m_fnGetHeight() ) {
		sprintf(szErr, "Image size is diffenent.");
		return -1;
	}
	if( Dib1.m_fnGetBitCount() != 8 || Dib2.m_fnGetBitCount() != 8 ){
		sprintf(szErr, "Image is not gray.");
		return -3;
	}

	if( Dib1.m_fnGetBitCount() == 8 && Dib2.m_fnGetBitCount() == 8 )
	{
		Result.m_fnCreateGrayImage( Dib1.m_fnGetWidth(), Dib1.m_fnGetHeight());
		BYTE** ptr1 = Dib1.m_fnGetGrayPtr();
		BYTE** ptr2 = Dib2.m_fnGetGrayPtr();
		BYTE** ptr_result = Result.m_fnGetGrayPtr();
		
		for(y=0; y<h; y++)
		{
			for( x=0; x<w; x++)
			{
				ptr_result[y][x] = (BYTE)limit((ptr1[y][x] | ptr2[y][x]));
			}
		}		
	}
	else
	{
		sprintf(szErr, "Bitcount is different.");
		return -2;
	}
	return 0;
}

/*=====================================================================
* nBit : 0~7
*=====================================================================*/
int MV_BitPlane(CDib& Dib, int nBit, CDib& Result, char* szErr)
{
	Result = Dib;

	if( nBit < 0 || nBit > 7 ) {
		sprintf(szErr, "parameter error.");
		return -1; 
	}

	if( Dib.m_fnGetBitCount() != 8 ){
		sprintf(szErr, "Image is not gray.");
		return -2;	
	}

	BYTE** ptr1 = NULL;
	BYTE** ptr2 = NULL;
	ptr1 = Dib.m_fnGetGrayPtr();
	ptr2 = Result.m_fnGetGrayPtr();
	if( ptr1 == NULL || ptr2 == NULL) {
		sprintf(szErr, "memory can not allocated.");
		return -3;
	}

	register int x,y;
	int w = Dib.m_fnGetWidth();
	int h = Dib.m_fnGetHeight();

	for(y=0; y<h; y++)
	{
		for(x=0; x<w; x++)
		{
			ptr2[y][x] = (ptr1[y][x] & (0x01<<nBit)) ? 255 : 0;
		}
	}

	return 0;
}

/*=====================================================================
* nBit : 1~8, Clear 할 비트개수(하위비트부터)
*=====================================================================*/
int MV_BitClean(CDib& Dib, int nBit, CDib& Result, char* szErr)
{
	Result = Dib;

	if( nBit < 0 || nBit > 7 ) {
		sprintf(szErr, "parameter error.");
		return -1; 
	}

	if( Dib.m_fnGetBitCount() != 8 ){
		sprintf(szErr, "Image is not gray.");           
		return -2;	
	}

	BYTE** ptr1 = NULL;
	BYTE** ptr2 = NULL;
	ptr1 = Dib.m_fnGetGrayPtr();
	ptr2 = Result.m_fnGetGrayPtr();
	if( ptr1 == NULL || ptr2 == NULL) {
		sprintf(szErr, "memory can not allocated.");
		return -3;
	}

	register int x,y;
	int w = Dib.m_fnGetWidth();
	int h = Dib.m_fnGetHeight();
	int nMask = 0; // 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F,0xFF

	for(y=0; y<h; y++)
	{
		for(x=0; x<w; x++)
		{
			ptr2[y][x] = (ptr2[y][x] & (0xFF<<(nBit)));
		}
	}

	return 0;
}

/*=====================================================================
*
*=====================================================================*/
int MV_Masking(CDib& Dib, int nMaskOpt, BYTE* m)
{
	int w=0,h=0;
	w = Dib.m_fnGetWidth();
	h = Dib.m_fnGetHeight();

	CDib cpy = Dib;

	BYTE** ptr1 = NULL;
	BYTE** ptr2 = NULL;
	ptr1 = Dib.m_fnGetGrayPtr();
	ptr2 = cpy.m_fnGetGrayPtr();

	register int x=0,y=0;
	double dTemp=0.0,dSum=0.0;
	if( nMaskOpt == 0 ){
		dSum =  m[0]+m[1]+m[2]+
				m[3]+m[4]+m[5]+
				m[6]+m[7]+m[8];
		for(y=1; y<h-1; y++){
			for(x=1; x<w-1; x++){
				dTemp = 0.0;
				dTemp = ptr2[y-1][x-1]*m[0] + ptr2[y-1][x]*m[1] + ptr2[y-1][x+1]*m[2] +
						ptr2[y  ][x-1]*m[3] + ptr2[y  ][x]*m[4] + ptr2[y  ][x+1]*m[5] +
						ptr2[y+1][x-1]*m[6] + ptr2[y+1][x]*m[7] + ptr2[y+1][x+1]*m[8];				

				ptr1[y][x] = (BYTE)limit(dTemp/dSum + 0.5);
			}
		}
	}else{
		dSum =  m[ 0]+m[ 1]+m[ 2]+m[ 3]+m[ 4]+
				m[ 5]+m[ 6]+m[ 7]+m[ 8]+m[ 9]+
				m[10]+m[11]+m[12]+m[13]+m[14]+
				m[15]+m[16]+m[17]+m[18]+m[19]+
				m[20]+m[21]+m[22]+m[23]+m[24];
		for(y=2; y<h-2; y++){
			for(x=2; x<w-2; x++){
				dTemp = 0.0;
				dTemp = ptr2[y-2][x-2]*m[ 0] + ptr2[y-2][x-1]*m[ 1] + ptr2[y-2][x]*m[ 2] + ptr2[y-2][x+1]*m[ 3] + ptr2[y-2][x+2]*m[ 4] +
						ptr2[y-1][x-2]*m[ 5] + ptr2[y-1][x-1]*m[ 6] + ptr2[y-1][x]*m[ 7] + ptr2[y-1][x+1]*m[ 8] + ptr2[y-1][x+2]*m[ 9] +
						ptr2[y  ][x-2]*m[10] + ptr2[y  ][x-1]*m[11] + ptr2[y  ][x]*m[12] + ptr2[y  ][x+1]*m[13] + ptr2[y  ][x+2]*m[14] +
						ptr2[y+1][x-2]*m[15] + ptr2[y+1][x-1]*m[16] + ptr2[y+1][x]*m[17] + ptr2[y+1][x+1]*m[18] + ptr2[y+1][x+2]*m[19] +
						ptr2[y+2][x-2]*m[20] + ptr2[y+2][x-1]*m[21] + ptr2[y+2][x]*m[22] + ptr2[y+2][x+1]*m[23] + ptr2[y+2][x+2]*m[24];

				ptr1[y][x] = (BYTE)limit(dTemp/dSum + 0.5);
			}
		}
	}
	return 0;
}

/*=====================================================================
// 평균값 필터
nMaskOpt : 0=3x3, 1=5x5
         | 1 1 1 |
  1/9  x | 1 1 1 |
         | 1 1 1 |

         | 1 1 1 1 1 |
         | 1 1 1 1 1 |
  1/25 x | 1 1 1 1 1 |
         | 1 1 1 1 1 |
         | 1 1 1 1 1 |
=====================================================================*/
int MV_FilterMean(CDib& Dib, int nMaskOpt, char* szErr)
{
	BYTE mask1[9] = { 1, 1, 1,
					  1, 1, 1,
					  1, 1, 1};

	BYTE mask2[25] ={ 1, 1, 1, 1, 1,
					  1, 1, 1, 1, 1,
					  1, 1, 1, 1, 1,
					  1, 1, 1, 1, 1,
					  1, 1, 1, 1, 1};

	if( Dib.m_fnGetBitCount() != 8 ){
		sprintf(szErr, "Image is not gray.");
		return -1;
	}
	if( nMaskOpt < 0 || nMaskOpt > 1 ){
		sprintf(szErr, "nMaskOpt Parameter is error.");
		return -2;
	}

	if( nMaskOpt == 0 ){
		MV_Masking(Dib, nMaskOpt, mask1);
	}else{
		MV_Masking(Dib, nMaskOpt, mask2);
	}
	return 0;
}

/*=====================================================================
// 가중 평균값 필터
          | 1 2 1 |
  1/16  x | 2 4 2 |
          | 1 2 1 |

          |  1  4  6  4  1 |
          |  4 16 24 16  4 |
  1/256 x |  6 24 36 24  6 |
          |  4 16 24 16  4 |
          |  1  4  6  4  1 |
=====================================================================*/
int MV_FilterWMean(CDib& Dib, int nMaskOpt, char* szErr)
{
	BYTE mask1[9] = { 1, 2, 1,
					  2, 4, 2,
					  1, 2, 1};

	BYTE mask2[25] ={ 1,  4,  6,  4, 1,
					  4, 16, 24, 16, 4,
					  6, 24, 36, 24, 6,
					  4, 16, 24, 16, 4,
					  1,  4,  6,  4, 1};

	if( Dib.m_fnGetBitCount() != 8 ){
		sprintf(szErr, "Image is not gray.");
		return -1;
	}
	if( nMaskOpt < 0 || nMaskOpt > 1 ){
		sprintf(szErr, "nMaskOpt Parameter is error.");
		return -2;
	}

	if( nMaskOpt == 0 ){
		MV_Masking(Dib, nMaskOpt, mask1);
	}else{
		MV_Masking(Dib, nMaskOpt, mask2);
	}
	return 0;
}

int MV_FilterGausian(CDib& Dib, char* szErr)
{
	return 0;
}

int MV_FilterUnsharpMask(CDib& Dib, char* szErr)
{
	return 0;
}

int MV_FilterLaplacianUnsharpMask(CDib& Dib, char* szErr)
{
	return 0;
}

int MV_AddNoise(CDib& Dib, char* szErr)
{
	return 0;
}

int MV_AddNoiseSaltNPepper(CDib& Dib, int amount, char* szErr)
{
	return 0;
}

int MV_FilterMedian(CDib& Dib, char* szErr)
{
	return 0;
}

int MV_FilterAnisotropicDiffusion(CDib& Dib, char* szErr)
{
	return 0;
}


// biColor : 0=red, 1=green, 2=blue, 3=YUV
int MV_ConvertToGray(CDib& Src, CDib& Result, BYTE biColor, char* szErr)
{
	if( Src.m_fnGetBitCount() != 24 ){	
		sprintf(szErr, "Image is not color.");
		return -1;	
	}

	RGBBYTE** ptr1 = NULL;
	ptr1 = Src.m_fnGetRgbPtr();

	register int x,y;
	int w = Src.m_fnGetWidth();
	int h = Src.m_fnGetHeight();

	Result.m_fnCreateGrayImage(w, h);
	BYTE** ptr2=NULL;
	ptr2 = Result.m_fnGetGrayPtr();

	for(y=0; y<h; y++)
	{
		for(x=0; x<w; x++)
		{
			switch( biColor )
			{
			case 0: ptr2[y][x] = ptr1[y][x].r; break;
			case 1: ptr2[y][x] = ptr1[y][x].g; break;
			case 2: ptr2[y][x] = ptr1[y][x].b; break;
			case 3:
				{
					double val=0.0;
					val = ((ptr1[y][x].r*0.3) + (ptr1[y][x].g*0.59) + (ptr1[y][x].b*0.11));
					ptr2[y][x] = (BYTE)limit(val);
				}break;
			}			
		}
	}

	return 0;
}


