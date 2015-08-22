#include "StdAfx.h"
#include "..\include\modelbase.h"

CSimObject::CSimObject(void)
: m_bIsModify(FALSE)
{
	m_Box =NULL;
}

CSimObject::~CSimObject(void)
{
	if( m_Box )
		delete m_Box;
}

CBox3D CSimObject::GetBox(void)
{
	if( m_bIsModify == TRUE )
	{
		UpdateBox();
		m_bIsModify = FALSE;
	}
	//if( m_Box )
		return *m_Box;
	//else

}
