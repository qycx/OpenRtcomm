// Comm.h: interface for the CComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(COMM_H__)
#define COMM_H__

HANDLE  openComm(  LPCTSTR  pPort,  int nBaudRate=57600, int nParity=NOPARITY, int nByteSize=8, int nStopBits=ONESTOPBIT  );
void  closeComm(  HANDLE  hComm  );
int  readComm(  HANDLE  hComm,  void* pData, int nLength);
int  writeComm(  HANDLE  hComm,  void* pData, int nLength);

#endif // !defined(COMM_H__)
