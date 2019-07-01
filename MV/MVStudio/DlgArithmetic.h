#if !defined(AFX_DLGARITHMETIC_H__E3EEFCEF_FEE7_4AC3_BEA9_B19AFFCA5859__INCLUDED_)
#define AFX_DLGARITHMETIC_H__E3EEFCEF_FEE7_4AC3_BEA9_B19AFFCA5859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgArithmetic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgArithmetic dialog

class CDlgArithmetic : public CDialog
{
// Construction
public:
	CDlgArithmetic(CWnd* pParent = NULL);   // standard constructor

	void m_fnLoadDocList();

	void* m_pDoc1;
	void* m_pDoc2;

// Dialog Data
	//{{AFX_DATA(CDlgArithmetic)
	enum { IDD = IDD_DLG_ARITHMETIC };
	CComboBox	m_cbImage2;
	CComboBox	m_cbImage1;
	int		m_nFunction;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgArithmetic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgArithmetic)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtnBrowse1();
	afx_msg void OnBtnBrowse2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGARITHMETIC_H__E3EEFCEF_FEE7_4AC3_BEA9_B19AFFCA5859__INCLUDED_)
