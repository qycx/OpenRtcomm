


//  globals
var		gTimerId;
var		giRefreshInterval	=	2000;	//  3000;
var		gAppName			=	"qm";
var		gVer				=	"010102";
var		gRndS				=	"";
var		gRndC				=	null;	
var		gSessId				=	null;
//
var		gbDebug				=	false;
//
var		giLoop				=	0;
//
var		giTranNo			=	100;
//
var		gMsgContents		=	new Array(  );
var		gMsgTos				=	new Array(  );
var		giMsgTranNos		=	new Array(  );
var		gtMsgSendTimes		=	new Array(  );
//
var		giMaxMsgs			=	1000;
//
var		giSending			=	-1;
var		giSent				=	-1;		
//
var		gbUsrListNeedGot	=	true;
//
var		giTo_send			=	30;

//
var isIE = navigator.appName.toLowerCase().indexOf('internet explorer')+1;
var isMac = navigator.appVersion.toLowerCase().indexOf('mac')+1;

////////////////

function isDefined(variable) {
		   return (typeof(variable) == "undefined") ? false : true;
}


////////////


function btnHover(obj) 
{
   var newsrc = obj.src;
   newsrc = newsrc.replace(/_hover/, '');
   obj.src = newsrc.replace(/\.png/, '_hover.png');
}

function btnDown(obj) 
{
   obj.src = obj.src.replace(/_hover\.png/, '_down.png');
}

function btnNormal(obj) 
{
   obj.src = obj.src.replace(/\_hover.png/, '.png').replace(/\_down.png/, '.png');
}




//////////////////

 function  sendMsg(  from,  to,  iTranNo,  msgContent  ) 
{
	if  (  msgContent  ==  null  )  return;
	
	var  i  =  giSending  +  1;
	//  alert(  "sendMsg enters"  );
	
	if  (  i  >=  giMaxMsgs  )  return  false;
	if  (  i  <  0  )  {
		alert(  "giSending err"  +  giSending  );  return false;
	}
	
	gMsgTos[i]  =  to;
	gMsgContents[i]  =  msgContent;
	giMsgTranNos[i]  =  iTranNo;
	gtMsgSendTimes[i]  =  0;
	//
	giSending  =  i;
	//
	
	return  true;  
}


 function  startToSend(  )
{
	var	i;
	var	bMsgNeedSent	=	false;
		
	if  (  giSending  >=  0  )  {
		if  (  giSent  <  giSending  )  bMsgNeedSent  =  true;
	} 
	
	if  (  bMsgNeedSent  )  {
	
		if  (  giSent  <  0  )  i  =  0;
		else  	i  =  giSent  +  1;
		
		for  (  ;  i  <=  giSending;  i  ++  )  {		//  collect garbege
			 if  (  gMsgContents[i]  ==  null  )  {
				 giSent  =  i;  continue;
			 }  
			 break;
		}
		if  (  giSending  ==  giSent  )  {
			giSending  =  -1;	//  -1 means no msg
			giSent  =  -1;
			//  alert(  "giSending and giSent are set to -1"  );
			//  no msg
			}
		else  {
				
			  var  str  =  "";
			  var  tNow  =  myGetTInMs(  );
			  			
			  for  (  ;  i  <=  giSending;  i  ++  )  {		
			       if  (  gMsgContents[i]  ==  null  )  continue;	 
			       if  (  tNow  -  gtMsgSendTimes[i]  <  (  giTo_send  *  1000  )  )  continue;
			       //  alert(  "will to send "  +  gMsgContents[i]  +  ":tNow is %d"  );
				   str  +=   "&c=tlk&to="  +  encodeURIComponent(  gMsgTos[i]  )  +  "&tNo="  +  giMsgTranNos[i]  +  gMsgContents[i];	
				   gtMsgSendTimes[i]  =  tNow;		 
				   if  (  str.length  >  8192  )  break;		
			 }
	
			 doQmConn(  "&frm="  +  encodeURIComponent(  ""  )  +  str,  fp_sendMsg  );
			return;
		}
	}
	
	return;
 
}



