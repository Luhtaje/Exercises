const util = require('util');
const fs = require('fs');

const writeFile = util.promisify(fs.writeFile);
const readFile = util.promisify(fs.readFile);

class fileHandle{

    constructor(path){
        this.path = path;
        this.data = null;
    }

    save = (data) => {
        writeFile(this.path,JSON.stringify(data));
    }
    
    load = async () => {
        const response = await readFile(this.path);
        this.data = response;
        console.log(`Loaded: ${this.data}`)
    }

    logString = () => {
        console.log(this);
    }

    logDescriptors = () => {
        console.log(Object.getOwnPropertyDescriptors(fileHandle));
    }

}

Object.defineProperty(fileHandle,'save',{
    configurable:false,
    writable:false
})

Object.defineProperty(fileHandle,'load',{
    configurable:false,
    writeable:false
})



module.exports = fileHandle;


