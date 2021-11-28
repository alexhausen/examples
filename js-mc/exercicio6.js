const DatabaseError = function (statement, message) {
  return {
    statement,
    message,
  };
};

function split(values, separator = ",") {
  return values.split(separator).map((s) => s.trim());
}

function parse(command, regex) {
  const match = command.trim().match(regex);
  if (!match) {
    throw new DatabaseError(command, `Syntax error: '${command}'`);
  }
  return match.splice(1);
}

const database = {
  tables: {},
  insert(command) {
    const regex = /^insert\s+into\s+(\w+)\s*\((.+?)\)\s*values\s*\((.+?)\)$/;
    const [tableName, columnsString, valuesString] = parse(command, regex);
    const columns = split(columnsString);
    const values = split(valuesString);
    if (columns.length !== values.length) {
      throw new DatabaseError(command, `Syntax error: '${command}'`);
    }
    const row = {};
    columns.forEach((column, i) => (row[column] = values[i]));
    this.tables[tableName].data.push(row);
  },
  createTable(command) {
    const regex = /^create\s+table\s+(\w+)\s+\((.+)\)$/;
    const [tableName, columnsString] = parse(command, regex);
    const columns = split(columnsString).reduce((acc, column) => {
      const [key, value] = column.replace(/\s+/, " ").split(" ");
      return { ...acc, [key]: value };
    }, {});
    this.tables[tableName] = { columns, data: [] };
  },
  select(command) {
    const regex = /^select\s+(.+)\s+from\s+(\w+)(?:\s+where\s+(.+))?$/;
    const [columnsString, tableName, whereString] = parse(command, regex);
    const columns = split(columnsString);
    let rows = this.tables[tableName].data;
    if (whereString) {
      const [columnWhere, valueWhere] = split(whereString, "=");
      rows = rows.filter((row) => row[columnWhere] === valueWhere);
    }
    rows = rows.map(function (row) {
      const selectedRow = {};
      columns.forEach(function (column) {
        selectedRow[column] = row[column];
      });
      return selectedRow;
    });
    return rows;
  },
  execute(command) {
    if (command.trim().startsWith("create ")) {
      return this.createTable(command);
    }
    if (command.trim().startsWith("insert ")) {
      return this.insert(command);
    }
    if (command.trim().startsWith("select ")) {
      return this.select(command);
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
// console.log(JSON.stringify(database, null, "  "));
const select1 = database.execute("select name, age from author");
console.log(JSON.stringify(select1, null, "  "));
const select2 = database.execute("select name, age from author where id = 1");
console.log(JSON.stringify(select2, null, "  "));

/*
try {
  database.execute("select id, name from author");
} catch (error) {
  console.log(error.message);
}
*/
