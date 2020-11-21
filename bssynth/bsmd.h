/* bsmd.h - bssynth MIDI Driver Library */

/* Copyright (c) 2007 - 2019 bismark LLC. All rights reserved. */


/*
modification history
--------------------
*/

/* 
DESCRIPTION 
*/

#ifndef __INCbsmdh
#define __INCbsmdh

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

/* defines */

/* BSMD_EXPORTS should be UNDEFINED by applications using bsmd.dll */

#ifdef BSMD_STATIC
	#define BSMD_API 
/*	#define BSMD_API */
#else /* BSMD_STATIC */
	#ifdef BSMD_EXPORTS
		#ifdef _MSC_VER
			#define BSMD_API __declspec(dllexport)
		#else /* _MSC_VER */
			#define BSMD_API 
		#endif /* _MSC_VER */
	#else /* BSMD_EXPORTS */
		#ifdef _MSC_VER
			#define BSMD_API  __declspec(dllimport)
		#else /* _MSC_VER */
			#define BSMD_API 
		#endif /* _MSC_VER */
	#endif /* BSMD_EXPORTS */
#endif /* BSMD_STATIC */

#ifndef _MSC_VER
	#ifndef __TCHAR_DEFINED
		typedef char TCHAR;
		typedef char *LPSTR;
		typedef TCHAR * LPTSTR;
		typedef const TCHAR *LPCTSTR;
		#define __TCHAR_DEFINED
	#endif
#endif /* _MSC_VER */

typedef enum
{
	/* errors */
	BSMD_OK = 0,
	BSMD_ERR_PROTECTION = -1,
	BSMD_ERR_INVALID_HANDLE = -2,
	BSMD_ERR_FILE = -10,
	BSMD_ERR_MEMORY = -20,
	BSMD_ERR_RESOURCE = -30,
	BSMD_ERR_PARAM = -40,
	BSMD_ERR_AUDIO_DRIVER = -100,
	BSMD_ERR_DATA = -200,
	BSMD_ERR_MODULE = -800,
	BSMD_ERR_NOT_SUPPORTED = -900,
	BSMD_ERR_UNDEFINED = -901,
} BSMD_ERR;

typedef enum
{
	/* common controls: 00000 - 09999 */
	BSMD_CTRL_SET_MASTER_VOLUME = 0,	/* master volume */
	BSMD_CTRL_GET_MASTER_VOLUME,
	BSMD_CTRL_SET_MASTER_KEY = 10, /* master key */
	BSMD_CTRL_GET_MASTER_KEY,
	BSMD_CTRL_SET_MASTER_TUNE, /* master tune */
	BSMD_CTRL_GET_MASTER_TUNE,
	BSMD_CTRL_SET_SPEED = 20, /* speed control (Int) */
	BSMD_CTRL_GET_SPEED,
	BSMD_CTRL_SET_SPEED_ACCURATE, /* speed control (float) */
	BSMD_CTRL_GET_SPEED_ACCURATE,

	BSMD_CTRL_SET_REVERB = 100, /* reverb */
	BSMD_CTRL_GET_REVERB,
	BSMD_CTRL_GET_REVERB_AVAILABLE,
	BSMD_CTRL_SET_CHORUS = 110, /* chorus */
	BSMD_CTRL_GET_CHORUS,
	BSMD_CTRL_GET_CHORUS_AVAILABLE,
	BSMD_CTRL_SET_DELAY = 120, /* delay */
	BSMD_CTRL_GET_DELAY,
	BSMD_CTRL_GET_DELAY_AVAILABLE,

	BSMD_CTRL_SET_SAMPLE_RATE = 200,
	BSMD_CTRL_GET_SAMPLE_RATE,
	BSMD_CTRL_SET_CHANNELS,
	BSMD_CTRL_GET_CHANNELS,
	BSMD_CTRL_SET_BLOCK_SIZE,
	BSMD_CTRL_GET_BLOCK_SIZE,
	BSMD_CTRL_SET_BUFFERS,
	BSMD_CTRL_GET_BUFFERS,
	BSMD_CTRL_SET_POLY = 210,
	BSMD_CTRL_GET_POLY,

	/* bsse controls: 10000 - 19999 */
	BSMD_CTRL_GET_FREE_VOICES = 10000,
	BSMD_CTRL_GET_PLAY_VOICES,
	BSMD_CTRL_GET_RELEASE_VOICES,
	BSMD_CTRL_GET_USED_VOICES,

	BSMD_CTRL_SET_NO_INSTRUMENT_FIX = 10010,
	BSMD_CTRL_GET_NO_INSTRUMENT_FIX,
    
	BSMD_CTRL_SET_USE_BREATH_CONTROL_AS_EXPRESSION,

	BSMD_CTRL_SET_NUMBER_OF_REGIONS = 10020,

	BSMD_CTRL_GET_SOUND_LIBRARY_NUM = 11000,
	BSMD_CTRL_SET_SOUND_LIBRARY = BSMD_CTRL_GET_SOUND_LIBRARY_NUM + 10,
	BSMD_CTRL_SET_SOUND_LIBRARY_MEMORY = BSMD_CTRL_GET_SOUND_LIBRARY_NUM + 20,
	BSMD_CTRL_GET_SOUND_LIBRARY_MEMORY,
	BSMD_CTRL_SET_SOUND_LIBRARY_SEL = BSMD_CTRL_GET_SOUND_LIBRARY_NUM + 30,
	BSMD_CTRL_GET_SOUND_LIBRARY_SEL,

	BSMD_CTRL_GET_INSTRUMENT_NAME = 12000,
	BSMD_CTRL_SET_MUTE = 12100,
	BSMD_CTRL_GET_MUTE = 12200,
	BSMD_CTRL_SET_SOLO = 12300,
	BSMD_CTRL_GET_SOLO = 12400,

	/* bsmd controls: 30000 - 39999 */
	BSMD_CTRL_GET_AUDIO_UNIT = 37000, /* <iOS only> */

	/* internal use only: 99900 - 99999 */
	BSMD_CTRL_GET_BSSE_FUNC = 99900,
	BSMD_CTRL_GET_BSSE_HANDLE,
} BSMD_CTRL;

