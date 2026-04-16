

/* D3DES (V5.09) -
 *
 * A portable, public domain, version of the Data Encryption Standard.
 *
 * Written with Symantec's THINK (Lightspeed) C by Richard Outerbridge.
 * Thanks to: Dan Hoey for his excellent Initial and Inverse permutation
 * code;  Jim Gillogly & Phil Karn for the DES key schedule code; Dennis
 * Ferguson, Eric Young and Dana How for comparing notes; and Ray Lau,
 * for humouring me on.
 *
 * Copyright (c) 1988,1989,1990,1991,1992 by Richard Outerbridge.
 * (GEnie : OUTER; CIS : [71755,204]) Graven Imagery, 1992.
 */

#include	"myd3des.h"

static void scrunch();
static void unscrun();
static void desfunc();
static void cookey();
static unsigned long KnL[32] = { 0L };
static unsigned long KnR[32] = { 0L };
static unsigned long Kn3[32] = { 0L };
static unsigned char Df_Key[24] = {
	0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
	0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,
	0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67 };

static unsigned short bytebit[8]        = {
	0200, 0100, 040, 020, 010, 04, 02, 01 };

static unsigned long bigbyte[24] = {
	0x800000L,      0x400000L,      0x200000L,      0x100000L,
	0x80000L,       0x40000L,       0x20000L,       0x10000L,
	0x8000L,        0x4000L,        0x2000L,        0x1000L,
	0x800L,         0x400L,         0x200L,         0x100L,
	0x80L,          0x40L,          0x20L,          0x10L,
	0x8L,           0x4L,           0x2L,           0x1L    };

/* Use the key schedule specified in the Standard (ANSI X3.92-1981). */

static unsigned char pc1[56] = {
	56, 48, 40, 32, 24, 16,  8,      0, 57, 49, 41, 33, 25, 17,
	 9,  1, 58, 50, 42, 34, 26,     18, 10,  2, 59, 51, 43, 35,
	62, 54, 46, 38, 30, 22, 14,      6, 61, 53, 45, 37, 29, 21,
	13,  5, 60, 52, 44, 36, 28,     20, 12,  4, 27, 19, 11,  3 };

static unsigned char totrot[16] = {
	1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28 };

static unsigned char pc2[48] = {
	13, 16, 10, 23,  0,  4,  2, 27, 14,  5, 20,  9,
	22, 18, 11,  3, 25,  7, 15,  6, 26, 19, 12,  1,
	40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31 };


void deskey(key, edf)   /* Thanks to James Gillogly & Phil Karn! */
unsigned char *key;
short edf;
/*
 * Effettua la schedulazione delle sottochiavi, da PC1 a PC2,
 * dispondendo la sottochiave sinistra e la sottoschiave
 * destra in 2 long.
*/
{
	register int i, j, l, m, n;
	unsigned char pc1m[56], pcr[56];
	unsigned long kn[32];

	for ( j = 0; j < 56; j++ ) {
		l = pc1[j];
		m = l & 07;
		pc1m[j] = (key[l >> 3] & bytebit[m]) ? 1 : 0;
		}
	for( i = 0; i < 16; i++ ) {
		if( edf == DE1 ) m = (15 - i) << 1;
		else m = i << 1;
		n = m + 1;
		kn[m] = kn[n] = 0L;
		for( j = 0; j < 28; j++ ) {
			l = j + totrot[i];
			if( l < 28 ) pcr[j] = pc1m[l];
			else pcr[j] = pc1m[l - 28];
			}
		for( j = 28; j < 56; j++ ) {
		    l = j + totrot[i];
		    if( l < 56 ) pcr[j] = pc1m[l];
		    else pcr[j] = pc1m[l - 28];
		    }
		for( j = 0; j < 24; j++ ) {
			if( pcr[pc2[j]] ) kn[m] |= bigbyte[j];
			if( pcr[pc2[j+24]] ) kn[n] |= bigbyte[j];
			}
		}
	cookey(kn);
	return;
	}