///////////////////

 function  getNextTranNo(  )
{
	giTranNo  =  giTranNo  +  1;
	return  giTranNo;
}




////////////////

 function  addGrp(groupname) 
{
	var gList = $('imGrpList');
  
	try  { 
		 gList.innerHTML  =  '<li id="' + groupname.replace(/\s/, '_') + '_groupTop" class="groupTop" onmousedown="return false;" onselectstart="return false;" onclick=" toggleGroup(\'' + groupname + '\');"><img id="' + groupname.replace(/\s/, '_') + '_groupArrow" src="images/arrow.png" />&nbsp;&nbsp;' + groupname + 
					         '</li>' + "\n" + '<ul id="' + groupname.replace(/\s/, '_') + '_group" class="group"></ul>' + gList.innerHTML;
					         
         //  alert(  gList.innerHTML  );
		 }		
	catch  (  e  )  {
		   alert(  e  );
		   return  false;
	}
}
		
 function toggleGroup(groupname) 
{
	var groupList = $(groupname.replace(/\s/, '_') + '_group');
	var groupArrow = $(groupname.replace(/\s/, '_') + '_groupArrow');
   
	if(groupList.style.display != 'none') {
		groupList.style.display = 'none';
		groupArrow.src = 'images/arrow_up.png';
		} 
	else {
		  groupList.style.display = 'block';
		  groupArrow.src = 'images/arrow.png';
	}
}


 function  setUsrStatus(  msgrId,  status  )
{
	var  img  =  'images/online.png';
	
	if  (  status  !=  "1"  )  img  =  'images/offline.png';
		
    $(msgrId+'_msgrImg').src = img;
	        
}

		
 function  addMsgr(  msgrId, username, groupname, status  ) 
{
	if(!$(groupname.replace(/\s/, '_') + '_group')) addGrp(groupname);

	var gList = $(groupname.replace(/\s/, '_') + '_group');
				   
	//  alert(  msgrId  );

	gList.innerHTML += '<li id="'+msgrId+'_msgr" class="msgrCls" onmousedown="clickMsgr(\''+msgrId+'\',\''+username+'\');return false;" onselectstart="return false;" onmouseover="selectMsgr(this, \''+msgrId+'\', true);" onmouseout="selectMsgr(this, \''+msgrId+'\', false);" ondblclick="onMsgrDblClick();">&nbsp;&nbsp;&nbsp;&nbsp;<img src="images/online.png" width="16" height="16" alt="" id="'+msgrId+'_msgrImg">&nbsp;'+username+  '<span id="'  +  msgrId  +'_msgrHint"></span>'  +'</li>';
				   $(msgrId + '_msgr').style.listStyleType = 'none';
				   				   
	setUsrStatus(  msgrId,  status  );
}


 function selectMsgr(sel, username, selected) 
{
	if(selected === false) {
		if(curSelMsgrId != username) {
			sel.style.background = '#e3eaf3';
			sel.style.color = '#333';
			} 
		else {
			 sel.style.background = '#d0dae6';
			 sel.style.color = '#000';
		}
		} 
	else {
		  sel.style.background = '#e1ebf7';
	      sel.style.color = '#000';
	}
}

 function clickMsgr(msgrId,displayName) 
{
	if(curSelMsgrId.length > 0) {
		var sel = $(curSelMsgrId + '_msgr');   
		sel.style.background = '#e3eaf3';
		sel.style.color = '#333';
	}
   
	curSelMsgrId = msgrId;
	curSelMsgrName  =  displayName;
   
	sel = $(curSelMsgrId + '_msgr');
	sel.style.background = '#d0dae6';
	sel.style.color = '#333';
}
		
	

 function onMsgrDblClick() 
{
	if  (  curSelMsgrId.length  <=  0  )  return;
			
	//  alert(  curSelMsgrId  );

	var  w  =  dlgTalks[curSelMsgrId];
	if  (  w  &&  w  !=  "undefined"  )  {
		w.focus(  );
		return;
	}
	 
	$(curSelMsgrId  +  "_msgrHint"  ).innerHTML  =  "";	
 	dlgTalks[curSelMsgrId]  =  window.open('./b.html',   curSelMsgrId  + '_im', 'left=333,top=333,width=491,height=335,toolbar=0,location=1,status=0,menubar=0,resizable=1,scrollbars=0');

}


 //
 function emotReplace(str, itemsList) 
{
	var r;
	
	for(var i=0; i<itemsList.length; i++) {
		r = itemsList[i].split('~');
		if(str.indexOf(r[0]) > -1)
			str = str.replace(new RegExp(regExpEscape(r[0]), 'g'), '<img src="images/emots/' + r[1] + '" alt="' + r[1] + '" title="' + r[0] + '" />');
	}
	return str;
}

 function regExpEscape(text) 
{
	if (!arguments.callee.sRE) {
		var specials = [
					      '/', '.', '*', '+', '?', '|',
					      '(', ')', '[', ']', '{', '}', '\\'
					    ];
		arguments.callee.sRE = new RegExp(
					      '(\\' + specials.join('|\\') + ')', 'g'
					    );
	}
	return text.replace(arguments.callee.sRE, '\\$1');
}



 function setStatus(iStatus, statusStr,  hint) 
{
	if  (  statusStr  )  $('curStatus').innerHTML = statusStr;
	if  (  hint  )  $(  'curHint'  ).innerHTML  =  "&nbsp;&nbsp;|"  +  "&nbsp;&nbsp;"  +  hint;
}


