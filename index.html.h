#pragma once
#include "pagehelper.h"    
namespace index_html
{
CreatePageName; 
HTMLPAGE = R"===(
<!DOCTYPE HTML>
<html lang = "en">
  <head>
    <title>EspRelay</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0"> 
    <meta http-equiv="Cache-control" content="public">
    <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css" rel="stylesheet"/>
    <link href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700&display=swap" rel="stylesheet"/>
    <link href="https://cdnjs.cloudflare.com/ajax/libs/mdb-ui-kit/3.3.0/mdb.min.css" rel="stylesheet"/>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-timepicker/0.5.2/css/bootstrap-timepicker.min.css" integrity="sha512-/Ae8qSd9X8ajHk6Zty0m8yfnKJPlelk42HTJjOHDWs1Tjr41RfsSkceZ/8yyJGLkxALGMIYd5L2oGemy/x1PLg==" crossorigin="anonymous" />
    <script src="https://code.jquery.com/jquery-3.5.1.min.js" integrity="sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/bootstrap-timepicker/0.5.2/js/bootstrap-timepicker.min.js" integrity="sha512-2xXe2z/uA+2SyT/sTSt9Uq4jDKsT0lV4evd3eoE/oxKih8DSAsOF6LUb+ncafMJPAimWAXdu9W+yMXGrCVOzQA==" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/vue@2/dist/vue.js"></script>
  <style>
  body { background: gray;}
  h2 {
    color: white; 
    padding: 1% 1%;
  }  
  @media (max-width : 480px) {
      mobile_fix {
      padding:0;
      }
  }
 #time, #mqstatus
  {
    margin-top:3px;
    font-size:14px;
    color:silver;
    border:2px dashed #2E9AFE;
    padding:5px;
    width:70px;
    margin-left:5px;
    margin-bottom:3px;
    display: inline-block;
  }
  #mqstatus{
    width:108px;
  }
  .bootstrap-timepicker-widget table td input {
    font-size: 70%;
    width: 35px;
  }
  .fas {
    margin-right: 10px;
    margin-left: 2px;
    font-size: 110%;  
  }
  </style>
</head>
<body>
<h2>ESP Relay</h2>
<table  id="app" class="table table-bordered">
  <tbody v-for="n in numRel">
      <tr style="border-top: 3px solid white">
      <th scope="row" :id="'data-'+n"  :style="{ 'color': rColor[n-1] }">R{{n}} is {{rText[n-1]}}</th>
            <td>
                <div class="btn-group-lg" role="group" aria-label="Relay">
                    <button :disabled="rDis1[n-1]"  type="button" class="btn btn-success" :id="'on-'+n" :onclick="'setRelay('+n+', true);'">
              On
          </button>
                    <button :disabled="rDis2[n-1]"  type="button" class="btn btn-danger" :id="'off-'+n" :onclick="'setRelay('+n+', false);'">
              Off
                    </button>
                </div>
            </td>
        </tr>
       <tr>
          <th scope="row">Start
       <div style="margin-top: 5px" class="progress">
           <div
             class="progress-bar"
             role="progressbar"
            :style="{width: timePass[n-1]}"
             aria-valuenow="100"
             aria-valuemin="100"
             aria-valuemax="100">
           </div>
        </div> 
          
          </th>
            <td>
            <div class="input-group bootstrap-timepicker timepicker">
            <input :id="'timepicker'+n1(n)" type="text" class="form-control input-small">
            <span class="input-group-addon"><i class="fas fa-clock"></i></span>
              <button  :disabled="sDis1[n-1]"  type="button" class="btn" :class="{'btn-secondary': sAct1[n-1]}" :id="'send-'+n1(n)" :onclick="s1(n)">  
              OK 
          </button>
                    <button type="button" class="btn btn-light" :id="'clear-'+n1(n)" :onclick="d1(n)"> 
              No 
          </button>
            </div>
            </td>
        </tr>
        <tr style="border-bottom: 3px solid white">
     <th scope="row">Finish
        <div style="margin-top: 5px" class="progress">
           <div
             class="progress-bar"
             role="progressbar"
            :style="{width: timeLapse[n-1]}"
             aria-valuenow="100"
             aria-valuemin="100"
             aria-valuemax="100">
           </div>
        </div> 
      </th>
            <td>
            <div class="input-group bootstrap-timepicker timepicker">
            <input :id="'timepicker'+n2(n)" type="text" class="form-control input-small">
            <span class="input-group-addon"><i  class="fas fa-clock"></i></span>
                    <button  :disabled="sDis2[n-1]"  type="button" class="btn" :class="{'btn-secondary': sAct2[n-1]}" :id="'send-'+n2(n)" :onclick="s2(n)"> 
              OK 
          </button>
                    <button type="button" class="btn btn-light" :id="'clear-'+n2(n)" :onclick="d2(n)"> 
              No 
          </button>
            </div>
            </td>
        </tr>
      </tbody>
      <tbody>
        <tr style="border-bottom: 3px solid white">
            <th scope="row">Info</th>
            <td>
             <p id="time">{{time}}</p>{{ " " }}<p id="mqstatus">{{mqttst}}</p>
            </td>
        </tr>
      </tbody>
 </table>

