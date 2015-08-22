// RoboSimerView.cpp : CRoboSimerView 类的实现
//

#include "stdafx.h"
#include "RoboSimer.h"

#include "RoboSimerDoc.h"
#include "RoboSimerView.h"
#include ".\robosimerview.h"
#include ".\PathSeting.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRoboSimerView

IMPLEMENT_DYNCREATE(CRoboSimerView, CView)

BEGIN_MESSAGE_MAP(CRoboSimerView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_TOOL_TRACT, OnToolTract)
	ON_UPDATE_COMMAND_UI(ID_TOOL_TRACT, OnUpdateToolTract)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_COMMAND(ID_PATHMARK, OnPathmark)
	ON_UPDATE_COMMAND_UI(ID_PATHMARK, OnUpdatePathmark)
	ON_COMMAND(ID_VISION, OnVision)
	ON_MESSAGE( WM_DELETEDLG, OnDeleteDlg )
	ON_COMMAND(ID__SET_PATHMARK, OnSetPathMark)
	ON_COMMAND(ID_FILE_PLAY, OnFilePlay)
	ON_UPDATE_COMMAND_UI(ID_FILE_PLAY, OnUpdateFilePlay)
END_MESSAGE_MAP()

// CRoboSimerView 构造/析构

CRoboSimerView::CRoboSimerView()
: m_pDC(NULL)
, m_fEyeAngleX(-75)
, m_fEyeAngleZ(0)
, m_fTranslateX(0)
, m_fTranslateY(0)
, m_fTranslateZ(0)
, m_bIsTracing(FALSE)
, LDownPoint(0)
, RDownPoint(0)
, m_bIsLDown(FALSE)
, m_bIsRDown(FALSE)
, m_fLastTime(0)
, m_bIsPathMark(true)
, m_bIsRun(FALSE)
{
	// TODO: 在此处添加构造代码
	//m_CameraDlg = new CCameraDlg(this);
	m_CameraDlg = NULL;

}

CRoboSimerView::~CRoboSimerView()
{
	if( m_CameraDlg )
		delete m_CameraDlg;
}

BOOL CRoboSimerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CRoboSimerView 绘制

void CRoboSimerView::OnDraw(CDC* /*pDC*/)
{
	/*CRoboSimerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;*/
	if( m_bIsRun )
		InputKey();
	DrawScene();
}


// CRoboSimerView 诊断

#ifdef _DEBUG
void CRoboSimerView::AssertValid() const
{
	CView::AssertValid();
}

void CRoboSimerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRoboSimerDoc* CRoboSimerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRoboSimerDoc)));
	return (CRoboSimerDoc*)m_pDocument;
}
#endif //_DEBUG


// CRoboSimerView 消息处理程序

BOOL CRoboSimerView::bSetupPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		  PFD_SUPPORT_OPENGL |          // support OpenGL
		  PFD_DOUBLEBUFFER,             // float buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
	{
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}

	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}

	return TRUE;
}

int CRoboSimerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	Init();

	return 0;
}

void CRoboSimerView::Init(void)
{
	GLInit();

	
	
	//SetTimer(1, 15, NULL);
	m_SimTimer.Start();
	
	
	m_PathMark.SetInterval( 0.9 );
	m_PathMark.SetLineWidth( 1 );
	m_PathMark.SetMaxMarkCount( 1000 );
	m_PathMark.SetColor( 255, 255, 255 );
	
	
	//CPoint3D Target( 70, 80 );
	
	
	CPoint3D pmin( 0, 0, 0 );
	CPoint3D pmax( 12, 12, 8 );
	CPoint3D pmaxt( 2, 2, 10 );

	m_SimRobot=CSimCube( pmin, pmax );
	m_TargetCube=CSimCube( pmin, pmaxt );
	CPoint3D pos;
	m_SimRobot.GetPosPoint( pos );
	pos.x = 20, pos.y = 10;
	m_fTranslateX=-pos.x, m_fTranslateY=-pos.y;
	m_SimRobot.SetPosition( pos );
	pos.x=70, pos.y=150;
	m_TargetCube.SetPosition( pos );
	m_TargetCube.SetAngle( 0 );
	
	m_SimRobot.SetAngle( 0 );
	
	
	m_InDoorMap.LoadFile( "hall.map" );
	m_Collision.LoadMap( &m_InDoorMap );

	m_fLastTime = m_SimTimer.GetTime();

}

void CRoboSimerView::GLInit(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int         n;
	HGLRC       hrc;
	//GLfloat      fAspect=0.0f;
	

	m_pDC = new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if (!bSetupPixelFormat())
		return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	//glEnable( GL_BLEND );
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
	glClearDepth(1.0f);
	//glEnable(GL_DEPTH_TEST);
	
	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW);

	//Lighting();
	
}

