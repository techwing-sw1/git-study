// DlgHistogram.cpp : implementation file
//

#include "stdafx.h"
#include "MVStudio.h"
#include "DlgHistogram.h"
#include "DibEnhancement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram dialog


CDlgHistogram::CDlgHistogram(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHistogram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHistogram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(m_nHistogram, 0x00, sizeof(int)*256);
	memset(m_nHistogramRGB, 0x00, sizeof(int)*256*3);
	m_nBitCount = 0;
}


void CDlgHistogram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHistogram)
	DDX_Control(pDX, IDC_CHECK_B, m_chkDrawB);
	DDX_Control(pDX, IDC_CHECK_G, m_chkDrawG);
	DDX_Control(pDX, IDC_CHECK_R, m_chkDrawR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHistogram, CDialog)
	//{{AFX_MSG_MAP(CDlgHistogram)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_B, OnCheck)
	ON_BN_CLICKED(IDC_CHECK_G, OnCheck)
	ON_BN_CLICKED(IDC_CHECK_R, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram message handlers

BOOL CDlgHistogram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	char szTemp[64]={0};
	sprintf(szTemp, "BitCount = %d", m_nBitCount);
	SetDlgItemText(IDC_STATIC_BC, szTemp);
	
	if( m_nBitCount == 8 )
	{
		m_chkDrawR.ShowWindow(SW_HIDE);
		m_chkDrawG.ShowWindow(SW_HIDE);
		m_chkDrawB.ShowWindow(SW_HIDE);
	}else if( m_nBitCount == 24 )
	{
		m_chkDrawR.SetCheck(1);
		m_chkDrawG.SetCheck(1);
		m_chkDrawB.SetCheck(1);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHistogram::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_fnDrawSpectrum();
	if( m_nBitCount == 8 ){
		m_fnDrawHistogram();
	}else if ( m_nBitCount == 24 ){
		m_fnDrawHistogramRGB();
	}
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgHistogram::m_fnDrawSpectrum()
{
	BYTE byGrayValue=0;
	double dGrayValue=0.0;
	int nWidth = 0;
	register int i=0;
	int x,y;
	CRect rSpectrum;
	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_GRAY_SPECTRUM);
	if( pWnd ){
		CClientDC dc(pWnd);
		pWnd->GetClientRect(&rSpectrum);
		CPen *pPen=NULL, *pPen_Old=NULL;
		nWidth = rSpectrum.Width();
		for( i=0; i<nWidth; i++){			
			byGrayValue = (BYTE)((double)(((double)i/(double)nWidth)*255.0));
			x = rSpectrum.left+i;
			y = rSpectrum.top;

			pPen = new CPen;
			pPen->CreatePen(PS_SOLID, 1, RGB(byGrayValue, byGrayValue, byGrayValue));

			pPen_Old = dc.SelectObject(pPen);

			dc.MoveTo(x,y);
			dc.LineTo(x,y+rSpectrum.Height());

			dc.SelectObject(pPen_Old);
			pPen->DeleteObject();

			delete pPen;
			pPen = NULL;
		}
	}	
}

void CDlgHistogram::m_fnDrawHistogram()
{
	CRect rHisto;
	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_HISTO);
	if( pWnd )
	{
		pWnd->GetClientRect(&rHisto);
		CClientDC dc(pWnd);
		int nMargin = 5;
		int w = rHisto.Width() - (nMargin*2);
		int h = rHisto.Height();
		int x,y;
		register int i=0;
		CPen *pPen=NULL, *pPen_old=NULL;
		pPen = new CPen;
		pPen->CreatePen(PS_SOLID, 1, RGB(50,50,50));
		pPen_old = dc.SelectObject(pPen);
		for( i=0; i<256; i++)
		{
			x = nMargin + (w*i/255);
			y = h*m_nHistogram[i]/100;
			dc.MoveTo(x, rHisto.bottom);
			dc.LineTo(x, rHisto.bottom-y);
		}
		dc.SelectObject(pPen_old);
		pPen->DeleteObject();
		delete pPen;
		pPen = NULL;
	}
}

void CDlgHistogram::m_fnDrawHistogramRGB()
{
	CRect rHisto;
	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_HISTO);
	if( pWnd )
	{
		pWnd->GetClientRect(&rHisto);
		CClientDC dc(pWnd);
		int nMargin = 5;
		int w = rHisto.Width() - (nMargin*2);
		int h = rHisto.Height();
		int x,y;
		register int i=0,j=0;
		CPen *pPen=NULL, *pPen_old=NULL;
		COLORREF col[3]={RGB(255,0,0),RGB(0,255,0),RGB(0,0,255)};
		int nDrawChk[3]={0};
		nDrawChk[0] = m_chkDrawR.GetCheck();
		nDrawChk[1] = m_chkDrawG.GetCheck();
		nDrawChk[2] = m_chkDrawB.GetCheck();
		for( j=0; j<3; j++)
		{
			if( nDrawChk[j] == 0 ) continue;
			pPen = new CPen;
			pPen->CreatePen(PS_SOLID, 1, col[j]);
			pPen_old = dc.SelectObject(pPen);
			for( i=0; i<256; i++)
			{
				x = nMargin + (w*i/255);
				y = h*m_nHistogramRGB[j][i]/100;
				dc.MoveTo(x, rHisto.bottom);
				dc.LineTo(x, rHisto.bottom-y);
			}
			dc.SelectObject(pPen_old);
			pPen->DeleteObject();
			delete pPen;
			pPen = NULL;
		}
	}
}

BOOL CDlgHistogram::m_fnSetImage(CDib& dib)
{
	float fHisto[256];
	memset(fHisto, 0x00, sizeof(float)*256);

	float fHistoRGB[3][256];
	memset(fHistoRGB, 0x00, sizeof(float)*256*3);

	m_nBitCount = dib.m_fnGetBitCount();
	
	int nRet = 0;
	switch( m_nBitCount )
	{
	case 8:
		nRet = MV_Histogram(dib, fHisto);
		break;
	case 24:
		nRet = MV_HistogramRGB(dib, fHistoRGB[0],fHistoRGB[1],fHistoRGB[2]);
		break;
	default:
		return FALSE;
	}

	if( nRet != 0 ) return FALSE;
		
	register int i=0;

	if( m_nBitCount == 8 )
	{
		float fMax = 0.0;
		for(i=0; i<256; i++){
			if( fHisto[i] > fMax ) fMax = fHisto[i];
		}

		for(i=0; i<256; i++){
			m_nHistogram[i] = (int)(fHisto[i]/fMax*100.0);
		}
	}
	else
	{
		float fMax[3] = {0.0};
		for(i=0; i<256; i++){
			if( fHistoRGB[0][i] > fMax[0] ) fMax[0] = fHistoRGB[0][i];
			if( fHistoRGB[1][i] > fMax[1] ) fMax[1] = fHistoRGB[1][i];
			if( fHistoRGB[2][i] > fMax[2] ) fMax[2] = fHistoRGB[2][i];
		}

		for(i=0; i<256; i++){
			m_nHistogramRGB[0][i] = (int)(fHistoRGB[0][i]/fMax[0]*100.0);
			m_nHistogramRGB[1][i] = (int)(fHistoRGB[1][i]/fMax[1]*100.0);
			m_nHistogramRGB[2][i] = (int)(fHistoRGB[2][i]/fMax[2]*100.0);
		}
	}

	return TRUE;
}

void CDlgHistogram::OnCheck() 
{
	// TODO: Add your control notification handler code here
	Invalidate(TRUE);
}
