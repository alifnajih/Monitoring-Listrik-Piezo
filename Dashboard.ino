void handleRoot()
{
String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>

<meta charset="UTF-8">

<meta name="viewport" content="width=device-width, initial-scale=1">

<title> SIPEKA </title>

<style>

*{
margin:0;
padding:0;
box-sizing:border-box;
font-family:Segoe UI,Arial;
}

body{

background:#0f172a;

color:white;

padding:20px;

}

.container{

max-width:1200px;

margin:auto;

}

.header{

margin-bottom:25px;

}

.title{

font-size:36px;

font-weight:bold;

}

.subtitle{

color:#94a3b8;

margin-top:5px;

}

.grid{

display:grid;

grid-template-columns:repeat(auto-fit,minmax(250px,1fr));

gap:18px;

}

.card{

padding:20px;

border-radius:18px;

color:white;

box-shadow:0 5px 15px rgba(0,0,0,.35);

}

.blue{

background:linear-gradient(135deg,#2563eb,#3b82f6);

}

.green{

background:linear-gradient(135deg,#059669,#10b981);

}

.orange{

background:linear-gradient(135deg,#ea580c,#f59e0b);

}

.purple{

background:linear-gradient(135deg,#7c3aed,#a855f7);

}

.label{

font-size:18px;

opacity:.9;

}

.value{

font-size:42px;

font-weight:bold;

margin-top:12px;

}

.statusCard{

margin-top:20px;

background:#1e293b;

padding:20px;

border-radius:18px;

}

.status{

display:inline-block;

padding:8px 16px;

border-radius:20px;

font-weight:bold;

}

.connected{

background:#22c55e;

}

.apmode{

background:#2563eb;

}

.offline{

background:#ef4444;

}

.button{

display:inline-block;

margin-top:15px;

padding:12px 20px;

background:#3b82f6;

color:white;

text-decoration:none;

border-radius:10px;

}

#graphContainer{

display:none;

margin-top:20px;

}

#graphArea{

display:flex;

flex-direction:column;

gap:20px;

background:#0f172a;

border:2px dashed #475569;

border-radius:15px;

padding:20px;

}

.chartCard{

width:100%;

background:#111827;

padding:20px;

border-radius:15px;

}

.chartCard h3{

margin-top:0;

color:white;

}

.chartCard canvas{

width:100% !important;

height:250px !important;

}


</style>

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

</head>

<body>

<div class="container">

<div class="header">

<div class="title">

⚡ SIPEKA

</div>

<div class="subtitle">

Sistem Pemanen Energi Langkah Kaki V2.0

</div>

</div>

<div class="grid">

<div class="card blue">

<div class="label">Voltage</div>

<div class="value" id="voltage">

Loading...

</div>

</div>

<div class="card green">

<div class="label">Current</div>

<div class="value" id="current">

Loading...

</div>

</div>

<div class="card orange">

<div class="label">Power</div>

<div class="value" id="power">

Loading...

</div>

</div>

<div class="card purple">

<div class="label">Energy</div>

<div class="value" id="energy">

Loading...

</div>

</div>

</div>

<div id="graphContainer">

<div class="statusCard">

<h2>📈 Realtime Monitoring</h2>

<div id="graphArea">

    <div class="chartCard">

        <h3>Voltage Grafik</h3>

        <canvas id="voltageChart"></canvas>

    </div>

    <div class="chartCard">

        <h3>Current Grafik</h3>

        <canvas id="currentChart"></canvas>

    </div>

    <div class="chartCard">

        <h3>Power Grafik</h3>

        <canvas id="powerChart"></canvas>

    </div>

</div>

</div>

</div>

<div class="statusCard">


<h2>System Status</h2>

<br>

<p>

WiFi :

<span id="wifiStatus">

Loading...

</span>

</p>

<br>

<p>

IP :

<span id="ip">

Loading...

</span>

</p>

<br>

<a href="/wifi" class="button">

⚙ WiFi Settings

</a>

</div>

</div>

<script>




let voltageChart;
let currentChart;
let powerChart;

let chartCreated = false;

// Timer reset grafik
let chartCounter = 0;
const MAX_POINT = 60;


function updateData(){

    fetch('/data')
    .then(response => response.json())
    .then(data => {

        document.getElementById("voltage").innerHTML = data.voltage + " V";
        document.getElementById("current").innerHTML = data.current + " mA";
        document.getElementById("power").innerHTML   = data.power + " W";
        document.getElementById("energy").innerHTML  = data.energy + " Wh";

        let wifi="";

        if(data.wifi=="CONNECTED")
            wifi='<span class="status connected">CONNECTED</span>';
        else if(data.wifi=="AP MODE")
            wifi='<span class="status apmode">AP MODE</span>';
        else
            wifi='<span class="status offline">OFFLINE</span>';

        document.getElementById("wifiStatus").innerHTML = wifi;
        document.getElementById("ip").innerHTML = data.ip;

        const graphContainer = document.getElementById("graphContainer");

        if(data.graph){

            graphContainer.style.display="block";

            if(!chartCreated){

                createCharts();

                chartCreated=true;

            }

            updateCharts(data);

        }
        else{

            graphContainer.style.display="none";

        }

    });

}


function createCharts(){

    // Voltage Chart
    voltageChart = new Chart(
        document.getElementById("voltageChart"),
        {
            type:"line",
            data:{
                labels:[],
                datasets:[{
                    data:[],
                    borderColor:"#3b82f6",
                    backgroundColor:"rgba(59,130,246,.15)",
                    fill:true,
                    tension:0.3,
                    pointRadius:0
                }]
            },
options:{
    responsive:true,
    maintainAspectRatio:false,
    animation:false,

    plugins:{
        legend:{
            display:false
        }
    },

    scales:{

        x:{

            ticks:{
                maxTicksLimit:6,
                color:"#94a3b8"
            },

            grid:{
                color:"rgba(255,255,255,0.08)"
            }

        },

        y:{

            beginAtZero:false,

            ticks:{
                color:"#94a3b8"
            },

            grid:{
                color:"rgba(255,255,255,0.08)"
            }

        }

    }

}
        }
    );

    // Current Chart
    currentChart = new Chart(
        document.getElementById("currentChart"),
        {
            type:"line",
            data:{
                labels:[],
                datasets:[{
                    data:[],
                    borderColor:"#10b981",
                    backgroundColor:"rgba(16,185,129,.15)",
                    fill:true,
                    tension:0.3,
                    pointRadius:0
                }]
            },
options:{
    responsive:true,
    maintainAspectRatio:false,
    animation:false,

    plugins:{
        legend:{
            display:false
        }
    },

    scales:{

        x:{

            ticks:{
                maxTicksLimit:6,
                color:"#94a3b8"
            },

            grid:{
                color:"rgba(255,255,255,0.08)"
            }

        },

        y:{

            beginAtZero:false,

            ticks:{
                color:"#94a3b8"
            },

            grid:{
                color:"rgba(255,255,255,0.08)"
            }

        }

    }

}
        }
    );

    // Power Chart
    powerChart = new Chart(
        document.getElementById("powerChart"),
        {
            type:"line",
            data:{
                labels:[],
                datasets:[{
                    data:[],
                    borderColor:"#f59e0b",
                    backgroundColor:"rgba(245,158,11,.15)",
                    fill:true,
                    tension:0.3,
                    pointRadius:0
                }]
            },
options:{
    responsive:true,
    maintainAspectRatio:false,
    animation:false,

    plugins:{
        legend:{
            display:false
        }
    },

    scales:{

        x:{

            ticks:{
                maxTicksLimit:6,
                color:"#94a3b8"
            },

            grid:{
                color:"rgba(255,255,255,0.08)"
            }

        },

        y:{

            beginAtZero:false,

            ticks:{
                color:"#94a3b8"
            },

            grid:{
                color:"rgba(255,255,255,0.08)"
            }

        }

    }

}
        }
    );

}


function updateCharts(data){

    if(!chartCreated) return;

    const waktu = new Date().toLocaleTimeString();

    voltageChart.data.labels.push(waktu);
    voltageChart.data.datasets[0].data.push(parseFloat(data.voltage));

    currentChart.data.labels.push(waktu);
    currentChart.data.datasets[0].data.push(parseFloat(data.current));

    powerChart.data.labels.push(waktu);
    powerChart.data.datasets[0].data.push(parseFloat(data.power));

    chartCounter++;

    // Reset otomatis setiap 60 titik
    if(chartCounter >= MAX_POINT){

        chartCounter = 0;

        voltageChart.data.labels = [];
        currentChart.data.labels = [];
        powerChart.data.labels = [];

        voltageChart.data.datasets[0].data = [];
        currentChart.data.datasets[0].data = [];
        powerChart.data.datasets[0].data = [];

    }

    voltageChart.update("none");
    currentChart.update("none");
    powerChart.update("none");

}


updateData();

setInterval(updateData,1000);

</script>

</body>

</html>

)rawliteral";

server.send(200,"text/html",html);

}


void handleWiFiPage()
{
String html = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<meta name="viewport"
content="width=device-width,initial-scale=1">

<title>WiFi Settings</title>

<style>

*{
margin:0;
padding:0;
box-sizing:border-box;
font-family:Segoe UI,Arial;
}

body{

background:#0f172a;

color:white;

padding:20px;

}

.container{

max-width:600px;

margin:auto;

}

.card{

background:#1e293b;

padding:30px;

border-radius:20px;

box-shadow:0 10px 25px rgba(0,0,0,.35);

}

.title{

font-size:34px;

font-weight:bold;

}

.subtitle{

margin-top:5px;

color:#94a3b8;

margin-bottom:25px;

}

.statusBox{

background:#334155;

padding:15px;

border-radius:12px;

margin-bottom:20px;

}

.label{

font-size:14px;

color:#94a3b8;

margin-bottom:6px;

}

.value{

font-size:18px;

font-weight:bold;

}

input{

width:100%;

padding:14px;

margin-top:8px;

margin-bottom:18px;

border:none;

border-radius:10px;

background:#475569;

color:white;

font-size:16px;

}

input:focus{

outline:none;

border:2px solid #3b82f6;

}

.saveBtn{

width:100%;

padding:14px;

background:#10b981;

border:none;

border-radius:10px;

color:white;

font-size:18px;

font-weight:bold;

cursor:pointer;

}

.backBtn{

display:block;

width:100%;

padding:14px;

margin-top:12px;

background:#3b82f6;

text-align:center;

text-decoration:none;

color:white;

border-radius:10px;

font-weight:bold;

}

.footer{

margin-top:20px;

text-align:center;

font-size:13px;

color:#94a3b8;

}

</style>

</head>

<body>

<div class="container">

<div class="card">

<div class="title">

📶 WiFi Settings

</div>

<div class="subtitle">

Configure ESP32 Network Connection

</div>
)rawliteral";

html += R"rawliteral(

<div class="statusBox">

<div class="label">

Current Status

</div>

<div class="value">

)rawliteral";

