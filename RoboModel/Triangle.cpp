#include "StdAfx.h"
#include "..\include\modelbase.h"

CTriangle::CTriangle(void)
{
	for( int i=0; i<3; i++ )
		p[i] = 0;
}

CTriangle::~CTriangle(void)
{
}

CTriangle::CTriangle(CPoint3D p1, CPoint3D p2, CPoint3D p3)
{
	p[0] = p1, p[1] = p2, p[2] = p3;
}

CTriangle::CTriangle(const CTriangle& triangleSrc)
{
	for( int i=0; i<3; i++ )
		p[i] = triangleSrc.p[i];
}

const CTriangle& CTriangle::operator=(const CTriangle& triangleSrc)
{
	for( int i=0; i<3; i++ )
		p[i] = triangleSrc.p[i];
	return *this;
}

void CTriangle::Draw(void)
{
}
