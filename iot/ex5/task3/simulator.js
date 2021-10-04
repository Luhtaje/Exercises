'use strict';

const mqtt = require('mqtt');


const addr = 'mqtt://127.0.0.1:1883';  // replace the xs with your broker's IP address
const t = 2;  // modify to change the sending interval

let count = 0;
let tmp = 20;
let ts = 0;


const client = mqtt.connect(addr);


setInterval(() => {
	const obj = {
		samplenr: count,
		timestamp: ts,
		temperature: tmp
	}
	tmp += Math.floor(Math.random() * 3 - 1);
	client.publish('sim/sensors/tmp', JSON.stringify(obj));
	count += 1;
	ts += t;
}, t * 1000);