if(apMode)
    html += "🔵 AP MODE";

else if(wifiConnected)
    html += "🟢 CONNECTED";

else
    html += "🔴 OFFLINE";

html += R"rawliteral(

</div>

</div>

<div class="statusBox">

<div class="label">

Current IP Address

</div>

<div class="value">

)rawliteral";

html += ipAddress;
html += R"rawliteral(

</div>

</div>

<form action="/save" method="GET">

<div class="label">

WiFi Name (SSID)

</div>

<input
type="text"
name="ssid"
placeholder="Enter WiFi Name">

<div class="label">

WiFi Password

</div>

<input
type="password"
name="pass"
placeholder="Enter Password">

<button
class="saveBtn"
type="submit">

💾 SAVE WIFI

</button>

</form>

<a
href="/"
class="backBtn">

🏠 BACK TO DASHBOARD

</a>

<div class="footer">

Sistem Pemanen Enenrgy Langkah Kaki V2.0

</div>

</div>

</div>

</body>

</html>

)rawliteral";
server.send(200,"text/html",html);
}


void handleSaveWiFi()
{
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    if(ssid.length() == 0)
    {
        server.send(200, "text/html",
        "<h2>SSID tidak boleh kosong!</h2><br><a href='/wifi'>Kembali</a>");
        return;
    }

    prefs.begin("wifi", false);

    prefs.putString("ssid", ssid);
    prefs.putString("pass", pass);

    prefs.end();

    WiFi.disconnect(true);
    delay(1000);
    connectWiFi(ssid, pass);

    server.send(200, "text/html",
    "<h2>WiFi berhasil disimpan.</h2><p>ESP32 akan mencoba terhubung...</p>");
    if(wifiConnected)
{
    server.send(200,"text/html",
    "<h2>Berhasil terhubung ke WiFi.</h2>"
    "<p>Silakan buka Dashboard menggunakan IP baru.</p>");
}

else
{
    startAP();

    server.send(200,"text/html",
    "<h2>Gagal terhubung ke WiFi.</h2>"
    "<p>ESP32 kembali ke AP MODE.</p>"
    "<br><a href='/wifi'>Kembali</a>");
}

}

void handleData()
{
    String json="{";

    json+="\"voltage\":"+String(voltage,2)+",";
    json+="\"current\":"+String(current,2)+",";
    json+="\"power\":"+String(power,3)+",";
    json+="\"energy\":"+String(energyWh,4)+",";

    json += "\"graph\":";
    json += wifiConnected ? "true," : "false,";

    if(apMode)
        json+="\"wifi\":\"AP MODE\",";
    else if(wifiConnected)
        json+="\"wifi\":\"CONNECTED\",";
    else
        json+="\"wifi\":\"OFFLINE\",";

    json+="\"ip\":\""+ipAddress+"\"";

    json+="}";

    server.send(200,"application/json",json);
}