'use strict';

const TypeEnum= {
	BYTE: 1,
	KILO: 2,
	MEGA: 3,
	GIGA: 4
}

//Type: Enum type for keeping track of selected datatype(kb,MB,GB...)
//Total: total memory
let Memory = {
	type:1,
	total:0,
};

//fetch total memory from server and update html manually
fetch('http://localhost:3000/totalmem')
	.then(response => response.json())
	.then(data => Memory.total = data.memTotal)
.catch(err => console.log(err));
update();

//returns the datatype what the enumerator represents
function inverseTypeEnum(enumerator){
	switch (enumerator){
		case 1:
			return 'Bytes'
		case 2:
			return 'kB'
		case 3: 
			return 'MB'
		case 4: 
			return 'GB'
	}
}

//Return amount of memory in different scale
function bytesToType(enumerator,memory){
	let i = 1;
	while(i < enumerator){
		memory = memory/1024;
		i++
	}
	return memory;
}

//Callback function for buttons on DOM
//Sets "scale" of memory displayed
//Such snappy, much crisp
function setDataType(type){
	Memory.type = type;
	update();
}

//Changes text colour of DOM based on relative memory usage.
function colourText(relative){
	let colour;
	if(relative >= 0.9 ){
		colour = 'red';
	}else if(relative >= 0.8){
		colour = 'orange';
	}else if(relative >= 0.6){
		colour = 'black';
	}else{
		colour='green'
	}
	document.getElementById('absolute').style.color = colour;
	document.getElementById('relative').style.color = colour;
}

//Returns memory in same form as it is returned by os.freemem()
function fetchFreeMem(){
	return new Promise((resolve, reject) => {
	fetch('http://localhost:3000/freemem')
		.then( response => response.json())
		.then( data =>  { 
			resolve(data.memFree);
		})
		.catch(err => {
			console.log(err)
			reject(err);
		});
	}) 
}


//Main function that is called periodically
//Fetches free memory and changes html elements.
function update(){
	fetchFreeMem()
	.then(memory => {
		const memAbs = Memory.total - memory; 
		const memRel = memAbs / Memory.total;
		document.getElementById('absolute').innerHTML = (bytesToType(Memory.type, memAbs).toFixed(1) +' '+ inverseTypeEnum(Memory.type));
		document.getElementById('relative').innerHTML = (memRel * 100).toFixed(2) + '%';
		colourText(memRel);
	}).catch(err => console.log(err));
}

const interval = setInterval(() => update(),1000);