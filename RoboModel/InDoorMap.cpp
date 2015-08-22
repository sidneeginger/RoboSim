#include "StdAfx.h"
#include "..\include\modelbase.h"

CInDoorMap::CInDoorMap(void)
{
	CPoint3D *Vertex1st = new CPoint3D( 0, 0, 0 );
	m_VertexArray.Add( Vertex1st );

	CPoint3D *Color1st = new CPoint3D( 1, 1, 1 );
	m_ColorArray.Add( Color1st );
}

CInDoorMap::~CInDoorMap(void)
{
	for( int i=0; i<m_ColorArray.GetSize(); i++ )
		delete m_ColorArray[i];
	for( int i=0; i<m_CubeArray.GetSize(); i++ )
		delete m_CubeArray[i];
	for( int i=0; i<m_FaceArray.GetSize(); i++ )
		delete m_FaceArray[i];
	for( int i=0; i<m_VertexArray.GetSize(); i++ )
		delete m_VertexArray[i];
}

void CInDoorMap::Draw(void)
{
	//glEnable( GL_DEPTH_TEST );
	glPushMatrix();
	for( int i=0; i<m_FaceArray.GetSize(); i++ )
		m_FaceArray[i]->Draw();
	for( int i=0; i<m_CubeArray.GetSize(); i++ )
		m_CubeArray[i]->Draw();
	glPopMatrix();
}

BOOL CInDoorMap::LoadFile(LPCTSTR lpszMapFileName)
{
	CStdioFile aFile;
	if( aFile.Open(  lpszMapFileName, CFile::modeRead )  )
	{
		
		char flag='\0';
		CString string( '\0', 50 );
		int ic=0;
		CString name('\0', 50 );
		while( flag !='e' )
		{
			fscanf( aFile.m_pStream, "%c", &flag );
			switch( flag )
			{
			
			case 'v':
				ReadVertex( aFile.m_pStream );
				//fscanf( aFile.m_pStream, " %f %f %f", &x, &y, &z );
				//cout<< "v " <<"x=" << x << "\ty=" << y << "\tz=" << z << endl;
				break;
			case 'c':
				ReadColor( aFile.m_pStream );
				//fscanf( aFile.m_pStream, " %f %f %f", &r, &g, &b );
				//cout<<"c" <<"r" << r << "\tg" << g << "\tb" << b << endl;
				break;
			case 'g':
				fscanf( aFile.m_pStream, "%s", name );
				//cout<<"g " <<name << endl;
				break;
			case 'o':
				fscanf( aFile.m_pStream, "%s %d", name, &ic );
				//cout<< "o "<<name << ic << endl;
				break;
			case '#' :
				aFile.ReadString( string );
				
				break;
			case 'q':
				ReadFace( aFile.m_pStream );
				//fscanf( aFile.m_pStream, " %d %d %d %d", &iq, &iw, &ie, &ir );
				//cout<<"q " <<iq << " " << iw << " " << ie << " " << ir << endl;
				break;
			case 'd':
				ReadCube( aFile.m_pStream );
				//fscanf( aFile.m_pStream, " %d %d", &imin, &imax );
				//cout<< "d"<<imin << " " << imax << endl;
				break;
			}

		}
		aFile.Close();
		return TRUE;
	}
	else
		return FALSE;
}

void CInDoorMap::ReadVertex(FILE* pStream)
{
	float x=0.0f, y=0.0f, z=0.0f;
	
	fscanf( pStream, " %f %f %f", &x, &y, &z );
	CPoint3D *pVertex=new CPoint3D( x, y, z );
	m_VertexArray.Add( pVertex );
}

void CInDoorMap::ReadColor(FILE* pStream)
{
	float r=0.0f, g=0.0f, b=0.0f;

	fscanf( pStream, " %f %f %f", &r, &g, &b );
	CPoint3D *pColor = new CPoint3D( r, g, b );
	m_ColorArray.Add( pColor );
}

void CInDoorMap::ReadFace(FILE* pStream)
{
	int iq=0, iw=0, ie=0, ir=0;
	fscanf( pStream, " %d %d %d %d", &iq, &iw, &ie, &ir );
	CFace *pFace = new CFace( *m_VertexArray[iq], *m_VertexArray[iw],
		*m_VertexArray[ie], *m_VertexArray[ir] );
	m_FaceArray.Add( pFace );
}

void CInDoorMap::ReadCube(FILE* pStream)
{
	int imin=0, imax=0;
	fscanf( pStream, " %d %d", &imin, &imax );
	CSimCube *pCube = new CSimCube( *m_VertexArray[imin],
		*m_VertexArray[imax] );
	CPoint3D pos;
	pos.x = (m_VertexArray[imin]->x + m_VertexArray[imax]->x) * 0.5f;
	pos.y = (m_VertexArray[imin]->y + m_VertexArray[imax]->y) * 0.5f;
	pos.z = (m_VertexArray[imin]->z + m_VertexArray[imax]->z) * 0.5f;
	
	pCube->SetStaticPos( pos ); 
	m_CubeArray.Add( pCube );
}