static void cookey(raw1)
register unsigned long *raw1;
/*
 * La seguente funzione riorganizza la rappresentazione delle sottochiavi DES
 * mischiando i blocchi della sottochiave destra e della sottochaive sinistra
 * nel modo che e' stato mostrato.
*/
{
	register unsigned long *cook, *raw0;
	unsigned long dough[32];
	register int i;

	cook = dough;
	for( i = 0; i < 16; i++, raw1++ ) {
		raw0 = raw1++;
		*cook    = (*raw0 & 0x00fc0000L) << 6;
		*cook   |= (*raw0 & 0x00000fc0L) << 10;
		*cook   |= (*raw1 & 0x00fc0000L) >> 10;
		*cook++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cook    = (*raw0 & 0x0003f000L) << 12;
		*cook   |= (*raw0 & 0x0000003fL) << 16;
		*cook   |= (*raw1 & 0x0003f000L) >> 4;
		*cook++ |= (*raw1 & 0x0000003fL);
		}
	usekey(dough);
	return;
	}


/*
 * la funzione che segue non viene chiamata
*/
void cpkey(into)
register unsigned long *into;
{
	register unsigned long *from, *endp;

	from = KnL, endp = &KnL[32];
	while( from < endp ) *into++ = *from++;
	return;
	}

void usekey(from)
register unsigned long *from;
/* E' usata per copiare il contenuto del vettore 'from' che contiene le 16 sottochiavi
   schedulate nel vettore, variabile globale, KnL
*/
{
	register unsigned long *to, *endp;

	to = KnL, endp = &KnL[32];
	while( to < endp ) *to++ = *from++;
	return;
	}


void desd3(inblock, outblock)
unsigned char *inblock, /* e' il blocco di 64 bit da cifrare */
	      *outblock; /* conterra' il blocco di 64 bit cifrato */

/* 
 * E' la funzione centrale: chiamata subito dopo la
 *  schedulazione delle sottochiavi.
*/
{ 
	unsigned long work[2];

	scrunch(inblock, work);
	desfunc(work, KnL);      /* KnL e' una variabile globale. Contiene le sottochiavi */ 
	unscrun(work, outblock);
	return;
	}


static void scrunch(outof, into)
register unsigned char *outof; /* contiene l'input alla funzione */
register unsigned long *into;  /* conterra' alla fine l'output */
/* 
 * Trasferisce il vettore di 8 caratteri d'input 
 * in due long, quelli sui quali si agira' nel corso della
 * cifratura. 
*/
{
	*into    = (*outof++ & 0xffL) << 24;
	*into   |= (*outof++ & 0xffL) << 16;
	*into   |= (*outof++ & 0xffL) << 8;
	*into++ |= (*outof++ & 0xffL);
	*into    = (*outof++ & 0xffL) << 24;
	*into   |= (*outof++ & 0xffL) << 16;
	*into   |= (*outof++ & 0xffL) << 8;
	*into   |= (*outof   & 0xffL);
	return;
	}



static void unscrun(outof, into)
register unsigned long *outof;/* input della funzione, contiene il blocco cifrato */
register unsigned char *into; /* output della funzione */
/* 
 * Trasferisce i 64 bit di testo cifrato, (contenuto in 2 long)
 * in un vettore di 8 caratteri 
*/

{
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >>  8) & 0xffL;
	*into++ =  *outof++      & 0xffL;
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >>  8) & 0xffL;
	*into   =  *outof        & 0xffL;
	return;
	}


/*
 * I seguenti 8 vettori costituiscono le 8 SPBOX utilizzate dall'implementazione
*/
  

