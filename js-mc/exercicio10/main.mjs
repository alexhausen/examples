import { Database } from "./database.mjs";

const database = new Database();

database.execute(
  "create table author (id number, name string, age number, city string, state string, country string)"
);
database.execute(
  "insert into author (id, name, age) values (1, Douglas Crockford, 62)"
);
database.execute(
  "insert into author (id, name, age) values (2, Linus Torvalds, 47)"
);
database.execute(
  "insert into author (id, name, age) values (3, Martin Fowler, 54)"
);
database.execute("delete from author where id = 2");
const select = database.execute("select1 name, age from author");
console.log(JSON.stringify(select, null, "  "));
