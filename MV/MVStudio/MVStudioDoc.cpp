// MVStudioDoc.cpp : implementation of the CMVStudioDoc class
//

#include "stdafx.h"
#include "MVStudio.h"

#include "MVStudioDoc.h"
#include "DlgNewImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CMVStudioApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CMVStudioDoc

IMPLEMENT_DYNCREATE(CMVStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CMVStudioDoc, CDocument)
	//{{AFX_MSG_MAP(CMVStudioDoc)
	ON_COMMAND(ID_WINDOW_DUPLICATE, OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMVStudioDoc construction/destruction

CMVStudioDoc::CMVStudioDoc()
{
	// TODO: add one-time construction code here
}

CMVStudioDoc::~CMVStudioDoc()
{
}

BOOL CMVStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	BOOL bRet=FALSE;

	if( theApp.m_pNewImage == NULL )
	{
		CDlgNewImage dlg;

		if( dlg.DoModal() == IDOK )
		{
			if( dlg.m_nImageType == CDlgNewImage::_eImgType_Gray )
			{
				bRet = m_Dib.m_fnCreateGrayImage(dlg.m_nSizeX, dlg.m_nSizeY, dlg.m_nGrayValue);
			}
			else
			{
				COLORREF col = RGB(dlg.m_Color.r,dlg.m_Color.g, dlg.m_Color.b);
				bRet = m_Dib.m_fnCreateRGBImage(dlg.m_nSizeX, dlg.m_nSizeY, col);
			}
		}
	}
	else
	{
		bRet = m_Dib.m_fnCopy(theApp.m_pNewImage);
		theApp.m_pNewImage=NULL;
	}

	return bRet;
}



/////////////////////////////////////////////////////////////////////////////
// CMVStudioDoc serialization

void CMVStudioDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMVStudioDoc diagnostics

#ifdef _DEBUG
void CMVStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMVStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMVStudioDoc commands

BOOL CMVStudioDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	return m_Dib.m_fnLoad(lpszPathName);
}

BOOL CMVStudioDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class

	return m_Dib.m_fnSave(lpszPathName);
	
	//return CDocument::OnSaveDocument(lpszPathName);
}

void CMVStudioDoc::OnWindowDuplicate() 
{
	// TODO: Add your command handler code here
	g_fnNewImage(m_Dib);
}

void CMVStudioDoc::OnEditCopy() 
{
	// TODO: Add your command handler code here
	if( m_Dib.m_fnIsValid() )
	{
		m_Dib.m_fnCopyToClipboard();
	}	
}

void CMVStudioDoc::OnEditPaste() 
{
	// TODO: Add your command handler code here
	if( IsClipboardFormatAvailable(CF_DIB) ){
		CDib dib;
		dib.m_fnPasteFromClipboard();
		g_fnNewImage(dib);
	}
}

void CMVStudioDoc::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( IsClipboardFormatAvailable(CF_DIB) );		
}


