'use strict';

const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const fs = require('fs');
const util = require('util');
const MongoClient = require('mongodb').MongoClient;
const assert = require('assert');
const { ClientRequest } = require('http');
const { ObjectId } = require('bson');
const { response } = require('express');

const app = express();
app.use(bodyParser.urlencoded({extended: true}));

const url= 'mongodb://localhost:27017';
const dbName = 'carDealership';
const client = new MongoClient(url);
const db = client.db(dbName);
const collection = db.collection('cars');


//Connect to database
client.connect(err=>{
	assert.equal(err,null);
	console.log('Connected to database');
})

app.listen(3000);

//Returns all elements in cars collection.
app.get('/', async (req, res) => {

	try{
		const cars = await collection.find().toArray();
		console.log(cars);
		res.status(200).send(cars);
	}
	catch(err){
		res.status(500).send();
	}
});

//Returns specified document by id
app.get('/:id', async (req, res) => {

 	try{
		const cars = await collection.findOne({_id : ObjectId(req.params.id)})
		res.status(200).send(JSON.stringify(cars));
	}
	catch(err){
		res.status(500).send();
	}
});

//Returns all documents by specified make 
app.get('/makes/:make', async(req,res) => {

	try{
		const cars = await collection.find({make : req.params.make}).toArray();
		res.status(200).send(cars);
	}
	catch(err){
		res.status(500).send(err)
	}

})

//Add an document to the database
app.post('/', async (req, res) => {

	try{
		await collection.insertOne({make:req.body.make});
		res.status(200).send('Element added');
	}
	catch(err){
		res.status(500).send(err);
	}

});


//Delete document specified by id from database  
app.delete('/:id', async (req, res) => {
	
	try{
		await collection.deleteOne({_id : ObjectId(req.params.id)});
		res.status(200).send('Element deleted');
	}
	catch(err){
		res.status(500).send(err);
	}
});