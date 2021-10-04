'use strict';

const express = require('express');
const cookieParser = require('cookie-parser');
const bodyParser = require('body-parser');
const { text } = require('express');
const port = 3000;

const app = express();

app.use(cookieParser());
app.use(bodyParser.urlencoded({extended: true}));
app.set('view engine', 'ejs');

app.get('/favicon.ico', (req, res) => res.status(204));


app.get('/', (req, res) => {
    updateView(req, res);
});

//Post a new event
app.post('/events', (req, res) => {

    //Create expirydate
    var expiryDate = new Date();

    //Ugly check for input validity but rather this than redo whole program.
    //Prevents input that is in the past
    const eventDate = new Date(req.body.date);
    if((eventDate.getTime() + toMillis(req.body.time) - expiryDate.getTime() - 3*60*60*1000) < 0){
        res.render('events',{error: 'Invalid input. Event was in the past' , events:[]})
        return;
    }

    //Expiry date for cookies
    expiryDate.setHours(expiryDate.getHours() + 24);

    const cookieOptions = {
        httpOnly: true,
        expires: expiryDate,
        sameSite: true,
    }

    const newCookie={
        eventName : req.body.name,
        eventDate : req.body.date,
        eventTime : req.body.time,
    }
    
    //Creates the cookie from recipies above
    res.cookie(req.body.name, newCookie, cookieOptions);
});

//Clear cookies
app.get('/reset', (req, res) => {
    Object.keys(req.cookies).forEach(key=>{
        res.clearCookie(key);
    })
    res.send('Cookies cleared');
});


app.listen(port, () => {
    console.log('Listening');
})

//Construcs a string to show time left to event
function timeLeftString(eventDate,time){
    
    const currDate = new Date;
    const tempDate = new Date(eventDate);                           //Convert to Date-object
    const millisecondsInHr = 60*60*1000;

    //This is my "rautakanki" which I use to fix time. Amazing but not very generic.
    const offsetgmt3 = 3*millisecondsInHr;  

    //Get difference of current date and the event date in milliseconds
    const toEventMS = ((tempDate.getTime()+ toMillis(time)) - (currDate.getTime() - offsetgmt3));
    
    //Do the calculations
    const event ={
        days: Math.floor(toEventMS / (millisecondsInHr * 24) % 365),              //If the event is over a year from now "days left" go to 0.
        hours: Math.floor(toEventMS / millisecondsInHr % 24),                     //But cookies die in 24 hrs so...
        minutes : Math.floor(toEventMS / (millisecondsInHr / 60) % 60),
        seconds : Math.floor(toEventMS / (millisecondsInHr/ 3600) % 60)
    }

    //Construct the final string
    return ('In ' +event.days + ' days, '+ event.hours+ ' hours, '+ event.minutes + ' minutes ' + event.seconds +' seconds.'); 
}

//Converts HH:MM time to milliseconds
function toMillis(time){
    return Number(time.split(':')[0])*60*60*1000+Number(time.split(':')[1])*60*1000;
}

//Renders the page with currently listed events
function updateView(req,res){
    const cookiePot = req.cookies;

    let template= [];
    Object.values(cookiePot).forEach(cookie => {
        template.push({
            event : cookie.eventName,
            text : timeLeftString(cookie.eventDate, cookie.eventTime) 
        })
    })
    template.reverse();
    res.render('events', {events : template, error:'' });
}