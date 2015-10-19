//Works covered by CC BY-NC-SA 4.0
var maxTriesForSendingAppMessage = 3;
var timeoutForAppMessageRetry = 3000;
var timeoutForAPIRequest = 3000;
var updateDataInterval = 60000;

// Persist read a key's value. May be null!
if((localStorage.getItem(1) === null) || (localStorage.getItem(2) === null)){
  var lat, lon;
}else{
  // getting the previous lat
  var lat = localStorage.getItem(1);
  //getting the previous lon
  var lon = localStorage.getItem(2);
}

var locationOptions = {
  enableHighAccuracy: true, 
  maximumAge: 30000, 
  timeout: 5000
};



console.log("starting javascript");
function sendAppMessage(message, numTries, transactionId) {
	numTries = numTries || 0;
	if (numTries < maxTriesForSendingAppMessage) {
		numTries++;
		console.log('Sending AppMessage to Pebble: ' + JSON.stringify(message));
		Pebble.sendAppMessage(
			message, function() {}, function(e) {
				console.log('Failed sending AppMessage for transactionId:' + e.data.transactionId + '. Error: ' + e.data.error.message);
				setTimeout(function() {
					sendAppMessage(message, numTries, e.data.transactionId);
				}, timeoutForAppMessageRetry);
			}
		);
	} else {
		console.log('Failed sending AppMessage for transactionId:' + transactionId + '. Bailing. ' + JSON.stringify(message));
	}
}
function makeRequest() {
	var nearestStationStr, nearestStationCode;
	var east1, east2;
  var west1, west2;
  navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
	//Creating and Opening the needed XMLHttpRequest Object
	var xhr = new XMLHttpRequest();
  xhr.open('GET',"http://narwhy.pw/greenline/api.php?cx="+lat+"&cy=" + lon + "&format=json", true);
  xhr.send();
	//timeouts?
	xhr.timeout = timeoutForAPIRequest;

	xhr.onload = function(e) {
		if (xhr.readyState == 4) {
			if (xhr.status == 200) {
        console.log(xhr.responseText);
        var res = JSON.parse(xhr.responseText);
        nearestStationStr = res.stationName;
        nearestStationCode = res.stationID;
        east1 = res.EastDeparture1;
        east2 = res.EastDeparture2;
        west1 = res.WestDeparture1;
        west2 = res.WestDeparture2;
        console.log(nearestStationStr);
				console.log(nearestStationCode);
        console.log(east1);
        console.log(east2);
        console.log(west1);
        console.log(west2);
        
        
        //console.log("I am running now!");
        //Updating the Pebble
				sendAppMessage({
					'nearestStation': nearestStationStr,
          'nearestStationCode': nearestStationCode,
					'eastbound': east1 + ", " + east2,
					'westbound': west1 + ", " + west2
				});
			} else {
				console.log('Request returned error code ' + xhr.status.toString());
				sendAppMessage({'item_name': 'Error: ' + xhr.statusText});
			}
		}
    
  };
	xhr.ontimeout = function() {
		console.log('Error: request timed out!');
		sendAppMessage({'item_name': 'Error: Request timed out!'});
	};
	xhr.onerror = function(e) {
		console.log(JSON.stringify(e));
		sendAppMessage({'item_name': 'Error: Failed to connect!'});
	};
  xhr.send(null);
  
  setTimeout(function() { makeRequest(); }, updateDataInterval);
  //intervalID = window.setTimeout(progressSlide, 10000/speed);
}

function locationSuccess(pos) {
    console.log('Got Location!');
    lat = pos.coords.latitude;
    lon = pos.coords.longitude;
    console.log('lat= ' + lat + ' lon= ' + lon);
    var latKey = 1;
    var lonKey = 2;
    // Persist write a key with associated value
    // storing the lat and lon in case the pebble cant load the
    // location next time
    localStorage.setItem(latKey, lat);
    localStorage.setItem(lonKey, lon);
}
// function for when the device cannot get the location.
function locationError(err) {
    console.log('location error (' + err.code + '): ' + err.message);
    if((localStorage.getItem(1) === null) || (localStorage.getItem(2) === null)){
      lat = 0;
      lon = 0;
    }else{
      // getting the previous lat
      lat = localStorage.getItem(1);
      //getting the previous lon
      lon = localStorage.getItem(2);
    }
}
// event listener for when the javascript sends a message to the pebble. 
Pebble.addEventListener('appmessage', function(e) {
	console.log('AppMessage received from Pebble: ' + JSON.stringify(e.payload));
	makeRequest();
});

