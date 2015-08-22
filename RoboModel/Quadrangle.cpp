#include "StdAfx.h"
#include "..\include\modelbase.h"

CQuadrangle::CQuadrangle(void)
{
}

CQuadrangle::~CQuadrangle(void)
{
}

void CQuadrangle::CQuardrangle(CPoint3D p1, CPoint3D p2, CPoint3D p3, CPoint3D p4)
{
	p[0] = p1, p[1] = p2, p[2] = p3, p[3]= p4;
}

CQuadrangle::CQuadrangle(const CQuadrangle& quadrangleSrc)
{
	for( int i=0; i<4; i++ )
		p[i] = quadrangleSrc.p[i];
}

const CQuadrangle& CQuadrangle::operator=(const CQuadrangle& quadrangleSrc)
{
	for( int i=0; i<4; i++ )
		p[i] = quadrangleSrc.p[i];
	return *this;
}
