
#include	"stdafx.h"

#pragma comment(lib, "crypt32.lib")

#include <stdio.h>
#include <windows.h>
#include <Wincrypt.h>
#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
void MyHandleError(char *s);


//
 extern  "C"  int  myProtectData(  char  *  pbDataInput, int  cbDataInput,  char  *  pbDataOutput,  int  *  pcbDataOutput  )
{
	int  iErr  =  -1;

// Copyright (C) Microsoft.  All rights reserved.
// Encrypt data from DATA_BLOB DataIn to DATA_BLOB DataOut.
// Then decrypt to DATA_BLOB DataVerify.

//-------------------------------------------------------------------
// Declare and initialize variables.

DATA_BLOB DataIn;
DATA_BLOB DataOut;
//DATA_BLOB DataVerify;
//

memset(  &DataIn,  0,  sizeof(  DataIn  )  );
memset(  &DataOut,  0,  sizeof(  DataOut  )  );

if  (  !pbDataInput  ||  !cbDataInput  )  return  -1;

//BYTE *pbDataInput =(BYTE *)"Hello world of data protection.";
//DWORD cbDataInput = strlen((char *)pbDataInput)+1;
//
DataIn.pbData = (BYTE*)pbDataInput;    
DataIn.cbData = cbDataInput;
CRYPTPROTECT_PROMPTSTRUCT PromptStruct;
//LPWSTR pDescrOut = NULL;

//-------------------------------------------------------------------
//  Begin processing.

printf("The data to be encrypted is: %s\n",pbDataInput);

//-------------------------------------------------------------------
//  Initialize PromptStruct.

ZeroMemory(&PromptStruct, sizeof(PromptStruct));
PromptStruct.cbSize = sizeof(PromptStruct);
PromptStruct.dwPromptFlags = CRYPTPROTECT_PROMPT_ON_PROTECT;
PromptStruct.szPrompt = L"This is a user prompt.";

//-------------------------------------------------------------------
//  Begin protect phase.

if(CryptProtectData(
     &DataIn,
     L"This is the description string.", // A description string. 
     NULL,                               // Optional entropy
                                         // not used.
     NULL,                               // Reserved.
     NULL,	//&PromptStruct,                      // Pass a PromptStruct.
     0,
     &DataOut))
{
     printf("The encryption phase worked. \n");
}
else
{
    //MyHandleError("Encryption error!");
	goto  errLabel;
}

if  (  !pbDataOutput  ||  !pcbDataOutput  )  goto  errLabel;
if  (  *pcbDataOutput  <  DataOut.cbData  )  goto  errLabel;

memcpy(  pbDataOutput,  DataOut.pbData,  DataOut.cbData  );
*pcbDataOutput  =  DataOut.cbData;

//-------------------------------------------------------------------
// At this point, memcmp could be used to compare DataIn.pbData and 
// DataVerify.pbDate for equality. If the two functions worked
// correctly, the two byte strings are identical. 

iErr  =  0;

errLabel:

//-------------------------------------------------------------------
//  Clean up.

//LocalFree(pDescrOut);
if  (  DataOut.pbData  )  {
	LocalFree(DataOut.pbData);
}
//LocalFree(DataVerify.pbData);

return  iErr;

} // End of main



 //
