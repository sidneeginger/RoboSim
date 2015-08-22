//===================================================================================
//	physics.h : RoboPhysics
#pragma once
#include "afx.h"
#include "stdafx.h"

//=================================================================================
//			AFX_EXT_API
//==================================================================================
BOOL	AFX_EXT_API _IsPointFrontFace( CPoint3D point, CFace face );
BOOL	AFX_EXT_API _IsBoxAcross(CBox3D boxa, CBox3D boxb);




//==================================================================================
//	the class using in physics system
//==================================================================================

class AFX_EXT_CLASS CSimTimer
	: public CObject
{
protected:
	long m_lStartMilliseconds;
	long m_lCurrentMilliseconds;
	BOOL m_bIsRun;
public:
	CSimTimer(void);
	virtual ~CSimTimer(void);

public:
	void Start(void);
	float GetTime(void);
	void Stop(void);
	
	float GetDeltaTime(void);
protected:
	float m_fLastTime;
	float m_fDeltaTime;
	float m_fMaxDeltaTime;
public:
	void SetMaxDeltaTime(float fDeltaTime);
};

enum CollisionTypes
{
	NO_COLLIDING,			//  û����ײ
	PENETRATING,			//  ����
	COLLIDING_WITH_WALL,	//  ����߽�֮�����ײ
	COLLIDING_WITH_CUBE		//  ������֮�����ײ
};


class AFX_EXT_CLASS CSimCollisions :
	public CObject
{
public:
	CSimCollisions(void);
	virtual ~CSimCollisions(void);
	BOOL IsBoxAcross(CBox3D boxa, CBox3D boxb);
	BOOL IsPointFrontFace(CPoint3D point, CFace face);
	int CheckForCollisions(CSimCube* pObject);
	void LoadMap(CInDoorMap* pInDoorMap);
protected:
	CInDoorMap* m_pInDoorMap;
};
