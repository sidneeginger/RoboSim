#pragma once


// CPathSeting 对话框

class CPathSeting : public CDialog
{
	DECLARE_DYNAMIC(CPathSeting)

public:
	CPathSeting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPathSeting();

// 对话框数据
	enum { IDD = IDD_SET_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetPathColor();
	int m_nLength;
	float m_nTip;
	float m_nWidth;
	COLORREF m_PathColor;
};
