const express = require('express')
const path = require('path');
const app = express();

app.listen(3000, ()=>{
	console.log('Server is listening')
});



/*///////////////////////////////////////////////////////////////////////////
Routes
///////////////////////////////////////////////////////////////////////////*/

app.get('/', async(req,res)=>{
	res.sendFile(path.resolve(__dirname,'home.html'));
});