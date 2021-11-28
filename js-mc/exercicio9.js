class DatabaseError {
  constructor(statement, message) {
    this.statement = statement;
    this.message = message;
  }
}

class Parser {
  static commands = new Map([
    ["createTable", /^create\s+table\s+(\w+)\s+\((.+)\)$/],
    ["delete", /^delete\s+from\s+(\w+)\s+where\s+(.+)$/],
    ["insert", /^insert\s+into\s+(\w+)\s*\((.+?)\)\s*values\s*\((.+?)\)$/],
    ["select", /^select\s+(.+)\s+from\s+(\w+)(?:\s+where\s+(.+))?$/],
  ]);

  parse(statement) {
    for (const [command, regex] of Parser.commands) {
      const match = statement.trim().match(regex);
      if (match) {
        return {
          command,
          parsedStatement: match.splice(1),
        };
      }
    }
    throw new DatabaseError(statement, `Syntax error: '${statement}'`);
  }
}

function split(values, separator = ",") {
  return values.split(separator).map((s) => s.trim());
}

class Database {
  constructor() {
    this.tables = {};
    this.parser = new Parser();
  }

  insert(parsedStatement) {
    const [tableName, columnsString, valuesString] = parsedStatement;
    const columns = split(columnsString);
    const values = split(valuesString);
    if (columns.length !== values.length) {
      throw new DatabaseError("insert", "Syntax error");
    }
    const row = {};
    columns.forEach((column, i) => (row[column] = values[i]));
    this.tables[tableName].data.push(row);
  }

  createTable(parsedStatement) {
    const [tableName, columnsString] = parsedStatement;
    const columnsAndTypes = split(columnsString).reduce((acc, column) => {
      const [key, value] = column.replace(/\s+/, " ").split(" ");
      return { ...acc, [key]: value };
    }, {});
    this.tables[tableName] = { columns: columnsAndTypes, data: [] };
  }

  select(parsedStatement) {
    const [columnsString, tableName, whereString] = parsedStatement;
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
  }

  delete(parsedStatement) {
    const [tableName, whereString] = parsedStatement;
    const [columnWhere, valueWhere] = split(whereString, "=");
    this.tables[tableName].data = this.tables[tableName].data.filter(
      (row) => row[columnWhere] !== valueWhere
    );
  }

  execute(statement) {
    const { command, parsedStatement } = this.parser.parse(statement);
    return this[command](parsedStatement);
  }
}

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
const select = database.execute("select name, age from author");
console.log(JSON.stringify(select, null, "  "));
