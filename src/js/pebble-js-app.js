//Works covered by CC BY-NC-SA 4.0

var maxTriesForSendingAppMessage = 3;
var timeoutForAppMessageRetry = 3000;
var timeoutForAPIRequest = 12000;

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
	var west1, west2;
  var lat, lon;
  // Persist read a key's value. May be null!
  var lastLat = localStorage.getItem(1);
  var lastLon = localStorage.getItem(2);



	//Creating and Opening the needed XMLHttpRequest Objects
	//var xhrStation= new XMLHttpRequest();
  //xhrHash.open('GET','http://narwhy.pw/shibe/nethash/',true);
	//var xhrEast= new XMLHttpRequest();
  //xhrDiff.open('GET','http://dogechain.info/chain/Dogecoin/q/getdifficulty?cache='+(Math.random()*1000000),true);
	//var xhrWest= new XMLHttpRequest();


  
  
  
  
  var id;

  var locationOptions = {
    enableHighAccuracy: true, 
    maximumAge: 0, 
    timeout: 5000
  };

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

  Pebble.addEventListener('ready',
    function(e) {
      // Get location updates
      id = navigator.geolocation.watchPosition(locationSuccess, locationError, locationOptions);
    }
  );

  
  
  
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

Pebble.addEventListener('ready', function(e) {});

Pebble.addEventListener('appmessage', function(e) {
	console.log('AppMessage received from Pebble: ' + JSON.stringify(e.payload));

	makeRequest();
});

Pebble.addEventListener("ready", function(e) {
	console.log("PEBBLEJS connected!" + e.ready);
	Pebble.sendAppMessage({"message": "ready"});
});
