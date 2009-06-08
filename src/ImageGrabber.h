#ifndef __INCLUDE_IMAGE_GRABBER_H
#define __INCLUDE_IMAGE_GRABBER_H

/**
 * ImageGrabber singleton.
 *
 * See class ImageGrabber for more information.
 */


#ifndef WIN32
#error ERROR: should not be compiled for non-windows build
#endif

#include "dib.h"
#include "dmtx.h"
#include "twain.h"     // Standard TWAIN header.
#include "Singleton.h"
#include "simpleini.h"

#include <windows.h>

#include <map>

/**
 * This class interfaces with the TWAIN driver to acquire images from the
 * scanner.
 */
class ImageGrabberImpl {
public:
	ImageGrabberImpl();
	~ImageGrabberImpl();

	bool twainAvailable();

	/**
	 * returns false if user pressed cancel when presented with dialog box to
	 * select a scanner.
	 */
	bool selectSourceAsDefault(const char ** err);

	HANDLE acquireImage(const char ** err, double top, double left,
			double bottom, double right);
	DmtxImage* acquireDmtxImage(const char ** err);
	void freeImage(HANDLE handle);

private:
	static const char * TWAIN_DLL_FILENAME;

	static const char * INI_SECTION_NAME;

	unsigned invokeTwain(TW_IDENTITY * srcId, unsigned long dg, unsigned dat,
			unsigned msg, void * data);

	void unloadTwain();

	void setFloatToIntPair(const float f, short & whole, unsigned short & frac);

	void getConfigFromIni(CSimpleIniA & ini);

	int GetPaletteSize(BITMAPINFOHEADER& bmInfo);

	BOOL setCapability(TW_UINT16 cap,TW_UINT16 value,BOOL sign);

	// g_hinstDLL holds this DLL's instance handle. It is initialized in response
	// to the DLL_PROCESS_ATTACH message. This handle is passed to CreateWindow()
	// when a window is created, just before opening the data source manager.
	//static HINSTANCE g_hinstDLL;

	// g_hLib holds the handle of the TWAIN_32.DLL library. It is initialized in
	// response to the DLL_PROCESS_ATTACH message. This handle is used to obtain
	// the DSM_Entry() function address in the DLL and (if not 0) to free the DLL
	// library in response to a DLL_PROCESS_DETACH message.
	HMODULE g_hLib;

	// g_pDSM_Entry holds the address of function DSM_Entry() in TWAIN_32.DLL. If
	// this address is 0, either TWAIN_32.DLL could not be loaded or there is no
	// DSM_Entry() function in TWAIN_32.DLL.
	DSMENTRYPROC g_pDSM_Entry;

	// g_AppID serves as a TWAIN identity structure that uniquely identifies the
	// application process responsible for making calls to function DSM_Entry().
	static TW_IDENTITY g_AppID;

	// properties used by the scanner
	static const int DPI = 300;
	static const int SCAN_CONTRAST = 500;
	static const int SCAN_BRIGHTNESS = 500;

	static const unsigned MAX_PLATES = 4;

	map<unsigned, ScFrame> plateFrames;
};

typedef Loki::SingletonHolder<ImageGrabberImpl> ImageGrabber;

#endif /* __INCLUDE_IMAGE_GRABBER_H */
