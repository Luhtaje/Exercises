//Execute this file before running the server (index.js)
const sqlite3 = require('sqlite3').verbose();
const db = new sqlite3.Database('./db/cars.db');
db.run('CREATE TABLE cars(id INTEGER PRIMARY KEY AUTOINCREMENT,make VARCHAR(30) NOT NULL)');
console.log(`Table created`);
db.close();