typedef enum
{
	/* callback command - callback_parameter */
	BSMD_CALLBACK_TYPE_NULL = -1,

	BSMD_CALLBACK_TYPE_OPEN = 0, /* [reserved only] */
	BSMD_CALLBACK_TYPE_CLOSE, /* [reserved only] */

	BSMD_CALLBACK_TYPE_START = 10, /* - */
	BSMD_CALLBACK_TYPE_STOP, /* (UInt32 *) errorcode */
	BSMD_CALLBACK_TYPE_FRAME,
	BSMD_CALLBACK_TYPE_FRAME_FLOAT,

	BSMD_CALLBACK_TYPE_FILE_START = 20,
	BSMD_CALLBACK_TYPE_FILE_STOP,
	BSMD_CALLBACK_TYPE_FILE_SEEK,

	BSMD_CALLBACK_TYPE_CLOCK = 30, /* - */
	BSMD_CALLBACK_TYPE_TEMPO, /* (UInt32 *) usecPerBeat */
	BSMD_CALLBACK_TYPE_TIME_SIGNATURE, /* (UInt32 *) (nn/dd/cc/bb) */

	BSMD_CALLBACK_TYPE_CHANNEL_MESSAGE, /* (UInt32 *) (port/status/data0/data1) */
	BSMD_CALLBACK_TYPE_SYSTEM_EXCLUSIVE_MESSAGE, /* (UInt8 *) (data) */
} BSMD_CALLBACK_TYPE;

enum 
{
	/* file types */
	BSMD_FILE_FORMAT_SMF_0 = 0x0000,
	BSMD_FILE_FORMAT_SMF_1,
	BSMD_FILE_FORMAT_SMF_2,

	BSMD_FILE_FORMAT_MCOMP_SMF0 = 0x0010,
	BSMD_FILE_FORMAT_MCOMP_SMF1,
	BSMD_FILE_FORMAT_MCOMP_SMF2,
	BSMD_FILE_FORMAT_MCOMP_MFMP,

	BSMD_FILE_FORMAT_SMAF_MA2 = 0x0020,
	BSMD_FILE_FORMAT_SMAF_MA3,

	BSMD_FILE_FORMAT_MFi_1 = 0x0030,
	BSMD_FILE_FORMAT_MFi_2,
	BSMD_FILE_FORMAT_MFi_3,
	BSMD_FILE_FORMAT_MFi_4,
	BSMD_FILE_FORMAT_MFi_5,

	BSMD_FILE_FORMAT_MFMP = 0x0040,

	BSMD_FILE_FORMAT_CMX = 0x0050,

	BSMD_FILE_FORMAT_MCDF = 0x0060,

	/* volume */
	BSMD_VOLUME_MIN = 0,
	BSMD_VOLUME_DEF = 10,
	BSMD_VOLUME_MAX = 10,

	/* key control */
	BSMD_KEY_MIN = -24,
	BSMD_KEY_DEF = 0,
	BSMD_KEY_MAX = 24,

	/* speed control */
	BSMD_SPEED_MIN = -50,
	BSMD_SPEED_DEF = 0,
	BSMD_SPEED_MAX = 50,

	/* fine tune control [cent] */
	BSMD_TUNE_MIN = -100,
	BSMD_TUNE_DEF = 0,
	BSMD_TUNE_MAX = 100,
};

typedef enum {
	BSMD_SOUND_LIBRARY_SEL_MODE_NORMAL = 0,
} BSMD_SOUND_LIBRARY_SEL_MODE;

/* typedefs */

typedef void *BSMD_HANDLE;

typedef void (*BSMD_CALLBACK) (BSMD_HANDLE handle, BSMD_CALLBACK_TYPE type, void *data, void *user);

