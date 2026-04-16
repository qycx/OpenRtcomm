/*
 * @Description: fun
 * @Author: guoxi
 * @Date: 2022-04-24 11:11:18
 * @LastEditors: guoxi
 * @LastEditTime: 2022-05-09 12:05:42
 */
var external = null;
//获取滚动条高度
var sh = 0; 
var new_sh = 0;

//鼠标点击位置
var x = 0;
var y = 0;

String.prototype.format = function () {
  if (arguments.length == 0) return this;
  var obj = arguments[0];
  var s = this;
  for (var key in obj) {
    s = s.replace(new RegExp("\\{\\{" + key + "\\}\\}", "g"), obj[key]);
    //$("#" + obj[key]).onclick = clickHandler
    //$("#" + obj[key]).trigger("click");
  }

  new_sh = $("#placeholder").prop("scrollHeight");
  //new_sh = document.body.scrollHeight;
  //console.log("333333333333:"+ new_sh);
  return s;
};

new QWebChannel(qt.webChannelTransport, function (channel) {
  external = channel.objects.external;
  external.FileMessageProgress.connect(fileMsgUploadProgress);
});

function appendHtml(msg) {  
  //判断是文件还是文本消息
 var msgid = msg.HTMLID;
 //console.log("-------USERIDUSERIDUSERIDUSERID---:" +msg.TYPE)
 //过滤相同id
 if(msgid){
  if ($('#' + msgid).length > 0) { 
    // 存在
    return false;
  }
 }
  if(msg.MSGTYPE == 0){
    if(msg.ISMORE == 0){
      $("#placeholder").append(external.msgRHtmlTmpl.format(msg));
      //$("#" + msgid).find('.void_png').css("display","none");
    }else if(msg.ISMORE == 1){  
      $("#placeholder").prepend(external.msgRHtmlTmpl.format(msg));
      $('.more').css('display','block');
     // $("#" + msgid).find('.void_png').css("display","none");
    }else if(msg.ISMORE ==3){
      $("#placeholder").prepend(external.msgRHtmlTmpl.format(msg));
      $('.more').css('display','block');
      //$("#" + msgid).find('.void_png').css("display","none");
    }
 
  }else if(msg.MSGTYPE == 1){
   
    if(msg.ISMORE == 0){
     
     //console.log(msg.FILENAME);
      $("#placeholder").append(external.msgRHtmlFile.format(msg));
    }else if(msg.ISMORE == 1){
      $("#placeholder").prepend(external.msgRHtmlFile.format(msg));
      $('.more').css('display','block');
    }else if(msg.ISMORE ==3){
      $("#placeholder").prepend(external.msgRHtmlFile.format(msg));
      $('.more').css('display','block');
    }

      if(msg.FILESTATUS == 1){
        //传输完成
      //隐藏接收按钮
      $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
      //隐藏取消按钮
      $('#'+ msgid).find('.btn_do').eq(1).css("display","none");

      //发送方判断群组个人
      if(msg.TYPE == 1){
        //隐藏接收按钮
      $("#"+ msgid).find('.btn_do').eq(0).css("display","none");
          //显示取消按钮
          $("#"+ msgid).find('.btn_do').eq(1).css("display","inline");
      }else{
          //进度条设置为已完成
          $("#" + msgid).find(".progress").css("display","none");
          
        $("#" + msgid).find(".open_s").css("display","inline");
         // $("#" + msgid).find(".open_s").html(" <a href='javascript:;' class='openFile'> 打 开 </a>");
          $("#" + msgid).find(".open_s").html("传输完成");
      }
      
      }else if(msg.FILESTATUS == 2){
  
        //隐藏接收按钮
      $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
      //隐藏取消按钮
      $('#'+ msgid).find('.btn_do').eq(1).css("display","none");
      //进度条设置为已取消
      $("#" + msgid).find(".progress").css("display","none");
      
      $("#" + msgid).find(".open_s").css("display","inline");
      $("#" + msgid).find(".open_s").text("已取消 ");
    }else{
        //隐藏接收按钮
        $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
        //隐藏取消按钮
        $('#'+ msgid).find('.btn_do').eq(1).css("display","inline");
    }

  }else if(msg.MSGTYPE == 2){
    
    $("#placeholder").append(external.msgRHtmlTmpl.format(msg));
    //$("#" + msgid).find('.void_png').css("display","inline");
  }
  //window.scrollTo(0,  document.body.scrollHeight);
  if(msg.ISMORE == 0 ){
    window.scrollTo(0, document.body.scrollHeight);
    //var ss =$("#placehoulder").prop("scrollHeight");
    //console.log("----------------------------:" + $('#placeholder')[0].scrollHeight);
   // var div = document.getElementById('placeholder');

   //window.scrollTo(0,  document.body.scrollHeight);
   //$('#placeholder').scrollTop(new_sh + 19900);
   // $('#placeholder').scrollTop(1800);
    //window.scrollTo(0,  document.body.scrollHeight);
  
  }else{
    //获取滚动条高度
		//var sh = $("#placeholder").prop("scrollHeight");
    //console.log("1111111111111111111") 
    //设置滚动条位置 
    console.log("++++++++++:" +(new_sh - sh)  + "-----------:"+msg.ISMORE);
    window.scrollTo(0, (new_sh - sh) + 50);
  }
  
}