static unsigned long SP1[64] = {
	0x01010400L, 0x00000000L, 0x00010000L, 0x01010404L,
	0x01010004L, 0x00010404L, 0x00000004L, 0x00010000L,
	0x00000400L, 0x01010400L, 0x01010404L, 0x00000400L,
	0x01000404L, 0x01010004L, 0x01000000L, 0x00000004L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00010400L,
	0x00010400L, 0x01010000L, 0x01010000L, 0x01000404L,
	0x00010004L, 0x01000004L, 0x01000004L, 0x00010004L,
	0x00000000L, 0x00000404L, 0x00010404L, 0x01000000L,
	0x00010000L, 0x01010404L, 0x00000004L, 0x01010000L,
	0x01010400L, 0x01000000L, 0x01000000L, 0x00000400L,
	0x01010004L, 0x00010000L, 0x00010400L, 0x01000004L,
	0x00000400L, 0x00000004L, 0x01000404L, 0x00010404L,
	0x01010404L, 0x00010004L, 0x01010000L, 0x01000404L,
	0x01000004L, 0x00000404L, 0x00010404L, 0x01010400L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00000000L,
	0x00010004L, 0x00010400L, 0x00000000L, 0x01010004L };

static unsigned long SP2[64] = {
	0x80108020L, 0x80008000L, 0x00008000L, 0x00108020L,
	0x00100000L, 0x00000020L, 0x80100020L, 0x80008020L,
	0x80000020L, 0x80108020L, 0x80108000L, 0x80000000L,
	0x80008000L, 0x00100000L, 0x00000020L, 0x80100020L,
	0x00108000L, 0x00100020L, 0x80008020L, 0x00000000L,
	0x80000000L, 0x00008000L, 0x00108020L, 0x80100000L,
	0x00100020L, 0x80000020L, 0x00000000L, 0x00108000L,
	0x00008020L, 0x80108000L, 0x80100000L, 0x00008020L,
	0x00000000L, 0x00108020L, 0x80100020L, 0x00100000L,
	0x80008020L, 0x80100000L, 0x80108000L, 0x00008000L,
	0x80100000L, 0x80008000L, 0x00000020L, 0x80108020L,
	0x00108020L, 0x00000020L, 0x00008000L, 0x80000000L,
	0x00008020L, 0x80108000L, 0x00100000L, 0x80000020L,
	0x00100020L, 0x80008020L, 0x80000020L, 0x00100020L,
	0x00108000L, 0x00000000L, 0x80008000L, 0x00008020L,
	0x80000000L, 0x80100020L, 0x80108020L, 0x00108000L };

static unsigned long SP3[64] = {
	0x00000208L, 0x08020200L, 0x00000000L, 0x08020008L,
	0x08000200L, 0x00000000L, 0x00020208L, 0x08000200L,
	0x00020008L, 0x08000008L, 0x08000008L, 0x00020000L,
	0x08020208L, 0x00020008L, 0x08020000L, 0x00000208L,
	0x08000000L, 0x00000008L, 0x08020200L, 0x00000200L,
	0x00020200L, 0x08020000L, 0x08020008L, 0x00020208L,
	0x08000208L, 0x00020200L, 0x00020000L, 0x08000208L,
	0x00000008L, 0x08020208L, 0x00000200L, 0x08000000L,
	0x08020200L, 0x08000000L, 0x00020008L, 0x00000208L,
	0x00020000L, 0x08020200L, 0x08000200L, 0x00000000L,
	0x00000200L, 0x00020008L, 0x08020208L, 0x08000200L,
	0x08000008L, 0x00000200L, 0x00000000L, 0x08020008L,
	0x08000208L, 0x00020000L, 0x08000000L, 0x08020208L,
	0x00000008L, 0x00020208L, 0x00020200L, 0x08000008L,
	0x08020000L, 0x08000208L, 0x00000208L, 0x08020000L,
	0x00020208L, 0x00000008L, 0x08020008L, 0x00020200L };

static unsigned long SP4[64] = {
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802080L, 0x00800081L, 0x00800001L, 0x00002001L,
	0x00000000L, 0x00802000L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00800080L, 0x00800001L,
	0x00000001L, 0x00002000L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002001L, 0x00002080L,
	0x00800081L, 0x00000001L, 0x00002080L, 0x00800080L,
	0x00002000L, 0x00802080L, 0x00802081L, 0x00000081L,
	0x00800080L, 0x00800001L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00000000L, 0x00802000L,
	0x00002080L, 0x00800080L, 0x00800081L, 0x00000001L,
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802081L, 0x00000081L, 0x00000001L, 0x00002000L,
	0x00800001L, 0x00002001L, 0x00802080L, 0x00800081L,
	0x00002001L, 0x00002080L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002000L, 0x00802080L };

