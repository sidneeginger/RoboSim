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
	NO_COLLIDING,			//  没有碰撞
	PENETRATING,			//  穿过
	COLLIDING_WITH_WALL,	//  球与边界之间的碰撞
	COLLIDING_WITH_CUBE		//  球与球之间的碰撞
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