function recvHtml(msg) {
  var msgid = msg.HTMLID;
  //console.log("-----------===================" + msg.FILESTATUS);
   //过滤相同id
 if(msgid){
  if ($('#' + msgid).length > 0) { 
    // 存在
    return false;
  }
 }
  //判断是文件还是文本消息
  if(msg.MSGTYPE == 0){
    if(msg.ISMORE == 0){
      $("#placeholder").append(external.msgLHtmlTmpl.format(msg));
     // $("#"+ msgid).find('.void_png').css("display","none");
    }else if(msg.ISMORE == 1){
      $("#placeholder").prepend(external.msgLHtmlTmpl.format(msg));
      $('.more').css('display','block');
      //$("#"+ msgid).find('.void_png').css("display","none");
    }else if(msg.ISMORE == 3){
      $("#placeholder").prepend(external.msgLHtmlTmpl.format(msg));
      $('.more').css('display','block');
      //$("#"+ msgid).find('.void_png').css("display","none");
    }
  }else if(msg.MSGTYPE == 1){
    if(msg.ISMORE == 0){
      $("#placeholder").append(external.msgLHtmlFile.format(msg));
    }else if(msg.ISMORE == 1){
      $("#placeholder").prepend(external.msgLHtmlFile.format(msg));
      $('.more').css('display','block');
    }else if(msg.ISMORE == 3){
      $("#placeholder").prepend(external.msgLHtmlFile.format(msg));
     $('.more').css('display','block');
    }
      if(msg.FILESTATUS == 1){
        //传输完成
      //隐藏接收按钮
      $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
      //隐藏取消按钮
      $('#'+ msgid).find('.btn_do').eq(1).css("display","none");
   
        //进度条设置为已完
        $("#" + msgid).find(".progress").css("display","none");
        $("#" + msgid).find(".open_s").css("display","inline");
        $("#" + msgid).find(".open_s").html(" <a href='javascript:;' class='openFile'> 打 开 </a>");
     
      }else if(msg.FILESTATUS == 2){
 
        //隐藏接收按钮
      $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
      //隐藏取消按钮
      $('#'+ msgid).find('.btn_do').eq(1).css("display","none");
      //进度条设置为已取消
      $("#" + msgid).find(".progress").css("display","none");
      $("#" + msgid).find(".open_s").css("display","inline");
      $("#" + msgid).find(".open_s").text("已取消 ");
    }
  }else if(msg.MSGTYPE == 2){
    
    $("#placeholder").append(external.msgLHtmlTmpl.format(msg));
   // $("#" + msgid).find('.void_png').css("display","inline");
  }
  
  if(msg.ISMORE == 0 ){
    //console.log("++++++++++:_________________");
    window.scrollTo(0, document.body.scrollHeight);

  }else{
    //console.log("++++++++++:" +(new_sh - sh) + "-----------:"+msg.ISMORE);
    //设置滚动条位置
    window.scrollTo(0, (new_sh - sh) + 50);
  }

}

//不显示更多了
function MoreEnd(){
  $('.more').css('cursor','default');
  $('.more').css('color','#999');
  $('.more').text("没有更多了");
}

