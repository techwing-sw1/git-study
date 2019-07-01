// DlgConvert1D.cpp : implementation file
//

#include "stdafx.h"
#include "MVStudio.h"
#include "DlgConvert1D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConvert1D dialog


CDlgConvert1D::CDlgConvert1D(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConvert1D::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConvert1D)
	m_nSelectedColor = 0;
	//}}AFX_DATA_INIT
}


void CDlgConvert1D::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConvert1D)
	DDX_Radio(pDX, IDC_RADIO_R, m_nSelectedColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConvert1D, CDialog)
	//{{AFX_MSG_MAP(CDlgConvert1D)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConvert1D message handlers

BOOL CDlgConvert1D::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
