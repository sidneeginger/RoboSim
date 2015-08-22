#include "stdafx.h"
#include "../include/physics.h"


BOOL	 _IsPointFrontFace( CPoint3D point, CFace face )
{
	CMathDefs m_MathDefs;
	float axbyczd=0.0f;
	axbyczd = (float)m_MathDefs.DotProduct(  &point, 
		&face.normal ) 
			+ face.d ;
			
	if( axbyczd < 0.0 )
		return FALSE;
	else
		return TRUE;
}

BOOL	_IsBoxAcross(CBox3D boxa, CBox3D boxb)
{
	/*TRACE( "\nboxacross %f, %f, %f",
		(boxa.x1 - boxb.x0) * (boxa.x0 - boxb.x1 ),
		(boxa.y1 - boxb.y0) * (boxa.y0 - boxb.y1 ),
		(boxa.z1 - boxb.z0) * (boxa.z0 - boxb.z1 ) );*/

	
	if(		((boxa.x1 - boxb.x0) * (boxa.x0 - boxb.x1 )>0.0)
		||	((boxa.y1 - boxb.y0) * (boxa.y0 - boxb.y1 )>0.0)
		||	((boxa.z1 - boxb.z0) * (boxa.z0 - boxb.z1 )>0.0)  )
	
		return FALSE;
	
	else
	{
		/*TRACE( "\n\nboxa %f %f %f || %f %f %f \nboxb %f %f %f || %f %f %f",
			boxa.x0, boxa.y0, boxa.z0,
			boxa.x1, boxa.y1, boxa.z1, 
			boxb.x0, boxb.y0, boxb.z0,
			boxb.x1, boxb.y1, boxb.z1 );
		
		TRACE( "\nboxacross %f, %f, %f",
		(boxa.x1 - boxb.x0) * (boxa.x0 - boxb.x1 ),
		(boxa.y1 - boxb.y0) * (boxa.y0 - boxb.y1 ),
		(boxa.z1 - boxb.z0) * (boxa.z0 - boxb.z1 ) );*/
		return TRUE;
	}
}

