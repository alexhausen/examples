import { DatabaseError } from "./error.mjs";
import { Parser } from "./parser.mjs";

function split(values, separator = ",") {
  return values.split(separator).map((s) => s.trim());
}

export class Database {
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
