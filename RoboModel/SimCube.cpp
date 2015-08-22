#include "Stdafx.h"
#include "..\include\modelbase.h"

CSimCube::CSimCube(void)
: m_fRadAngle(0)
{
	m_PosPoint=CPoint3D( 0, 0, 0 );
	m_Direction.dx = cos( 0.0f );
	m_Direction.dy = sin( 0.0f );
}

CSimCube::~CSimCube(void)
{
}

CSimCube::CSimCube(CPoint3D MinPoint, CPoint3D MaxPoint)
{
	m_PointList[0] = MinPoint;
	m_PointList[6] = MaxPoint;

	m_PosPoint.x = (MinPoint.x + MaxPoint.x) * 0.5f;
	m_PosPoint.y = (MinPoint.y + MaxPoint.y) * 0.5f;
	m_PosPoint.z = (MinPoint.z + MaxPoint.z) * 0.5f;


	for( int i=0; i<4; i++ )
	{
		m_PointList[i].z = MinPoint.z;
		m_PointList[i+4].z = MaxPoint.z;
	}

	m_PointList[1].x = MaxPoint.x;
	m_PointList[1].y = MinPoint.y;

	m_PointList[2].x = MaxPoint.x;
	m_PointList[2].y = MaxPoint.y;

	m_PointList[3].x = MinPoint.x;
	m_PointList[3].y = MaxPoint.y;

	m_PointList[4].x = MinPoint.x;
	m_PointList[4].y = MinPoint.y;

	m_PointList[5].x = MaxPoint.x;
	m_PointList[5].y = MinPoint.y;

	m_PointList[7].x = MinPoint.x;
	m_PointList[7].y = MaxPoint.y;

	CalcFirst();
	//m_bIsModify = TRUE;
}

void CSimCube::SetPosition(CPoint3D pos)
{
	//TRACE( "\nm_posPoint %f, %f, %f", m_PosPoint.x ,m_PosPoint.y ,m_PosPoint.z );
	m_PosPoint.x = pos.x;
	m_PosPoint.y = pos.y;
	m_PosPoint.z = pos.z;

	CalcVectorAngle();
	//CalcPoints();
	CalcFace();
}

void CSimCube::SetAngle(float Angle)
{
	m_fRadAngle = Angle*0.017453292f ;
	m_Direction.dx = cos( m_fRadAngle );
	m_Direction.dy = sin( m_fRadAngle );

	CalcVectorAngle();
	//CalcPoints();
	CalcFace();

}

void CSimCube::Draw(void)
{
	for( int i=0; i<6; i++ )
		face[i].Draw();
	
}

void CSimCube::CalcFace(void)
{
	face[0] = CFace( m_PointList[3], m_PointList[2], m_PointList[1], m_PointList[0] );
	face[1] = CFace( m_PointList[0], m_PointList[1], m_PointList[5], m_PointList[4] );
	face[2] = CFace( m_PointList[1], m_PointList[2], m_PointList[6], m_PointList[5] );
	face[3] = CFace( m_PointList[2], m_PointList[3], m_PointList[7], m_PointList[6] );
	face[4] = CFace( m_PointList[3], m_PointList[0], m_PointList[4], m_PointList[7] );
	face[5] = CFace( m_PointList[4], m_PointList[5], m_PointList[6], m_PointList[7] );
}

CSimCube & CSimCube::operator=(const CSimCube& SimCubeSrc)
{
	//TODO: return statement
	m_Direction = SimCubeSrc.m_Direction;
	m_Velocity = SimCubeSrc.m_Velocity;
	m_PosPoint = SimCubeSrc.m_PosPoint;
	m_fRadAngle = SimCubeSrc.m_fRadAngle;
	for( int i=0; i<8; i++ )
	{
		m_PointList[i] = SimCubeSrc.m_PointList[i];
		m_VectorList[i] = SimCubeSrc.m_VectorList[i];
	}
	for( int i=0; i<6; i++ )
		face[i] = SimCubeSrc.face[i];

	return *this;
}

void CSimCube::CalcPoints(void)
{
	for( int i=0; i<8; i++ )
	{
		m_PointList[i]=m_PosPoint+m_VectorList[i];
	}
	m_bIsModify = TRUE;
}



void CSimCube::CalcFirst(void)
{
	CalcVector();
	m_PosPoint.x=0;
	m_PosPoint.y=0;
	CalcPoints();
	CalcFace();
}

void CSimCube::CalcVector(void)
{
	for( int i=0; i<8; i++ )
	{
		m_VectorList[i]=m_PointList[i]-m_PosPoint;	
	}
}

void CSimCube::GetPosPoint(CPoint3D& PosPoint)
{
	PosPoint=m_PosPoint;
}

void CSimCube::CalcVectorAngle(void)
{
	CVector3D v;
	CVector3D tv[8];
	for( int i=0; i<8; i++ )
	{
		tv[i] = m_VectorList[i];
		MultVector( m_VectorList[i], m_Direction, v );
		m_VectorList[i] = v;
	}
	CalcPoints();
	for( int i=0; i<8; i++ )
		m_VectorList[i] = tv[i];
}

void CSimCube::SetVelocity(float speed)
{
	m_Velocity.dx = speed * m_Direction.dx;
	m_Velocity.dy = speed * m_Direction.dy;
}

float CSimCube::GetAngle(void)
{
	return (m_fRadAngle*57.29577951f);
}

void CSimCube::UpdatePosition(void)
{
	//CalcVectorAngle();
	//CalcPoints();
	//CalcFace();
}

void CSimCube::UpdateBox(void)
{
	if( m_Box )
		delete m_Box;
	m_Box = NULL;

	CPoint3D MaxPoint( -100000, -100000, -100000 ), MinPoint( 100000, 100000, 100000);
	for( int i=0; i<8; i++ )
	{
		MaxPoint.x = (MaxPoint.x > m_PointList[i].x) ? MaxPoint.x : m_PointList[i].x;
		MaxPoint.y = (MaxPoint.y > m_PointList[i].y) ? MaxPoint.y : m_PointList[i].y;
		MaxPoint.z = (MaxPoint.z > m_PointList[i].z) ? MaxPoint.z : m_PointList[i].z;

		MinPoint.x =(MinPoint.x < m_PointList[i].x) ? MinPoint.x : m_PointList[i].x;
		MinPoint.y =(MinPoint.y < m_PointList[i].y) ? MinPoint.y : m_PointList[i].y;
		MinPoint.z =(MinPoint.z < m_PointList[i].z) ? MinPoint.z : m_PointList[i].z;
	}
	m_Box = new CBox3D( MinPoint, MaxPoint );
	
}

//void CSimCube::DrawRobot(void)
//{
//	static CSimDeRobo robot;
//	robot.m_dAngle = m_fRadAngle*57.29577951;
//	glPushMatrix();
//	glTranslated( m_PosPoint.x, m_PosPoint.y, 0 );
//	robot.Draw();
//	glPopMatrix();
//}

void CSimCube::SetStaticPos(CPoint3D pos)
{
	m_PosPoint.x = pos.x;
	m_PosPoint.y = pos.y;
	m_PosPoint.z = pos.z;

	//CalcVectorAngle();
	CalcPoints();
	CalcFace();
}