void CRoboSimerView::OnDestroy()
{
	HGLRC   hrc;

	KillTimer(1);

	hrc = ::wglGetCurrentContext();
	::wglMakeCurrent(NULL,  NULL);

	if (hrc)
		::wglDeleteContext(hrc);

	if (m_pDC)
		delete m_pDC;
	if( m_CameraDlg )
	{
		m_CameraDlg->DestroyWindow();
		delete m_CameraDlg;
		m_CameraDlg = NULL;
	}

	CView::OnDestroy();
}

void CRoboSimerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if(cy > 0)
	{
		glViewport(0, 0, cx, cy);

		if((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
			RedrawWindow();

		m_oldRect.right = cx;
		m_oldRect.bottom = cy;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( 45.0f, (GLfloat)cx/cy, 1.0f, 8000.0f);
		
		glMatrixMode(GL_MODELVIEW);

		Invalidate( TRUE );
		
	}
	//// TODO: Add your message handler code here
	//if(cy == 0)		  // 避免被0除
	//	cy = 1;
	//float dAspect = (float)cx/(float)cy;
	//// 设置视口
 //   glViewport(0, 0, cx, cy);
	//// 设置投影矩阵
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//// 设置投影变换
	//gluPerspective(45.0, dAspect,0.2f, 2000);
	////  设置模型矩阵
	//glMatrixMode(GL_MODELVIEW);
	////glLoadIdentity();
	//Invalidate( TRUE );
}

void CRoboSimerView::DrawScene(void)
{
	static BOOL     bBusy = FALSE;
	
	if(bBusy)
		return;
	bBusy = TRUE;

	glClearColor(0.0f, 0.0f, 0.4f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
		if( m_bIsTracing )
		{
			//glTranslatef( 0, 0, (-100.0f+m_fTranslateZ) ) ;
			glTranslatef( 0, 0, -8 ) ;
			//glRotatef( (GLfloat)m_fEyeAngleX+90, 1.0f, 0.0f, 0.0f);
			//glRotatef( (GLfloat)m_fEyeAngleZ+180, 0.0f, 1.0f, 0.0f );
			glRotatef( -m_SimRobot.GetAngle()-90, 0.0f, 1.0f, 0.0f );
			gluLookAt( m_SimRobot.m_PosPoint.x, m_SimRobot.m_PosPoint.y, 10, 
				0, -1000, 0, 
				0, 0, 1 );
		}
		else
		{
			//glTranslatef( m_fTranslateX, m_fTranslateY, (-100.0f+m_fTranslateZ) ) ;
			//glRotatef( (GLfloat)m_fEyeAngleX, 1.0f, 0.0f, 0.0f);
			//glRotatef( (GLfloat)m_fEyeAngleZ, 0.0f, 0.0f, 1.0f );
			glTranslatef( 0, 0, (-100.0f+m_fTranslateZ) ) ;
			glRotatef( (GLfloat)m_fEyeAngleX+90, 1.0f, 0.0f, 0.0f);
			glRotatef( (GLfloat)m_fEyeAngleZ+180, 0.0f, 1.0f, 0.0f );
			//glRotatef( -m_SimRobot.GetAngle()-90, 0.0f, 1.0f, 0.0f );
			gluLookAt( m_SimRobot.m_PosPoint.x, m_SimRobot.m_PosPoint.y, 0, 
				0, -1000, 0, 
				0, 0, 1 );
		}
		
		
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	//glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	//glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	glEnable(GL_LIGHTING);
		DrawWorld();
	glPopMatrix();

	DrawText();
	
	glFinish();
	SwapBuffers(wglGetCurrentDC());

	bBusy = FALSE;
}

void CRoboSimerView::DrawWorld(void)
{
	glPushMatrix();
	Lighting();
	if( m_bIsPathMark )	
		m_PathMark.Draw();
	m_SimRobot.Draw();
	glColor3f( 1, 0, 0 );
	if( !m_CameraDlg )		
		m_TargetCube.Draw();
	
	
	//CBox3D box=m_SimRobot.GetBox();
	

	DrawMap();
	glPopMatrix();
}

void CRoboSimerView::DrawMap(void)
{
	glColor3f( 0.65f, 0.65f, 0.65f );
	m_InDoorMap.Draw();
}

void CRoboSimerView::OnToolTract()
{
	m_bIsTracing = m_bIsTracing ? FALSE : TRUE;
}

void CRoboSimerView::OnUpdateToolTract(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_bIsTracing );
}

void CRoboSimerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_bIsLDown = TRUE;
	LDownPoint = point;

	CView::OnLButtonDown(nFlags, point);
}

void CRoboSimerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_bIsLDown = FALSE;

	CView::OnLButtonUp(nFlags, point);
}

void CRoboSimerView::OnMouseMove(UINT nFlags, CPoint point)
{
	if( GetCapture()==this )
	{	//DownPoint=point;
		if( m_bIsLDown && m_bIsRDown )
		{
			m_fTranslateX += ( point.x - LDownPoint.x ) * 0.5f;
			m_fTranslateY -= (point.y-LDownPoint.y)*0.5f;
			LDownPoint = point;
		}

		if( m_bIsRDown && !m_bIsLDown  )
		{

			m_fEyeAngleX += (point.y-RDownPoint.y)*0.5;

			if( m_fEyeAngleX >=0 ) m_fEyeAngleX =0;
			if( m_fEyeAngleX <= -90 ) m_fEyeAngleX = -90;

			m_fEyeAngleZ += (point.x-RDownPoint.x);
			RDownPoint = point;
		}
		if( m_bIsLDown && !m_bIsRDown )
		{
			m_fTranslateZ += ( point.y - LDownPoint.y ) * 0.5f;
			LDownPoint = point;
		}
	Invalidate( TRUE );
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL CRoboSimerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_fTranslateZ += zDelta*0.05f;
	Invalidate( TRUE );

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CRoboSimerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_bIsRDown = FALSE;


	CView::OnRButtonUp(nFlags, point);
}

void CRoboSimerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	m_bIsRDown = TRUE;
	RDownPoint = point;

	CView::OnRButtonDown(nFlags, point);
}

BOOL CRoboSimerView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CRoboSimerView::Lighting(void)
{
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat  specular[] = { 0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat  specref[] =  { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat	 lightPos[] = { 50.0f, 5.0f, 70.0f, 1.0f };

	glEnable( GL_NORMALIZE );
	//glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	//glCullFace( GL_BACK );

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos );
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

void CRoboSimerView::OnTimer(UINT nIDEvent)
{
	//InputKey();
	Invalidate( TRUE );

	CView::OnTimer(nIDEvent);
}

void CRoboSimerView::InputKey(void)
{

	float DeltaTime=m_SimTimer.GetDeltaTime();
	float angle=m_SimRobot.GetAngle();

	
	static float speed=0.0;
	float deltaangle =0.0f;
	
	float tspeed = 0.0f;
	float tangle = 0.0f;
	float ospeed = 0.0f;
	float oangle = 0.0f;
	float senor=0.0f;
	float	VisionTurn=0;
	
	CVector3D v;
	v = m_TargetCube.m_PosPoint - m_SimRobot.m_PosPoint  ;
	senor = v.GetLengthXY();
	oangle = _AngleBetween( v, m_SimRobot.m_Direction )*57.29577951f;
	
	

	CPoint3D tpos=m_TargetCube.m_PosPoint;
	
	if( m_CameraDlg )
	{
		if( m_CameraDlg->point.x != -1 )
		{
			VisionTurn = 160 - m_CameraDlg->point.x;
			
			angle += VisionTurn*DeltaTime*0.56f;
		}
	}
	
	if( GetAsyncKeyState( VK_LEFT ) ) 
		//angle+=5, deltaangle = 5.2f;
		tpos.x -= 1;
		
	if( GetAsyncKeyState( VK_RIGHT ) )
		//angle-=5, deltaangle = -5.2f;
		tpos.x += 1;
	if(	GetAsyncKeyState( VK_UP ) )
		//speed += 0.5;
		tpos.y += 1;
	if( GetAsyncKeyState( VK_DOWN ) )
		//speed -= 0.5;
		tpos.y -= 1;
		
	m_TargetCube.SetPosition( tpos );
		
	m_SimRobot.SetVelocity( speed );
	m_SimRobot.m_PosPoint.x += m_SimRobot.m_Velocity.dx*DeltaTime;
	m_SimRobot.m_PosPoint.y += m_SimRobot.m_Velocity.dy*DeltaTime;
	
	CPoint3D pos=m_SimRobot.m_PosPoint;
	m_SimRobot.SetPosition( pos );

	
	if( m_Collision.CheckForCollisions( &m_SimRobot ) == PENETRATING )
	{
		m_SimRobot.m_PosPoint.x -= m_SimRobot.m_Velocity.dx*DeltaTime;
		m_SimRobot.m_PosPoint.y -= m_SimRobot.m_Velocity.dy*DeltaTime;
		angle +=85.0f*DeltaTime;
	}
	else
	{
		if( m_bIsPathMark)
		{
			CPoint3D mark=m_SimRobot.m_PosPoint;
			mark.z = 0.1;
			m_PathMark.AddMark( mark );
		}
		if( senor < 75 && oangle < 30 && oangle > -30  &&  m_CameraDlg==NULL  )
		{
			ospeed = senor*0.9;
			ospeed = ospeed > 15 ? 15 : ospeed;
			//
			float MaxAngle=75.0f*DeltaTime;
			if( oangle > MaxAngle )
			oangle = MaxAngle;
			if( oangle < -MaxAngle )
			oangle = -MaxAngle;
			angle += oangle *0.6;
		}
		else 
			ospeed =9.63f;
		speed = ospeed;
		if( senor < 15  && oangle < 30 && oangle > -30  &&  m_CameraDlg==NULL  )
			speed = 0.0f;
	}
	if( speed < 0 )
	{
		speed *= 0.8;
		if( speed > -0.00001 )
			speed = 0;
	}

	
	m_SimRobot.SetAngle( angle );
	
	
}

void CRoboSimerView::DrawText(void)
{
	glPushMatrix();
		glDisable( GL_LIGHTING );
		glDisable( GL_DEPTH_TEST );
		glColor3f(1, 1, 1);
		
		//glLoadIdentity();
		glTranslatef(-65, 38, -100);
		glScalef(0.025, 0.025, 0);
		
		char string[80]={0};
		char *p=NULL;
		//static float fLastTime = 0.0f;
		//static float fCurrentTime = m_SimTimer.GetTime();
		//float dt = fCurrentTime;
		//static int count = 0;
		//if( dt >=1 )
		//{
		//	count = 0;
		//	//fLastTime = fCurrentTime;
		//}
		////sprintf( string, "X=%.3f Y=%.3f", 
		////	m_SimRobot.m_PosPoint.x, m_SimRobot.m_PosPoint.y );
		if( m_CameraDlg )
		{
			if( m_CameraDlg->point.x != -1 )
				sprintf( string, "Target find angle: %0.3f ", 
				(160.0f-m_CameraDlg->point.x)*0.1875f );
			else
				sprintf( string, "Target lost.");
		}
		else
		{
			sprintf( string, "Camera off" );
		}
		
		p=string;
		while(*p)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p++ );
	glPopMatrix();
}

int CRoboSimerView::CheckForCollisions(void)
{
	
	int CollisionState=-1;
	CollisionState = m_Collision.CheckForCollisions( &m_SimRobot );
	if( CollisionState == PENETRATING )
		return -1;
	else
		return 0;
}

void CRoboSimerView::OnPathmark()
{
	m_bIsPathMark = !m_bIsPathMark ;
	
	if( m_bIsPathMark == false )
		m_PathMark.CleanMark(),
		m_SimRobot.SetVisionMark( FALSE );
	else
		m_SimRobot.SetVisionMark( TRUE );
}

void CRoboSimerView::OnUpdatePathmark(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_bIsPathMark );
}