static unsigned long SP5[64] = {
	0x00000100L, 0x02080100L, 0x02080000L, 0x42000100L,
	0x00080000L, 0x00000100L, 0x40000000L, 0x02080000L,
	0x40080100L, 0x00080000L, 0x02000100L, 0x40080100L,
	0x42000100L, 0x42080000L, 0x00080100L, 0x40000000L,
	0x02000000L, 0x40080000L, 0x40080000L, 0x00000000L,
	0x40000100L, 0x42080100L, 0x42080100L, 0x02000100L,
	0x42080000L, 0x40000100L, 0x00000000L, 0x42000000L,
	0x02080100L, 0x02000000L, 0x42000000L, 0x00080100L,
	0x00080000L, 0x42000100L, 0x00000100L, 0x02000000L,
	0x40000000L, 0x02080000L, 0x42000100L, 0x40080100L,
	0x02000100L, 0x40000000L, 0x42080000L, 0x02080100L,
	0x40080100L, 0x00000100L, 0x02000000L, 0x42080000L,
	0x42080100L, 0x00080100L, 0x42000000L, 0x42080100L,
	0x02080000L, 0x00000000L, 0x40080000L, 0x42000000L,
	0x00080100L, 0x02000100L, 0x40000100L, 0x00080000L,
	0x00000000L, 0x40080000L, 0x02080100L, 0x40000100L };

static unsigned long SP6[64] = {
	0x20000010L, 0x20400000L, 0x00004000L, 0x20404010L,
	0x20400000L, 0x00000010L, 0x20404010L, 0x00400000L,
	0x20004000L, 0x00404010L, 0x00400000L, 0x20000010L,
	0x00400010L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x00000000L, 0x00400010L, 0x20004010L, 0x00004000L,
	0x00404000L, 0x20004010L, 0x00000010L, 0x20400010L,
	0x20400010L, 0x00000000L, 0x00404010L, 0x20404000L,
	0x00004010L, 0x00404000L, 0x20404000L, 0x20000000L,
	0x20004000L, 0x00000010L, 0x20400010L, 0x00404000L,
	0x20404010L, 0x00400000L, 0x00004010L, 0x20000010L,
	0x00400000L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x20000010L, 0x20404010L, 0x00404000L, 0x20400000L,
	0x00404010L, 0x20404000L, 0x00000000L, 0x20400010L,
	0x00000010L, 0x00004000L, 0x20400000L, 0x00404010L,
	0x00004000L, 0x00400010L, 0x20004010L, 0x00000000L,
	0x20404000L, 0x20000000L, 0x00400010L, 0x20004010L };

static unsigned long SP7[64] = {
	0x00200000L, 0x04200002L, 0x04000802L, 0x00000000L,
	0x00000800L, 0x04000802L, 0x00200802L, 0x04200800L,
	0x04200802L, 0x00200000L, 0x00000000L, 0x04000002L,
	0x00000002L, 0x04000000L, 0x04200002L, 0x00000802L,
	0x04000800L, 0x00200802L, 0x00200002L, 0x04000800L,
	0x04000002L, 0x04200000L, 0x04200800L, 0x00200002L,
	0x04200000L, 0x00000800L, 0x00000802L, 0x04200802L,
	0x00200800L, 0x00000002L, 0x04000000L, 0x00200800L,
	0x04000000L, 0x00200800L, 0x00200000L, 0x04000802L,
	0x04000802L, 0x04200002L, 0x04200002L, 0x00000002L,
	0x00200002L, 0x04000000L, 0x04000800L, 0x00200000L,
	0x04200800L, 0x00000802L, 0x00200802L, 0x04200800L,
	0x00000802L, 0x04000002L, 0x04200802L, 0x04200000L,
	0x00200800L, 0x00000000L, 0x00000002L, 0x04200802L,
	0x00000000L, 0x00200802L, 0x04200000L, 0x00000800L,
	0x04000002L, 0x04000800L, 0x00000800L, 0x00200002L };

