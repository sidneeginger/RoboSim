// RoboSimerDoc.cpp :  CRoboSimerDoc ���ʵ��
//

#include "stdafx.h"
#include "RoboSimer.h"

#include "RoboSimerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRoboSimerDoc

IMPLEMENT_DYNCREATE(CRoboSimerDoc, CDocument)

BEGIN_MESSAGE_MAP(CRoboSimerDoc, CDocument)
END_MESSAGE_MAP()


// CRoboSimerDoc ����/����

CRoboSimerDoc::CRoboSimerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CRoboSimerDoc::~CRoboSimerDoc()
{
}

BOOL CRoboSimerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CRoboSimerDoc ���л�

void CRoboSimerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CRoboSimerDoc ���

#ifdef _DEBUG
void CRoboSimerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRoboSimerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRoboSimerDoc ����
