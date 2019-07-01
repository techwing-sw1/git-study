// MVStudioDoc.h : interface of the CMVStudioDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MVSTUDIODOC_H__2EAD21D1_4AFA_4E11_AF81_B20DA80A519F__INCLUDED_)
#define AFX_MVSTUDIODOC_H__2EAD21D1_4AFA_4E11_AF81_B20DA80A519F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dib.h"

class CMVStudioDoc : public CDocument
{
protected: // create from serialization only
	CMVStudioDoc();
	DECLARE_DYNCREATE(CMVStudioDoc)


public:
	void m_fnHistogram();


// Attributes
public:
	CDib m_Dib;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVStudioDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMVStudioDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMVStudioDoc)
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVSTUDIODOC_H__2EAD21D1_4AFA_4E11_AF81_B20DA80A519F__INCLUDED_)
