/* bsmp.h - bssynth MIDI Player Library */

/* Copyright (c) 2002 - 2021 bismark LLC. All rights reserved */

/*
modification history
--------------------
*/

/* 
DESCRIPTION 
*/

#ifndef __INCbsmph
#define __INCbsmph

#ifdef __cplusplus
extern "C" {
#endif

/* includes */

/* defines */

/* BSMP_EXPORTS should be UNDEFINED by applications using bsmp.dll */

#ifdef BSMP_STATIC
	#define BSMP_API 
/*	#define BSMP_API */
#else /* BSMP_STATIC */
	#ifdef BSMP_EXPORTS
		#ifdef _MSC_VER
			#define BSMP_API __declspec(dllexport)
		#else /* _MSC_VER */
			#define BSMP_API 
		#endif /* _MSC_VER */
	#else /* BSMP_EXPORTS */
		#ifdef _MSC_VER
			#define BSMP_API  __declspec(dllimport)
		#else /* _MSC_VER */
			#define BSMP_API 
		#endif /* _MSC_VER */
	#endif /* BSMP_EXPORTS */
#endif /* BSMP_STATIC */

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
	BSMP_OK = 0,
	BSMP_ERR_PROTECTION = -1,
	BSMP_ERR_INVALID_HANDLE = -2,
	BSMP_ERR_FILE = -10,
	BSMP_ERR_MEMORY = -20,
	BSMP_ERR_RESOURCE = -30,
	BSMP_ERR_PARAM = -40,
	BSMP_ERR_AUDIO_DRIVER = -100,
	BSMP_ERR_DATA = -200,
	BSMP_ERR_MODULE = -800,
	BSMP_ERR_NOT_SUPPORTED = -900,
	BSMP_ERR_UNDEFINED = -901,
} BSMP_ERR;

typedef enum
{
	/* common controls: 00000 - 09999 */
	BSMP_CTRL_SET_MASTER_VOLUME = 0,	/* master volume */
	BSMP_CTRL_GET_MASTER_VOLUME,
	BSMP_CTRL_SET_MASTER_KEY = 10, /* master key */
	BSMP_CTRL_GET_MASTER_KEY,
	BSMP_CTRL_SET_MASTER_TUNE, /* master tune */
	BSMP_CTRL_GET_MASTER_TUNE,
	BSMP_CTRL_SET_SPEED = 20, /* speed control */
	BSMP_CTRL_GET_SPEED,
	BSMP_CTRL_SET_GUIDE = 30, /* guide melody control */
	BSMP_CTRL_GET_GUIDE,
	BSMP_CTRL_SET_GUIDE_MAIN_CH, /* guide melody target port/channel */
	BSMP_CTRL_GET_GUIDE_MAIN_CH,
	BSMP_CTRL_SET_GUIDE_SUB_CH, /* guide melody target port/channel */
	BSMP_CTRL_GET_GUIDE_SUB_CH,

	BSMP_CTRL_SET_REVERB = 100, /* reverb */
	BSMP_CTRL_GET_REVERB,
	BSMP_CTRL_GET_REVERB_AVAILABLE,
	BSMP_CTRL_SET_CHORUS = 110, /* chorus */
	BSMP_CTRL_GET_CHORUS,
	BSMP_CTRL_GET_CHORUS_AVAILABLE,
	BSMP_CTRL_SET_DELAY = 120, /* delay */
	BSMP_CTRL_GET_DELAY,
	BSMP_CTRL_GET_DELAY_AVAILABLE,

	BSMP_CTRL_SET_SAMPLE_RATE = 200,
	BSMP_CTRL_GET_SAMPLE_RATE,
	BSMP_CTRL_SET_BLOCK_SIZE,
	BSMP_CTRL_GET_BLOCK_SIZE,
	BSMP_CTRL_SET_CHANNELS,
	BSMP_CTRL_GET_CHANNELS,
	BSMP_CTRL_SET_POLY = 210,
	BSMP_CTRL_GET_POLY,

	/* bsse controls: 10000 - 19999 */
	BSMP_CTRL_GET_FREE_VOICES = 10000, /* <private only> */
	BSMP_CTRL_GET_PLAY_VOICES, /* <private only> */
	BSMP_CTRL_GET_RELEASE_VOICES, /* <private only> */
	BSMP_CTRL_GET_USED_VOICES, /* <private only> */

	BSMP_CTRL_SET_NO_INSTRUMENT_FIX = 10010,
	BSMP_CTRL_GET_NO_INSTRUMENT_FIX,

	BSSP_CTRL_SET_USE_BREATH_CONTROL_AS_EXPRESSION,

	BSMP_CTRL_SET_NUMBER_OF_REGIONS = 10020,
	
	BSMP_CTRL_GET_SOUND_LIBRARY_NUM = 11000,
	BSMP_CTRL_SET_SOUND_LIBRARY = BSMP_CTRL_GET_SOUND_LIBRARY_NUM + 10,
	BSMP_CTRL_SET_SOUND_LIBRARY_MEMORY = BSMP_CTRL_GET_SOUND_LIBRARY_NUM + 20,
	BSMP_CTRL_GET_SOUND_LIBRARY_MEMORY,
	BSMP_CTRL_SET_SOUND_LIBRARY_SEL = BSMP_CTRL_GET_SOUND_LIBRARY_NUM + 30,
	BSMP_CTRL_GET_SOUND_LIBRARY_SEL,

	BSMP_CTRL_GET_INSTRUMENT_NAME = 12000,
	BSMP_CTRL_SET_MUTE = 12100,
	BSMP_CTRL_GET_MUTE = 12200,
	BSMP_CTRL_SET_SOLO = 12300,
	BSMP_CTRL_GET_SOLO = 12400,

	/* bsmp controls: 20000 - 29999 */

	


	BSMP_CTRL_GET_OPEN_SL_ENGINE = 28000, /* <android only> */
	BSMP_CTRL_GET_OPEN_SL_ENGINE_INTERFACE, /* <android only> */


	/* internal use only: 99900 - 99999 */
	BSMP_CTRL_GET_BSSE_FUNC = 99900, /* <private only> */
	BSMP_CTRL_GET_BSSE_HANDLE, /* <private only> */
} BSMP_CTRL;

