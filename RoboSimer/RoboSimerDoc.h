// RoboSimerDoc.h :  CRoboSimerDoc ��Ľӿ�
//


#pragma once

class CRoboSimerDoc : public CDocument
{
protected: // �������л�����
	CRoboSimerDoc();
	DECLARE_DYNCREATE(CRoboSimerDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CRoboSimerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


