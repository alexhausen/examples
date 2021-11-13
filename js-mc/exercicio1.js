const command =
  "create table author (id number, name string, age number, city string, state string, country string)";
const result = {
  tableName: "",
  columns: [],
};
const regex = /^create\s+table\s+(\w+)\s+\((.+)\)$/;
const match = command.trim().match(regex);
if (match) {
  result.tableName = match[1];
  result.columns = match[2].split(", ");
}
console.log(`tableName = "${result.tableName}"`);
console.log(`columns = [ ${result.columns.map((e) => "'" + e + "'")} ]`);
