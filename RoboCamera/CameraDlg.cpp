// CameraDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "RoboCamera.h"
#include "Resource.h"
#include "..\include\Vision.h"



//my test
#include <shlwapi.h>
//#include <mmsystem.h>



void RGB_TO_HSV( float r, float g, float b, float *h, float *s, float *v )
//	known: r, g, b all in [0, 1]
//	find: h in [0, 360], v and s in [0, 1]
{	
	
	float m, n, delta;

	m = max( max( r, g), b );
	n = min( min( r, g), b );

	*v = m;

	if( m != 0 )
		*s = ( m -n ) / m;
	else
		*s = 0;
	if( *s == 0 )
		*h = 0;
	else
	{
		delta = m - n;
		if( r == m )
			*h = ( g - b ) / delta;
		else if( g == m )
			*h = 2 + ( b - r ) / delta;
		else if( b == m )
			*h = 4 + ( r - g ) / delta;
		*h = *h * 60;
		if( *h < 0 )
			*h = *h + 360;
	}
	
}//RGB_TO_HSV

static unsigned PixelBytes(int w, int bpp)
{
    return (w * bpp + 7) / 8;
}

static unsigned DibRowSize(int w, int bpp)
{
    return (w * bpp + 31) / 32 * 4;
}

static unsigned DibRowSize(LPBITMAPINFOHEADER pbi)
{
    return DibRowSize(pbi->biWidth, pbi->biBitCount);
}

static unsigned DibRowPadding(int w, int bpp)
{
    return DibRowSize(w, bpp) - PixelBytes(w, bpp);
}

static unsigned DibRowPadding(LPBITMAPINFOHEADER pbi)
{
    return DibRowPadding(pbi->biWidth, pbi->biBitCount);
}

static unsigned DibImageSize(int w, int h, int bpp)
{
    return h * DibRowSize(w, bpp);
}

static size_t DibSize(int w, int h, int bpp)
{
    return sizeof (BITMAPINFOHEADER) + DibImageSize(w, h, bpp);
}

static int jiggle(void)
{
    int r1 = (2 * rand() / RAND_MAX) - 1;
    int r2 = (2 * rand() / RAND_MAX) - 1;
    int r3 = (2 * rand() / RAND_MAX) - 1;
    return r1 * r2 * r3;
}
// CCameraDlg 对话框

IMPLEMENT_DYNAMIC(CCameraDlg, CDialog)
CCameraDlg::CCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCameraDlg::IDD, pParent)
	, m_pbits(NULL)
	
{
	//{{AFX_DATA_INIT(CCameraDlg)
	m_pView = NULL;
	m_pbi=NULL;
	//}}AFX_DATA_INIT
	point=(0, 0);
}

CCameraDlg::~CCameraDlg()
{
}

void CCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEOPORTAL, m_VideoPortal);
}


BEGIN_MESSAGE_MAP(CCameraDlg, CDialog)
	ON_COMMAND(IDC_INIT_VIDEO, OnInitVideo)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	
//	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CCameraDlg 消息处理程序

BOOL CCameraDlg::CreateDlg(void)
{

	return CDialog::Create( IDD_CAMERA );

}

