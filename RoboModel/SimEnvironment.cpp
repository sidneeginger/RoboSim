#include "StdAfx.h"
#include "..\include\modelbase.h"

CSimEnvironment::CSimEnvironment(void)
{
}

CSimEnvironment::~CSimEnvironment(void)
{
}

void CSimEnvironment::Draw(void)
{
	//glEnable( GL_ALPHA_TEST );
	//glEnable( GL_BLEND );
	glBegin( GL_QUADS );
		glColor4f( 0.4f, 0.8f, 0.2f, 0.5f );
		glNormal3f( 0.0f, 0.0f, 1.0f );
		glVertex3f( -500.0f, -500.0f, 0.0f );
		glVertex3f( 500.0f, -500.0f, 0.0f );
		glVertex3f( 500.0f, 500.0f, 0.0f );
		glVertex3f( -500.0f, 500.0f, 0.0f );

		glNormal3f( 0, 1, 0 );
		glVertex3f( -200, -200, 200 );
		glVertex3f( 200, -200, 200 );
		glVertex3f( 200, -200, 0 );
		glVertex3f( -200, -200, 0 );

		glNormal3f( 0, -1, 0 );
		glVertex3f( -200, 200, 0 );
		glVertex3f( 200, 200, 0 );
		glVertex3f( 200, 200, 200 );
		glVertex3f( -200, 200, 200 );

		glNormal3f( 1, 0, 0 );
		glVertex3f( -200, -200, 0 );
		glVertex3f( -200, 200, 0 );
		glVertex3f( -200, 200, 200 );
		glVertex3f( -200, -200, 200 );

		glNormal3f( -1, 0, 0 );
		glVertex3f( 200, 200, 0 );
		glVertex3f( 200, -200, 0 );
		glVertex3f( 200, -200, 200 );
		glVertex3f( 200, 200, 200 );
	glEnd();
}

BOOL CSimEnvironment::LoadFile(LPCTSTR lpszMapFileName)
{
	return 0;
}
