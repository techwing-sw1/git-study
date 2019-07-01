// MVStudioView.h : interface of the CMVStudioView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MVSTUDIOVIEW_H__24BA879E_1167_4AC2_A3BF_76FAF2820274__INCLUDED_)
#define AFX_MVSTUDIOVIEW_H__24BA879E_1167_4AC2_A3BF_76FAF2820274__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//=============================================================================
// INCLUSE
//=============================================================================
#include "DlgHistogram.h"

//=============================================================================
// CONST
//=============================================================================
enum _eMouse_Mode {
	_eMoNothing=0, _eMoHand
};



//=============================================================================
// CLASS
//=============================================================================
class CMVStudioView : public CScrollView
{
protected: // create from serialization only
	CMVStudioView();
	DECLARE_DYNCREATE(CMVStudioView)

// Attributes
public:
	CMVStudioDoc* GetDocument();
	void m_fnSetScrollSizeToFit();


protected:
	CDlgHistogram* m_pDlgHisto;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVStudioView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVStudioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	double m_dZoom;
	int m_nMouseMode;


protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVStudioView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewZoom1();
	afx_msg void OnViewZoom2();
	afx_msg void OnViewZoom3();
	afx_msg void OnViewZoom4();
	afx_msg void OnUpdateViewZoom1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoom2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoom3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoom4(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnImgInverse();
	afx_msg void OnUpdateImgInverse(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomIn();
	afx_msg void OnUpdateViewZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnViewZoomOut();
	afx_msg void OnUpdateViewZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnViewHand();
	afx_msg void OnUpdateViewHand(CCmdUI* pCmdUI);
	afx_msg void OnImgBright();
	afx_msg void OnImgContrast();
	afx_msg void OnImgGamma();
	afx_msg void OnImgHistogram();
	afx_msg void OnImgHistoequal();
	afx_msg void OnImgArithmetic();
	afx_msg void OnImgBitplane();
	afx_msg void OnToolCvt1d();
	afx_msg void OnFilterMean();
	afx_msg void OnFilterWmean();
	afx_msg void OnFilterGausian();
	afx_msg void OnFilterUnsharpMask();
	afx_msg void OnFilterLaflacian();
	afx_msg void OnFilterAddNoise();
	afx_msg void OnFilterMidien();
	afx_msg void OnFilterAnisotropicDiffusion();
	afx_msg void OnImgBitClean();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MVStudioView.cpp
inline CMVStudioDoc* CMVStudioView::GetDocument()
   { return (CMVStudioDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVSTUDIOVIEW_H__24BA879E_1167_4AC2_A3BF_76FAF2820274__INCLUDED_)