<script>
  /*
  NUMBERS OF RELAYS
  */
  var NumRelays=2;

  var app = new Vue({
  el: '#app',
  methods: {
    n1: function (n) {
      return (n-1)*2+1;
    },
    n2: function (n) {
      return (n-1)*2+2;
    },
    s1: function (n) {
      return "sendTime("+this.n1(n)+","+n+", 'start')";
    },
    s2: function (n) {
       return "sendTime("+this.n2(n)+","+n+", 'stop')";
    },
    d1: function (n) {
      return "sendClear("+n+",'start')";
    },
    d2: function (n) {
       return "sendClear("+n+",'stop')";
    },
    connectWS : function(){
      console.log('Trying connect to WS...');       
      this.connection  = new WebSocket('ws://'+ window.location.hostname + '/ws');
      this.connection.onopen = function(e) {
      console.log("[open] Connection established");
      };

      this.connection.onmessage = function(event) {
     window.parseDataW(event.data);
      };
      this.connection.onclose = function(event) {
        if (event.wasClean) {
    console.log(`[close] Connection closed cleanly, code=${event.code} reason=${event.reason}`);
        } else {
    console.log('[close] Connection died');
        }
        setTimeout(function() {
    window.connectWSW();
        }, 1000);
        };
      this.connection.onerror = function(error) {
      console.log(`[error] ${error.message}`);
      };
    },

    parseData: function (data){
    //case 1 
     if (data.startsWith("status")){
       i=data.indexOf(":");
       e=data.substring(i+1);
       var jq=JSON.parse(e);
       console.log(e);
       var y=jq["relay"];          
       for (var i=0; i<y.length; i++){
         if (y[i]) {
           this.rText[i]="On";
           this.rDis1[i]=true;    
           this.rDis2[i]=false;   
           this.rColor[i]="red";       
        }
        else {
          this.rText[i]="Off";
          this.rDis1[i]=false;   
          this.rDis2[i]=true;                
          this.rColor[i]="green";   
            }
      } 
        var q=jq["timer"];
        for (var i=0; i<q.length; i++){
              if ((q[i].start_h)<100) {
                r3="AM";
                r1=q[i].start_h;
                if (r1>12) {r1-=12; r3="PM";}
        this.sDis1[i]=true;  
        this.sAct1[i]=false;       
                $('#timepicker'+(i*2+1).toString()).timepicker('setTime', r1+':'+q[i].start_m+r3);        
              }
              else{
        this.sDis1[i]=false;
        this.sAct1[i]=true;  
              }
              if ((q[i].stop_h)<100) {
                r3="AM";
                r1=q[i].stop_h;
                if (r1>12) {r1-=12; r3="PM";}
        this.sDis2[i]=true;
        this.sAct2[i]=false; 
                $('#timepicker'+(i*2+2).toString()).timepicker('setTime', r1+':'+q[i].stop_m+r3);
              }
              else {
        this.sDis2[i]=false;
        this.sAct2[i]=true;  
              };  
        var p=jq["time"];
        if (typeof c == 'undefined') c=new Date().getHours()*60+new Date().getMinutes();
        var a=p.h*60+p.m+(new Date()).getSeconds()/60;
        var bh=q[i].stop_h==24?0:(q[i].stop_h*60);
        var dh=q[i].start_h==24?0:(q[i].start_h*60);
        var b=bh+q[i].stop_m;
        var d=dh+q[i].start_m;
        this.timeLapse[i]=100.0-((b-a)*100.0)/(b-c)+'%';   
        this.timePass[i]=100.0-((d-a)*100.0)/(d-c)+'%';  
        this.time=p.h+((p.m<10)?":0":":")+p.m+((p.s<10)?":0":":")+p.s;   
       }
      };
     //case 2      
     if (data.startsWith("test")){
          i=data.indexOf(":");
          e=data.substring(i+1);
          console.log(e);
        };
     //case 3      
     if (data.startsWith("mqtt")){
          i=data.indexOf(":");
          e=data.substring(i+3);
          this.mqttst=e;
        };  
    }   
  },
  data: function() {
  z1=[];
  z2=[];
  z3=[];        
  z4=[];  
  z5=[];
  z6=[];  
  z7=[];
  z8=[];  
  z9=[]; 
  z10=[];      
    for (var i=0; i<NumRelays; i++) {
    z1.push("yellow");
    z2.push("Off"); 
    z3.push(false);   
    z4.push(true);    
    z5.push(false);   
    z6.push(false);   
    z7.push(true);    
    z8.push(true);    
    z9.push("0%");  
    z10.push("0%");  
  }
    return {
    numRel: NumRelays,
    connection: null,
    time: "00:00:00",
    rColor: z1,
    rText: z2,
    rDis1: z3,
    rDis2: z4,
    sDis1: z5,
    sDis2: z6,
    sAct1: z7,
    sAct2: z8,
    timeLapse: z9,
    timePass: z10,
    mqttst: "disconnected"
    }
  },
  created: function() {
      window.connectWSW=this.connectWS;
      window.parseDataW=this.parseData;   
      this.connectWS();
  }
})
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/mdb-ui-kit/3.3.0/mdb.min.js"></script>
<script type="text/javascript">
    function setRelay(i, s)
    {
         var xmlHttp = new XMLHttpRequest();
         xmlHttp.open( 'GET', '/Relay?number='+i.toString()+'&on='+s.toString(), true );
         xmlHttp.send( null );
    }
    function sendTime(i, j, t)
    {    var s=document.getElementById("timepicker"+i.toString()).value;
         console.log(s);
         var xmlHttp = new XMLHttpRequest();
         xmlHttp.open( 'GET', '/Timer?number='+(j).toString()+'&time='+s+'&st='+t, true );
         xmlHttp.send( null );

    }
    function sendClear(i,t)
    {    var xmlHttp = new XMLHttpRequest();
         xmlHttp.open( 'GET', '/Timer?number='+(i).toString()+'&time=88:00%20PM&st='+t, true );
         xmlHttp.send( null );

    }

    var ltp=$('.timepicker').length;
    for (var i=1; i<=ltp; i++){        
    $('#timepicker'+i.toString()).timepicker({
         minuteStep: 5,
         showInputs: false,
     disableFocus: true, 
    icons:{
         up: 'fas fa-angle-up',
         down: 'fas fa-angle-down'
          }
      }); 
    };
</script>

</body>
</html>

)===";
}
