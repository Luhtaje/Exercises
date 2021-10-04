const express = require('express')
const mqtt = require('mqtt');
const path = require('path');
const { Database } = require('sqlite3');
const app = express();
const assert = require('assert')

//Set up sqlite variables
const sqlite3 = require('sqlite3').verbose();
const db = new sqlite3.Database('./db/temps.db');

//Connect to mqtt broker
var client = mqtt.connect('mqtt://127.0.0.1:1883')

//Subscribes to simulated sensor data topic 'sim/sensors/tmp'
//Eventhandler executed when client has connected to broker.
client.on('connect',() => {
	client.subscribe('sim/sensors/tmp');
})

//Inserts data from mqtt packet in to database.
//Executed when mqtt message event occurs (when broker publishes).
client.on('message', (topic,message) => {
	const data = JSON.parse(message);
	db.run(`INSERT INTO temps(samplenr,timestamp,temperature) VALUES(${data.samplenr},${data.timestamp},${data.temperature})`,[], (err)=> {
		assert.equal(err,null);
	})
});

// Use this function to interpolate between two colors
const colorLerp = (color1, color2, percentage) => {
	const [rStart, gStart, bStart] = [color1 & 0xff0000, color1 & 0xff00, color1 & 0xff];
	const [rDiff, gDiff, bDiff] = [
		(color2 & 0xff0000) - rStart,
		(color2 & 0xff00) - gStart,
		(color2 & 0xff) - bStart];

	return '#' + (Math.floor(rStart + rDiff * percentage) & 0xff0000
			| Math.floor(gStart + gDiff * percentage) & 0xff00
			| Math.floor(bStart + bDiff * percentage) & 0xff).toString(16).padStart(6, '0');
};


//Returns relative value between min and max temperatures(-30, 30)
tempToPercentage = (inputTemp) => {
	let temp;
	if(inputTemp > 30){
		temp = 30;
	}else if(inputTemp < -30){
		temp = -30;
	}else{
		temp = inputTemp;
	}

	const percentage = (temp+30)/60;
	return percentage;
};

//Gather data to a single object
createResponseObj = (temps) => {

	const minLimit = -15;
	const maxLimit = 25;

	//Get current temperature
	const currentTemperature = temps[temps.length-1].temperature;

	//Create artificial relativity of min/max based on constants
	let relative = tempToPercentage(currentTemperature);
	const color = colorLerp(0x0000ff,0xff0000,relative);

	//Calculates endpoint coordinate for the svg path.
	const yvalue = 725 - (550 * relative);

	//Initialize to current value
	let min = temps[0].temperature;
	let max = temps[0].temperature;
	let average = 0;

	//Loop through database entries to find min, max, and avg values.
	for (let index = 0; index < temps.length; index++) {

		const aTemp = temps[index].temperature;
		average += aTemp;
			
		if(aTemp < min) min = aTemp;
		if(aTemp > max) max = aTemp;
	}
	average = average / temps.length;
	
	return {
		color:color,
		length:yvalue,
		current:currentTemperature,
		average:average.toFixed(2),
		min:min,
		max:max
	};
};

app.listen(3000, ()=>{
	console.log('Server is listening')
});



/*///////////////////////////////////////////////////////////////////////////
Routes
///////////////////////////////////////////////////////////////////////////*/

app.get('/', async(req,res)=>{
	res.sendFile(path.resolve(__dirname,'home.html'));
});


//Get 100 latest entries in the database and return and object which holds color, temperature, avg, min and max.
app.get('/color', async (req,res)=>{
	let responseObject;
	db.all('SELECT * FROM temps ORDER BY id DESC LIMIT 100',[],(err,response) =>{
		//assert.equal(err,null);
		responseObject = createResponseObj(response);
		console.log(responseObject);
		res.status(200).send(JSON.stringify(responseObject)); 
	})
});