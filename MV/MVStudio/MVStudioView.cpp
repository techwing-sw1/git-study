// MVStudioView.cpp : implementation of the CMVStudioView class
//

#include "stdafx.h"
#include "MVStudio.h"

#include "MVStudioDoc.h"
#include "MVStudioView.h"
#include "MainFrm.h"

#include "DibEnhancement.h"
#include "DlgInputValue.h"
#include "DlgHistogram.h"
#include "DlgArithmetic.h"
#include "DlgConvert1D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMVStudioView

IMPLEMENT_DYNCREATE(CMVStudioView, CScrollView)

BEGIN_MESSAGE_MAP(CMVStudioView, CScrollView)
	//{{AFX_MSG_MAP(CMVStudioView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_ZOOM1, OnViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, OnViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, OnViewZoom3)
	ON_COMMAND(ID_VIEW_ZOOM4, OnViewZoom4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, OnUpdateViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, OnUpdateViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, OnUpdateViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, OnUpdateViewZoom4)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_IMG_INVERSE, OnImgInverse)
	ON_UPDATE_COMMAND_UI(ID_IMG_INVERSE, OnUpdateImgInverse)
	ON_COMMAND(ID_VIEW_ZOOM_IN, OnViewZoomIn)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_IN, OnUpdateViewZoomIn)
	ON_COMMAND(ID_VIEW_ZOOM_OUT, OnViewZoomOut)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_OUT, OnUpdateViewZoomOut)
	ON_COMMAND(ID_VIEW_HAND, OnViewHand)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HAND, OnUpdateViewHand)
	ON_COMMAND(ID_IMG_BRIGHT, OnImgBright)
	ON_COMMAND(ID_IMG_CONTRAST, OnImgContrast)
	ON_COMMAND(ID_IMG_GAMMA, OnImgGamma)
	ON_COMMAND(ID_IMG_HISTOGRAM, OnImgHistogram)
	ON_COMMAND(ID_IMG_HISTOEQUAL, OnImgHistoequal)
	ON_COMMAND(ID_IMG_ARITHMETIC, OnImgArithmetic)
	ON_COMMAND(ID_IMG_BITPLANE, OnImgBitplane)
	ON_COMMAND(ID_TOOL_CVT1D, OnToolCvt1d)
	ON_COMMAND(ID_FILTER_MEAN, OnFilterMean)
	ON_COMMAND(ID_FILTER_WMEAN, OnFilterWmean)
	ON_COMMAND(ID_FILTER_GAUSIAN, OnFilterGausian)
	ON_COMMAND(ID_FILTER_UNSHARP_MASK, OnFilterUnsharpMask)
	ON_COMMAND(ID_FILTER_LAFLACIAN, OnFilterLaflacian)
	ON_COMMAND(ID_FILTER_ADD_NOISE, OnFilterAddNoise)
	ON_COMMAND(ID_FILTER_MIDIEN, OnFilterMidien)
	ON_COMMAND(ID_FILTER_ANISOTROPIC_DIFFUSION, OnFilterAnisotropicDiffusion)
	ON_COMMAND(ID_IMG_BIT_CLEAN, OnImgBitClean)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVStudioView construction/destruction

CMVStudioView::CMVStudioView()
{
	// TODO: add construction code here
	m_dZoom=1;
	m_pDlgHisto = NULL;
}

CMVStudioView::~CMVStudioView()
{
	if( m_pDlgHisto ){
		delete m_pDlgHisto;
		m_pDlgHisto = NULL;
	}
}

BOOL CMVStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMVStudioView drawing

void CMVStudioView::OnDraw(CDC* pDC)
{
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if( pDoc->m_Dib.m_fnIsValid() ){
		double w,h;
		w = pDoc->m_Dib.m_fnGetWidth()*m_dZoom;
		h = pDoc->m_Dib.m_fnGetHeight()*m_dZoom;
		pDoc->m_Dib.m_fnDraw(pDC->m_hDC,0, 0, (int)w, (int)h);
	}
}
void CMVStudioView::m_fnSetScrollSizeToFit()
{
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CSize sizeTotal;
	double w,h;
	w = pDoc->m_Dib.m_fnGetWidth();
	h = pDoc->m_Dib.m_fnGetHeight();
	if( pDoc->m_Dib.m_fnIsValid() ){
		sizeTotal.cx = (int)(w*m_dZoom);
		sizeTotal.cy = (int)(h*m_dZoom);
	}
	else{
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(TRUE);
}


void CMVStudioView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: calculate the total size of this view
	m_fnSetScrollSizeToFit();
}

/////////////////////////////////////////////////////////////////////////////
// CMVStudioView printing

BOOL CMVStudioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMVStudioView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMVStudioView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMVStudioView diagnostics

#ifdef _DEBUG
void CMVStudioView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMVStudioView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMVStudioDoc* CMVStudioView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMVStudioDoc)));
	return (CMVStudioDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVStudioView message handlers

BOOL CMVStudioView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush br;
	br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	FillOutsideRect(pDC, &br);	
	return TRUE;
	//return CScrollView::OnEraseBkgnd(pDC);
}

