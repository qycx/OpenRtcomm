
#include	<windows.h>
#include	"qyEncCommon.h"
int  traceLogA(  char  *  fmt,  ...  );

 static  int  do_rand(  unsigned  long  *  ctx  )
{
	return  (  (  *ctx  =  *ctx  *  1103515245  +  12345  )  %  (  (  unsigned  long  int  )RAND_MAX  +  1  )  );
}

 
#include <stdlib.h>
 
static unsigned long int next = 0x1971120;
 
 int  qyRand(  void  )
{
	long hi, lo, x;

	hi = next / 127773L;
	lo = next % 127773L;
	x = 16807L * lo - 2836L * hi;
	if (x <= 0)
		x += 0x7fffffffL;
	return ((next = x) % ((unsigned long)RAND_MAX + 1));
}
 
 void  qySrand(unsigned int seed)
{
 	next = seed;
}

 void  qyFakeBuf(  char  *  input,  unsigned  int  size,  char  *  output  )
{
	 unsigned  long	 l;
	 unsigned  int	i;

	 if  (  !size  )  return;
	 for  (  i  =  0;  i  <  2  *  size;  i  =  i  +  2  )  {
		  l  =  qyRand(  );
		  memcpy(  output,  (  char  *  )&l,  2  );
	 }
	 for  (  i  =  0;  i  <  size;  i  ++  )  {
		  output[i  +  1]  =  (  char  )input;
	 }

	 return;

}

 int  qyUnfakeBuf(  char  *  input,  unsigned  int  size,  char  *  output  )
{
	 unsigned  int  i;

	 if  (  !size  ||  size  %  2  )  return  -1;
	 for  (  i  =  0;  i  <  size  /  2;  i  ++  )  {
		  output[i]  =  input[i  +  1];
	 }

	 return  0;
}

 int  testRand( )
{
    int i;

    traceLogA(  "seeding rand with 0x19610910: "  );
    qySrand(0x19610910);

    traceLogA("generating three pseudo-random numbers:");
    for (  i  =  0;  i  <  3;  i  ++  )  {
		traceLogA(  "next random number = %d\n",  qyRand(  )  );
    }

    
    return 0;
}



