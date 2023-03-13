const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
  <link rel="icon" href="https://e7.pngegg.com/pngimages/623/454/png-clipart-strawberry-strawberry-thumbnail.png">
  <title>LIVE HYDROPONIK</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" rel="stylesheet">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
      h1 { font-size: 2.0rem; }
      p { font-size: 2.0rem; }
      .units { font-size: 1.2rem; }
      .dht-labels{
        font-size: 1.5rem;
        vertical-align:middle;
        padding-bottom: 15px;
      }
    </style>
  </head>
  <body>
    <h1>MONITORING HYDROPONIK</h1>
    <p>
      <i class="fa fa-thermometer-half" style="font-size:3.0rem;color:#62a1d3;"></i> 
      <span class="dht-labels">Temperature : </span> 
      <span id="TValue">0</span>
      <sup class="units">&deg;C</sup>
    </p>
    <p>
      <i class="fa fa-thermometer-half" style="font-size:3.0rem;color:#62a1d3;"></i>
      <span class="dht-labels">Suhuair : </span>
      <span id="SHValue">0</span>
      <sup class="units">&deg;C</sup>
    </p>
    <p>
      <i class="fa fa-tint" style="font-size:3.0rem;color:#75e095;"></i>
      <span class="dht-labels">Humidity : </span>
      <span id="KValue">0</span>
      <sup class="units">%</sup>
    </p>
    <p>
      <i class="fa fa-tint" style="font-size:3.0rem;color:#75e095;"></i>
      <span class="dht-labels">PPM : </span>
      <span id="TDSValue">0</span>
      <sup class="units">%</sup>
    </p>
    <p>
      <i class="far fa-clock" style="font-size:1.0rem;color:#e3a8c7;"></i>
      <span style="font-size:1.0rem;">Time </span>
      <span id="time" style="font-size:1.0rem;"></span>
      
      <i class="far fa-calendar-alt" style="font-size:1.0rem;color:#f7dc68";></i>
      <span style="font-size:1.0rem;">Date </span>
      <span id="date" style="font-size:1.0rem;"></span>
    </P>
     <style>
      body {
        font-family: Arial, sans-serif;
        margin: 0;
        padding: 0;
      }
      h1 {
        text-align: center;
        margin-top: 20px;
      }
      .container {
        display: flex;
        justify-content: center;
        align-items: center;
        height: 10vh;
      }
      .switch {
        position: relative;
        display: inline-block;
        width: 150px;
        height: 55px;
      }
      .switch input {
        opacity: 0;
        width: 0;
        height: 0;
      }
      .slider {
        position: absolute;
        cursor: pointer;
        top: 0px;
        left: 10px;
        right: 10px;
        bottom: 0px;
        background-color: #ccc;
        -webkit-transition: .4s;
        transition: .4s;
      }
      .slider:before {
        position: absolute;
        content: "";
        height: 42px;
        width: 42px;
        left: 15px;
        bottom: 6px;
        background-color: black;
        -webkit-transition: .4s;
        transition: .4s;
      }
      input:checked + .slider {
        background-color: #32CD32;
      }
      input:focus + .slider {
        box-shadow: 0 0 1px #999;
      }
      input:checked + .slider:before {
        -webkit-transform: translateX(60px);
        -ms-transform: translateX(60px);
        transform: translateX(60px);
      }
    </style>
</head>
<body>
<h2>POMPA</h2>
    <div class="container">
    <h1>OFF</h1>
      <label class="switch">
        <input type="checkbox" onchange="toggleRelay(this)">
        <span class="slider"></span>
      </label>
      <h1>ON</h1>
    </div>
    <script>
      setInterval(function() {
        // Call a function repetatively with 2 Second interval
        getTemperatureData();
        getHumidityData();
        getPPMData();
        getSuhuairData();
      }, 2000); 
      
      setInterval(function() {
        Time_Date();
      }, 1000); 

      function getTemperatureData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("TValue").innerHTML =
            this.responseText;
          }
        };
        xhttp.open("GET", "readT", true);
        xhttp.send();
      }

      function getHumidityData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
          document.getElementById("KValue").innerHTML =
          this.responseText;
          }
        };
        xhttp.open("GET", "readK", true);
        xhttp.send();
      }
       function getSuhuairData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
          document.getElementById("SHValue").innerHTML =
          this.responseText;
          }
        };
        xhttp.open("GET", "readSH", true);
        xhttp.send();
      }

      function getPPMData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
          document.getElementById("TDSValue").innerHTML =
          this.responseText;
          }
        };
        xhttp.open("GET", "readTDS", true);
        xhttp.send();
      }

            function toggleRelay(element) {
        var xhr = new XMLHttpRequest();
        if (element.checked) {
          xhr.open("GET", "/toggle?state=on", true);
        } else {
          xhr.open("GET", "/toggle?state=off", true);
        }
        xhr.send();
      }
      
      function Time_Date() {
        var t = new Date();
        document.getElementById("time").innerHTML = t.toLocaleTimeString();
        var d = new Date();
        const dayNames = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday","Saturday"];
        const monthNames = ["January", "February", "March", "April", "May", "June","July", "August", "September", "October", "November", "December"];
        document.getElementById("date").innerHTML = dayNames[d.getDay()] + ", " + d.getDate() + "-" + monthNames[d.getMonth()] + "-" + d.getFullYear();
      }       
    </script>
    
  </body>
</html>
)=====";