typedef struct {
	int index;
	LPCTSTR path;
} BSMD_SOUND_LIBRARY;

typedef struct {
	int index;
	char *address;
	unsigned long size;
} BSMD_SOUND_LIBRARY_MEMORY;

typedef struct {
	int module;
	int part;
	int index;
	BSMD_SOUND_LIBRARY_SEL_MODE mode;
} BSMD_SOUND_LIBRARY_SEL;

typedef struct {
	long sampleFrames;
	void *data;
} BSMD_FRAME;

typedef struct {
	unsigned char port;
	unsigned char status;
	int size;
	const unsigned char *data;
} BSMD_SYSTEM_EXCLUSIVE_MESSAGE;

typedef struct {
	int size;

	/* status */
	BSMD_ERR (*initialize) (BSMD_HANDLE *handle, BSMD_CALLBACK callback, void *user, void *target, const unsigned char *key);
	BSMD_ERR (*initializeWithSoundLib) (BSMD_HANDLE *handle, BSMD_CALLBACK callback, void *user, LPCTSTR libraryPath, void *target, const unsigned char *key);
	BSMD_ERR (*initializeWithSoundLibMemory) (BSMD_HANDLE *handle, BSMD_CALLBACK callback, void *user, char *libraryAddress, unsigned long librarySize, void *target, const unsigned char *key);
	BSMD_ERR (*exit) (BSMD_HANDLE handle);

	/* wave device */
	int (*getNumDrivers) (BSMD_HANDLE handle);
	int (*getNumDevice) (BSMD_HANDLE handle, LPCTSTR driver);
	LPCTSTR (*getDriverName) (BSMD_HANDLE handle, int index);
	LPCTSTR (*getDeviceName) (BSMD_HANDLE handle, LPCTSTR driver, int index);
	void (*showDeviceControlPanel) (BSMD_HANDLE handle, LPCTSTR driver, LPCTSTR device);
	BSMD_ERR (*open) (BSMD_HANDLE handle, LPCTSTR driver, LPCTSTR device);
	BSMD_ERR (*close) (BSMD_HANDLE handle);

	/* play */
	BSMD_ERR (*start) (BSMD_HANDLE handle);
	BSMD_ERR (*stop) (BSMD_HANDLE handle);
	int (*isPlaying) (BSMD_HANDLE handle);

	/* midi message */
	void (*setChannelMessage) (BSMD_HANDLE handle, unsigned char port, unsigned char status, unsigned char data1, unsigned char data2);
	void (*setSystemExclusiveMessage) (BSMD_HANDLE handle, unsigned char port, unsigned char status, const unsigned char *data, int size);

	/* engine */
	unsigned char (*getRxChannel) (BSMD_HANDLE handle, int module, int part);
	unsigned char (*getUseForRhythmPart) (BSMD_HANDLE handle, int module, int part);
	unsigned char (*getProgramChangeMessage) (BSMD_HANDLE handle, int module, int part);
	unsigned char (*getControlChangeMessage) (BSMD_HANDLE handle, int module, int part, unsigned char control);
	unsigned char (*getPitchBendSense) (BSMD_HANDLE handle, int module, int part);
	unsigned char (*getMasterCoarseTune) (BSMD_HANDLE handle, int module, int part);
	unsigned short (*getMasterFineTune) (BSMD_HANDLE handle, int module, int part);
	unsigned short (*getPitchBend) (BSMD_HANDLE handle, int module, int part);
	unsigned char (*getMode) (BSMD_HANDLE handle, int module, int part);

	/* file */
	BSMD_ERR (*setFile) (BSMD_HANDLE handle, LPCTSTR path);
	BSMD_ERR (*setFileMemory) (BSMD_HANDLE handle, char *address, unsigned long size);
	BSMD_ERR (*getFileMemory) (BSMD_HANDLE handle, char **address, unsigned long *size);
	BSMD_ERR (*getFileInfo) (BSMD_HANDLE handle, int *format, unsigned short *division, unsigned long *totaltick, unsigned long *totaltime);
	BSMD_ERR (*startFilePlay) (BSMD_HANDLE handle);
	BSMD_ERR (*stopFilePlay) (BSMD_HANDLE handle);
	BSMD_ERR (*seekFilePlay) (BSMD_HANDLE handle, unsigned long tick);
	BSMD_ERR (*seekFilePlayWithTime) (BSMD_HANDLE handle, float time);
	int (*isFilePlaying) (BSMD_HANDLE handle);

	/* etc */
	BSMD_ERR (*ctrl) (BSMD_HANDLE handle, BSMD_CTRL ctrl, void *data, int size);
	void (*version) (BSMD_HANDLE handle, LPTSTR engine, int engineSize, LPTSTR player, int playerSize);
} BSMD_FUNC;

typedef BSMD_FUNC *(*BSMD_LOAD) (void);

/* function declarations */

BSMD_API BSMD_FUNC *bsmdLoad (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCbsmdh */

