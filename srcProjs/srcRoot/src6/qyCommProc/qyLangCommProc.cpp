
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<WinSock2.h>

#include	"qyCommon.h"
#include	"qyLangCommProc.h"


#define		CONST_sym_jt			_T(  "jt"  )
#define		CONST_sym_ft			_T(  "ft"  )
//	#define		CONST_sym_en			_T(  "en"  )		//  缺省为英语
#define		CONST_sym_ja			_T(  "ja"  )



 QY_IDCITEM  CONST_langStrTable[]  =		//  Locale,  ISO 369 abbreviated (no hyphen) language string,  ISO 369 standard accept language string 
{ 
    { 0x0436,	(  LONG_PTR  )_T(  "af"  ),    (TCHAR*)_T(  "af"  ),			}, //Afrikaans 
    { 0x041c,	(  LONG_PTR  )_T(  "sq"  ),    (TCHAR*)_T(  "sq"  ),			}, //Albanian 
    { 0x0401,	(  LONG_PTR  )_T(  "ar-sa"  ), (TCHAR*)_T(  "arsa"  ),			}, // Arabic(Saudi Arabia) 
    { 0x0801, 	(  LONG_PTR  )_T(  "ar-iq"  ), (TCHAR*)_T(  "ariq"  ),			}, // Arabic(Iraq) 
    { 0x0C01, 	(  LONG_PTR  )_T(  "ar-eg"  ), (TCHAR*)_T(  "areg"  ),			}, // Arabic(Egypt) 
    { 0x1001, 	(  LONG_PTR  )_T(  "ar-ly"  ), (TCHAR*)_T(  "arly"  ),			}, // Arabic(Libya) 
    { 0x1401, 	(  LONG_PTR  )_T(  "ar-dz"  ), (TCHAR*)_T(  "ardz"  ),			}, // Arabic(Algeria) 
    { 0x1801, 	(  LONG_PTR  )_T(  "ar-ma"  ), (TCHAR*)_T(  "arma"  ),			}, // Arabic(Morocco) 
    { 0x1C01, 	(  LONG_PTR  )_T(  "ar-tn"  ), (TCHAR*)_T(  "artn"  ),			}, // Arabic(Tunisia) 
    { 0x2001, 	(  LONG_PTR  )_T(  "ar-om"  ), (TCHAR*)_T(  "arom"  ),			}, // Arabic(Oman) 
    { 0x2401, 	(  LONG_PTR  )_T(  "ar-ye"  ), (TCHAR*)_T(  "arye"  ),			}, // Arabic(Yemen) 
    { 0x2801, 	(  LONG_PTR  )_T(  "ar-sy"  ), (TCHAR*)_T(  "arsy"  ),			}, // Arabic(Syria) 
    { 0x2C01, 	(  LONG_PTR  )_T(  "ar-jo"  ), (TCHAR*)_T(  "arjo"  ),			}, // Arabic(Jordan) 
    { 0x3001, 	(  LONG_PTR  )_T(  "ar-lb"  ), (TCHAR*)_T(  "arlb"  ),			}, // Arabic(Lebanon) 
    { 0x3401, 	(  LONG_PTR  )_T(  "ar-kw"  ), (TCHAR*)_T(  "arkw"  ),			}, // Arabic(Kuwait) 
    { 0x3801, 	(  LONG_PTR  )_T(  "ar-ae"  ), (TCHAR*)_T(  "arae"  ),			}, // Arabic(U.A.E.) 
    { 0x3C01, 	(  LONG_PTR  )_T(  "ar-bh"  ), (TCHAR*)_T(  "arbh"  ),			}, // Arabic(Bahrain) 
    { 0x4001, 	(  LONG_PTR  )_T(  "ar-qa"  ), (TCHAR*)_T(  "arqa"  ),			}, // Arabic(Qatar) 
    { 0x042D, 	(  LONG_PTR  )_T(  "eu"  ),    (TCHAR*)_T(  "eu"  ),  								}, // Basque 
    { 0x0402, 	(  LONG_PTR  )_T(  "bg"  ),    (TCHAR*)_T(  "bg"  ),  								}, // Bulgarian 
    { 0x0423, 	(  LONG_PTR  )_T(  "be"  ),    (TCHAR*)_T(  "be"  ),  								}, // Belarusian 
    { 0x0403, 	(  LONG_PTR  )_T(  "ca"  ),    (TCHAR*)_T(  "ca"  ),  								}, // Catalan 
    { 0x0404, 	(  LONG_PTR  )_T(  "zh-tw"  ), (TCHAR*)_T(  "zhtw"  ),		(  LONG_PTR  )CONST_sym_ft,				}, // Chinese(Taiwan Region) 
    { 0x0804, 	(  LONG_PTR  )_T(  "zh-cn"  ), (TCHAR*)_T(  "zhcn"  ),		(  LONG_PTR  )CONST_sym_jt,				}, // Chinese(PRC) 
    { 0x0C04, 	(  LONG_PTR  )_T(  "zh-hk"  ), (TCHAR*)_T(  "zhhk"  ),		(  LONG_PTR  )CONST_sym_ft,				}, // Chinese(Hong Kong SAR, PRC) 
    { 0x1004, 	(  LONG_PTR  )_T(  "zh-sg"  ), (TCHAR*)_T(  "zhsg"  ),		(  LONG_PTR  )CONST_sym_jt,				}, // Chinese(Singapore) 
    { 0x041a, 	(  LONG_PTR  )_T(  "hr"  ),    (TCHAR*)_T(  "hr"  ),  								}, // Croatian 
    { 0x0405, 	(  LONG_PTR  )_T(  "cs"  ),    (TCHAR*)_T(  "cs"  ),  								}, // Czech 
    { 0x0406, 	(  LONG_PTR  )_T(  "da"  ),    (TCHAR*)_T(  "da"  ),  								}, // Danish 
    { 0x0413, 	(  LONG_PTR  )_T(  "nl"  ),    (TCHAR*)_T(  "nl"  ),  								}, // Dutch(Standard) 
    { 0x0813, 	(  LONG_PTR  )_T(  "nl-be"  ), (TCHAR*)_T(  "nlbe"  ),								}, // Dutch(Belgian) 
    { 0x0009, 	(  LONG_PTR  )_T(  "en"  ),    (TCHAR*)_T(  "en"  ),  			}, // English 
    { 0x0409, 	(  LONG_PTR  )_T(  "en-us"  ), (TCHAR*)_T(  "enus"  ),			}, // English(United States) 
    { 0x0809, 	(  LONG_PTR  )_T(  "en-gb"  ), (TCHAR*)_T(  "engb"  ),			}, // English(British) 
    { 0x0c09, 	(  LONG_PTR  )_T(  "en-au"  ), (TCHAR*)_T(  "enau"  ),			}, // English(Australian) 
    { 0x1009, 	(  LONG_PTR  )_T(  "en-ca"  ), (TCHAR*)_T(  "enca"  ),			}, // English(Canadian) 
    { 0x1409, 	(  LONG_PTR  )_T(  "en-nz"  ), (TCHAR*)_T(  "ennz"  ),			}, // English(New Zealand) 
    { 0x1809, 	(  LONG_PTR  )_T(  "en-ie"  ), (TCHAR*)_T(  "enie"  ),			}, // English(Ireland) 
    { 0x1c09, 	(  LONG_PTR  )_T(  "en-za"  ), (TCHAR*)_T(  "enza"  ),			}, // English(South Africa) 
    { 0x2009, 	(  LONG_PTR  )_T(  "en-jm"  ), (TCHAR*)_T(  "enjm"  ),			}, // English(Jamaica) 
    { 0x2409, 	(  LONG_PTR  )_T(  "en"  ),    (TCHAR*)_T(  "en"  ),  			}, // English(Caribbean) 
    { 0x2809, 	(  LONG_PTR  )_T(  "en-bz"  ), (TCHAR*)_T(  "enbz"  ),			}, // English(Belize) 
    { 0x2c09, 	(  LONG_PTR  )_T(  "en-tt"  ), (TCHAR*)_T(  "entt"  ),			}, // English(Trinidad) 
    { 0x0425, 	(  LONG_PTR  )_T(  "et"  ),    (TCHAR*)_T(  "et"  ),  			}, // Estonian 
    { 0x0438, 	(  LONG_PTR  )_T(  "fo"  ),   (TCHAR*)_T(  "fo"  ),  			}, // Faeroese 
    { 0x0429, 	(  LONG_PTR  )_T(  "fa"  ),   (TCHAR*)_T(  "fa"  ),  			}, // Farsi 
    { 0x040b, 	(  LONG_PTR  )_T(  "fi"  ),   (TCHAR*)_T(  "fi"  ),  			}, // Finnish 
    { 0x040c, 	(  LONG_PTR  )_T(  "fr"  ),   (TCHAR*)_T(  "fr"  ),  			}, // French(Standard) 
    { 0x080c, 	(  LONG_PTR  )_T(  "fr-be"  ),(TCHAR*)_T(  "frbe"  ),			}, // French(Belgian) 
    { 0x0c0c, 	(  LONG_PTR  )_T(  "fr-ca"  ),(TCHAR*)_T(  "frca"  ),			}, // French(Canadian) 
    { 0x100c, 	(  LONG_PTR  )_T(  "fr-ch"  ),(TCHAR*)_T(  "frch"  ),			}, // French(Swiss) 
    { 0x140c, 	(  LONG_PTR  )_T(  "fr-lu"  ),(TCHAR*)_T(  "frlu"  ),			}, // French(Luxembourg) 
    { 0x043c, 	(  LONG_PTR  )_T(  "gd"  ),   (TCHAR*)_T(  "gd"  ),  			}, // Gaelic(Scots) 
    { 0x083c, 	(  LONG_PTR  )_T(  "gd-ie"  ),(TCHAR*)_T(  "gdie"  ),			}, // Gaelic(Irish) 
    { 0x0407, 	(  LONG_PTR  )_T(  "de"  ),   (TCHAR*)_T(  "de"  ),  			}, // German(Standard) 
    { 0x0807, 	(  LONG_PTR  )_T(  "de-ch"  ),(TCHAR*)_T(  "dech"  ),			}, // German(Swiss) 
    { 0x0c07, 	(  LONG_PTR  )_T(  "de-at"  ),(TCHAR*)_T(  "deat"  ),			}, // German(Austrian) 
    { 0x1007, 	(  LONG_PTR  )_T(  "de-lu"  ),(TCHAR*)_T(  "delu"  ),			}, // German(Luxembourg) 
    { 0x1407, 	(  LONG_PTR  )_T(  "de-li"  ),(TCHAR*)_T(  "deli"  ),			}, // German(Liechtenstein) 
    { 0x0408, 	(  LONG_PTR  )_T(  "el"  ),   (TCHAR*)_T(  "el"  ),  			}, // Greek 
    { 0x040D, 	(  LONG_PTR  )_T(  "he"  ),   (TCHAR*)_T(  "he"  ),  			}, // Hebrew 
    { 0x0439, 	(  LONG_PTR  )_T(  "hi"  ),   (TCHAR*)_T(  "hi"  ),  			}, // Hindi 
    { 0x040e, 	(  LONG_PTR  )_T(  "hu"  ),   (TCHAR*)_T(  "hu"  ),  			}, // Hungarian 
    { 0x040F, 	(  LONG_PTR  )_T(  "is"  ),   (TCHAR*)_T(  "is"  ),  										}, // Icelandic 
    { 0x0421, 	(  LONG_PTR  )_T(  "in"  ),   (TCHAR*)_T(  "in"  ),  										}, // Indonesian 
    { 0x0410, 	(  LONG_PTR  )_T(  "it"  ),   (TCHAR*)_T(  "it"  ),  										}, // Italian(Standard) 
    { 0x0810, 	(  LONG_PTR  )_T(  "it-ch"  ),(TCHAR*)_T(  "itch"  ),										}, // Italian(Swiss) 
    { 0x0411, 	(  LONG_PTR  )_T(  "ja"  ),   (TCHAR*)_T(  "ja"  ),  		(  LONG_PTR  )CONST_sym_ja,			}, // Japanese 
    { 0x0412, 	(  LONG_PTR  )_T(  "ko"  ),   (TCHAR*)_T(  "ko"  ),  			}, // Korean 
    { 0x0812, 	(  LONG_PTR  )_T(  "ko"  ),   (TCHAR*)_T(  "ko"  ),  			}, // Korean(Johab) 
    { 0x0426, 	(  LONG_PTR  )_T(  "lv"  ),   (TCHAR*)_T(  "lv"  ),  			}, // Latvian 
    { 0x0427, 	(  LONG_PTR  )_T(  "lt"  ),   (TCHAR*)_T(  "lt"  ),  			}, // Lithuanian 
    { 0x042f, 	(  LONG_PTR  )_T(  "mk"  ),   (TCHAR*)_T(  "mk"  ),  			}, // Macedonian 
    { 0x043e, 	(  LONG_PTR  )_T(  "ms"  ),   (TCHAR*)_T(  "ms"  ),  			}, // Malaysian 
    { 0x043a, 	(  LONG_PTR  )_T(  "mt"  ),   (TCHAR*)_T(  "mt"  ),  			}, // Maltese 
    { 0x0414, 	(  LONG_PTR  )_T(  "no"  ),   (TCHAR*)_T(  "no"  ),  			}, // Norwegian(Bokmal) 
    { 0x0814, 	(  LONG_PTR  )_T(  "no"  ),   (TCHAR*)_T(  "no"  ),  			}, // Norwegian(Nynorsk) 
    { 0x0415, 	(  LONG_PTR  )_T(  "pl"  ),   (TCHAR*)_T(  "pl"  ),  			}, // Polish 
    { 0x0416, 	(  LONG_PTR  )_T(  "pt-br"  ),(TCHAR*)_T(  "ptbr"  ),			}, // Portuguese(Brazilian) 
    { 0x0816, 	(  LONG_PTR  )_T(  "pt"  ),   (TCHAR*)_T(  "pt"  ),  			}, // Portuguese(Standard) 
    { 0x0417, 	(  LONG_PTR  )_T(  "rm"  ),   (TCHAR*)_T(  "rm"  ),  			}, // Rhaeto-Romanic 
    { 0x0418, 	(  LONG_PTR  )_T(  "ro"  ),   (TCHAR*)_T(  "ro"  ),  			}, // Romanian 
    { 0x0818, 	(  LONG_PTR  )_T(  "ro-mo"  ),(TCHAR*)_T(  "romo"  ),			}, // Romanian(Moldavia) 
    { 0x0419, 	(  LONG_PTR  )_T(  "ru"  ),   (TCHAR*)_T(  "ru"  ),  			}, // Russian 
    { 0x0819, 	(  LONG_PTR  )_T(  "ru-mo"  ),(TCHAR*)_T(  "rumo"  ),			}, // Russian(Moldavia) 
    { 0x043b, 	(  LONG_PTR  )_T(  "sz"  ),   (TCHAR*)_T(  "sz"  ),  			}, // Sami(Lappish) 
    { 0x0c1a, 	(  LONG_PTR  )_T(  "sr"  ),   (TCHAR*)_T(  "sr"  ),  			}, // Serbian(Cyrillic) 
    { 0x081a, 	(  LONG_PTR  )_T(  "sr"  ),   (TCHAR*)_T(  "sr"  ),  			}, // Serbian(Latin) 
    { 0x041b, 	(  LONG_PTR  )_T(  "sk"  ),   (TCHAR*)_T(  "sk"  ),  			}, // Slovak 
    { 0x0424, 	(  LONG_PTR  )_T(  "sl"  ),   (TCHAR*)_T(  "sl"  ),  			}, // Slovenian 
    { 0x042e, 	(  LONG_PTR  )_T(  "sb"  ),   (TCHAR*)_T(  "sb"  ),  			}, // Sorbian 
    { 0x040a, 	(  LONG_PTR  )_T(  "es"  ),   (TCHAR*)_T(  "es"  ),  			}, // Spanish(Spain - Traditional Sort) 
    { 0x080a, 	(  LONG_PTR  )_T(  "es-mx"  ),(TCHAR*)_T(  "esmx"  ),			}, // Spanish(Mexican) 
    { 0x0c0a, 	(  LONG_PTR  )_T(  "es"  ),   (TCHAR*)_T(  "es"  ),  			}, // Spanish(Spain - Modern Sort) 
    { 0x100a, 	(  LONG_PTR  )_T(  "es-gt"  ),(TCHAR*)_T(  "esgt"  ),			}, // Spanish(Guatemala) 
    { 0x140a, 	(  LONG_PTR  )_T(  "es-cr"  ),(TCHAR*)_T(  "escr"  ),			}, // Spanish(Costa Rica) 
    { 0x180a, 	(  LONG_PTR  )_T(  "es-pa"  ),(TCHAR*)_T(  "espa"  ),			}, // Spanish(Panama) 
    { 0x1c0a, 	(  LONG_PTR  )_T(  "es-do"  ),(TCHAR*)_T(  "esdo"  ),			}, // Spanish(Dominican Republic) 
    { 0x200a, 	(  LONG_PTR  )_T(  "es-ve"  ),(TCHAR*)_T(  "esve"  ),			}, // Spanish(Venezuela) 
    { 0x240a, 	(  LONG_PTR  )_T(  "es-co"  ),(TCHAR*)_T(  "esco"  ),			}, // Spanish(Colombia) 
    { 0x280a, 	(  LONG_PTR  )_T(  "es-pe"  ),(TCHAR*)_T(  "espe"  ),			}, // Spanish(Peru) 
    { 0x2c0a, 	(  LONG_PTR  )_T(  "es-ar"  ),(TCHAR*)_T(  "esar"  ),			}, // Spanish(Argentina) 
    { 0x300a, 	(  LONG_PTR  )_T(  "es-ec"  ),(TCHAR*)_T(  "esec"  ),			}, // Spanish(Ecuador) 
    { 0x340a, 	(  LONG_PTR  )_T(  "es-cl"  ),(TCHAR*)_T(  "escl"  ),			}, // Spanish(Chile) 
    { 0x380a, 	(  LONG_PTR  )_T(  "es-uy"  ),(TCHAR*)_T(  "esuy"  ),			}, // Spanish(Uruguay) 
    { 0x3c0a, 	(  LONG_PTR  )_T(  "es-py"  ),(TCHAR*)_T(  "espy"  ),			}, // Spanish(Paraguay) 
    { 0x400a, 	(  LONG_PTR  )_T(  "es-bo"  ),(TCHAR*)_T(  "esbo"  ),			}, // Spanish(Bolivia) 
    { 0x440a, 	(  LONG_PTR  )_T(  "es-sv"  ),(TCHAR*)_T(  "essv"  ),			}, // Spanish(El Salvador) 
    { 0x480a, 	(  LONG_PTR  )_T(  "es-hn"  ),(TCHAR*)_T(  "eshn"  ),			}, // Spanish(Honduras) 
    { 0x4c0a, 	(  LONG_PTR  )_T(  "es-ni"  ),(TCHAR*)_T(  "esni"  ),			}, // Spanish(Nicaragua) 
    { 0x500a, 	(  LONG_PTR  )_T(  "es-pr"  ),(TCHAR*)_T(  "espr"  ),			}, // Spanish(Puerto Rico) 
    { 0x0430, 	(  LONG_PTR  )_T(  "sx"  ),   (TCHAR*)_T(  "sx"  ),  			}, // Sutu 
    { 0x041D, 	(  LONG_PTR  )_T(  "sv"  ),   (TCHAR*)_T(  "sv"  ),  			}, // Swedish 
    { 0x081d, 	(  LONG_PTR  )_T(  "sv-fi"  ),(TCHAR*)_T(  "svfi"  ),			}, // Swedish(Finland) 
    { 0x041E, 	(  LONG_PTR  )_T(  "th"  ),   (TCHAR*)_T(  "th"  ),  			}, // Thai 
    { 0x0431, 	(  LONG_PTR  )_T(  "ts"  ),   (TCHAR*)_T(  "ts"  ),  			}, // Tsonga 
    { 0x0432, 	(  LONG_PTR  )_T(  "tn"  ),   (TCHAR*)_T(  "tn"  ),  			}, // Tswana 
    { 0x041f, 	(  LONG_PTR  )_T(  "tr"  ),   (TCHAR*)_T(  "tr"  ),  			}, // Turkish 
    { 0x0422, 	(  LONG_PTR  )_T(  "uk"  ),   (TCHAR*)_T(  "uk"  ),  			}, // Ukrainian 
    { 0x0420, 	(  LONG_PTR  )_T(  "ur"  ),   (TCHAR*)_T(  "ur"  ),  			}, // Urdu 
    { 0x0433, 	(  LONG_PTR  )_T(  "ve"  ),   (TCHAR*)_T(  "ve"  ),  			}, // Venda 
    { 0x042a, 	(  LONG_PTR  )_T(  "vi"  ),   (TCHAR*)_T(  "vi"  ),  			}, // Vietnamese 
    { 0x0434, 	(  LONG_PTR  )_T(  "xh"  ),   (TCHAR*)_T(  "xh"  ),  			}, // Xhosa 
    { 0x043d, 	(  LONG_PTR  )_T(  "ji"  ),   (TCHAR*)_T(  "ji"  ),  			}, // Yiddish 
    { 0x0435, 	(  LONG_PTR  )_T(  "zu"  ),   (TCHAR*)_T(  "zu"  ),  			}, // Zulu 
	{	-1,		0,		},
};



 extern  "C"  QY_DMITEM	CONST_qyLangTable[]  =
{
	{	CONST_langId_PRC,				(TCHAR*)_T(  "简体中文(PRC)"  ),				},			//  0x0804			//  Chinese (PRC) 
	{	CONST_langId_tw,				(TCHAR*)_T(  "繁体中文(Tw)"  ),					},			//	0x0404			//  Chinese (Taiwan Region) 
	{	CONST_langId_hk,				(TCHAR*)_T(  "繁体中文(HK)"  ),					},			//  0x0c04			//  Chinese (Hong Kong SAR, PRC) 
	{	CONST_langId_Singapore,			(TCHAR*)_T(  "简体中文(Singapore)"  ),			},			//	0x1004			//  Chinese (Singapore) 
	{	CONST_langId_US,				(TCHAR*)_T(  "English(United States)"  ),		},			//	0x0409			//  English (United States) 
	{	CONST_langId_UK,				(TCHAR*)_T(  "English(United Kingdom)"  ),		},			//  0x0809			//	English (United Kingdom) 
	{	CONST_langId_Australian,		(TCHAR*)_T(  "English(Australian)"  ),			},			//  0x0c09			//  English (Australian) 
	{	CONST_langId_Candian,			(TCHAR*)_T(  "English(Canadian)"  ),			},			//  0x1009			//  English (Canadian) 
	{	CONST_langId_NewZealand,		(TCHAR*)_T(  "English(New Zealand)"  ),			},			//  0x1409			//  English (New Zealand) 
	{	CONST_langId_Ireland,			(TCHAR*)_T(  "English(Ireland)"  ),				},			//	0x1809			//	English (Ireland) 
	{	CONST_langId_SouthAfrica,		(TCHAR*)_T(  "English(South Africa)"  ),		},			//	0x1c09			//  English (South Africa) 
	{	CONST_langId_Jamaica,			(TCHAR*)_T(  "English(Jamaica)"  ),				},			//	0x2009			//  English (Jamaica) 
	{	CONST_langId_Caribbean,			(TCHAR*)_T(  "English(Caribbean)"  ),			},			//	0x2409			//	English (Caribbean) 
	{	CONST_langId_Belize,			(TCHAR*)_T(  "English(Belize)"  ),				},			//	0x2809			//  English (Belize) 
	{	CONST_langId_Trinidad,			(TCHAR*)_T(  "English(Trinidad)"  ),			},			//	0x2c09			//  English (Trinidad) 
	{	CONST_langId_Japanese,			(TCHAR*)_T(  "Japanese"  ),						},			//  0x0411			//	Japanese 
	{	CONST_langId_Korean,			(TCHAR*)_T(  "Korean"  ),						},			//	0x0412			//  Korean 
	{	CONST_langId_KoreanJohab,		(TCHAR*)_T(  "Korean(Johab)"  ),				},			//	0x0812			//  Korean (Johab) 
	{	CONST_langId_Russian,			(TCHAR*)_T(  "Russian"  ),						},			//  0x0419			//  Russian 
	{	CONST_langId_RussianMoldavia,	(TCHAR*)_T(  "Russian(Moldavia)"  ),			},			//  0x0819			//  Russian(Moldavia) 
	{	-1,							NULL,			},
};

 extern  "C"  QY_DMITEM	CONST_qyLangTable_en[]  =
{
	{	CONST_langId_PRC,				(TCHAR*)_T(  "Chinese(PRC)"  ),					},			//  0x0804			//  Chinese (PRC) 
	{	CONST_langId_tw,				(TCHAR*)_T(  "Chinese(Tw)"  ),					},			//	0x0404			//  Chinese (Taiwan Region) 
	{	CONST_langId_hk,				(TCHAR*)_T(  "Chinese(HK)"  ),					},			//  0x0c04			//  Chinese (Hong Kong SAR, PRC) 
	{	CONST_langId_Singapore,			(TCHAR*)_T(  "Chinese(Singapore)"  ),			},			//	0x1004			//  Chinese (Singapore) 
	{	CONST_langId_US,				(TCHAR*)_T(  "English(United States)"  ),		},			//	0x0409			//  English (United States) 
	{	CONST_langId_UK,				(TCHAR*)_T(  "English(United Kingdom)"  ),		},			//  0x0809			//	English (United Kingdom) 
	{	CONST_langId_Australian,		(TCHAR*)_T(  "English(Australian)"  ),			},			//  0x0c09			//  English (Australian) 
	{	CONST_langId_Candian,			(TCHAR*)_T(  "English(Canadian)"  ),			},			//  0x1009			//  English (Canadian) 
	{	CONST_langId_NewZealand,		(TCHAR*)_T(  "English(New Zealand)"  ),			},			//  0x1409			//  English (New Zealand) 
	{	CONST_langId_Ireland,			(TCHAR*)_T(  "English(Ireland)"  ),				},			//	0x1809			//	English (Ireland) 
	{	CONST_langId_SouthAfrica,		(TCHAR*)_T(  "English(South Africa)"  ),		},			//	0x1c09			//  English (South Africa) 
	{	CONST_langId_Jamaica,			(TCHAR*)_T(  "English(Jamaica)"  ),				},			//	0x2009			//  English (Jamaica) 
	{	CONST_langId_Caribbean,			(TCHAR*)_T(  "English(Caribbean)"  ),			},			//	0x2409			//	English (Caribbean) 
	{	CONST_langId_Belize,			(TCHAR*)_T(  "English(Belize)"  ),				},			//	0x2809			//  English (Belize) 
	{	CONST_langId_Trinidad,			(TCHAR*)_T(  "English(Trinidad)"  ),			},			//	0x2c09			//  English (Trinidad) 
	{	CONST_langId_Japanese,			(TCHAR*)_T(  "Japanese"  ),						},			//  0x0411			//	Japanese 
	{	CONST_langId_Korean,			(TCHAR*)_T(  "Korean"  ),						},			//	0x0412			//  Korean 
	{	CONST_langId_KoreanJohab,		(TCHAR*)_T(  "Korean(Johab)"  ),				},			//	0x0812			//  Korean (Johab) 
	{	CONST_langId_Russian,			(TCHAR*)_T(  "Russian"  ),						},			//  0x0419			//  Russian 
	{	CONST_langId_RussianMoldavia,	(TCHAR*)_T(  "Russian(Moldavia)"  ),			},			//  0x0819			//  Russian(Moldavia) 
	{	-1,							NULL,							},
};

