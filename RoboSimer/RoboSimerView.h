// RoboSimerView.h : CRoboSimerView 类的接口
//
#pragma once

#include ".\RoboSimerDoc.h"
#include "..\include\mathdefs.h"

#include "atltypes.h"


#include "..\include\modelbase.h"
#include "..\include\vision.h"
#include "..\include\physics.h"
#include "..\include\decision.h"

class CRoboSimerView : public CView
{
protected: // 仅从序列化创建
	CRoboSimerView();
	DECLARE_DYNCREATE(CRoboSimerView)

// 属性
public:
	CRoboSimerDoc* GetDocument() const;
	CClientDC		*m_pDC;
	CRect			m_oldRect;
	CSimRobot		m_SimRobot;
	CSimCube		m_TargetCube;
	CInDoorMap		m_InDoorMap;
	CMathDefs		m_MathDefs;
	CSimTimer		m_SimTimer;
	CSimPathMark	m_PathMark;
	CPoint			LDownPoint;
	CPoint			RDownPoint;

	float			m_fEyeAngleX;
	float			m_fEyeAngleZ;
	float			m_fTranslateX;
	float			m_fTranslateY;
	float			m_fTranslateZ;
	float			m_fLastTime;
	
	BOOL			m_bIsLDown;
	BOOL			m_bIsRDown;
	BOOL			m_bIsTracing;
	bool			m_bIsPathMark;
	
	CSimCollisions	m_Collision;
	CCameraDlg		*m_CameraDlg;
protected:
	BOOL m_bIsRun;

	CSimPathFinder m_PathFinder;

// 操作
public:
	void InputKey(void);
	void DrawText(void);
	BOOL bSetupPixelFormat(void);
	void DrawScene(void);
	void DrawWorld(void);
	void DrawMap(void);
	void Lighting(void);
	int CheckForCollisions(void);
	void CheckTest(CSimCube *Cube);

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CRoboSimerView();
	void Init(void);
	void GLInit(void);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToolTract();
	afx_msg void OnUpdateToolTract(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPathmark();
	afx_msg void OnUpdatePathmark(CCmdUI *pCmdUI);
	afx_msg void OnVision();
	afx_msg LRESULT OnDeleteDlg(WPARAM wparam, LPARAM lparam);
	afx_msg void OnSetPathMark();
	afx_msg void OnFilePlay();
	afx_msg void OnUpdateFilePlay(CCmdUI *pCmdUI);

};

#ifndef _DEBUG  // RoboSimerView.cpp 的调试版本
inline CRoboSimerDoc* CRoboSimerView::GetDocument() const
   { return reinterpret_cast<CRoboSimerDoc*>(m_pDocument); }
#endif

