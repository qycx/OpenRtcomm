
//  Appendice C: il codice di D3Des.c    
//  Successivo: Appendice D: il codice Su: Computer Virus Precedente: Appendice B: 
//  il codice 

//  Appendice C: il codice di D3Des.c
/* d3des.h -
 *
 *      Headers and defines for d3des.c
 *      Graven Imagery, 1992.
 *
 * Copyright (c) 1988,1989,1990,1991,1992 by Richard Outerbridge
 *      (GEnie : OUTER; CIS : [71755,204])
 */

#ifndef  __D3DES_H__
#define  __D3DES_H__	/*  {  */

#ifdef  __cplusplus
  extern  "C"  {
#endif


#define D2_DES          /* include double-length support */
#define D3_DES          /* include triple-length support */
#ifdef D3_DES
#ifndef D2_DES
#define D2_DES          /* D2_DES is needed for D3_DES */
#endif
#endif
#define EN0     0       /* MODE == encrypt */
#define DE1     1       /* MODE == decrypt */

/* A useful alias on 68000-ish machines, but NOT USED HERE. */

typedef union {
	unsigned long blok[2];
	unsigned short word[4];
	unsigned char byte[8];
	} M68K;

extern void deskey();
/*                    hexkey[8]     MODE unsigned char *, shor
 * Sets the internal key register according to the hexadecimal
 * key contained in the 8 bytes of hexkey, according to the DES,
 * for encryption or decryption according to MODE.
 */

extern void usekey();
/*                  cookedkey[32] unsigned long *
 * Loads the internal key register with the data in cookedkey.
 */

extern void cpkey();
/*                 cookedkey[32] unsigned long *
 * Copies the contents of the internal key register into the storage
 * located at &cookedkey[0].
 */

extern void desd3();
/*                  from[8]           to[8] unsigned char *, unsigned char 
 * Encrypts/Decrypts (according to the key currently loaded in the
 * internal key register) one block of eight bytes at address 'from'
 * into the block at address 'to'.  They can be the same.
 */

#ifdef D2_DES

#define desDkey(a,b)    des2key((a),(b))
extern void des2key();
/*                    hexkey[16]     MODE unsigned char *, short
 * Sets the internal key registerS according to the hexadecimal
 * keyS contained in the 16 bytes of hexkey, according to the DES,
 * for DOUBLE encryption or decryption according to MODE.
 * NOTE: this clobbers all three key registers!
 */

extern void Ddes();
/*                  from[8]           to[8] unsigned char *, unsigned char 
 * Encrypts/Decrypts (according to the keyS currently loaded in the
 * internal key registerS) one block of eight bytes at address 'from'
 * into the block at address 'to'.  They can be the same.
 */

extern void D2des();
/*                  from[16]          to[16] unsigned char *, unsigned char 
 * Encrypts/Decrypts (according to the keyS currently loaded in the
 * internal key registerS) one block of SIXTEEN bytes at address 'from'
 * into the block at address 'to'.  They can be the same.
 */

extern void makekey();
/*              *password,      single-length key[8] char *, unsigned char *
 * With a double-length default key, this routine hashes a NULL-terminated
 * string into an eight-byte random-looking key, suitable for use with the
 * deskey() routine.
 */

#define makeDkey(a,b)   make2key((a),(b))
extern void make2key();
/*              *password,      double-length key[16] char *, unsigned char *
 * With a double-length default key, this routine hashes a NULL-terminated
 * string into a sixteen-byte random-looking key, suitable for use with the
 * des2key() routine.
 */

#ifndef D3_DES  /* D2_DES only */

#define useDkey(a)      use2key((a))
#define cpDkey(a)       cp2key((a))

extern void use2key();
/*                  cookedkey[64] unsigned long *
 * Loads the internal key registerS with the data in cookedkey.
 * NOTE: this clobbers all three key registers!
 */
extern void cp2key();
/*                 cookedkey[64] unsigned long *
 * Copies the contents of the internal key registerS into the storage
 * located at &cookedkey[0].
 */

#else   /* D3_DES too */

#define useDkey(a)      use3key((a))
#define cpDkey(a)       cp3key((a))

extern void des3key();
/*                    hexkey[24]     MODE unsigned char *, short
 * Sets the internal key registerS according to the hexadecimal
 * keyS contained in the 24 bytes of hexkey, according to the DES,
 * for DOUBLE encryption or decryption according to MODE.
 */

extern void use3key();
/*                  cookedkey[96] unsigned long *
 * Loads the 3 internal key registerS with the data in cookedkey.
 */

extern void cp3key();
/*                 cookedkey[96] unsigned long *
 * Copies the contents of the 3 internal key registerS into the storage
 * located at &cookedkey[0].
 */

extern void make3key();
/*              *password,      triple-length key[24] char *, unsigned char *
 * With a triple-length default key, this routine hashes a NULL-terminated
 * string into a twenty-four-byte random-looking key, suitable for use with
 * the des3key() routine. */
#endif  /* D3_DES */
#endif  /* D2_DES */


typedef  struct  {
				 unsigned  long  ek[32];
				 unsigned  long  dk[32];
}		 des_ctx;


void  des_key(  des_ctx  *  dc,  unsigned  char  *  key  );
void  des_enc(  des_ctx  *  dc,  unsigned  char  *  data,  int  blocks  );
void  des_dec(  des_ctx  *  dc,  unsigned  char  *  data,  int  blocks  );





#ifdef  __cplusplus
  }
#endif

#endif  /*  }  */

/* d3des.h V5.09 rwo 9208.04 15:06 Graven Imagery*/

