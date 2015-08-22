#include "StdAfx.h"
#include "..\include\physics.h"

CSimCollisions::CSimCollisions(void)
: m_pInDoorMap(NULL)
{
}

CSimCollisions::~CSimCollisions(void)
{
}

BOOL CSimCollisions::IsBoxAcross(CBox3D boxa, CBox3D boxb)
{
	return _IsBoxAcross(boxa, boxb);	
}

BOOL CSimCollisions::IsPointFrontFace(CPoint3D point, CFace face)
{
	return _IsPointFrontFace(point, face);
}

int CSimCollisions::CheckForCollisions(CSimCube* pObject)
{
	int CollisionState = NO_COLLIDING;
	CMathDefs MathDefs;
	float axbyczd=0.0f, dddd=0.0f;

	for( int i=1; (i<m_pInDoorMap->m_FaceArray.GetSize()) 
		&& (CollisionState != PENETRATING); i++ )
	{
		if( _IsBoxAcross(pObject->GetBox(), 
			m_pInDoorMap->m_FaceArray[i]->GetBox())==TRUE )
		{
			for( int k=0; k<8; k++ )
			{
				axbyczd = MathDefs.DotProduct(  &pObject->m_PointList[k],
					&m_pInDoorMap->m_FaceArray[i]->normal ) 
					+ m_pInDoorMap->m_FaceArray[i]->d  ;
				if( axbyczd < 0.001f )
				
					CollisionState = PENETRATING;
					//return PENETRATING;
			}
		}
	}

	for( int i=0; (i<m_pInDoorMap->m_CubeArray.GetSize())
		&&( CollisionState != PENETRATING ); i++ )
	{
		if( _IsBoxAcross( pObject->GetBox(),
			m_pInDoorMap->m_CubeArray[i]->GetBox() ) == TRUE )
		{
			BOOL IsInCube[6];
			BOOL IsInRobo[6];
			for( int k=0; k<8; k++ )
			{
				for( int j=0; j<6; j++ )
				{
					axbyczd = MathDefs.DotProduct( &pObject->m_PointList[k],
						&m_pInDoorMap->m_CubeArray[i]->face[j].normal )
						+ m_pInDoorMap->m_CubeArray[i]->face[j].d ;
					
					if( axbyczd < 0.001f ) 
						IsInCube[j] = TRUE;
					else 
						IsInCube[j] = FALSE;

					dddd = MathDefs.DotProduct( 
						&m_pInDoorMap->m_CubeArray[i]->m_PointList[k], 
						&pObject->face[j].normal )
						+ pObject->face[j].d;
					
					if( dddd < 0.001f ) 
						IsInRobo[j] = TRUE;
					else 
						IsInRobo[j] = FALSE;
				}
				if( IsInCube[0] && IsInCube[1] && IsInCube[2] &&
					IsInCube[3] && IsInCube[4] && IsInCube[5] )
					CollisionState = PENETRATING;
				
				if( IsInRobo[0] && IsInRobo[1] && IsInRobo[2] &&
					IsInRobo[3] && IsInRobo[4] && IsInRobo[5] )
					CollisionState = PENETRATING;
					//return PENETRATING;
			}
		}
	}
	return CollisionState;
}

void CSimCollisions::LoadMap(CInDoorMap* pInDoorMap)
{
	m_pInDoorMap = pInDoorMap;
}