extern  "C"  int myUnprotectData(char  *  pbDataInput,  int  cbDataInput,  char  *  pbDataOutput,  int  *  pcbDataOutput )
{
	int  iErr  =  -1;

// Copyright (C) Microsoft.  All rights reserved.
// Encrypt data from DATA_BLOB DataIn to DATA_BLOB DataOut.
// Then decrypt to DATA_BLOB DataVerify.

//-------------------------------------------------------------------
// Declare and initialize variables.

DATA_BLOB DataOut;
DATA_BLOB DataVerify;
#if  0
BYTE *pbDataInput =(BYTE *)"Hello world of data protection.";
DWORD cbDataInput = strlen((char *)pbDataInput)+1;
DataIn.pbData = pbDataInput;    
DataIn.cbData = cbDataInput;
#endif
CRYPTPROTECT_PROMPTSTRUCT PromptStruct;
LPWSTR pDescrOut = NULL;

//
memset(  &DataOut,  0,  sizeof(  DataOut  )  );
memset(  &DataVerify,  0,  sizeof(  DataVerify  )  );

//
if  (  !pbDataInput  ||  !cbDataInput  )  return  -1;

DataOut.pbData  =  (  BYTE  *  )pbDataInput;
DataOut.cbData  =  cbDataInput;

//-------------------------------------------------------------------
//  Begin processing.


//-------------------------------------------------------------------
//  Initialize PromptStruct.

ZeroMemory(&PromptStruct, sizeof(PromptStruct));
PromptStruct.cbSize = sizeof(PromptStruct);
PromptStruct.dwPromptFlags = CRYPTPROTECT_PROMPT_ON_PROTECT;
PromptStruct.szPrompt = L"This is a user prompt.";

//-------------------------------------------------------------------
//  Begin protect phase.

//-------------------------------------------------------------------
//   Begin unprotect phase.

if (CryptUnprotectData(
        &DataOut,
        &pDescrOut,
        NULL,                 // Optional entropy
        NULL,                 // Reserved
        NULL,//&PromptStruct,        // Optional PromptStruct
        0,
        &DataVerify))
{
     printf("The decrypted data is: %s\n", DataVerify.pbData);
     printf("The description of the data was: %S\n",pDescrOut);
}
else
{
    //MyHandleError("Decryption error!");
	goto  errLabel;
}

if  (  !pbDataOutput  ||  !pcbDataOutput   )  goto  errLabel;
if  (  *pcbDataOutput  <  DataVerify.cbData  )  goto errLabel;
memcpy(  pbDataOutput,  DataVerify.pbData,  DataVerify.cbData  );
*pcbDataOutput  =  DataVerify.cbData;

//-------------------------------------------------------------------
// At this point, memcmp could be used to compare DataIn.pbData and 
// DataVerify.pbDate for equality. If the two functions worked
// correctly, the two byte strings are identical. 

iErr  =  0;

errLabel:
//-------------------------------------------------------------------
//  Clean up.

if  (  pDescrOut  )  {
	LocalFree(pDescrOut);
}
//LocalFree(DataOut.pbData);
if  (  DataVerify.pbData  )  {
	LocalFree(DataVerify.pbData);
}

return  iErr;
} // End of main





//
#if  0
__declspec(  dllexport  )  void testProtectData()
{

// Copyright (C) Microsoft.  All rights reserved.
// Encrypt data from DATA_BLOB DataIn to DATA_BLOB DataOut.
// Then decrypt to DATA_BLOB DataVerify.

//-------------------------------------------------------------------
// Declare and initialize variables.

DATA_BLOB DataIn;
DATA_BLOB DataOut;
DATA_BLOB DataVerify;
BYTE *pbDataInput =(BYTE *)"Hello world of data protection.";
DWORD cbDataInput = strlen((char *)pbDataInput)+1;
DataIn.pbData = pbDataInput;    
DataIn.cbData = cbDataInput;
CRYPTPROTECT_PROMPTSTRUCT PromptStruct;
LPWSTR pDescrOut = NULL;

//-------------------------------------------------------------------
//  Begin processing.

printf("The data to be encrypted is: %s\n",pbDataInput);

//-------------------------------------------------------------------
//  Initialize PromptStruct.

ZeroMemory(&PromptStruct, sizeof(PromptStruct));
PromptStruct.cbSize = sizeof(PromptStruct);
PromptStruct.dwPromptFlags = CRYPTPROTECT_PROMPT_ON_PROTECT;
PromptStruct.szPrompt = L"This is a user prompt.";

//-------------------------------------------------------------------
//  Begin protect phase.

if(CryptProtectData(
     &DataIn,
     L"This is the description string.", // A description string. 
     NULL,                               // Optional entropy
                                         // not used.
     NULL,                               // Reserved.
     NULL,	//&PromptStruct,                      // Pass a PromptStruct.
     0,
     &DataOut))
{
     printf("The encryption phase worked. \n");
}
else
{
    MyHandleError("Encryption error!");
}
//-------------------------------------------------------------------
//   Begin unprotect phase.

if (CryptUnprotectData(
        &DataOut,
        &pDescrOut,
        NULL,                 // Optional entropy
        NULL,                 // Reserved
        &PromptStruct,        // Optional PromptStruct
        0,
        &DataVerify))
{
     printf("The decrypted data is: %s\n", DataVerify.pbData);
     printf("The description of the data was: %S\n",pDescrOut);
}
else
{
    MyHandleError("Decryption error!");
}
//-------------------------------------------------------------------
// At this point, memcmp could be used to compare DataIn.pbData and 
// DataVerify.pbDate for equality. If the two functions worked
// correctly, the two byte strings are identical. 

//-------------------------------------------------------------------
//  Clean up.

LocalFree(pDescrOut);
LocalFree(DataOut.pbData);
LocalFree(DataVerify.pbData);
} // End of main
#endif

//-------------------------------------------------------------------
//  This example uses the function MyHandleError, a simple error
//  handling function, to print an error message to the  
//  standard error (stderr) file and exit the program. 
//  For most applications, replace this function with one 
//  that does more extensive error reporting.

void MyHandleError(char *s)
{
    fprintf(stderr,"An error occurred in running the program. \n");
    fprintf(stderr,"%s\n",s);
    fprintf(stderr, "Error number %x.\n", GetLastError());
    fprintf(stderr, "Program terminating. \n");
    //exit(1);
} // End of MyHandleError


