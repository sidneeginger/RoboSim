#include "StdAfx.h"

#include "..\include\modelbase.h"


CSimRobot::CSimRobot(void)
{
}

CSimRobot::~CSimRobot(void)
{
}

void CSimRobot::Draw(void)
{
	m_dAngle = m_fRadAngle*57.29577951f;
	glPushMatrix();
	glTranslated( m_PosPoint.x, m_PosPoint.y, 0 );
	CSimDeRobo::Draw();
	glPopMatrix();

	#ifdef _DEBUG
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		CSimCube::Draw();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	#endif
	
	
}

void CSimRobot::UpdateBox(void)
{
	CSimCube::UpdateBox();
}
CSimRobot::CSimRobot(CPoint3D MinPoint, CPoint3D MaxPoint)
{
	CSimCube::CSimCube( MinPoint, MaxPoint );
}

CSimRobot& CSimRobot::operator=(const CSimCube& cube)
{
	//TODO: return statement
	CSimCube::operator =( cube );
	return *this;
}
	
