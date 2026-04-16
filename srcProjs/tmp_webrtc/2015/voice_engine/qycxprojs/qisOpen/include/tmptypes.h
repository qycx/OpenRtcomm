#define  HACMDRIVERID  HANDLE
#define  HACMSTREAM  HANDLE

typedef unsigned long       DWORD;
typedef unsigned short      WORD;


#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef struct tWAVEFORMATEX
{
	WORD    wFormatTag;        /* format type */
	WORD    nChannels;         /* number of channels (i.e. mono, stereo...) */
	DWORD   nSamplesPerSec;    /* sample rate */
	DWORD   nAvgBytesPerSec;   /* for buffer estimation */
	WORD    nBlockAlign;       /* block size of data */
	WORD    wBitsPerSample;    /* Number of bits per sample of mono data */
	WORD    cbSize;            /* The count in bytes of the size of
							   extra information (after cbSize) */

} WAVEFORMATEX;
typedef WAVEFORMATEX       *PWAVEFORMATEX;
//typedef WAVEFORMATEX NEAR *NPWAVEFORMATEX;
//typedef WAVEFORMATEX FAR  *LPWAVEFORMATEX;
#endif /* _WAVEFORMATEX_ */

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM         1
#endif
