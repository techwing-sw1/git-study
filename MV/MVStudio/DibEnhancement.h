#ifndef __DIBENHANCEMENT_H__
#define __DIBENHANCEMENT_H__

#include "Dib.h"
#include "RGBBYTE.h"

// 이번에는 두번째 브랜치에서 수정 하였습니다.

// IMAGE Enhancement
int MV_Inverse(CDib& Src, CDib& Result);
int MV_Brightness(CDib& Src, int nVal, CDib& Result);
int MV_Contrast(CDib& Src, int nAlpha, CDib& Result);
int MV_GammaCollection(CDib& Src, double dGamma, CDib& Result);
int MV_Histogram(CDib& Dib, float fHisto[256]);
int MV_HistogramRGB(CDib& Dib, float fHistoR[256], float fHistoG[256], float fHistoB[256]);
int MV_HistoEqulization(CDib& Src, CDib& Result);

int MV_Add(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr);
int MV_Sub(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr);
int MV_Avr(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr);
int MV_Diff(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr);

int MV_AND(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr);
int MV_OR(CDib& Dib1, CDib& Dib2, CDib& Result, char* szErr);
int MV_BitPlane(CDib& Dib, int nBit, CDib& Result, char* szErr);
int MV_BitClean(CDib& Dib, int nBit, CDib& Result, char* szErr);

// FILTER Processing
int MV_Masking(CDib& Dib, int nMaskOpt, BYTE* m);
int MV_FilterMean(CDib& Dib, int nMaskOpt, char* szErr);
int MV_FilterWMean(CDib& Dib, int nMaskOpt, char* szErr);
int MV_FilterGausian(CDib& Dib, char* szErr);
int MV_FilterUnsharpMask(CDib& Dib, char* szErr);
int MV_FilterLaplacianUnsharpMask(CDib& Dib, char* szErr);
int MV_AddNoise(CDib& Dib, char* szErr);
int MV_AddNoiseSaltNPepper(CDib& Dib, int amount, char* szErr);
int MV_FilterMedian(CDib& Dib, char* szErr);
int MV_FilterAnisotropicDiffusion(CDib& Dib, char* szErr);

// COLOR Processing
int MV_ConvertToGray(CDib& Src, CDib& Result, BYTE biColor, char* szErr); 



#endif // __DIBENHANCEMENT_H__