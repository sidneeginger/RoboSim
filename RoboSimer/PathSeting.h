#pragma once


// CPathSeting �Ի���

class CPathSeting : public CDialog
{
	DECLARE_DYNAMIC(CPathSeting)

public:
	CPathSeting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPathSeting();

// �Ի�������
	enum { IDD = IDD_SET_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetPathColor();
	int m_nLength;
	float m_nTip;
	float m_nWidth;
	COLORREF m_PathColor;
};
