// PathSeting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RoboSimer.h"
#include "PathSeting.h"
#include ".\pathseting.h"


// CPathSeting �Ի���

IMPLEMENT_DYNAMIC(CPathSeting, CDialog)
CPathSeting::CPathSeting(CWnd* pParent /*=NULL*/)
	: CDialog(CPathSeting::IDD, pParent)
	, m_nLength(0)
	, m_nTip(0)
	, m_nWidth(0)
{
}

CPathSeting::~CPathSeting()
{
}

void CPathSeting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_nLength);
	DDX_Text(pDX, IDC_EDIT_TIP, m_nTip);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
}


BEGIN_MESSAGE_MAP(CPathSeting, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnSetPathColor)
END_MESSAGE_MAP()


// CPathSeting ��Ϣ�������

void CPathSeting::OnSetPathColor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_PathColor = dlg.GetColor();
	}
	
}
