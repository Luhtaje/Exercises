'use strict';

const bodyParser = require('body-parser');
const path = require('path');
const fs = require('fs');
const util = require('util');
const port = 3000
const express = require('express');
const app = express();


const writeFile = util.promisify(fs.writeFile);
const readFile = util.promisify(fs.readFile);

app.use(express.urlencoded({extended: true}));


//Generates random string.
function createid(){
    const id = Date.now().toString(36).substr(2,3) + Math.random().toString(36).substr(2,5);
    console.log(id);
    return id;
};


//Reads file from disk and passes json object on resolve
function getCars(){
    return  new Promise((resolve,reject) => {
        readFile('data/cars.txt')
            .then(cars =>{
                if(!cars){
                    reject(err);
                }
                else{
                    // Resolves empty array if file is empty
                    if(cars.length === 0) {
                        resolve([]);
                    }else{
                        resolve(JSON.parse(cars));
                    }
                }
            })
    })
}

//Appends new car to the cars list
function appendCars(cars,newCar){
    return new Promise((resolve,reject) => {
        
        //Special thanks to Tapani Moilanen for this nice guard
        if(!newCar){
            return reject(err);  
        }

        cars.push(newCar); 
        resolve(cars);

    });
}


//Return a list of all cars
app.get('/', async (req, res) => {
    readFile('data/cars.txt')
        .then( file => {
            let temp = JSON.parse(file);    
            res.send(temp);
        }).catch((err)=> {
            res.send('Something went wrong. Here is what I got instead of the correct file\n\r' + err);
    });
    
});



app.get('/:id', async (req, res) => {
   
    readFile('data/cars.txt')
        .then(file => {
            let temp = JSON.parse(file);
            const index = temp.findIndex(element => element.id === req.params.id)
            res.send(JSON.stringify(temp[index]));
        }).catch(file =>{
            res.send('Something went wrong. Here is what I got instead of the correct file\n\r' + file);
        });
});


app.post('/', async (req, res) => {

    //Guard to terminate execution if year is NaN.
    if(isNaN(req.body.year)){
        res.send('Year is not a number. Please input a number please').end();
        return;
    }
    //Create new car
    let brandNewCar = {
        make:req.body.make,
        model:req.body.model,
        year:req.body.year,
        id:createid()
    }
      
    //Reads carlist from the file
    //Adds new car to the array
    //Writes new list back into file
    try {
        const cars = await getCars();
        const carList = await appendCars(cars,brandNewCar);
        await writeFile('data/cars.txt', JSON.stringify(carList)); 
        res.send(brandNewCar);
    } catch(err) {
        console.log(err);
        res.sendStatus(500).end();
    }
});

//Deletes a car element based on ID
//Returns deleted element
app.delete('/:id', async (req, res) => {
    
    //Implement body parser
    //E: Apparently body parser only works on POST requests.
    let id = req.params.id;
    readFile('data/cars.txt')
    .then(file => {

        const temp = JSON.parse(file);

        //Find the corresponding element with id and pop it form the array
        // write the updated array back into file.
        const index = temp.findIndex((element) => element.id === id);
           
        if(-1 != index){
                const removed = temp.splice(index,1);
                writeFile('data/cars.txt', JSON.stringify(temp)).then(() => {
                    res.send(201,removed);
                }).catch(err => {
                    console.log(err);
                })
            }
    }).catch(err =>{
        console.log(err);
        res.sendStatus(500).end();
    })
});


app.listen(port, ()=> {
	console.log('Exercise app listening at http://localhost:${port}')
});
