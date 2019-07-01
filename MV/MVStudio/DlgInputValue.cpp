// DlgInputValue.cpp : implementation file
//

#include "stdafx.h"
#include "MVStudio.h"
#include "DlgInputValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInputValue dialog


CDlgInputValue::CDlgInputValue(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInputValue::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInputValue)
	m_nValueHiden = 0;
	//}}AFX_DATA_INIT
	memset(m_szValue, 0x00, sizeof(m_szValue));
	m_dMin = 0.0;
	m_dMax = 0.0;
}

CDlgInputValue::CDlgInputValue(double dMin, double dMax, CWnd* pParent/* = NULL*/)
: CDialog(CDlgInputValue::IDD, pParent), m_dMin(dMin), m_dMax(dMax)
{
	m_nValueHiden = 0;
	memset(m_szValue, 0x00, sizeof(m_szValue));
}


void CDlgInputValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInputValue)
	DDX_Control(pDX, IDC_SLIDER_VALUE, m_Slider);
	DDX_Control(pDX, IDC_EDIT_VALUE, m_eValue);
	DDX_Text(pDX, IDC_EDIT_VALUE_HIDEN, m_nValueHiden);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInputValue, CDialog)
	//{{AFX_MSG_MAP(CDlgInputValue)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VALUE, OnCustomdrawSliderValue)
	ON_EN_CHANGE(IDC_EDIT_VALUE_HIDEN, OnChangeEditValueHiden)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VALUE, OnReleasedcaptureSliderValue)
	ON_EN_UPDATE(IDC_EDIT_VALUE, OnUpdateEditValue)
	ON_EN_UPDATE(IDC_EDIT_VALUE_HIDEN, OnUpdateEditValueHiden)
	ON_EN_SETFOCUS(IDC_EDIT_VALUE, OnSetfocusEditValue)
	ON_EN_SETFOCUS(IDC_EDIT_VALUE_HIDEN, OnSetfocusEditValueHiden)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInputValue message handlers

BOOL CDlgInputValue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Slider.SetRange((int)(m_dMin*1000), (int)(m_dMax*1000), TRUE);
	m_Slider.SetPos(0);

	m_eValue.SetWindowText("0");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BYTE CDlgInputValue::m_fnGetValByte()
{
	BYTE byRet=0;
	byRet = (BYTE)limit(atoi(m_szValue));
	return byRet;
}

int CDlgInputValue::m_fnGetValInt()
{
	int nRet=0;
	nRet = (int)atoi(m_szValue);
	return nRet;
}

double CDlgInputValue::m_fnGetValDouble()
{
	double dRet=0;
	dRet = (double)atof(m_szValue);
	return dRet;
}

void CDlgInputValue::OnCustomdrawSliderValue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if( atoi(m_szValue) != m_Slider.GetPos() ) 
	{
		char szValue[256] = {0};
		sprintf(szValue, "%d", m_Slider.GetPos()); 
		m_nValueHiden = m_Slider.GetPos();
		UpdateData(FALSE);
		sprintf(szValue, "%.3f", (float)m_nValueHiden/1000.f);	
		SetDlgItemText(IDC_EDIT_VALUE, szValue);
	}
	
	*pResult = 0;
}

void CDlgInputValue::OnChangeEditValueHiden() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here	
}

void CDlgInputValue::OnReleasedcaptureSliderValue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDlgInputValue::OnUpdateEditValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgInputValue::OnUpdateEditValueHiden() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CDlgInputValue::OnSetfocusEditValue() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgInputValue::OnSetfocusEditValueHiden() 
{
	// TODO: Add your control notification handler code here

}

BOOL CDlgInputValue::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_LBUTTONDOWN ) 
	{
		if(	pMsg->hwnd == GetDlgItem(IDC_BTN_UP)->m_hWnd )
		{
			m_nValueHiden += 10;
			char szValue[256]={0};
			sprintf(szValue, "%.3f", (float)m_nValueHiden/1000.f);	
			SetDlgItemText(IDC_EDIT_VALUE, szValue);
			m_Slider.SetPos(m_Slider.GetPos()+10);
			UpdateData(FALSE);
			TRACE("UP BTN UP\n");
		}
		else if( pMsg->hwnd == GetDlgItem(IDC_BTN_DN)->m_hWnd )
		{
			m_nValueHiden -= 10;
			char szValue[256]={0};
			sprintf(szValue, "%.3f", (float)m_nValueHiden/1000.f);	
			SetDlgItemText(IDC_EDIT_VALUE, szValue);
			m_Slider.SetPos(m_Slider.GetPos()-10);
			UpdateData(FALSE);
			TRACE("DN BTN DN\n");
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgInputValue::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CDlgInputValue::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText(IDC_EDIT_VALUE, m_szValue, sizeof(m_szValue)-1);
	
	CDialog::OnOK();
}


void CDlgInputValue::m_fnSetRange(double dMin, double dMax)
{
	m_dMin = dMin;
	m_dMax = dMax;
}