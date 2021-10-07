const path = require('path');


const fileHandler = require('./lib/filehandler.js')

const myFile = new fileHandler('users.json');

testerLoad = async () =>{
    await myFile.load();
    myFile.toString();
}

testerWriteJSON = () =>{
    myFile.save({
        name:'Tarzan',
        lover:'Jane'
    })
}

testDescriptors = () => {
    myFile.logDescriptors();
}

testDescriptors();
//testerLoad();
//testerWriteString();


