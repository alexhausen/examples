import { DatabaseError } from "./error.mjs";

export class Parser {
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
