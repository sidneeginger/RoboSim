// RoboSimerDoc.cpp :  CRoboSimerDoc 类的实现
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


// CRoboSimerDoc 构造/析构

CRoboSimerDoc::CRoboSimerDoc()
{
	// TODO: 在此添加一次性构造代码

}

CRoboSimerDoc::~CRoboSimerDoc()
{
}

BOOL CRoboSimerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CRoboSimerDoc 序列化

void CRoboSimerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CRoboSimerDoc 诊断

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


// CRoboSimerDoc 命令