//////


//
 function  setTimers(  )
{	
	gTimerId  =  setTimeout(  "refreshAll()",  giRefreshInterval  );
}

 function  newQmConn(  )
{
	var  xmlHttp;
	
	try  {
		 xmlHttp  =  new  ActiveXObject(  'Msxml2.XMLHTTP'  );
		 }
	catch  (  e  )  {
		   try  {
		        xmlHttp  =  new  ActiveXObject('Microsoft.XMLHTTP');		
		        }
		   catch  (  e1  )  {
				  xmlHttp  =  null;
		   }     
	}
	if  (  !xmlHttp  &&  typeof  XMLHttpRequest  !=  "undefined"  )  {
		xmlHttp  =  new  XMLHttpRequest(  );		
	}	
	return  xmlHttp;	
}

 function  doConn(  xmlHttp, sUrl, sMethod, sVars, fp  )
{
    if  (  !xmlHttp  )  return  false;
  
    sMethod = sMethod.toUpperCase();

	  //  alert(  "doConn"  );

    try  {
         if  (  sMethod == "GET"  )  {
             xmlHttp.open(sMethod, sUrl  +  "?"  +  sVars, true  );
			 sVars  =  "";
			 }
		 else  {
			   xmlHttp.open(  sMethod, sUrl, true  );
        	   xmlHttp.setRequestHeader("Method", "POST "+sUrl+" HTTP/1.1");
        	   xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
         }
     	 xmlHttp.onreadystatechange = function(){
			if  (  xmlHttp.readyState  ==  4  )  {
				if  (  fp  !=  null  )  fp(  xmlHttp  );
        	}
			};
		 xmlHttp.send(sVars);
	    }
    catch(e) { return false; }
    return true;
 }


 function  getCookie(  name  )
{
	var		start  =  document.cookie.indexOf(  name  +  "="  );
	if  (  start  ==  -1  )  return  null;
	
	if  (  !start  &&  name  !=  document.cookie.substring(  0,  name.length  )  )  return  null;

	var  len  =  start  +  name.length  +  1;
	var  end  =  document.cookie.indexOf(  ';',  len  );
	if  (  end  ==  -1  )  end  =  document.cookie.length;
	return  unescape(  document.cookie.substring(  len,  end  )  );
		
 }
 

 function  setCookie(  name,  value,  expires,  path,  domain,  secure  )
{
	var  today  =  new  Date( );
	today.setTime(  today.getTime(  )  );
	if  (  expires  )  expires  =  expires  *  1000  *  60  *  60  *  24;
	var  expires_date  =  new  Date(  today.getTime(  )  +  expires  );
	document.cookie  =  name  +  '='  +  escape(  value  )  +
			 (  expires  ?  ';expires='  +  expires_date.toUTCString()  :  ''  )  +
			 (  path  ?  ';path='  +  path  :  ''  )  +
			 (  domain  ?  ';domain='  +  domain  :  ''  )  +
			 (  secure  ?  ';secure='  +  secure  :  ''  );
			 	
}

 function  deleteCookie(  name,  path,  domain  )  
{
	if  (  getCookie(  name  )  )  document.cookie  =  name  +  '='  +  
		(  path  ?  ';path=' +  path  :  ''  )  +
		(  domain  ?  ';domain='  +domain  :  ''  )  +
		';expires  =  Thu,  01-Jan-1979  00:00:01  GMT';		
}


 function  setUsrCookie(  )
{
	if  (  gRndS  &&  gRndC  )  {
		setCookie(  "rndS",  gRndS  );
		setCookie(  "rndC",  gRndC  );
	}
}


 function  getUsrCookie(  )
{
	var  tmpRndS,  tmpRndC;
	tmpRndS  =  getCookie(  "rndS"  );
	tmpRndC  =  getCookie(  "rndC"  );
	if  (  tmpRndS  &&  tmpRndC  )  {
		gRndS  =  tmpRndS;
		gRndC  =  tmpRndC;
	}		
}

 function  startQm(  )
 {	
	gRndC  =  Math.round(  Math.random(  )  *  1000000  ).toString(  16  );
  
    //
	getUsrCookie(  );
	  
	// to get usr list
	gbUsrListNeedGot  =  true;
	doQmConn(  "&c=getU",  fp_getUsrList  );
	//
	setTimers(  );		
	
	//
 }
  
 
 function stopQm(  )
{
	var  i;
	for  (  i  in  dlgTalks  )  {	
		 var  w=dlgTalks[i];
		 if  (  w  &&  w!="undefined"  )  {
			 w.close(  );
		 }		 
	}
}

 function  myGetTInMs(  )
 {
	var  t  =  new  Date(  );
	var  t1  =  t.valueOf(  );
	t  =  null;
	return  t1;
 }

 function  doQmConn(  sendContent,  fp  )
{    	
   var myConn	=	newQmConn();
   var	str		=	"";
   	
   str  =  "a="  +  gAppName;
   if  (  gSessId  )  str  =  str  +  "&s="  +  gSessId;   
   if  (  !gSessId  )  str  =  str  +  "&v="  +  gVer;   
   if  (  gRndC  )  str  =  str  +  "&rC="  +  encodeURIComponent(  gRndC  );
   if  (  !gSessId  )  {
	   if  (  gRndS  )  str  =  str  +  "&rS="  +  encodeURIComponent(  gRndS  );	
   }
      
   doConn(  myConn,  "./cgi-bin/qnm.cgi", "POST", str  +  sendContent,  fp  );
   
   //   
   
}

 function  procErr(  resp  )
{
	var	rs;
		
	try  {
		 rs  =  resp.getElementsByTagName(  "errCode"  );	
		 if  (  rs  !=  null  )  {			
			 if  (  rs[0].firstChild.data  !=  "0"  )  {
				 gSessId  =  null;
			 }		
			 setStatus(  10, "&nbsp;"  +  resp.getElementsByTagName(  "content"  )[0].firstChild.data  );
		 }
		 }
	catch  (  e  )  {
	}
}



 function  fp_getUsrList(  xh  ) 
{
	
	if  (  !gbUsrListNeedGot  )  return;
	
	//  alert(  xh.responseText  );

	var  resp  =  xh.responseXML.documentElement;
	if  (  !resp  )  {
		if  (  gbDebug  )  alert(  "getUsrList(  ): responseText:"  +  xh.responseText  );
		return;
	}

	//  alert(  resp.xml  );
	
	var  rs;
	var	 hint  =  "";
	var  status;
	var	 tmp;
	
	rs  =  resp.getElementsByTagName(  "hint"  );
	if  (  rs  !=  null  &&  rs.length  >  0  )  hint  =  rs[0].firstChild.data;
	
	rs  =  resp.getElementsByTagName(  "bBody"  );
	if  (  rs  !=  null  &&  rs.length  >  0  )  bBody  =  rs[0].firstChild.data;
	//  alert(  "bBody is "  +  bBody  );
	
	rs  =  resp.getElementsByTagName(  "bInner"  );
	if  (  rs  !=  null  &&  rs.length  >  0  )  bInner  =  rs[0].firstChild.data;
	//  alert(  "bInner is "  +  bInner  );
	
		
	rs  =  resp.getElementsByTagName(  "usr"  );
	if  (  rs  ==  null  ||  rs.length  ==  0  )  {
		procErr(  resp  );				
		return;
	}
	for  (  i  =  0;  i  <  rs.length;  i  ++  )  {
		 //  alert(  "grpName: "  +  rs[i].getElementsByTagName(  "g"  )[0].firstChild.data  );				 
		 tmp  =  rs[i].getElementsByTagName(  'st'  );
		 if  (  tmp  !=  null  &&  tmp.length  >  0  &&  tmp[0].firstChild  )  status  =  tmp[0].firstChild.data;
		 addMsgr(  rs[i].getElementsByTagName(  'msgr'  )[0].firstChild.data,  rs[i].getElementsByTagName(  'name'  )[0].firstChild.data,  rs[i].getElementsByTagName(  'grp'  )[0].firstChild.data,  status  );
	}
		
	rs  =  resp.getElementsByTagName(  "s"  );
	if  (  rs  !=  null  &&  rs.length  >  0  )  gSessId  =  rs[0].firstChild.data;
		
	rs  =  resp.getElementsByTagName(  "rS"  );
	if  (  rs  !=  null  &&  rs.length  >  0  &&  rs[0].firstChild  )  {
		gRndS  =  rs[0].firstChild.data;  //  rs[0].firstChild.data;
		//
		setUsrCookie(  );
	}
			
	//
	gbUsrListNeedGot  =  false;
		
	setStatus(  0, "&nbsp;I'm online",  hint  );	//  
		
 }

 function  isRsValid(  tmp  )
{
	if  (  tmp  !=  null  &&  tmp.length  >  0  &&  tmp[0].firstChild  )  return  true;
	return  false;
}

 function  fp_sendMsg(  xh  ) 
{    		

	//    alert(  "responseText: "  +  xh.responseText  );
			
	var  resp  =  xh.responseXML.documentElement;
	if  (  !resp  )  {
	    if  (  gbDebug  )  alert(  "fp_sendMsg(  ):  responseText: "  +  xh.responseText  );
		return;
	}
	
	//  alert(  "responseXml:"  +  resp.xml  );
		
	var  rs;
	var	 hint		=  "";
	var  status;
	var	 tmp;
	var  iTranNo	=	0;
	var  i;
	var  j;

	rs  =  resp.getElementsByTagName(  "hint"  );
	if  (  rs  !=  null  &&  rs.length  >  0  )  hint  =  rs[0].firstChild.data;
	
	//  alert(  resp.xml  );    
			 
	
	rs  =  resp.getElementsByTagName(  "tlk"  );	
	if  (  rs  !=  null  &&  rs.length  >  0  )  {
		
		for  (  i  =  0;  i  <  rs.length;  i  ++  )  {
			 //
			 //  alert(  resp.xml  );    
			 //
			 tmp  =  rs[i].getElementsByTagName(  'rc'  );
			 if  (  isRsValid(  tmp  )  )  {
				 //  alert(  resp.xml  );
				 if  (  tmp[0].firstChild.data  !=  "0"  )  continue;
				 
				 tmp  =  rs[i].getElementsByTagName(  'tNo'  );
				 if  (  !isRsValid(  tmp  )  )  continue;
				 
				 iTranNo  =  parseInt(  tmp[0].firstChild.data,  16  );
				
				 //  alert(  tmp[0].firstChild.data  +  ":"  +  iTranNo  );
				
				 for  (  j  =  giSent  +  1;  j  <=  giSending;  j  ++  )  {
					  if  (  giMsgTranNos[j]  ==  iTranNo  )  {
						  //  alert(  gMsgContents[j] + " is sent"  );
						  gMsgContents[j]  =  null;
					  }
				 }
				 //				 
			 	 continue;
			 }
			 //
			 var  msgrId  =  rs[i].getElementsByTagName(  'msgr'  )[0].firstChild.data;
			 var  str  =  rs[i].getElementsByTagName(  'str'  )[0].firstChild.data;
			 var  displayName = null;
			 tmp  =  rs[i].getElementsByTagName(  'name'  );
			 if  (  tmp  !=  null  &&  tmp.length  >  0  )  displayName  =  tmp[0].firstChild.data;
		 
			 var  w=dlgTalks[msgrId];
			 if  (  w  &&  w!="undefined"  )  {
			     if  (  !displayName  )  displayName=w.defaultTitle;
			     //  
   				 w.focus(  );
				 w.addToRecentMsgList(  displayName,  str  );
				}
			else  {
				  t = new Date(); var h = String(t.getHours()); var m = String(t.getMinutes()); var s = String(t.getSeconds());
			      h = (h.length > 1) ? h : "0"+h; m = (m.length > 1) ? m : "0"+m;
			      //
			      try  {
					   $(msgrId  +  "_msgrHint"  ).innerHTML  =    "&nbsp;&nbsp;<b>says"  +  "(" + h + ":" + m + ")" +  ":&nbsp;</b> <span>"  +  str  + "</span>";
				  }
				  catch  (  e  )  {  
						 //  alert(  e  );
				  }
			}
		}
		
	}

		
	rs  =  resp.getElementsByTagName(  "usr"  );
	if  (  rs  !=  null  &&  rs.length  >  0  )  {
		for  (  i  =  0;  i  <  rs.length;  i  ++  )  {
			 //  alert(  "grpName: "  +  rs[i].getElementsByTagName(  "g"  )[0].firstChild.data  );				 
			 tmp  =  rs[i].getElementsByTagName(  'st'  );
			 if  (  tmp  !=  null  &&  tmp.length  >  0  &&  tmp[0].firstChild  )  status  =  tmp[0].firstChild.data;
			 //
			 setUsrStatus(  rs[i].getElementsByTagName(  "msgr"  )[0].firstChild.data,  status  );
		}	
		//  
	}
		
	
	setStatus(  0, "&nbsp;I'm online",  hint  );	//  


	
}

 function  refreshAll(  )
{
	clearTimeout(  gTimerId  );
	giLoop  ++;
	
	//  alert(  "refreshall"  );
	if  (  !(  giLoop  %  2  )  )  {		//  per 4 seconds
		if  (  gbUsrListNeedGot  )  {
			doQmConn(  "&c=getU",  fp_getUsrList  );
			}
		else  {
			  //
		      if  (  !(  giLoop  %  5  )  )  {
				  doQmConn(  "&c=refrshU",  fp_sendMsg  );
				  }
			  else  {
					//  to recv msg
		  			doQmConn(  "&c=rcv",  fp_sendMsg  );
			  }
		}
		}
	else  {						//  per 4 seconds
	      startToSend(  );
	}
		
	setTimers(  );
} 