void CMVStudioView::OnViewZoom1() 
{
	// TODO: Add your command handler code here
	m_dZoom=1;
	m_fnSetScrollSizeToFit();
	Invalidate(TRUE);
}

void CMVStudioView::OnViewZoom2() 
{
	// TODO: Add your command handler code here
	m_dZoom=2;
	m_fnSetScrollSizeToFit();
	Invalidate(TRUE);
}

void CMVStudioView::OnViewZoom3() 
{
	// TODO: Add your command handler code here
	m_dZoom=3;
	m_fnSetScrollSizeToFit();
	Invalidate(TRUE);
}

void CMVStudioView::OnViewZoom4() 
{
	// TODO: Add your command handler code here
	m_dZoom=4;
	m_fnSetScrollSizeToFit();
	Invalidate(TRUE);
}

void CMVStudioView::OnUpdateViewZoom1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_dZoom==1);	
}

void CMVStudioView::OnUpdateViewZoom2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_dZoom==2);
}

void CMVStudioView::OnUpdateViewZoom3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_dZoom==3);
}

void CMVStudioView::OnUpdateViewZoom4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_dZoom==4);
}

void CMVStudioView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	HCURSOR hCursor=NULL;

	CPoint pt = point + GetScrollPosition();
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	LONG w,h,nBitCount;
	char szText[256];

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	w = pDoc->m_Dib.m_fnGetWidth();
	h = pDoc->m_Dib.m_fnGetHeight();
	nBitCount = pDoc->m_Dib.m_fnGetBitCount();
	// 1. Image info
	memset(szText, 0x00, sizeof(szText));
	sprintf(szText, "(W:%d x H:%d x BIT:%d)", w,h,nBitCount);
	pMainFrame->m_wndStatusBar.SetPaneText(0, szText, TRUE);

	int x,y;
	x = (int)((double)pt.x/m_dZoom);
	y = (int)((double)pt.y/m_dZoom);

	if( x>=0 && x<w && y>=0 && y<h)
	{
		memset(szText, 0x00, sizeof(szText));
		// 2. pixel info
		if( pDoc->m_Dib.m_fnGetPaletteNums()==0)
		{
			RGBBYTE pixel;
			RGBBYTE** pPixel = pDoc->m_Dib.m_fnGetRgbPtr();
			pixel = pPixel[y][x];
			sprintf(szText, "(R:%d, G:%d, B:%d)", pixel.r, pixel.g, pixel.b);	
		}
		else
		{
			BYTE pixel;
			BYTE** pPixel = pDoc->m_Dib.m_fnGetGrayPtr();
			pixel = pPixel[y][x];
			sprintf(szText, "(Gray Value:%d)", pixel);	
		}
		pMainFrame->m_wndStatusBar.SetPaneText(1, szText, TRUE);

		// 3. mouse pos
		memset(szText, 0x00, sizeof(szText));
		sprintf(szText, "(X:%d, Y:%d)", x, y);	
		pMainFrame->m_wndStatusBar.SetPaneText(2, szText, TRUE);
	}
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CMVStudioView::OnUpdateImgInverse(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CMVStudioView::OnViewZoomIn() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnUpdateViewZoomIn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMVStudioView::OnViewZoomOut() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnUpdateViewZoomOut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMVStudioView::OnViewHand() 
{
	// TODO: Add your command handler code here
	(m_nMouseMode != _eMoHand) ? m_nMouseMode = _eMoHand : m_nMouseMode = _eMoNothing;
	//SetClassLong(m_hWnd,GCL_HCURSOR,(long)AfxGetApp()->LoadCursor(IDC_HAND_OFF));	
}

void CMVStudioView::OnUpdateViewHand(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	( m_nMouseMode == _eMoHand ) ? pCmdUI->SetCheck(1) : pCmdUI->SetCheck(0);
}

void CMVStudioView::OnImgInverse() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	

 	CDib dib;
 	MV_Inverse(pDoc->m_Dib, dib);
 	g_fnNewImage(dib);
}

void CMVStudioView::OnImgBright() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	

	CDlgInputValue dlg(-255,255,this);

	if( dlg.DoModal() != IDOK ) return;

	CDib dib;
	BYTE byValue=0;
	byValue = dlg.m_fnGetValByte();
	MV_Brightness(pDoc->m_Dib, byValue, dib);
	g_fnNewImage(dib);
}

void CMVStudioView::OnImgContrast() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	
	CDlgInputValue dlg(-255,255,this);
	
	if( dlg.DoModal() != IDOK ) return;
	
	CDib dib;
	BYTE byValue=0;
	byValue = dlg.m_fnGetValByte();
	MV_Contrast(pDoc->m_Dib, byValue, dib);
	g_fnNewImage(dib);	
}

