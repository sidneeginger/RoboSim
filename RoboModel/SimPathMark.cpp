#include "StdAfx.h"
#include "..\include\modelbase.h"

CSimPathMark::CSimPathMark(void)
: m_nMaxMarkCount(100)
, m_fLineWidth(1)
, m_dInterval(0)
{
	for( int i=0; i<3; i++ )
		c[i] = 255;
}

CSimPathMark::~CSimPathMark(void)
{
	for( int i=0; i<m_MarkArray.GetSize(); i++ )
		delete m_MarkArray[i];
}

void CSimPathMark::Draw(void)
{
	glEnable( GL_LINE_SMOOTH );
	glColor3ub( GetRValue(m_ColorRef), GetGValue(m_ColorRef), GetBValue(m_ColorRef) );
	glLineWidth( m_fLineWidth );
	glBegin( GL_LINE_STRIP );
	for( int i=0; i<m_MarkArray.GetSize(); i++ )
		glVertex3d( m_MarkArray[i]->x,m_MarkArray[i]->y, m_MarkArray[i]->z );
	glEnd();
	glDisable( GL_LINE_SMOOTH );
	glLineWidth( 1 );
}

void CSimPathMark::AddMark(CPoint3D mark)
{
	float interval=m_dInterval + 10.0f;
	CVector3D aVector;

	if( m_MarkArray.GetSize() != 0 )
	{
		aVector = *m_MarkArray[ m_MarkArray.GetSize() -1 ] - mark;
		interval = aVector.GetLengthXY();
	}
	
	if( interval > m_dInterval )
	{
		
		if( m_MarkArray.GetSize() > m_nMaxMarkCount )
		{
			delete m_MarkArray[0];
			m_MarkArray.RemoveAt( 0, 1 );
		}	
		else
		{
			CPoint3D *pmark = new CPoint3D( mark );
			m_MarkArray.Add( pmark );
		}
	}
}

void CSimPathMark::SetMaxMarkCount(int nCount)
{
	m_nMaxMarkCount = nCount;
}

void CSimPathMark::SetColor(float r, float g, float b)
{
	
	m_ColorRef = RGB( r, g, b );
	c[0]=GetRValue( m_ColorRef );
	c[1]=GetGValue( m_ColorRef );
	c[2]=GetBValue( m_ColorRef );
}

void CSimPathMark::SetLineWidth(float fLineWidth)
{
	m_fLineWidth = fLineWidth;
}

void CSimPathMark::SetInterval(float dInterval)
{
	m_dInterval = dInterval;
}

void CSimPathMark::CleanMark(void)
{
	for( int i=0; i<m_MarkArray.GetSize(); i++ )
		delete m_MarkArray[i];
	m_MarkArray.RemoveAll();
}
