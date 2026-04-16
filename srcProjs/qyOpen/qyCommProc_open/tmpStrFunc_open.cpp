
#include    "stdafx.h"
#include	<string.h>
#include	<tchar.h>
#include	<stdlib.h>

#include    "tmpStrFunc.h"






 extern  "C"  void  tTrim(  TCHAR  *  buf  )
{
        TCHAR			*	p;
		unsigned  int		len		=	_tcslen(  buf  );

		if  (  !buf  ||  !(  len  =  _tcslen(  buf  )  )  )  return;
        p  =  buf  +  len  -  1;

        while  (  _istspace(  *p  )  &&  p  >=  buf  )  p  --;
        p[1]  =  0;

        if  (  p  >=  buf  )  {
            p  =  buf;
            while  (  _istspace(  *p  )  )  p  ++;
			_tcscpy(  buf,  p  );
        }

        return;

}

