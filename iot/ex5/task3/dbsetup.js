//Execute this file before running the server (index.js)
const sqlite3 = require('sqlite3').verbose();
const db = new sqlite3.Database('./db/temps.db');
db.run('CREATE TABLE temps(id INTEGER PRIMARY KEY AUTOINCREMENT,samplenr INTEGER NOT NULL, timestamp INTEGER NOT NULL,temperature INTEGER)');
console.log(`Table created`);
db.close();