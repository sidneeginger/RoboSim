#include "StdAfx.h"
#include "..\include\physics.h"

CSimTimer::CSimTimer(void)
: m_lStartMilliseconds(0)
, m_lCurrentMilliseconds(0)
, m_fLastTime(0)
, m_fDeltaTime(0)
 
{
	m_bIsRun = FALSE;
	m_fMaxDeltaTime=0.13f;
}

CSimTimer::~CSimTimer(void)
{
}

void CSimTimer::Start(void)
{
	m_bIsRun = TRUE;
	m_lStartMilliseconds = timeGetTime();
	m_fLastTime = GetTime();

}

float CSimTimer::GetTime(void)
{
	if( m_bIsRun )
	{
		m_lCurrentMilliseconds = timeGetTime();
		return (float)(m_lCurrentMilliseconds - m_lStartMilliseconds) / 1000.0f;
	}
	else
		return 0.0f;
}

void CSimTimer::Stop(void)
{
	m_lStartMilliseconds = m_lCurrentMilliseconds = 0;
	m_bIsRun = FALSE;
}

float CSimTimer::GetDeltaTime(void)
{
	float time = GetTime();
	m_fDeltaTime = time - m_fLastTime;
	if( m_fDeltaTime > m_fMaxDeltaTime )
		m_fDeltaTime = m_fMaxDeltaTime;
	m_fLastTime = time;
	return m_fDeltaTime;
}

void CSimTimer::SetMaxDeltaTime(float fDeltaTime)
{
	m_fMaxDeltaTime = fDeltaTime;
}
