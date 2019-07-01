#if !defined(AFX_DLGINPUTVALUE_H__5F306B1A_C24A_4254_B41C_58F65806C6B0__INCLUDED_)
#define AFX_DLGINPUTVALUE_H__5F306B1A_C24A_4254_B41C_58F65806C6B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInputValue.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInputValue dialog

class CDlgInputValue : public CDialog
{
// Construction
public:
	CDlgInputValue(CWnd* pParent = NULL);   // standard constructor
	CDlgInputValue(double dMin, double dMax, CWnd* pParent = NULL);

	BYTE m_fnGetValByte();
	int m_fnGetValInt();
	double m_fnGetValDouble();

	void m_fnSetRange(double dMin, double dMax);

private:
	char m_szValue[128];
	double m_dMin;
	double m_dMax;

public:

// Dialog Data
	//{{AFX_DATA(CDlgInputValue)
	enum { IDD = IDD_DLG_INPUT_VALUE };
	CSliderCtrl	m_Slider;
	CEdit	m_eValue;
	int		m_nValueHiden;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInputValue)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInputValue)
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSliderValue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditValueHiden();
	afx_msg void OnDeltaposSpinVal(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderValue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateEditValue();
	afx_msg void OnUpdateEditValueHiden();
	afx_msg void OnSetfocusEditValue();
	afx_msg void OnSetfocusEditValueHiden();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUTVALUE_H__5F306B1A_C24A_4254_B41C_58F65806C6B0__INCLUDED_)
