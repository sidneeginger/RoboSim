#include "StdAfx.h"
#include "..\include\modelbase.h"

CSimDeRobo::CSimDeRobo(void)
: m_dAngle(0)
, m_dVelocity(0)
, Wheel(NULL)
, m_bVision(TRUE)
{
}

CSimDeRobo::~CSimDeRobo(void)
{
}

void CSimDeRobo::Draw(void)
{
	
	//glScaled( 10, 10, 10 );
	
	glPushMatrix();
	glRotatef( (GLfloat)m_dAngle, 0, 0, 1 );
	glTranslatef( -1.0f,0.0f, 0.0f );
	DrawBody();
	if( m_bVision )
		DrawVision();
	glTranslatef( 1.0f, 6.0f, 2.0f );
	glRotatef( 90, 1, 0, 0 );
	DrawWheel();
	glTranslatef( 0, 0, -12 );
	DrawWheel();
	glPopMatrix();
	
}

void CSimDeRobo::Lighting(void)
{
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat  specular[] = { 0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat  specref[] =  { 0.6f, 0.6f, 0.6f, 1.0f };

	glEnable( GL_NORMALIZE );
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,64);

}

void CSimDeRobo::VelocityVectorCal(void)
{
	m_vVelocity.dx=m_dVelocity*cos( m_dAngle * 0.0174532f ),
	m_vVelocity.dy=m_dVelocity*sin( m_dAngle * 0.0174532f );
}

void CSimDeRobo::DrawBody(void)
{
	glPushMatrix();
	
	glRotatef( -90, 0, 0, 1 );
	glTranslatef( -5.0f, -5.0f, 0.0f );

	glColor3f( 0.75f, 0.55f, 0.15f );
	glBegin( GL_POLYGON  );
	glNormal3f( 0.0f, 0.0f, -1.0f );
	glVertex3f( 0.0f, 10.0f, 1.0f );
	glVertex3f( 5.0f, 12.0f, 1.0f );
	glVertex3f( 10.0f, 10.0f, 1.0f );
	glVertex3f( 10.0f, 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, 1.0f );
	glEnd();

	glBegin( GL_POLYGON  );
	glNormal3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, 6.0f );
	glVertex3f( 10.0f, 0.0f, 6.0f );
	glVertex3f( 10.0f, 10.0f, 6.0f );
	glVertex3f( 5.0f, 12.0f, 6.0f );
	glVertex3f( 0.0f, 10.0f, 6.0f );
	glEnd();
	
	glBegin( GL_QUADS);
	glNormal3f( 0.0f, -1.0f, 0.0f );
	glVertex3f( 0.0f, 0.0f, 6.0f );
	glVertex3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( 10.0f, 0.0f, 1.0f );
	glVertex3f( 10.0f, 0.0f, 6.0f );

	glNormal3f( 1.0f, 0.0f, 0.0f );
	glVertex3f( 10.0f, 0.0f, 6.0f );
	glVertex3f( 10.0f, 0.0f, 1.0f );
	glVertex3f( 10.0f, 10.0f, 1.0f );
	glVertex3f( 10.0f, 10.0f, 6.0f );

	glNormal3f( 2.0f, 5.0f, 0.0f );
	glVertex3f( 10.0f, 10.0f, 6.0f );
	glVertex3f( 10.0f, 10.0f, 1.0f );
	glVertex3f( 5.0f, 12.0f, 1.0f );
	glVertex3f( 5.0f, 12.0f, 6.0f );

	glNormal3f( -2.0f, 5.0f, 0.0f );
	glVertex3f( 5.0f, 12.0f, 6.0f );
	glVertex3f( 5.0f, 12.0f, 1.0f );
	glVertex3f( 0.0f, 10.0f, 1.0f );
	glVertex3f( 0.0f, 10.0f, 6.0f );

	glNormal3f( -1.0f, 0.0f, 0.0f );
	glVertex3f( 0.0f, 10.0f, 6.0f );
	glVertex3f( 0.0f, 10.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, 6.0f );
	glEnd();
	glPopMatrix();
}

void CSimDeRobo::DrawWheel(void)
{
	//glPushMatrix();
	Wheel = gluNewQuadric();
	
	//glTranslatef( -1.0f, 6.0f, 2.0f );
	//glRotatef( 90, 1, 0, 0 );
	
	glColor3f( 0.1f, 0.1f, 0.1f );
	gluCylinder( Wheel, 2.0, 2.0f, 1.0, 20, 2 );
	glTranslatef( 0, 0, 1 );
	gluDisk( Wheel, 0, 2.0, 20, 2 );
	glTranslatef( 0, 0, -1.0f );
	glRotatef( 180, 0, 1, 0 );
	gluDisk( Wheel, 0, 2.0, 20, 2 );
	//glPushMatrix();
}

void CSimDeRobo::UpdateBox(void)
{
}

void CSimDeRobo::DrawVision(void)
{
	Wheel = gluNewQuadric();
	gluQuadricDrawStyle( Wheel, GLU_LINE );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glTranslatef( 0, 0, 0.1f );
	gluPartialDisk( Wheel, 10, 75, 10, 5, 60, 60 );
	glTranslatef( 0, 0, -0.1f );
}

void CSimDeRobo::SetVisionMark(BOOL VisionMark)
{
	m_bVision = VisionMark;
}