typedef enum
{
	/* callback command - callback_parameter */
	BSMP_CALLBACK_TYPE_NULL = -1,

	BSMP_CALLBACK_TYPE_OPEN = 0,
	BSMP_CALLBACK_TYPE_CLOSE,

	BSMP_CALLBACK_TYPE_START = 10,
	BSMP_CALLBACK_TYPE_STOP, /* (UInt32 *) errorcode */
	BSMP_CALLBACK_TYPE_SEEK,

	BSMP_CALLBACK_TYPE_CLOCK = 30,
	BSMP_CALLBACK_TYPE_TEMPO, /* (UInt32 *) usecPerBeat */
	BSMP_CALLBACK_TYPE_TIME_SIGNATURE, /* (UInt32 *) (nn/dd/cc/bb) */
	
	BSMP_CALLBACK_TYPE_CHANNEL_MESSAGE, /* (UInt32 *) (port/status/data0/data1) */
	BSMP_CALLBACK_TYPE_SYSTEM_EXCLUSIVE_MESSAGE, /* (UInt8 *) (data) */
	
} BSMP_CALLBACK_TYPE;

typedef enum
{
	/* wave file types */
	BSMP_WAVE_FILE_RIFF = 0,
	BSMP_WAVE_FILE_AIFF,
} BSMP_WAVE_FILE;

enum 
{
	/* file types */
	BSMP_FILE_FORMAT_SMF_0 = 0x0000,
	BSMP_FILE_FORMAT_SMF_1,
	BSMP_FILE_FORMAT_SMF_2, /* <not supported> */


	/* volume */
	BSMP_VOLUME_MIN = 0,
	BSMP_VOLUME_DEF = 10,
	BSMP_VOLUME_MAX = 10,

	/* key control [semitone] */
	BSMP_KEY_MIN = -24,
	BSMP_KEY_DEF = 0,
	BSMP_KEY_MAX = 24,

	/* fine tune control [cent] */
	BSMP_TUNE_MIN = -100,
	BSMP_TUNE_DEF = 0,
	BSMP_TUNE_MAX = 100,

	/* speed control [%] */
	BSMP_SPEED_MIN = -50,
	BSMP_SPEED_DEF = 0,
	BSMP_SPEED_MAX = 50,

	/* guide control */
	BSMP_GUIDE_MIN = -2,
	BSMP_GUIDE_DEF = 0,
	BSMP_GUIDE_MAX = 2,


	BSMP_KT_SPEED_MIN = -20,
	BSMP_KT_SPEED_DEF = BSMP_SPEED_DEF,
	BSMP_KT_SPEED_MAX = 20,
};

typedef enum {
	BSMP_EXPORT_STATE_NORMAL = 0,
	BSMP_EXPORT_STATE_COMPLETED,
	BSMP_EXPORT_STATE_ERROR,
} BSMP_EXPORT_STATE;

typedef enum {
	BSMP_SOUND_LIBRARY_SEL_MODE_NORAMAL = 0,
} BSMP_SOUND_LIBRARY_SEL_MODE;


/* typedefs */

typedef void *BSMP_HANDLE;

typedef void (*BSMP_CALLBACK) (BSMP_HANDLE handle, BSMP_CALLBACK_TYPE type, void *data, void *user);

