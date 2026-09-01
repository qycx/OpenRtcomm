   struct MAIL_HEAD
   {
      char  bySoftwareVersion;   //version of mail process software£¬0x11H
      short wStructSize;         //length of mail head struct

      //the second part:summary of mail 
      char  strLineInfo[20];     //information of line
      char  strFileName[20];	 //original mail name
      int   dwFileSize;          //length of mail text
      long  int ftFileModifyTime;//creation time of original mail
      char  byFileType;          //type of original mail
                                 //0:Http;1:SMTP;2:POP3;3:Ftp;4:Telnet;5:;
      char  byFileCharacter;     //character of mail controled£¬1 available
      							//Bit0:according to IP address
         						//Bit1:according to mail address
								//Bit2:according to key words
								//Bit3:unknowen protocol
								//Bit4:secret mail
      char  bProtocolType;		//information of protocol order to distinguish
                                 //every kind of protocol in IP layer
      char  strFileDirection[10];//mail content type in string:politics,
                                 //economy or diplomatism
      //embody is defined by user
      char  byLanguage;			//language type of mail
                                //0:english 1 bit is efficient when set 1
								//bit0:chn bit1:jap bit2:kor bit3:rus bit7:oths
      int   dwKeyWordsValue;	 //total value of mail key words

      //the third part:detail of mail 
      //Part 1
      char  byIpVersion;		//version of IP protocal
      int   dwSrcIpAddress[4];	 //source IP address
      int   dwDestIpAddress[4];	 //destination IP address
      short wSrcPort;            //source port
      short wDestPort;			 //destination port
      char  wUserAccount[16];	 //user account
      char  wUserPassword[16];	 //user password

      //Part 2
      short wMailFromPos; 	 //position of Mail From
      short wMailFromLen;	 //length of Mail From
      short wRcptToPos;		 //position of RCPT To
      short wRcptToLen;		 //length of RCPT To
      short wFromPos;		 //position of From
      short wFromLen;		 //length of From
      short wToPos;			 //position of To
      short wToLen;			 //length of To
      short wSubjectPos;	 //position of Subject
      short wSubjectLen;	 //length of Subject
      char  byNeedMoreDeal;	 //if the attachment needs special procession
                                 //0:common text 1:WORD Winzip etc.
      int   wTail01TotalCount;	 //amont of the first kind of file tail struct
      int   wTail01StartPos;	 //start position of tail struct 1
      int   wTail02TotalCount;	 //amont of the second kind of file tail struct
      int   wTail02StartPos;	 //start position of file tail 2(37)
	  char  byDeformity;

      char  byReserved[10];		    //reserved section 
   };

   struct MAIL_TAIL_1
   {
      short wStructSize;        //length of current tail struct
      short byBlockType;		//block type:Bit0:0:mail head 1:text
                                //Bit1:0:text can be searched
                                //1:text can't be searched
      int   dwContentTypePos;	//position of ContentType
      int   dwContentTypeLen;	//length of ContentType
      int   dwCharsetPos;	//position of Charset
      int   dwCharsetLen;	//length of Charset
      int   dwAttachedFileNamePos;	//position of attchment name 
      int   dwAttachedFileNameLen;	//length of attchment name 
      int   dwTextOffset;	//offset of text block in mail body
      int   dwBlockOffset;	//offset of block text in block
      int   dwBlockSize;	//length of block
      int   dwDecodedPos;	//position of attchment after decoded
      int   dwDecodedSize;	//length of attchment after decoded
	  int   dwLanguageType;
      char  dwReserved[11];	//reserved
   };	        //60Bytes

   struct MAIL_SECTOR
   {
      int iSectorCounter;					
      int iSectorType[TOKEN_ARRAY_LEN];		
      int iLenSector[TOKEN_ARRAY_LEN];		
      int iSectorCodeType[TOKEN_ARRAY_LEN];	
      int iPosContentType[TOKEN_ARRAY_LEN];	
      int iLenContentType[TOKEN_ARRAY_LEN];	
      int iPosCharset[TOKEN_ARRAY_LEN];		
      int iLenCharset[TOKEN_ARRAY_LEN];
      int iPosEncoding[TOKEN_ARRAY_LEN];			
	  int iLenEncoding[TOKEN_ARRAY_LEN];
      int iPosFileName[TOKEN_ARRAY_LEN];
      int iLenFileName[TOKEN_ARRAY_LEN];
      int iPosOriBlock[TOKEN_ARRAY_LEN];
      int iLenOriBlock[TOKEN_ARRAY_LEN];
      int iPosDecBlock[TOKEN_ARRAY_LEN];
      int iLenDecBlock[TOKEN_ARRAY_LEN];	  
  	  int iLanguageType[TOKEN_ARRAY_LEN];
   };

