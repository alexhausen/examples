const DatabaseError = function (statement, message) {
  return {
    statement,
    message,
  };
};

function splitValues(values) {
  return values.split(",").map((s) => s.trim());
}

const database = {
  tables: {},
  insert(command) {
    const regex = /^insert\s+into\s+(\w+)\s*\((.+?)\)\s*values\s*\((.+?)\)$/;
    const match = command.trim().match(regex);
    if (!match) {
      throw new DatabaseError(command, `Syntax error: '${command}'`);
    }
    const [, tableName, columnsString, valuesString] = match;
    const columns = splitValues(columnsString);
    const values = splitValues(valuesString);
    if (columns.length !== values.length) {
      throw new DatabaseError(command, `Syntax error: '${command}'`);
    }
    const row = {};
    columns.forEach((column, i) => row[column] = values[i]);
    this.tables[tableName].data.push(row);
  },
  createTable(command) {
    const regex = /^create\s+table\s+(\w+)\s+\((.+)\)$/;
    const match = command.trim().match(regex);
    if (!match) {
      throw new DatabaseError(command, `Syntax error: '${command}'`);
    }
    const [, tableName, columnsString] = match;
    const columns = splitValues(columnsString).reduce((acc, column) => {
      const [key, value] = column.replace(/\s+/, " ").split(" ");
      return { ...acc, [key]: value };
    }, {});
    this.tables[tableName] = { columns, data: [] };
  },
  execute(command) {
    if (command.trim().startsWith("create ")) {
      return this.createTable(command);
    }
    if (command.trim().startsWith("insert ")) {
      return this.insert(command);
    }
    throw new DatabaseError(command, `Syntax error: '${command}'`);
  },
};

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
console.log(JSON.stringify(database, null, "  "));

/*
try {
  database.execute("select id, name from author");
} catch (error) {
  console.log(error.message);
}
*/
