#if !defined(AFX_DLGHISTOGRAM_H__4184E51B_B057_4715_B151_8E3FAF6E85D6__INCLUDED_)
#define AFX_DLGHISTOGRAM_H__4184E51B_B057_4715_B151_8E3FAF6E85D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHistogram.h : header file
//

#include "Dib.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgHistogram dialog

class CDlgHistogram : public CDialog
{
// Construction
public:
	CDlgHistogram(CWnd* pParent = NULL);   // standard constructor

	BOOL m_fnSetImage(CDib& dib);

protected:
	void m_fnDrawSpectrum();
	void m_fnDrawHistogram();
	void m_fnDrawHistogramRGB();

protected:
	int m_nHistogram[256];
	int m_nHistogramRGB[3][256];

	int m_nBitCount;


public:
// Dialog Data
	//{{AFX_DATA(CDlgHistogram)
	enum { IDD = IDD_DLG_HISTOGRAM };
	CButton	m_chkDrawB;
	CButton	m_chkDrawG;
	CButton	m_chkDrawR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHistogram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHistogram)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHISTOGRAM_H__4184E51B_B057_4715_B151_8E3FAF6E85D6__INCLUDED_)