static unsigned long SP8[64] = {
	0x10001040L, 0x00001000L, 0x00040000L, 0x10041040L,
	0x10000000L, 0x10001040L, 0x00000040L, 0x10000000L,
	0x00040040L, 0x10040000L, 0x10041040L, 0x00041000L,
	0x10041000L, 0x00041040L, 0x00001000L, 0x00000040L,
	0x10040000L, 0x10000040L, 0x10001000L, 0x00001040L,
	0x00041000L, 0x00040040L, 0x10040040L, 0x10041000L,
	0x00001040L, 0x00000000L, 0x00000000L, 0x10040040L,
	0x10000040L, 0x10001000L, 0x00041040L, 0x00040000L,
	0x00041040L, 0x00040000L, 0x10041000L, 0x00001000L,
	0x00000040L, 0x10040040L, 0x00001000L, 0x00041040L,
	0x10001000L, 0x00000040L, 0x10000040L, 0x10040000L,
	0x10040040L, 0x10000000L, 0x00040000L, 0x10001040L,
	0x00000000L, 0x10041040L, 0x00040040L, 0x10000040L,
	0x10040000L, 0x10001000L, 0x10001040L, 0x00000000L,
	0x10041040L, 0x00041000L, 0x00041000L, 0x00001040L,
	0x00001040L, 0x00040040L, 0x10000000L, 0x10041000L };




static void desfunc(block, keys)
register unsigned long *block, /* E' un vettore di 2 long ed e' l'output di 'scrunch' */
			*keys; /* contiene le 16 sottochiavi */
