'use strict';

const express = require('express');
const path = require('path');
const app = express();
const port = 3000

app.get('/favicon.ico', (req, res) => res.status(204));
app.use(express.static(__dirname + '/public'));


app.get('/', (req,res) => {
	res.sendFile(path.resolve(__dirname,"home.html"));
});

app.get('/:name', (req, res) => {
	
	let name = req.params.name;
	let age = req.query.age;


	if(age === undefined){
		res.sendFile(path.resolve(__dirname,"age.html"));
	}
	else{
		if(age >= 18){
			res.send("Hello " + name);
		}
		else{
			res.send("You are too young to view this website :( ");
		}
	}
	
});


app.get('/:name/:age', (req,res) => {
	let name = req.params.name;
	let age = req.query.age;

	if(age == null){
		res.redirect("http://localhost:3000/"+ name);
	}
	else{
		res.redirect("http://localhost:3000/" + name +"?age="+age);
	}
});



app.listen(port, ()=> {
	console.log('Exercise app listening at http://localhost:${port}')
});