BOOL CCameraDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	if (!m_VideoPortal.PrepareControl(_T("RoboSim"),
		_T("HKEY_CURRENT_USER\\Software\\Logitech\\RoboSim"), 0 )) 
	{
		AfxMessageBox(
			_T("Failed to initialize QuickCam Video\n\n")
			_T("Probable cause: QuickCam software was never installed, or has been deleted or damaged."),
			MB_ICONEXCLAMATION | MB_OK);
		EndDialog(-1);
	}
	PostMessage(WM_COMMAND, MAKEWPARAM(IDC_INIT_VIDEO,0), NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCameraDlg::OnDestroy()
{
	
	m_VideoPortal.StopVideoHook(0);
    m_VideoPortal.DisconnectCamera();	
	if( m_pbi )
		free(m_pbi);
	// TODO: 在此处添加消息处理程序代码
	CDialog::OnDestroy();
}
BEGIN_EVENTSINK_MAP(CCameraDlg, CDialog)
	ON_EVENT(CCameraDlg, IDC_VIDEOPORTAL, 1, PortalNotificationVideoportal, 
		VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENTSINK_MAP()

void CCameraDlg::PortalNotificationVideoportal(long lMsg, LPBITMAPINFOHEADER lParam1,
											   LPBYTE lParam2, long lParam3)
{
	// TODO: 在此处添加消息处理程序代码
	#define NOTIFICATIONMSG_VIDEOHOOK 10

    switch( lMsg ) {
    case NOTIFICATIONMSG_VIDEOHOOK:
        {
            LPBITMAPINFOHEADER lpbi =  /*(LPBITMAPINFOHEADER)*/ lParam1;
            LPBYTE lpBytes =   /*(LPBYTE)*/ lParam2;
           // unsigned long lTimeStamp = (unsigned long)lParam3;
			//static long ct = 0;
			//static float t=0;
			//static long ot=0;
			//ct = timeGetTime();
            ApplyFX(lpbi, lpBytes);
			//t = (ct - ot)/1000.0f;
			//TRACE( "\n time %f", t );
			//ot = ct;
			
        }
        break;

    default:
        break;
    } // switch
}

afx_msg void CCameraDlg::OnInitVideo(void)
{
	CWaitCursor zzzz;
	//zzzz.Restore();
    m_VideoPortal.put_PreviewMaxHeight(240);
    m_VideoPortal.put_PreviewMaxWidth(320);
    //m_VideoPortal.EnableUIElements(3, 0, 1);
    //m_VideoPortal.EnableUIElements(4, 0, 1);
    m_VideoPortal.ConnectCamera2();
	m_VideoPortal.put_EnablePreview( FALSE );

    m_VideoPortal.GetWindowRect(m_rcRect);
    ScreenToClient(m_rcRect);
    AllocateDIB(CSize(320,240));
    ComputeFX();
	m_VideoPortal.StartVideoHook(0);
	return afx_msg void();
}

CCameraDlg::CCameraDlg(CView* pView)
{
	m_pView = pView;
	m_pbi=NULL;
	m_pbits=NULL;
}

void CCameraDlg::OnOK()
{
	//if( m_pView != NULL )
	//{
	//	UpdateData( true );
	//	//m_pView->PostMessage( WM_DELETEDLG, IDOK );
	//}
	//else
	//{
	//	CDialog::OnOK();
	//}
}

void CCameraDlg::OnCancel()
{
	if( m_pView != NULL )
	{
		m_pView->PostMessage( WM_DELETEDLG, IDCANCEL );
	}
	else
	{
		CDialog::OnCancel();
	}
}

void CCameraDlg::ApplyFX(LPBITMAPINFOHEADER lpbi, LPBYTE lpBits)
{
	int W = lpbi->biWidth;
    int H = lpbi->biHeight;
    int nPels = W * H;
    int nPadBytes = DibRowPadding(lpbi);
    BYTE *dst = m_pbits;
	int x = 0, y=0, i=0;
	int cx=0,cy=0, count=0; 
	COLORREF c;
			
	WORD	h=0, l=0, s=0;
	
	for( y=H; y>0; y-- )
		for( x=0; x<W; x++ )
			
		//for (int i = 0; i < nPels; i++) 
		{	
	        
			BYTE *src = lpBits + XYmap[i];

		//	dst[0] = Bmap[src[0]];
	//       dst[1] = Gmap[src[1]];
	//       dst[2] = Rmap[src[2]];

		
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			
			if( dst[2] > (dst[1] + dst[0]) )
			{
				c = RGB( dst[2], dst[1], dst[0] );
				ColorRGBToHLS( c, &h, &l, &s );

				if( ((h>=232 && h<=239 ) || ( h>=0 && h<= 8)) 
					&& l>=60 && l<=200 && s>=110) 
				{
					dst[0] = 0 ;
					dst[1] = 255;
					dst[2] = 0;
					
					cx+=x;
					//cy+=y;
					count++;
				}
				//else
				//{
					//dst[0]= 0;
					//dst[1] = 0;
					//dst[2] = 0;
				//}
			}

			dst += 3;
			if ((i+1) % W == 0) 
			{
				// end of row, skip over padding
				dst += nPadBytes;
			}
			i++;
		}

	
	if( count > 1000 )
	{
		point.x = cx/count;
		//point.y = cy/count;
		
		//UpdateData( true );
		//m_EditDisX.
		
		//TRACE( "\nx%d, y%d, n%d", point.x, point.y ,count);
	}
	else
	{
		point.x = -1;
		point.y = -1;
	}
	

	CDC* pDC = GetDC();
	int nOldMode = SetStretchBltMode(pDC->GetSafeHdc(),COLORONCOLOR);

	StretchDIBits( pDC->GetSafeHdc(),
				   m_rcRect.left, 
				   m_rcRect.top,
				   m_rcRect.Width(), 
				   m_rcRect.Height(),
				   0,
				   0,
				   lpbi->biWidth, 
				   lpbi->biHeight,
				   m_pbits,
				   (BITMAPINFO*)m_pbi,
				   DIB_RGB_COLORS,
				   SRCCOPY);
 
	SetStretchBltMode(pDC->GetSafeHdc(),nOldMode);
	ReleaseDC(pDC);
}

void CCameraDlg::AllocateDIB(CSize sz)
{
	if (m_pbi) 
	{
        free(m_pbi); 
		m_pbi = NULL;
    }
    if (sz.cx | sz.cy) 
	{
        m_pbi = (LPBITMAPINFOHEADER)malloc( DibSize(sz.cx, sz.cy, 24));
        ASSERT(m_pbi);
        m_pbi->biSize = sizeof (BITMAPINFOHEADER);
        m_pbi->biWidth = sz.cx;
        m_pbi->biHeight = sz.cy;
        m_pbi->biPlanes = 1;
        m_pbi->biBitCount = 24;
        m_pbi->biCompression = BI_RGB;
        m_pbi->biSizeImage = /*0;*/DibImageSize(sz.cx, sz.cy, 24);
        m_pbi->biXPelsPerMeter = m_pbi->biYPelsPerMeter = 0;
        m_pbi->biClrImportant = m_pbi->biClrUsed = 0;
        m_pbits = (BYTE*)m_pbi + m_pbi->biSize;
    }
}

void CCameraDlg::ComputeFX(void)
{
	int W = m_pbi->biWidth;
    int H = m_pbi->biHeight;
    int cx = W / 2;
    int cy = H / 2;
    int nPels = W * H;
    int nRowStep = DibRowSize(m_pbi);
    int nPadBytes = DibRowPadding(m_pbi);
    int i = 0;
    for (int y = 0; y < H; y++) 
	{
        for (int x = 0; x < W; x++) 
		{
            int xt = x;
            int yt = y;
   
            XYmap[i] = xt*3 + yt*nRowStep;
            i++;
        } // for x
    } // for y
    //BYTE TRmap[16777216];
	for (i = 0; i < 256; i++) 
	{
        Rmap[i] = Gmap[i] = Bmap[i] = i;
    }
	/*for( i=0; i<256; i++ )
	{
		if( Rmap[i] >=200 || Rmap[i] <=100 )
			Rmap[i] = 0;
		else 
			Rmap[i] = 150;

		if( Gmap[i] >=200 || Gmap[i] <=100 )
			Gmap[i] = 0;
		else 
			Gmap[i] = 150;

		if( Bmap[i] >=200 || Bmap[i] <=100 )
			Bmap[i] = 0;
		else 
			Bmap[i] = 150;
	}*///
	
	//TRACE( "\n typeof bool %d", sizeof( bool) );
	//BYTE ccc[16][16][16];
	
	//float h=0.0f, s=0.0f, v=0.0f;
	//
	//int r=0, g=0, b=0, ci=0;
	//for(  r=0; r<256; r++ )
	//	for(  g=0; g<256; g++ )
	//		for(  b=0; b<256; b++ )
	//		{
	//			ci++;
	//			RGB_TO_HSV( r*0.00390625f, g*0.00390625f, 
	//			b*0.00390625f, &h, &s, &v );
	//				
	//			if( ( (h>=340 && h<=360)||(h>=0 && h<=30))   && s>0.5 && v>0.3 )
	//			{
	//				//Rmap[r] = 255 ;
	//				//Gmap[g] = 5;
	//				//Bmap[b] = 2;
	//			}
	//			else
	//			{
	//				////Rmap[r]= 0;
	//				//Gmap[g] = 0;
	//				//Bmap[b]= 0;
	//			}
	//		}
		//TRACE( "\n colorcount %d", ci );
		//	
		//RGB_TO_HSV( dst[2]*0.00390625f, dst[1]*0.00390625f, 
		//		dst[0]*0.00390625f, &h, &s, &v );
		//	
		//if( ( (h>=330 && h<=360)||(h>=0 && h<=20))   && s>0.5 && v>0.3 )
		//{
		//	dst[0] = 255 ;
		//	dst[1] = 5;
		//	dst[2] = 2;
		//}
		//else
		//{
		//	//dst[0]= 0;
		//	//dst[1] = 0;
		//	//dst[2] = 0;
		//}
}

int CCameraDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//OnInitDialog();

	return 0;
}



//void CCameraDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	m_DisX = point.x;
//	m_DisY = point.y;
//
//	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
//}