// event listern for when the pebble app has loaded and is ready for connections
Pebble.addEventListener("ready", function(e) {
	console.log("PEBBLEJS connected!" + e.ready);
  makeRequest();
});






















// comments, cause I spent a while hard coding things, in case I need it again, its here:
// // all the greenline stations
// var target = {
//   lat: 44.98331,
//   lon: -93.277048,
//   code: "TF1O",
//   desc: "Target Field Station Platform 1"
// };
// var warehouse = {
//   lat: 44.980122,
//   lon: -93.273159,
//   code: "WARE",
//   desc: "Warehouse District Hennepin Ave Station"
// };
// var nicollet = {
//   lat: 44.978478,
//   lon: -93.269934,
//   code: "5SNI",
//   desc: "Nicollet Mall Station"
// };
// var government = {
//   lat: 44.976826,
//   lon: -93.265951,
//   code: "GOVT",
//   desc: "Government Plaza Station"
// };
// var downtown = {
//   lat: 44.975049,
//   lon: -93.259732,
//   code: "DTE",
//   desc: "Downtown East Station"
// };
// var westBank = {
//   lat: 44.972095,
//   lon: -93.245586,
//   code: "WEBK",
//   desc: "West Bank Station"
// };
// var eastBank = {
//   lat: 44.973694,
//   lon: -93.231075,
//   code: "EABK",
//   desc: "East Bank Station"
// };
// var stadiVill = {
//   lat: 44.974354,
//   lon: -93.223473,
//   code: "STVI",
//   desc: "Stadium Village Station"
// };
// var prospect = {
//   lat: 44.971592,
//   lon: -93.215324,
//   code: "PSPK",
//   desc: "Prospect Park Station"
// };
// var westgate = {
//   lat: 44.967373,
//   lon: -93.206253,
//   code: "WGAT",
//   desc: "Westgate Station"
// };
// var raymond = {
//   lat: 44.963333,
//   lon: -93.195862,
//   code: "RAST",
//   desc: "Raymond Ave Station"
// };
// var fairview = {
//   lat: 44.956234,
//   lon: -93.178458,
//   code: "FAUN",
//   desc: "Fairview Ave Station"
// };
// var snelling = {
//   lat: 44.955662,
//   lon: -93.166718,
//   code: "SNUN",
//   desc: "Snelling Ave Station"
// };
// var hamline = {
//   lat: 44.955746,
//   lon: -93.157051,
//   code: "HMUN",
//   desc: "Hamline Ave Station"
// };
// var lexington = {
//   lat: 44.955681,
//   lon: -93.146278,
//   code: "LXUN",
//   desc: "Lexington Pkwy Station"
// };
// var victoria = {
//   lat: 44.955696,
//   lon: -93.136306,
//   code: "VIUN",
//   desc: "Victoria St Station"
// };
// var dale = {
//   lat: 44.955681,
//   lon: -93.125946,
//   code: "UNDA",
//   desc: "Dale St Station"
// };
// var western = {
//   lat: 44.955837,
//   lon: -93.116363,
//   code: "WEUN",
//   desc: "Western Ave Station"
// };
// var capitol = {
//   lat: 44.955734,
//   lon: -93.105324,
//   code: "UNRI",
//   desc: "Capitol Rice St Station"
// };
// var robert = {
//   lat: 44.954041,
//   lon: -93.097458,
//   code: "ROST",
//   desc: "Robert St Station"
// };
// var tenthSt = {
//   lat: 44.950168,
//   lon: -93.097061,
//   code: "10CE",
//   desc: "10th St Station"
// };
// var central = {
//   lat: 44.946098,
//   lon: -93.092445,
//   code: "CNST",
//   desc: "Central Station"
// };
// var union = {
//   lat: 44.947319,
//   lon: -93.084684,
//   code: "UNDP",
//   desc: "Union Depot"
// };

// var stations = [target, warehouse, nicollet, government, downtown, westBank, 
//                 eastBank, stadiVill, prospect, westgate, raymond, fairview, 
//                 snelling, hamline, lexington, victoria, dale, western, capitol, 
//                 robert, tenthSt, central, union];























