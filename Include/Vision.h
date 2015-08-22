//=====================================================================================
//	vision.h : RoboCamera
#pragma once


// CCameraDlg 对话框
#include "..\RoboCamera\Resource.h"
#include "..\RoboCamera\videoportal.h"
#include "afxwin.h"
#include "atltypes.h"






#define WM_DELETEDLG WM_USER+10	

class AFX_EXT_CLASS CCameraDlg : public CDialog
{
	DECLARE_DYNAMIC(CCameraDlg)

public:
	CCameraDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCameraDlg();

// 对话框数据
	enum { IDD = IDD_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	DECLARE_EVENTSINK_MAP()
	void PortalNotificationVideoportal(long lMsg, LPBITMAPINFOHEADER lParam1, 
		LPBYTE lParam2, long lParam3);

protected:
	afx_msg void OnInitVideo(void);
private:
	CVideoportal m_VideoPortal;
	CView *m_pView;
public:
	CCameraDlg(CView* pView);
	BOOL CreateDlg(void);
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	void ApplyFX(LPBITMAPINFOHEADER lpbi, LPBYTE lpBits);
	void AllocateDIB(CSize sz);
	CRect m_rcRect;
protected:
	BYTE* m_pbits;
	int					XYmap[320*240];
	BYTE                Rmap[256];
    BYTE                Gmap[256];
    BYTE                Bmap[256];
	LPBITMAPINFOHEADER m_pbi;
	
	
public:
	void ComputeFX(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	CPoint				point;
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
