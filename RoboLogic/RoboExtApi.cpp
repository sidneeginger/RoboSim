#include "stdafx.h"
#include "../include/geometry.h"

//float _AngleBetween(VECTOR2D v1,VECTOR2D v2)
//{
//	if(_IsParallel(v1,v2))	return 0;
//	CVector2D cv1(v1),cv2(v2);
//	return acos((cv1|cv2.GetNormal())/cv1.GetLength());
//}

float _AngleBetween(VECTOR3D v1,VECTOR3D v2)
{
	if(_IsParallel(v1,v2))	return 0;
	
	CVector3D cv1(v1),cv2(v2);
	CVector3D flag = cv2*cv1;
	//TRACE( "\nflag %f", flag.dz );
	if( flag.dz >0 )
		return acos((cv1|cv2.GetNormal())/cv1.GetLength());
	else
		return -acos((cv1|cv2.GetNormal())/cv1.GetLength());
}

float _DistOf(POINT2D pt0,POINT2D pt1)
{
	CVector2D vec(pt1.x-pt0.x,pt1.y-pt0.y);
	return vec.GetLength();
}

float _DistOf(POINT3D pt0,POINT3D pt1)
{
	CVector3D vec(pt1.x-pt0.x,pt1.y-pt0.y);
	return vec.GetLength();
}

BOOL _IsParallel(VECTOR2D v0,VECTOR2D v1)
{
	CVector2D cv0(v0),cv1(v1);
	return IS_ZERO((cv0*cv1).dz);
}

BOOL _IsParallel(VECTOR3D v0,VECTOR3D v1)
{
	CVector3D cv0(v0),cv1(v1);
	return IS_ZERO((cv0*cv1).GetLength());
}

BOOL _IsOrthogonal(VECTOR3D v0,VECTOR3D v1)
{
	CVector3D cv0(v0),cv1(v1);
	return IS_ZERO(cv0|cv1);
}

void HSV_TO_RGB( float h, float s, float v, float *r, float *g, float *b )
//	known:	h is the hue in [0, 360] with red at 0,
//			s is the saturation in [0, 1],
//			v is the value in [0, 1].
//	find:	r, g, b all in [0, 1]
{
	float  f, p, k, t;
	int i;
	if( s == 0 )
	{
		if( h == 0 )
		{
			*r = *g = *b = v;
		}
		else
			return;
	}
	else
	{
		if( h == 360 ) h=0;
		h= h / 60;
		i=(int)h;
		f=h-i;
		p=v*(1-s);
		k=v*(1-s*f);
		t=v*(1-(s*(1-f)));
		switch( i )
		{
			case 0:
				*r = v, *g = t, *b = p;
				//( *r, *g, *b ) = ( v, t, p ); 
				break; 
			case 1: 
				*r = k, *g = v, *b = p;
				//( *r, *g, *b ) = ( k, v, p ); 
				break;
			case 2:
				*r = p, *g = v, *b = t;
				//( *r, *g, *b ) = ( p, v, t ); 
				break;
			case 3:
				*r = p, *g = k, *b =v;
				//( *r, *g, *b ) = ( p, k, v ); 
				break;
			case 4:
				*r = t, *g = p, *b = v;
				//( *r, *g, *b ) = ( t, p, v ); 
				break;
			case 5:
				*r = v, *g = p, *b = k;
				//( *r, *g, *b ) = ( v, p, k ); 
				break;
			
			default:
				break;

		}
		//v=0.5f, p=0.5f, k=0.5f;
		//( *r, *g, *b ) = ( v, p, k );
	}
}

void RGB_TO_HSV( float r, float g, float b, float *h, float *s, float *v )
//	known: r, g, b all in [0, 1]
//	find: h in [0, 360], v and s in [0, 1]
{	
	float m, n, delta;

	m = max( max( r, g), b );
	n = min( min( r, g), b );

	*v = m;

	if( m != 0 )
		*s = ( m -n ) / m;
	else
		*s = 0;
	if( *s == 0 )
		*h = 0;
	else
	{
		delta = m - n;
		if( r == m )
			*h = ( g - b ) / delta;
		else if( g == m )
			*h = 2 + ( b - r ) / delta;
		else if( b == m )
			*h = 4 + ( r - g ) / delta;
		*h = *h * 60;
		if( *h < 0 )
			*h = *h + 360;
	}
}//RGB_TO_HSV


void MultVector( CVector2D &v1, CVector2D &v2, CVector2D &result )
{
	result.dx = v1.dx * v2.dx - v1.dy * v2.dy;
	result.dy = v1.dx* v2.dy + v1.dy * v2.dx;
}

void MultVector( CVector3D &v1, CVector3D &normal, CVector3D &result )
{
	result.dx = v1.dx * normal.dx - v1.dy * normal.dy;
	result.dy = v1.dx* normal.dy + v1.dy * normal.dx;
	result.dz = v1.dz;
}

void	ReduceToUnit(float vector[3])
{
	float length;
	
	// Calculate the length of the vector		
	length = (float)sqrt((vector[0]*vector[0]) + 
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if(length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}

void	CalcNormal(CPoint3D v[3], CVector3D &out)
{
	CVector3D v1,v2;
	//static const int x = 0;
	//static const int y = 1;
	//static const int z = 2;

	// Calculate two vectors from the three points
	//v1.dx = v[0].x - v[1].x;
	//v1.dy = v[0].y - v[1].y;
	//v1.dz = v[0].z - v[1].z;
	v1=v[0]-v[1];

	//v2.dx = v[1].x - v[2].x;
	//v2.dy = v[1].y - v[2].y;
	//v2.dz = v[1].z - v[2].z;
	v2=v[1]-v[2];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	//out.dx = v1.dy*v2.dz - v1.dz*v2.dy;
	//out.dy = v1.dz*v2.dx - v1.dx*v2.dz;
	//out.dz= v1.dx*v2.dy - v1.dy*v2.dx;
	out = v1*v2;

	// Normalize the vector (shorten length to one)
	out.Normalize();
}