typedef int (*BSMP_CALLBACK_BOUNCE) (int percent, void *user);

typedef struct {
	int index;
	LPCTSTR path;
} BSMP_SOUND_LIBRARY;

typedef struct {
	int index;
	char *address;
	unsigned long size;
} BSMP_SOUND_LIBRARY_MEMORY;

typedef struct {
	int module;
	int part;
	int index;
	BSMP_SOUND_LIBRARY_SEL_MODE mode;
} BSMP_SOUND_LIBRARY_SEL;



typedef struct {
	int size;

	/* status */
	BSMP_ERR (*initialize) (BSMP_HANDLE *handle, BSMP_CALLBACK callback, void *user, void *target, const unsigned char *key);
	BSMP_ERR (*initializeWithSoundLib) (BSMP_HANDLE *handle, BSMP_CALLBACK callback, void *user, LPCTSTR libraryPath, void *target, const unsigned char *key);
	BSMP_ERR (*initializeWithSoundLibMemory) (BSMP_HANDLE *handle, BSMP_CALLBACK callback, void *user, char *libraryAddress, unsigned long librarySize, void *target, const unsigned char *key);
	BSMP_ERR (*exit) (BSMP_HANDLE handle);

	/* wave device */
	int (*getNumDrivers) (BSMP_HANDLE handle);
	int (*getNumDevices) (BSMP_HANDLE handle, LPCTSTR driver);
	LPCTSTR (*getDriverName) (BSMP_HANDLE handle, int index);
	LPCTSTR (*getDeviceName) (BSMP_HANDLE handle, LPCTSTR driver, int index);
	void (*showDeviceControlPanel) (BSMP_HANDLE handle, LPCTSTR driver, LPCTSTR device);
	BSMP_ERR (*open) (BSMP_HANDLE handle, LPCTSTR driver, LPCTSTR device);
	BSMP_ERR (*close) (BSMP_HANDLE handle);

	/* play */
	BSMP_ERR (*start) (BSMP_HANDLE handle);
	BSMP_ERR (*stop) (BSMP_HANDLE handle);
	BSMP_ERR (*seek) (BSMP_HANDLE handle, unsigned long tick);
	BSMP_ERR (*seekWithTime) (BSMP_HANDLE handle, float time);
	int (*isPlaying) (BSMP_HANDLE handle);

	/* export */
	BSMP_ERR (*bounce) (BSMP_HANDLE handle, LPCTSTR path, BSMP_WAVE_FILE type, BSMP_CALLBACK_BOUNCE callback, void *user);

	/* file */
	BSMP_ERR (*setFile) (BSMP_HANDLE handle, LPCTSTR path);
	BSMP_ERR (*setFileMemory) (BSMP_HANDLE handle, char *address, unsigned long size);
	BSMP_ERR (*getFileMemory) (BSMP_HANDLE handle, char **address, unsigned long *size);
	BSMP_ERR (*getFileInfo) (BSMP_HANDLE handle, int *format, unsigned short *division, unsigned long *totaltick, unsigned long *totaltime);

	/* midi message insertion */
	void (*insertChannelMessage) (BSMP_HANDLE handle, unsigned char port, unsigned char status, unsigned char data1, unsigned char data2);
	void (*insertSystemExclusiveMessage) (BSMP_HANDLE handle, unsigned char port, unsigned char status, const unsigned char *data, int size);

	/* engine */
	unsigned char (*getRxChannel) (BSMP_HANDLE handle, int module, int part);
	unsigned char (*getUseForRhythmPart) (BSMP_HANDLE handle, int module, int part);
	unsigned char (*getProgramChangeMessage) (BSMP_HANDLE handle, int module, int part);
	unsigned char (*getControlChangeMessage) (BSMP_HANDLE handle, int module, int part, unsigned char control);
	unsigned char (*getPitchBendSense) (BSMP_HANDLE handle, int module, int part);
	unsigned char (*getMasterCoarseTune) (BSMP_HANDLE handle, int module, int part);
	unsigned short (*getMasterFineTune) (BSMP_HANDLE handle, int module, int part);
	unsigned short (*getPitchBend) (BSMP_HANDLE handle, int module, int part);
	unsigned char (*getMode) (BSMP_HANDLE handle, int module, int part);

	/* etc */
	BSMP_ERR (*ctrl) (BSMP_HANDLE handle, BSMP_CTRL ctrl, void *data, int size);
	void (*version) (BSMP_HANDLE handle, LPTSTR engine, int engineSize, LPTSTR player, int playerSize);
} BSMP_FUNC;

typedef BSMP_FUNC *(*BSMP_LOAD) (void);

/* function declarations */

BSMP_API BSMP_FUNC *bsmpLoad (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCbsmph */

