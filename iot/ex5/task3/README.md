To run program this program you need to install Node.js. Then run the simulator by opening up a terminal, navigate to this file and run node simulator.js
Leave that running and from another terminal issue these commands 
npm i 				//Installs needed dependeceis marked by package.json file	
npm run dbsetup            	//Creates the table for database
npm run start			//Runs program.

Then from a browser enter "localhost:3000" as the url.

Theres an interesing "bug". The program is supposed to update temperature each second, which it does, 
but the simulator does not send data with 1000 ms intervals.The client.on('message') event is triggered
somewhere between once every 1-2 seconds, which causes the program to display same information for atleast 
2 cycles.