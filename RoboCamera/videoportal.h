#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被改写。

/////////////////////////////////////////////////////////////////////////////
// CVideoportal 包装类

class CVideoportal : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVideoportal)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xE16BE35A, 0xC958, 0x416D, { 0xBA, 0x6, 0x6A, 0x3, 0xDF, 0x22, 0x7C, 0x6A } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 属性
public:


// 操作
public:

// IVideoPortal

// Functions
//

	long PrepareControl(LPCTSTR strUniqueName, LPCTSTR strRegistryKey, long lFlags)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strUniqueName, strRegistryKey, lFlags);
		return result;
	}
	long GetCameraCount(long * plCount)
	{
		long result;
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, plCount);
		return result;
	}
	long GetCameraDescription(long lIndex, BSTR * strDescription)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lIndex, strDescription);
		return result;
	}
	long GetCameraType(long lIndex, long * lCameraType)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PI4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lIndex, lCameraType);
		return result;
	}
	long QueryCameraConnected(long lIndex, long * bConnected)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PI4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lIndex, bConnected);
		return result;
	}
	long QueryRegistryCameraIndex(long * lIndex)
	{
		long result;
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lIndex);
		return result;
	}
	long GetCameraState(long lIndex, long * plCameraState)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PI4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lIndex, plCameraState);
		return result;
	}
	long ConnectCamera(long lIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lIndex);
		return result;
	}
	long ConnectCamera2()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long DisconnectCamera()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long LoadRegistrySettings(LPCTSTR strRegistryKey)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strRegistryKey);
		return result;
	}
	long SaveRegistrySettings(LPCTSTR strRegistryKey)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strRegistryKey);
		return result;
	}
	long SetCameraPropertyLong(long lProperty, long lPropertyValue)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lProperty, lPropertyValue);
		return result;
	}
	long GetCameraPropertyLong(long lProperty, long * plPropertyValue)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PI4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lProperty, plPropertyValue);
		return result;
	}
	long PictureToFile(long lFormatFourCC, long lBitDepth, LPCTSTR strFileName, LPCTSTR strTextStamp)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lFormatFourCC, lBitDepth, strFileName, strTextStamp);
		return result;
	}
	long PictureToMemory(long lFormatFourCC, long lBitDepth, long lMemory, long * plMemorySize, LPCTSTR strTextStamp)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lFormatFourCC, lBitDepth, lMemory, plMemorySize, strTextStamp);
		return result;
	}
	long StartMovieRecording(LPCTSTR strFileName, LPCTSTR strTextStamp)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFileName, strTextStamp);
		return result;
	}
	long StopMovieRecording()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long StepCaptureAddFrame()
	{
		long result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long MovieRecordWriteSingleFrame(LPCTSTR strFileName, LPCTSTR strTextStamp)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strFileName, strTextStamp);
		return result;
	}
	void GetLastError(long * plError)
	{
		static BYTE parms[] = VTS_PI4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, plError);
	}
	long SetVideoFormat(long lWidth, long lHeight, long lBitDepth, long lFormatFourCC)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWidth, lHeight, lBitDepth, lFormatFourCC);
		return result;
	}
	long GetVideoFormat(long * plWidth, long * plHeight, long * plBitDepth, long * lFormatFourCC)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms, plWidth, plHeight, plBitDepth, lFormatFourCC);
		return result;
	}
	long ShowCameraDlg(long lCameraDlg)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lCameraDlg);
		return result;
	}
	long EnableUIElements(long lElement, long lFlags, long lEnable)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lElement, lFlags, lEnable);
		return result;
	}
	long StartVideoHook(long lFlag)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lFlag);
		return result;
	}
	long StopVideoHook(long lFlag)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lFlag);
		return result;
	}
	long SendCommand(long lCommand, long lSubCommand, long lFlags, long lParam, long lParamSize, long plParam2, long lParamSize2)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lCommand, lSubCommand, lFlags, lParam, lParamSize, plParam2, lParamSize2);
		return result;
	}
	long Query(long lCommand, long lSubCommand, long lFlags, long lParam, long lParamSize, long lParam2, long lParamSize2)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lCommand, lSubCommand, lFlags, lParam, lParamSize, lParam2, lParamSize2);
		return result;
	}
	long get_CameraConnected()
	{
		long result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_CameraIndex()
	{
		long result;
		InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_PictureSound()
	{
		CString result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_PictureSound(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_EnablePreview()
	{
		long result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_EnablePreview(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieVideoCompressionFOURCC()
	{
		long result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieVideoCompressionFOURCC(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieVideoCompressionKeyFrameInterval()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieVideoCompressionKeyFrameInterval(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieVideoCompressionQuality()
	{
		long result;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieVideoCompressionQuality(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MoviePlaybackFPS()
	{
		long result;
		InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MoviePlaybackFPS(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieAudioSamplesPerSecond()
	{
		long result;
		InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieAudioSamplesPerSecond(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieAudioChannels()
	{
		long result;
		InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieAudioChannels(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieAudioBitsPerSample()
	{
		long result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieAudioBitsPerSample(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieAudioCompressionFOURCC()
	{
		long result;
		InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieAudioCompressionFOURCC(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieAudioCompressionQuality()
	{
		long result;
		InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieAudioCompressionQuality(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieRecordAudio()
	{
		long result;
		InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieRecordAudio(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieRecordMode()
	{
		long result;
		InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieRecordMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieCreateFlags()
	{
		long result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MovieCreateFlags(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MovieRecordingActiveLocal()
	{
		long result;
		InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_MovieRecordingActiveGlobal()
	{
		long result;
		InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_CameraState()
	{
		long result;
		InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_EnableMovieRecordErrorPrompt()
	{
		long result;
		InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_EnableMovieRecordErrorPrompt(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_EnablePictureDiskErrorPrompt()
	{
		long result;
		InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_EnablePictureDiskErrorPrompt(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_StatusBarText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PreviewMaxWidth()
	{
		long result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PreviewMaxWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PreviewMaxHeight()
	{
		long result;
		InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PreviewMaxHeight(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_VideoHookStateGlobal()
	{
		long result;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_VideoHookStateLocal()
	{
		long result;
		InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}

// Properties
//



};
