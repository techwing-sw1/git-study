#if !defined(AFX_DLGCONVERT1D_H__D26A7AD2_B193_406D_B8BA_5525F715FB31__INCLUDED_)
#define AFX_DLGCONVERT1D_H__D26A7AD2_B193_406D_B8BA_5525F715FB31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConvert1D.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgConvert1D dialog

class CDlgConvert1D : public CDialog
{
// Construction
public:
	CDlgConvert1D(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgConvert1D)
	enum { IDD = IDD_CONVERT_1D };
	int		m_nSelectedColor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConvert1D)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConvert1D)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONVERT1D_H__D26A7AD2_B193_406D_B8BA_5525F715FB31__INCLUDED_)
