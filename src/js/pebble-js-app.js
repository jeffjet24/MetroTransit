//Works covered by CC BY-NC-SA 4.0
var maxTriesForSendingAppMessage = 3;
var timeoutForAppMessageRetry = 3000;
var timeoutForAPIRequest = 12000;
var lat, lon;
// Persist read a key's value. May be null!
var lastLat = localStorage.getItem(1);
var lastLon = localStorage.getItem(2);
var id;
var locationOptions = {
  enableHighAccuracy: true, 
  maximumAge: 2000, 
  timeout: 5000
};

// all the greenline stations
var target = {
  lat: 44.98331,
  lon: -93.277048,
  code: "TF1O",
  desc: "Target Field Station Platform 1"
};
var warehouse = {
  lat: 44.980122,
  lon: -93.273159,
  code: "WARE",
  desc: "Warehouse District Hennepin Ave Station"
};
var nicollet = {
  lat: 44.978478,
  lon: -93.269934,
  code: "5SNI",
  desc: "Nicollet Mall Station"
};
var government = {
  lat: 44.976826,
  lon: -93.265951,
  code: "GOVT",
  desc: "Government Plaza Station"
};
var downtown = {
  lat: 44.975049,
  lon: -93.259732,
  code: "DTE",
  desc: "Downtown East Station"
};
var westBank = {
  lat: 44.972095,
  lon: -93.245586,
  code: "WEBK",
  desc: "West Bank Station"
};
var eastBank = {
  lat: 44.973694,
  lon: -93.231075,
  code: "EABK",
  desc: "East Bank Station"
};
var stadiVill = {
  lat: 44.974354,
  lon: -93.223473,
  code: "STVI",
  desc: "Stadium Village Station"
};
var prospect = {
  lat: 44.971592,
  lon: -93.215324,
  code: "PSPK",
  desc: "Prospect Park Station"
};
var westgate = {
  lat: 44.967373,
  lon: -93.206253,
  code: "WGAT",
  desc: "Westgate Station"
};
var raymond = {
  lat: 44.963333,
  lon: -93.195862,
  code: "RAST",
  desc: "Raymond Ave Station"
};
var fairview = {
  lat: 44.956234,
  lon: -93.178458,
  code: "FAUN",
  desc: "Fairview Ave Station"
};
var snelling = {
  lat: 44.955662,
  lon: -93.166718,
  code: "SNUN",
  desc: "Snelling Ave Station"
};
var hamline = {
  lat: 44.955746,
  lon: -93.157051,
  code: "HMUN",
  desc: "Hamline Ave Station"
};
var lexington = {
  lat: 44.955681,
  lon: -93.146278,
  code: "LXUN",
  desc: "Lexington Pkwy Station"
};
var victoria = {
  lat: 44.955696,
  lon: -93.136306,
  code: "VIUN",
  desc: "Victoria St Station"
};
var dale = {
  lat: 44.955681,
  lon: -93.125946,
  code: "UNDA",
  desc: "Dale St Station"
};
var western = {
  lat: 44.955837,
  lon: -93.116363,
  code: "WEUN",
  desc: "Western Ave Station"
};
var capitol = {
  lat: 44.955734,
  lon: -93.105324,
  code: "UNRI",
  desc: "Capitol Rice St Station"
};
var robert = {
  lat: 44.954041,
  lon: -93.097458,
  code: "ROST",
  desc: "Robert St Station"
};
var tenthSt = {
  lat: 44.950168,
  lon: -93.097061,
  code: "10CE",
  desc: "10th St Station"
};
var central = {
  lat: 44.946098,
  lon: -93.092445,
  code: "CNST",
  desc: "Central Station"
};
var union = {
  lat: 44.947319,
  lon: -93.084684,
  code: "UNDP",
  desc: "Union Depot"
};

var stations = [target, warehouse, nicollet, government, downtown, westBank, 
                eastBank, stadiVill, prospect, westgate, raymond, fairview, 
                snelling, hamline, lexington, victoria, dale, western, capitol, 
                robert, tenthSt, central, union];

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
	var nearestStationStr;
	var east1, east2;



	//Creating and Opening the needed XMLHttpRequest Objects
	var xhrStation= new XMLHttpRequest();
  //xhrHash.open('GET','http://narwhy.pw/shibe/nethash/',true);
	var xhrEast= new XMLHttpRequest();
  //xhrDiff.open('GET','http://dogechain.info/chain/Dogecoin/q/getdifficulty?cache='+(Math.random()*1000000),true);
	var xhrWest= new XMLHttpRequest();


  
  
  
  


  

  

  
  
  
	//timeouts?
// 	xhr.timeout = timeoutForAPIRequest;
// 	xhrBTC.timeout = timeoutForAPIRequest;

// 	xhr.onload = function(e) {
// 		if (xhr.readyState == 4) {
// 			if (xhr.status == 200) {


// 				block=xhrBlock.responseText;
//         block=block+'';
				
//         hashrate=xhrHash.responseText;
//         console.log(hashrate+'');
        

// 				//Parsing the JSON Sources
// 				var res = JSON.parse(xhr.responseText);
// 				var resBTC = JSON.parse(xhrBTC.responseText);


// 				//doing the required Math and stuff
// 				pricePerK=(parseFloat(res.last)*1000);
// 				pricePerBTC=(parseFloat(resBTC.last)*100000000);
// 				difficulty=xhrDiff.responseText;
        
// 				hashrate=(parseFloat(hashrate)/1000000000);
// 				difficulty=parseFloat(difficulty);
        
//         //Doing some Formatting so everything fits in its space.
//         pricePerK=pricePerK.toFixed(2);
//         pricePerBTC=pricePerBTC.toFixed(0);
//         difficulty=difficulty.toFixed(1);
//         hashrate=hashrate.toFixed(0);
//         hashrate=hashrate+"GH/s";
//         //Updating the Pebble
        
//         console.log("I am running now!");
//         console.log(hashrate);
// 				sendAppMessage({
// 					'nearestStation': pricePerK,
// 					'eastbound': pricePerBTC,
// 					'westbound': block
// 				});

// 			} else {
// 				console.log('Request returned error code ' + xhr.status.toString());
// 				sendAppMessage({'item_name': 'Error: ' + xhr.statusText});
// 			}
// 		}
//   }
// 	xhr.ontimeout = function() {
// 		console.log('Error: request timed out!');
// 		sendAppMessage({'item_name': 'Error: Request timed out!'});
// 	};
// 	xhr.onerror = function(e) {
// 		console.log(JSON.stringify(e));
// 		sendAppMessage({'item_name': 'Error: Failed to connect!'});
// 	};
// xhr.send(null);
// xhrBTC.send(null);
// xhrBlock.send(null);
// xhrDiff.send(null);
// xhrHash.send(null);

}

function locationSuccess(pos) {
    console.log('Location changed!');
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
    lastLat = lat;
    lastLon = lon;
  }

function locationError(err) {
    console.log('location error (' + err.code + '): ' + err.message);
    lat = lastLat;
    lon = lastLon;
  }

Pebble.addEventListener('appmessage', function(e) {
	console.log('AppMessage received from Pebble: ' + JSON.stringify(e.payload));

	makeRequest();
});

Pebble.addEventListener("ready", function(e) {
	console.log("PEBBLEJS connected!" + e.ready);
  id = navigator.geolocation.watchPosition(locationSuccess, locationError, locationOptions);
	Pebble.sendAppMessage({"message": "ready"});
  
});
