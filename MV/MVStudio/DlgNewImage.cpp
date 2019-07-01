// DlgNewImage.cpp : implementation file
//

#include "stdafx.h"
#include "MVStudio.h"
#include "DlgNewImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewImage dialog


CDlgNewImage::CDlgNewImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewImage)
	m_nSizeX = 100;
	m_nSizeY = 100;
	m_nGrayValue = 0;
	//}}AFX_DATA_INIT
	m_nImageType = _eImgType_Gray;
}


void CDlgNewImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewImage)
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nSizeX);
	DDV_MinMaxLong(pDX, m_nSizeX, 0, 2048);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nSizeY);
	DDV_MinMaxLong(pDX, m_nSizeY, 0, 2048);
	DDX_Text(pDX, IDC_EDIT_GRAY_VALUE, m_nGrayValue);
	DDV_MinMaxByte(pDX, m_nGrayValue, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewImage, CDialog)
	//{{AFX_MSG_MAP(CDlgNewImage)
	ON_BN_CLICKED(IDC_RADIO_IMGTYPE_GRAY, OnRadioImgtypeGray)
	ON_BN_CLICKED(IDC_RADIO_IMGTYPE_RGB, OnRadioImgtypeRgb)
	ON_BN_CLICKED(IDC_STATIC_COLOR, OnStaticColor)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_COLOR_SELECT, OnColorSelect)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT_GRAY_VALUE, OnChangeEditGrayValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewImage message handlers

BOOL CDlgNewImage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_RADIO_IMGTYPE_GRAY);
	pBtn1->SetCheck(1);
	CButton* pBtn2 = (CButton*)GetDlgItem(IDC_RADIO_IMGTYPE_RGB);
	pBtn2->SetCheck(0);
	UpdateData(TRUE);

	m_Color = RGB(100,100,100);
	m_nGrayValue = 0;

	SetDlgItemText(IDC_EDIT_GRAY_VALUE, "0");

	SetTimer(1, 100, NULL);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNewImage::OnRadioImgtypeGray() 
{
	// TODO: Add your control notification handler code here
//	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_RADIO_IMGTYPE_GRAY);
//	pBtn1->SetCheck(1);
//	CButton* pBtn2 = (CButton*)GetDlgItem(IDC_RADIO_IMGTYPE_RGB);
//	pBtn1->SetCheck(0);
	m_nImageType = _eImgType_Gray;	
}

void CDlgNewImage::OnRadioImgtypeRgb() 
{
	// TODO: Add your control notification handler code here
//	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_RADIO_IMGTYPE_GRAY);
//	pBtn1->SetCheck(0);
//	CButton* pBtn2 = (CButton*)GetDlgItem(IDC_RADIO_IMGTYPE_RGB);
//	pBtn1->SetCheck(1);
	m_nImageType = _eImgType_RGB;
}

void CDlgNewImage::OnStaticColor() 
{
	// TODO: Add your control notification handler code here
}

void CDlgNewImage::m_fnDrawColor()
{
	CWnd* pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_COLOR);
	if( pWnd == NULL ) return;

	CClientDC dc(pWnd);

	CBrush* pOldBr, *pBr;
	CRect rect;

	pBr = new CBrush;
	COLORREF col = RGB(m_Color.r, m_Color.g, m_Color.b);
	pBr->CreateSolidBrush(col);

	pOldBr = dc.SelectObject(pBr);

	pWnd->GetClientRect(&rect);

	dc.FillRect(rect, pBr);

	dc.SelectObject(pOldBr);

	delete pBr;
}

void CDlgNewImage::m_fnUpdateColor(COLORREF col)
{
	m_Color = col;

	Invalidate(TRUE);
}

void CDlgNewImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_fnDrawColor();
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDlgNewImage::OnColorSelect() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_Color = dlg.GetColor();
		
		char szWork[256];
		memset(szWork, 0x00, sizeof(szWork));
		
		sprintf(szWork, "%d, %d, %d", m_Color.r, m_Color.g, m_Color.b);
		SetDlgItemText(IDC_EDIT_COLOR, szWork);
		Invalidate(TRUE);
	}	
}

void CDlgNewImage::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_fnDrawColor();

	CDialog::OnTimer(nIDEvent);
}

void CDlgNewImage::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	
	CDialog::OnClose();
}

void CDlgNewImage::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}


void CDlgNewImage::OnChangeEditGrayValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int nInput = 0;
	CString strTemp;

	GetDlgItemText(IDC_EDIT_GRAY_VALUE, strTemp);

	nInput = atoi((LPCTSTR)strTemp);

	if( nInput < 0 || nInput > 255 )
	{
		AfxMessageBox("0~255");
		strTemp = "0";
		SetDlgItemText(IDC_EDIT_GRAY_VALUE, strTemp);
	}	
}
