'use strict';

const express = require('express');
const path = require('path');
const os = require('os');
const async = require('async');
const port = 3000;
const app = express();

app.use( express.static("public"));

app.get('/', async (req,res) => {
    res.sendFile(path.resolve(__dirname,"public/index.html"));
});

app.get('/freemem', async (req,res) => {
	const memFree = os.freemem();
	res.send({memFree:memFree});
});

app.get('/totalmem', async (req,res) => {
	const memTotal = os.totalmem();
	res.send({memTotal:memTotal});
});

app.listen(port, ()=> {
	console.log('Exercise app listening at http://localhost:${port}')
});
