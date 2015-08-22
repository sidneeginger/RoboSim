#include "Stdafx.h"
#include "..\include\modelbase.h"
#include <gl/gl.h>

CFace::CFace(void)
: d(0)
//, PositionRef(NULL)
{
}

CFace::~CFace(void)
{
	/*if( PositionRef )
		delete PositionRef;*/
}

CFace::CFace(CPoint3D p1, CPoint3D p2, CPoint3D p3, CPoint3D p4)
{
	p[0] = p1;
	p[1] = p2;
	p[2] = p3;
	p[3] = p4;
	Init();
}

void CFace::Init(void)
{
	CalcNormal( p, normal );
	d = (float)-( normal.dx * p[0].x 
		+ normal.dy * p[0].y 
		+ normal.dz * p[0].z );
	m_bIsModify = TRUE;
}

void CFace::Draw(void)
{
	glBegin( GL_QUADS );
	glNormal3d( normal.dx, normal.dy, normal.dz );
	for( int i=0; i<4; i++ )
	{
		glVertex3d( p[i].x, p[i].y, p[i].z );
	}
	glEnd();
	
}

CFace & CFace::operator =(const CFace& faceSrc)
{
	//TODO: return statement
	for( int i=0; i<4; i++ )
		p[i] = faceSrc.p[i];
	normal = faceSrc.normal;
	d = faceSrc.d;
	return *this;
}

CFace::CFace(const CFace& faceSrc)
{
	for( int i=0; i<4; i++ )
		p[i] = faceSrc.p[i];
	normal = faceSrc.normal;
	d = faceSrc.d;
}


void CFace::UpdateBox(void)
{
	if( m_Box )
		delete m_Box;
	m_Box = NULL;

	CPoint3D MaxPoint( -1000000, -1000000, -1000000), 
		MinPoint( 1000000, 1000000, 1000000 );
	for( int i=0; i<4; i++ )
	{
		MaxPoint.x = (MaxPoint.x > p[i].x) ? MaxPoint.x : p[i].x;
		MaxPoint.y = (MaxPoint.y > p[i].y) ? MaxPoint.y : p[i].y;
		MaxPoint.z = (MaxPoint.z > p[i].z) ? MaxPoint.z : p[i].z;
		//
		MinPoint.x =(MinPoint.x < p[i].x) ? MinPoint.x : p[i].x;
		MinPoint.y =(MinPoint.y < p[i].y) ? MinPoint.y : p[i].y;
		MinPoint.z =(MinPoint.z < p[i].z) ? MinPoint.z : p[i].z;
	}
	m_Box = new CBox3D( MinPoint, MaxPoint );

}

//CPoint3D CFace::GetPosRef(void)
//{
//	return *PositionRef;
//}

//void CFace::UpdatePosRef(void)
//{
//	/*if( PositionRef )
//		delete PositionRef;
//	PositionRef = NULL;
//	CBox3D box = GetBox();
//	float x=0.0, y=0.0, z=0.0;
//	x = (box.x0 + box.x1) * 0.5;
//	y = (box.y0 + box.y1) * 0.5;
//	z = (box.z0 + box.z1) * 0.5;
//	PositionRef = new CPoint3D( x, y, z );*/
//}
