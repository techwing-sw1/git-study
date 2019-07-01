#if !defined(AFX_DLGNEWIMAGE_H__605611FB_C0B7_43BA_94D5_4EAE39D9D831__INCLUDED_)
#define AFX_DLGNEWIMAGE_H__605611FB_C0B7_43BA_94D5_4EAE39D9D831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewImage.h : header file
//


#include "RGBBYTE.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgNewImage dialog

class CDlgNewImage : public CDialog
{
// Construction
public:
	CDlgNewImage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewImage)
	enum { IDD = IDD_DLG_NEW_IMG };
	long	m_nSizeX;
	long	m_nSizeY;
	BYTE	m_nGrayValue;
	//}}AFX_DATA

	enum {_eImgType_Gray=0, _eImgType_RGB=1};

	int m_nImageType; //0:Gray, 1:RGB
	RGBBYTE m_Color;

private:
	void m_fnUpdateColor(COLORREF col);
	void m_fnDrawColor();

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewImage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioImgtypeGray();
	afx_msg void OnRadioImgtypeRgb();
	afx_msg void OnStaticColor();
	afx_msg void OnPaint();
	afx_msg void OnColorSelect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnChangeEditGrayValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWIMAGE_H__605611FB_C0B7_43BA_94D5_4EAE39D9D831__INCLUDED_)
