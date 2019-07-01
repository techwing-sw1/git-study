// DlgArithmetic.cpp : implementation file
//

#include "stdafx.h"
#include "MVStudio.h"
#include "DlgArithmetic.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MVStudioDoc.h"
#include "MVStudioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgArithmetic dialog


CDlgArithmetic::CDlgArithmetic(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgArithmetic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgArithmetic)
	m_nFunction = 0;
	//}}AFX_DATA_INIT
	m_pDoc1 = NULL;
	m_pDoc2 = NULL;
}


void CDlgArithmetic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgArithmetic)
	DDX_Control(pDX, IDC_COMBO_IMG2, m_cbImage2);
	DDX_Control(pDX, IDC_COMBO_IMG1, m_cbImage1);
	DDX_Radio(pDX, IDC_RADIO_ADD, m_nFunction);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgArithmetic, CDialog)
	//{{AFX_MSG_MAP(CDlgArithmetic)
	ON_BN_CLICKED(IDC_BTN_BROWSE1, OnBtnBrowse1)
	ON_BN_CLICKED(IDC_BTN_BROWSE2, OnBtnBrowse2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgArithmetic message handlers

BOOL CDlgArithmetic::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_fnLoadDocList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgArithmetic::m_fnLoadDocList()
{
	CMVStudioApp* pApp = (CMVStudioApp*)AfxGetApp();
	CMVStudioDoc* pDoc = NULL;
	POSITION pos = pApp->m_pImageDocTemplate->GetFirstDocPosition();

	CString strSelectedItem_Bak1="";
	CString strSelectedItem_Bak2="";

	int nCurSel1 = m_cbImage1.GetCurSel();
	int nCurSel2 = m_cbImage2.GetCurSel();

	if( nCurSel1 != CB_ERR ){
		m_cbImage1.GetLBText( nCurSel1, strSelectedItem_Bak1 );
	}
	if( nCurSel2 != CB_ERR ){
		m_cbImage2.GetLBText( nCurSel2, strSelectedItem_Bak2 );
	}

	register int i=0;
	for( i=0; i<m_cbImage1.GetCount(); i++)
	{
		m_cbImage1.DeleteString(i);
		m_cbImage2.DeleteString(i);
		
	}
	m_cbImage1.Clear();
	m_cbImage2.Clear();
	
	char szDoc[256];
	int nIndex = 0;
	while( pos != NULL )
	{
		pDoc = (CMVStudioDoc*)pApp->m_pImageDocTemplate->GetNextDoc(pos);
		memset(szDoc, 0x00, sizeof(szDoc));
		sprintf(szDoc, "%s", pDoc->GetTitle() );
		m_cbImage1.InsertString(nIndex, szDoc);
		m_cbImage2.InsertString(nIndex, szDoc);
		
		m_cbImage1.SetItemDataPtr(nIndex, pDoc);
		m_cbImage2.SetItemDataPtr(nIndex, pDoc);
		nIndex++;
	}

	m_cbImage1.SetCurSel( m_cbImage1.FindString( 0, (LPCTSTR)strSelectedItem_Bak1 ) );
	m_cbImage2.SetCurSel( m_cbImage2.FindString( 0, (LPCTSTR)strSelectedItem_Bak2 ) );
}


void CDlgArithmetic::OnOK() 
{
	// TODO: Add extra validation here
	m_pDoc1 = (CMVStudioDoc*)m_cbImage1.GetItemDataPtr(m_cbImage1.GetCurSel());
	m_pDoc2 = (CMVStudioDoc*)m_cbImage2.GetItemDataPtr(m_cbImage2.GetCurSel());

	if( m_cbImage1.GetCurSel() < 0 || m_cbImage2.GetCurSel() < 0 )
	{
		AfxMessageBox("Image를 선택해 주세요.");
		return;
	}

	CMVStudioDoc* pDoc1 = (CMVStudioDoc*)m_pDoc1;
	CMVStudioDoc* pDoc2 = (CMVStudioDoc*)m_pDoc2;

	int nChk = 0;
	if( pDoc1->m_Dib.m_fnGetWidth() != pDoc2->m_Dib.m_fnGetWidth() ) nChk++;
	if( pDoc1->m_Dib.m_fnGetHeight()!= pDoc2->m_Dib.m_fnGetHeight()) nChk++;
	if( nChk > 0 )
	{
		AfxMessageBox("Image Size가 같지 않습니다.");
		return;
	}

	CDialog::OnOK();
}

void CDlgArithmetic::OnBtnBrowse1() 
{
	// TODO: Add your control notification handler code here
	CMVStudioApp* pApp = (CMVStudioApp*)AfxGetApp();

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, "BMP Files (*.BMP)|*.BMP||", this);
	if( dlg.DoModal() == IDOK )
	{
		CString strFileName = dlg.GetFileName();
		pApp->m_pImageDocTemplate->OpenDocumentFile( (LPCTSTR)strFileName );
		m_fnLoadDocList();
		m_cbImage1.SetCurSel( m_cbImage1.FindString( 0, (LPCTSTR)strFileName) );
	}	
}

void CDlgArithmetic::OnBtnBrowse2() 
{
	// TODO: Add your control notification handler code here
	CMVStudioApp* pApp = (CMVStudioApp*)AfxGetApp();

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, "BMP Files (*.BMP)|*.BMP||", this);
	if( dlg.DoModal() == IDOK )
	{
		CString strFileName = dlg.GetFileName();
		pApp->m_pImageDocTemplate->OpenDocumentFile( (LPCTSTR)strFileName );
		m_fnLoadDocList();
		m_cbImage2.SetCurSel( m_cbImage1.FindString( 0, (LPCTSTR)strFileName) );
	}
}
