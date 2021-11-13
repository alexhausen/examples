const DatabaseError = function (statement, message) {
  return {
    statement,
    message,
  };
};

const database = {
  tables: {},
  createTable(command) {
    let tableName = "";
    let columnsString = [];
    const regex = /^create\s+table\s+(\w+)\s+\((.+)\)$/;
    const match = command.trim().match(regex);
    if (match) {
      tableName = match[1];
      columnsString = match[2].split(", ");
    }
    const columns = columnsString.reduce((acc, column) => {
      const [key, value] = column.trim().replace(/\s+/, " ").split(" ");
      return { ...acc, [key]: value };
    }, {});
    this.tables[tableName] = { [tableName]: { columns, data: [] } };
  },
  execute(command) {
    if (command.trim().startsWith("create table")) {
      return this.createTable(command);
    }
    throw new DatabaseError(command, `Syntax error: '${command}'`);
  },
};

database.execute(
  "create table author (id number, name string, age number, city string, state string, country string)"
);
console.log(JSON.stringify(database, null, "  "));

try {
  database.execute("select id, name from author");
} catch (error) {
  console.log(error.message);
}
