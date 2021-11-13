const command =
  "create table author (id number, name string, age number, city string, state string, country string)";

let tableName = "";
let columnsString = [];
const regex = /^create\s+table\s+(\w+)\s+\((.+)\)$/;
const match = command.trim().match(regex);
if (match) {
  tableName = match[1];
  columnsString = match[2].split(", ");
}
console.log(`tableName = "${tableName}"`);
console.log(`columnsString = [ ${columnsString.map((e) => "'" + e + "'")} ]`);

const columns = columnsString.reduce((acc, column) => {
  const [key, value] = column.trim().replace(/\s+/, " ").split(" ");
  return { ...acc, [key]: value };
}, {});
// equivalente:
// let columns = {};
// for (let column of columnsString) {
//   const [key, value] = column.trim().replace(/\s+/, " ").split(" ");
//   columns[key] = value;
// }
const database = { tables: { [tableName]: { columns, data: [] } } };

console.log(JSON.stringify(database, null, "  "));
