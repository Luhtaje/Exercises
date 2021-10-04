'use strict';

const path = require('path');
const express = require('express');
const app = express();
const port = 3000

app.get('/favicon.ico', (req, res) => res.status(204));
app.use( express.static( "public" ) );
app.set('view engine', 'ejs');


app.get('/', (req, res) => {
	res.sendFile(path.resolve(__dirname,"home.html"));
});


app.get('/image', (req, res) => {

	let invalidNumberText = 'Number is invalid. If you are so smart to place input straight into the url field I believe you can only use numbers ranging from 1-6';
	let validNumberText = 'Click the button to roll a random number!';
	let imageNumber = req.query.number;
	console.log(req.query.number);
	const templateObj = {};

	 if( imageNumber >= 1  && imageNumber <= 6){
		templateObj.number =imageNumber;
		templateObj.text = validNumberText;
		res.render('die.ejs', templateObj);
	}
	else
	{
		templateObj.number = 'error';
		templateObj.text = invalidNumberText; 
		res.render('die.ejs', templateObj);
	}  

});




app.listen(port, ()=> {
	console.log('Exercise app listening at http://localhost:${port}')
});