void CRoboSimerView::OnVision()
{
	// TODO: 在此添加命令处理程序代码
	m_bIsRun = FALSE;
	InputKey();
	m_CameraDlg = new CCameraDlg(this);
	if( m_CameraDlg->GetSafeHwnd() == 0 )
	{
		m_CameraDlg->CreateDlg();
	}
}

afx_msg LRESULT CRoboSimerView::OnDeleteDlg(WPARAM wparam, LPARAM lparam)
{
	m_CameraDlg->DestroyWindow();
	delete m_CameraDlg;
	m_CameraDlg = NULL;
	return 0L;
}

void CRoboSimerView::OnSetPathMark()
{
	// TODO: 在此添加命令处理程序代码
	//TRACE( "\ndomodal" );
	CPathSeting aSetPathDlg;
	aSetPathDlg.m_nLength = m_PathMark.m_nMaxMarkCount;
	aSetPathDlg.m_nWidth = m_PathMark.m_fLineWidth;
	aSetPathDlg.m_nTip = m_PathMark.m_dInterval;
	aSetPathDlg.m_PathColor = m_PathMark.m_ColorRef;

	aSetPathDlg.DoModal();
	m_PathMark.m_nMaxMarkCount = aSetPathDlg.m_nLength;
	m_PathMark.m_fLineWidth = aSetPathDlg.m_nWidth;
	m_PathMark.m_dInterval = aSetPathDlg.m_nTip;
	m_PathMark.m_ColorRef = aSetPathDlg.m_PathColor;


}

void CRoboSimerView::CheckTest(CSimCube *Cube)
{
}

void CRoboSimerView::OnFilePlay()
{
	m_bIsRun = m_bIsRun ? FALSE : TRUE;

	if( m_bIsRun )
		SetTimer(1, 15, NULL);
	else
		KillTimer(1);
}

void CRoboSimerView::OnUpdateFilePlay(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_bIsRun );
}


