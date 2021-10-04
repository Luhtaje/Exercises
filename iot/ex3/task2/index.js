'use strict';

const express = require('express');
const bodyParser = require('body-parser');
const assert = require('assert');
const sqlite3 = require('sqlite3').verbose();

const app = express();
app.use(bodyParser.urlencoded({extended: true}));

const db = new sqlite3.Database('./db/cars.db');

//Returns all entires in the database
app.get('/', async (req, res) => {
	
	const sql = `SELECT * FROM cars ORDER BY Id`;
	db.all(sql,[], function(err,data){
		assert.equal(err,null);
		res.status(200).send(data);
	})
});

//Returns entry specified by ID
app.get('/:id', async (req, res) => {

	db.all(`SELECT * FROM cars WHERE id = ${req.params.id}`,[],function(err,data){
		assert.equal(err,null);
		res.status(200).send(data);
	})
});

//Adds new entry to database
app.post('/', async (req, res) => {

	/* 
	I know the task says to generate ID on the server, but if the database has such feature built in,
	I'm going to use that feature. Also we already generated ID's in a previous task.

	const car = req.body;  // Probably unsafe to treat the entire body as a car object, but will do for the task
	car.id = Math.floor(Math.random() * 0xffffff).toString(16);
	 */
	
	db.run(`INSERT INTO cars(make) VALUES("${req.body.make}")`,[], function(err){
		assert.equal(err,null);
		res.status(200).send({id : this.lastID, make : req.body.make});
	})
});

//Deletes ID specified entry from database 
app.delete('/:id', async (req, res) => {

	const sql = `DELETE FROM cars WHERE id = ${req.params.id}`;
	db.run(sql,[],function(err){
		assert.equal(err,null);
		res.status(200).send('Entry deleted');
	})
});

app.listen(3000);