//显示进度
function fileMsgUploadProgress(msgid, progress,iStatus , userid , isObjType) {
///////console.log("------------:"+msgid);

//console.log("-------------:"+iStatus);
//console.log("-------------:"+isObjType);

  $("#" + msgid).attr("userid" , userid);

  if(iStatus == 528 || iStatus == 527){
    //实时显示进度
    $("#" + msgid).find(".progress").css("display","inline");
    $("#" + msgid).find(".progress").text(progress);
    //隐藏接收按钮
    $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
    //显示取消按钮
    $('#'+ msgid).find('.btn_do').eq(1).css("display","inline");
  } else if (iStatus == 550) {
      //接收者接收完成
      //隐藏接收按钮
      $('#' + msgid).find('.btn_do').eq(0).css("display", "none");
      $("#" + msgid).find(".progress").css("display", "inline");
      $("#" + msgid).find(".open_s").css("display", "inline");
      $("#" + msgid).find(".progress").html(progress);
     // console.log("-------------:" + progress);

      //隐藏取消按钮
     // console.log("-------------:===========================================");
      $('#' + msgid).find('.btn_do').eq(1).css("display", "none");
      //进度条设置为已完成
      $("#" + msgid).find(".open_s").html("<a href='javascript:;' class='openFile'> 打 开 </a>");
  }

  else if ( iStatus == 551) {
    //发送者发送完成

      //判断组和个人
      if (isObjType == 0) {
          //隐藏接收按钮
          $('#' + msgid).find('.btn_do').eq(0).css("display", "none");
          $("#" + msgid).find(".progress").css("display", "inline");
          $("#" + msgid).find(".open_s").css("display", "inline");
          $("#" + msgid).find(".progress").html(progress);
         // console.log("-------------:" + progress);

          //隐藏取消按钮
        //  console.log("-------------:===========================================");
          $('#' + msgid).find('.btn_do').eq(1).css("display", "none");
          //进度条设置为已完成
          $("#" + msgid).find(".open_s").html("传输完成");
      } else {
          //隐藏接收按钮
          $('#' + msgid).find('.btn_do').eq(0).css("display", "none");
          $("#" + msgid).find(".progress").css("display", "inline");
          $("#" + msgid).find(".open_s").css("display", "inline");
          $("#" + msgid).find(".progress").html(progress);
         // console.log("-------------:" + progress);

          
      }
     
 
  
 
  } else if (iStatus == 700 ) {
      //发送者取消
      //隐藏接收按钮
      $('#' + msgid).find('.btn_do').eq(0).css("display", "none");
      //隐藏取消按钮
      $('#' + msgid).find('.btn_do').eq(1).css("display", "none");
      //进度条设置为已取消
      $("#" + msgid).find(".progress").text(progress);
      $("#" + msgid).find(".open_s").css("display", "inline");
      $("#" + msgid).find(".open_s").text("已取消 ");
  }

   else if (iStatus == 701) {


      //接收者取消


      //判断组和个人
      if (isObjType == 0) {
          //隐藏接收按钮
          $('#' + msgid).find('.btn_do').eq(0).css("display", "none");
          //隐藏取消按钮
          $('#' + msgid).find('.btn_do').eq(1).css("display", "none");
          //进度条设置为已取消
          $("#" + msgid).find(".progress").text(progress);
          $("#" + msgid).find(".open_s").css("display", "inline");
          $("#" + msgid).find(".open_s").text("已取消 ");
      } else {
          //隐藏接收按钮
          $('#' + msgid).find('.btn_do').eq(0).css("display", "none");
          //隐藏取消按钮
          $('#' + msgid).find('.btn_do').eq(1).css("display", "none");
          //进度条设置为已取消
          $("#" + msgid).find(".progress").text(progress);
      }
     
  }

}

function fileRecv(eventObj) {
  //点击接收按钮 
  var msgid = eventObj.getAttribute('mid');
  $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
    //显示进度
    $("#" + msgid).find(".progress").css("display","inline");
  
  external.fileRecv(msgid);  
}
var click_num = 1;
//显示更多
$(document).on('click','.more',function(){

  sh = $("#placeholder").prop("scrollHeight");
  
  external.showMore(click_num);
  click_num = click_num + 1;


})


$(document).on('click','.openFile',function(){
  var fileName = $(this).parent().parent().parent().parent().children().children().children().html();
  var msgid = $(this).parent().parent().parent().attr("id");
  var userid = $(this).parent().parent().parent().attr('userid');
 
  if(userid == ''){
    external.openFile(fileName, msgid,userid);  
  }else{
    external.openFile(null , msgid,userid);  
  }
  
  
})
// $(document).on('click','.openFile',function(){
//   var fileName = $(this).parent().parent().parent().parent().children().children().children().html();


//   var arr_file = fileName.split(' '); 
//   if( arr_file.length == 1 ){
//     external.openFile(arr_file[1]);  
//   }
//   else{
//     external.openFile(fileName);  
//   }
//   console.log(fileName);
  
// })

function fileCancel(eventObj) {
  //取消接收文件
  var msgid = eventObj.getAttribute("mid");
  $('#'+ msgid).find('.btn_do').eq(0).css("display","none");
  $("#" + msgid).find(".progress").css("display","none");
  $("#" + msgid).find(".open_s").css("display","inline");
  $("#" + msgid).find(".open_s").text("已取消 ");
  $('#'+ msgid).find('.btn_do').eq(1).css("display","none");


  eventObj.onclick=null; //移除点击事件
  
  external.fileCancel(msgid);

}

//右击消息体
$(document).on('mousedown','.msg_msg',function(e){
  if (e.which == 3) {
    x = e.pageX;
    y = e.pageY;
    var msgid = $(this).attr('ddd');
    var msg = $(this).text();
    //console.log("--------------"+msgid + "==========" + msg);
    external.clickReceive(msgid,msg);
  }
})

//左右击头像
$(document).on('mousedown','.header',function(e){
  
  if(e.which == 1){
    //左
    var userid = $(this).attr('userid');
    //console.log('useriduseriduser-------0' + userid);
    external.clickLeftHeader(userid);
  }else
  if (e.which == 3) {
    x = e.pageX;
    y = e.pageY;
    var chatType = $(this).attr("chatType");
    var userid = $(this).attr('userid');
      //console.log("((((((((((((((((((((((((((( " + chatType);
   // var msgid = $(this).attr('ddd');
    external.clickHeader(userid,chatType);
  }
})