/* 
* E' la procedura che effettua la cifratura di un blocco di 64 bit 'block' conoscendo il blocco
* e le sottochiavi schedulate 
*/
{
	register unsigned long fval, work, right, leftt;
	register int round;
/*
 * CALCOLO DI IP 
*/
	leftt = block[0];                                            
	right = block[1];                                            
/* Primo Passo */ 
	work = ((leftt >> 4) ^ right) & 0x0f0f0f0fL;                 
	right ^= work;                                               
	leftt ^= (work << 4);                                        
/* Secondo Passo */
	work = ((leftt >> 16) ^ right) & 0x0000ffffL;                
	right ^= work;                                               
	leftt ^= (work << 16);                                       
/* Terzo Passo */
	work = ((right >> 2) ^ leftt) & 0x33333333L;                 
	leftt ^= work;                                               
	right ^= (work << 2);                                        
/* Quarto Passo */
	work = ((right >> 8) ^ leftt) & 0x00ff00ffL;                 
	leftt ^= work;                                               
	right ^= (work << 8);                                        
/* Quinto Passo */
	right = ((right << 1) | ((right >> 31) & 1L)) & 0xffffffffL; 
	work = (leftt ^ right) & 0xaaaaaaaaL;                        
	leftt ^= work;                                               
/* Sesto Passo */
	right ^= work;                                               
	leftt = ((leftt << 1) | ((leftt >> 31) & 1L)) & 0xffffffffL; 
/*
 * Le iterazioni 
*/
	for( round = 0; round < 8; round++ ) {                    
/* 
** primo round ** 
*/                                
		work  = (right << 28) | (right >> 4); 
/* work=xxE1xxE3xxE5xxE7 */
		work ^= *keys++;
		fval  = SP7[ work                & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
/* right=xxE2xxE4xxE6xxE8 */
		work  = right ^ *keys++;          
		fval |= SP8[ work                & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		leftt ^= fval;
/* 
 ** secondo round ** 
*/
		work  = (leftt << 28) | (leftt >> 4);
/* work=xxE1xxE3xxE5xxE7 */
		work ^= *keys++;
		fval  = SP7[ work                & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
/* leftt=xxE2xxE4xxE6xxE8 */
		work  = leftt ^ *keys++;
		fval |= SP8[ work                & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		right ^= fval; 
		}/* fine delle iterazioni */

/*
 * CALCOLO DI IP -1 
*/

	right = (right << 31) | (right >> 1);
/* Primo Passo */
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = (leftt << 31) | (leftt >> 1);
/* Secondo Passo */
	work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
	right ^= work;
	leftt ^= (work << 8);
/* Terzo Passo */
	work = ((leftt >> 2) ^ right) & 0x33333333L;
	right ^= work;
	leftt ^= (work << 2);
/* Quarto Passo */
	work = ((right >> 16) ^ leftt) & 0x0000ffffL;
	leftt ^= work;
	right ^= (work << 16);
/* Quinto Passo */
	work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
	leftt ^= work;
	right ^= (work << 4);

	*block++ = right;
	*block = leftt;
	return;
	}


int hexdigit2(ch)
   register char ch;
{
   if (ch >= '0' && ch <= '9') return ch - '0';
   if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
   if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
   return -1;
}


unsigned  long  hex2(  char  *  d,  char  *  s,  unsigned  long  size)
   // register char *d, *s;
   // register unsigned size;
/*
 * Converte un numero ASCII esadecimale nella sua corrispondente stringa of 
	bytes
 * E' utilizzata per la chiave K fornita
 */
{
   register unsigned count = 0;
   register int lo, hi;

   if (size > 0) do {
      
      hi = hexdigit2(*s++);
      if (hi < 0) break;
      lo = hexdigit2(*s++);
      if (lo < 0) break;
      *d++ = (hi << 4) | lo;
      count++;
   } while (count < size);
   return count;
}



/*

void maind3(scelta,strkey,buffin,buffout,size)
   char *scelta,*buffin,*buffout;
   register char *strkey;
   int size;
//
// E' la procedura iniziale di d3_des
//

{ 
   register char key[8];
   char x;
   int i,j,opzione;
   clock_t tempo;
   struct tms time_in,time_fin;  

if (times(&time_in)==-1){printf("\nERRORE times\n");return -1.0;}

printf("************ D3_DES ***************\n");


    hex2(key,strkey,8);
  
   if (*scelta=='c' || *scelta=='C') {opzione=0;}
     else if (*scelta=='d' || *scelta=='D') {opzione=1;}

   deskey(key,(short)opzione); 

   for (j=0;j<size;j=j+8) {
			   desd3(buffin+j,buffout+j);        
			   }
 if (times(&time_fin)==-1){printf("\nERRORE times\n");return -1.0;}
 tempo=(time_fin.tms_stime - time_in.tms_stime)+
       (time_fin.tms_utime - time_in.tms_utime);  // tempo utente 

 return tempo;
}

  */




//  Aniello Castiglione e Gerardo Maiorano < anicas,germai@zoo.diaedu.unisa.it > 


//  ÏÂÃæÊÇ²¹³ä

 void  des_key(  des_ctx  *  dc,  unsigned  char  *  key  )
{
	 deskey(  key,  EN0  );
	 cpkey(  dc->ek  );
	 deskey(  key,  DE1  );
	 cpkey(  dc->dk  );
}


 void  des_enc(  des_ctx  *  dc,  unsigned  char  *  data,  int  blocks  )
{
	 unsigned  long  work[2];
	 int  i;
	 unsigned  char  *  cp;

	 cp  =  data;
	 for  (  i  =  0;  i  <  blocks;  i  ++  )  {
		  scrunch( cp,  work  );
		  desfunc(  work,  dc->ek  );
		  unscrun(  work,  cp  );
		  cp  +=  8;
	 }
}

 void  des_dec(  des_ctx  *  dc,  unsigned  char  *  data,  int  blocks  )
{
	 unsigned  long  work[2];
	 int  i;
	 unsigned  char  *  cp;

	 cp  =  data;
	 for  (  i  =  0;  i  <  blocks;  i  ++  )  {
		  scrunch(  cp,  work  );
		  desfunc(  work,  dc->dk  );
		  unscrun(  work,  cp  );
		  cp  +=  8;
	 }
}