void CMVStudioView::OnImgGamma() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	
	
	CDlgInputValue dlg(0,10,this);
	
	if( dlg.DoModal() != IDOK ) return;
	
	CDib dib;
	double dValue = dlg.m_fnGetValDouble();
	MV_GammaCollection(pDoc->m_Dib, dValue, dib);
	g_fnNewImage(dib);	
}

void CMVStudioView::OnImgHistogram() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	

	if( m_pDlgHisto ){
		delete m_pDlgHisto;
		m_pDlgHisto = NULL;
	}
	m_pDlgHisto = new CDlgHistogram(this);
	if( m_pDlgHisto->m_fnSetImage(pDoc->m_Dib) )
	{
		m_pDlgHisto->Create(IDD_DLG_HISTOGRAM, this);
		m_pDlgHisto->ShowWindow(SW_SHOW);
	}
}

void CMVStudioView::OnImgHistoequal() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDib dib;
	MV_HistoEqulization(pDoc->m_Dib, dib);
	g_fnNewImage(dib);
}

void CMVStudioView::OnImgArithmetic() 
{
	// TODO: Add your command handler code here
	CDlgArithmetic dlg;
	CDib dib;
	char szErr[512]={0};

	if( dlg.DoModal() == IDOK )
	{
		CMVStudioDoc* pDoc1 = (CMVStudioDoc*)dlg.m_pDoc1;
		CMVStudioDoc* pDoc2 = (CMVStudioDoc*)dlg.m_pDoc2;
		int nFunction = dlg.m_nFunction;
		int nRet = 0;
		switch( nFunction )
		{
		case 0: 
			nRet = MV_Add( pDoc1->m_Dib, pDoc2->m_Dib, dib, szErr); 
			break;
		case 1: 
			nRet = MV_Sub (pDoc1->m_Dib, pDoc2->m_Dib, dib, szErr); 
			break;
		case 2: 
			nRet = MV_Avr (pDoc1->m_Dib, pDoc2->m_Dib, dib, szErr); 
			break;
		case 3: 
			nRet = MV_Diff(pDoc1->m_Dib, pDoc2->m_Dib, dib, szErr); 
			break;
		case 4: 
			nRet = MV_AND (pDoc1->m_Dib, pDoc2->m_Dib, dib, szErr); 
			break;
		case 5: 
			nRet = MV_OR  (pDoc1->m_Dib, pDoc2->m_Dib, dib, szErr); 
			break;
		default: 
			return;
		}

		if( nRet == 0 ){
			g_fnNewImage(dib);
		}else{
			AfxMessageBox(szErr);
		}
	}
}

void CMVStudioView::OnImgBitplane() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );

	register int i=0;
	CDib dib;
	char szErr[512]={0};
	int nRtn=0;
	for( i=0; i<8; i++)
	{
		nRtn = MV_BitPlane(pDoc->m_Dib, i, dib, szErr);
		if( nRtn == 0 ){
			g_fnNewImage(dib);
		}else{
			AfxMessageBox( szErr );
		}
	}
}

void CMVStudioView::OnToolCvt1d() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );

	CDib dib;
	CDlgConvert1D dlg;
	char szErr[512]={0};
	int nRtn=0;
	if( dlg.DoModal() == IDOK ){
		nRtn = MV_ConvertToGray(pDoc->m_Dib, dib, dlg.m_nSelectedColor, szErr);
		if( nRtn == 0 ){
			g_fnNewImage( dib );
		}else{
			AfxMessageBox( szErr );
		}		
	}
}

void CMVStudioView::OnFilterMean() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );

	CDib dib = pDoc->m_Dib;
	char szErr[512]={0};
	int nRtn=0;
	int nMaskOpt=0;

	nRtn = MV_FilterMean(dib, nMaskOpt, szErr);
	if( nRtn == 0 ){
		g_fnNewImage( dib );
	}else{
		AfxMessageBox( szErr );
	}
}

void CMVStudioView::OnFilterWmean() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );

	CDib dib = pDoc->m_Dib;
	char szErr[512]={0};
	int nRtn=0;
	int nMaskOpt=0;

	nRtn = MV_FilterWMean(dib, nMaskOpt, szErr);
	if( nRtn == 0 ){
		g_fnNewImage( dib );
	}else{
		AfxMessageBox( szErr );
	}
}

void CMVStudioView::OnFilterGausian() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnFilterUnsharpMask() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnFilterLaflacian() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnFilterAddNoise() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnFilterMidien() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnFilterAnisotropicDiffusion() 
{
	// TODO: Add your command handler code here
	
}

void CMVStudioView::OnImgBitClean() 
{
	// TODO: Add your command handler code here
	CMVStudioDoc* pDoc = GetDocument();
	ASSERT_VALID( pDoc );

	CDib dib;
	char szErr[512]={0};
	int nRtn=0;
	nRtn = MV_BitClean(pDoc->m_Dib, 3, dib, szErr);
	if( nRtn == 0 ){
		g_fnNewImage(dib);
	}else{
		AfxMessageBox( szErr );
	}	
}
