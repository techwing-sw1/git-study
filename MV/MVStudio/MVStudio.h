// MVStudio.h : main header file for the MVSTUDIO application
//

#if !defined(AFX_MVSTUDIO_H__865265AB_6239_4707_98C7_EA5BE51AE3C4__INCLUDED_)
#define AFX_MVSTUDIO_H__865265AB_6239_4707_98C7_EA5BE51AE3C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Dib.h"

/////////////////////////////////////////////////////////////////////////////
// CMVStudioApp:
// See MVStudio.cpp for the implementation of this class
//



class CMVStudioApp : public CWinApp
{
public:
	CMVStudioApp();
	~CMVStudioApp();

	CDib* m_pNewImage;
	CMultiDocTemplate* m_pImageDocTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMVStudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMVStudioApp)
	afx_msg void OnAppAbout();
	afx_msg void OnWindowCloseall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void g_fnNewImage(CDib& dib);


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVSTUDIO_H__865265AB_6239_4707_98C7_EA5BE51AE3C4__INCLUDED_)
