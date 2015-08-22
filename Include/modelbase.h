//===================================================================================
//	Modelbase.h : RoboModel
#pragma once
//#include "..\include\geometry.h"
#include "stdafx.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include "..\include\geometry.h"
#include "geometry.h"
//#include "geometry.h"
//#include "geometry.h"
class CTriangle : public CObject
{
public:
	CTriangle(void);
	virtual ~CTriangle(void);
protected:
	CPoint3D p[3];
public:
	CTriangle(CPoint3D p1, CPoint3D p2, CPoint3D p3);
	CTriangle(const CTriangle& triangleSrc);
	const CTriangle& operator=(const CTriangle& triangleSrc);
	virtual void Draw(void);
};

class CQuadrangle : public CObject
{
public:
	CQuadrangle(void);
	virtual ~CQuadrangle(void);
protected:
	CPoint3D p[4];
public:
	void CQuardrangle(CPoint3D p1, CPoint3D p2, CPoint3D p3, CPoint3D p4);
	CQuadrangle(const CQuadrangle& quadrangleSrc);
	const CQuadrangle& operator=(const CQuadrangle& quadrangleSrc);
};

class AFX_EXT_CLASS CSimObject : 
	public CObject
{
public:
	CSimObject(void);
	virtual ~CSimObject(void);
protected:
	CBox3D *m_Box;
	BOOL m_bIsModify;
	virtual void UpdateBox(void) = 0;
public:
	CBox3D GetBox(void);
	virtual void Draw(void) = 0;
	

	
};

class AFX_EXT_CLASS CSimDeRobo 
	//: public CSimObject
{
public:
	CSimDeRobo(void);
	virtual ~CSimDeRobo(void);
	virtual void Draw(void);
	void Lighting(void);
	float m_dAngle;
	CVector2D m_vVelocity;
	float m_dVelocity;
	void VelocityVectorCal(void);
	
	void DrawBody(void);
	void DrawWheel(void);
private:
	GLUquadricObj* Wheel;
protected:
	void UpdateBox(void);
public:
	void DrawVision(void);
	BOOL m_bVision;
	void SetVisionMark(BOOL VisionMark);
};

class AFX_EXT_CLASS CSimEnvironment
{
public:
	CSimEnvironment(void);
	virtual ~CSimEnvironment(void);
	virtual void Draw(void);
	BOOL LoadFile(LPCTSTR lpszMapFileName);
};

class AFX_EXT_CLASS CFace :
	public CSimObject
{
public:
	CFace(void);
	virtual ~CFace(void);
	CPoint3D p[4];
	CFace(CPoint3D p1, CPoint3D p2, CPoint3D p3, CPoint3D p4);
	CVector3D normal;
	float d;
protected:
	void Init(void);
	virtual void UpdateBox(void);
public:
	virtual void Draw(void);
	CFace & operator =(const CFace& faceSrc);
	CFace(const CFace& faceSrc);
	
	
	//CPoint3D *PositionRef;
	//CPoint3D GetPosRef(void);
//protected:
//	virtual void UpdatePosRef(void);
};

class AFX_EXT_CLASS CSimCube :
	public CSimObject
{
public:
	CSimCube(void);
	virtual ~CSimCube(void);

	CVector2D m_Velocity;
	CPoint3D m_PosPoint;
	CFace face[6];
	CPoint3D m_PointList[8];
	CVector3D m_Direction;
protected:
	
	
	
	
	float m_fRadAngle;
	CVector3D m_VectorList[8];
	
	void CalcFace(void);
	void CalcPoints(void);
	void CalcFirst(void);
	void CalcVector(void);
	void CalcVectorAngle(void);

public:
	CSimCube(CPoint3D MinPoint, CPoint3D MaxPoint);
	CSimCube & operator=(const CSimCube& SimCubeSrc);
	void SetPosition(CPoint3D pos);
	void SetAngle(float Angle);
	virtual void Draw(void);
	void GetPosPoint(CPoint3D& PosPoint);
	void SetVelocity(float speed);
	float GetAngle(void);
	void UpdatePosition(void);
protected:
	virtual void UpdateBox(void);
//public:
//	void DrawRobot(void);
public:
	void SetStaticPos(CPoint3D pos);
};

class AFX_EXT_CLASS CInDoorMap
{
public:
	CInDoorMap(void);
	virtual ~CInDoorMap(void);
	virtual void Draw(void);
	BOOL LoadFile(LPCTSTR lpszMapFileName);
	
	CArray< CFace*, CFace* > m_FaceArray;
	CArray< CSimCube*, CSimCube* > m_CubeArray;
protected:
	CArray< CPoint3D*, CPoint3D*> m_VertexArray;
	CArray< CPoint3D*, CPoint3D* > m_ColorArray;
	

public:
	void ReadVertex(FILE* pStream);
	void ReadColor(FILE* pStream);
	void ReadFace(FILE* pStream);
	void ReadCube(FILE* pStream);
	
};

class AFX_EXT_CLASS CSimPathMark
{
public:
	CSimPathMark(void);
	virtual ~CSimPathMark(void);
	virtual void Draw(void);
protected:
	CArray< CPoint3D*, CPoint3D* > m_MarkArray;
public:
	void AddMark(CPoint3D mark);
	float m_dInterval;
	float m_fLineWidth;
	int m_nMaxMarkCount;
	BYTE c[3];
	COLORREF m_ColorRef;
protected:
	
	
public:
	void SetMaxMarkCount(int nCount);
	void SetColor(float r, float g, float b);
protected:
	
public:
	void SetLineWidth(float fLineWidth);
protected:
	
public:
	void SetInterval(float dInterval);
	void CleanMark(void);
};

class AFX_EXT_CLASS CSimRobot :
	public CSimCube,public CSimDeRobo
{
public:
	CSimRobot(void);
	~CSimRobot(void);
	virtual void Draw(void);
protected:
	virtual void UpdateBox(void);
public:
	CSimRobot(CPoint3D MinPoint, CPoint3D MaxPoint);
	CSimRobot& operator=(const CSimCube& cube);
	CVector3D m_Acceleration;
};

