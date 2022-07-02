import Card from "./card";
import Column from "./column";

export default class Board {
    name: string;
    description: string;
    columns: Column[];

    constructor(name: string, description: string) {
        this.name = name;
        this.description = description;
        this.columns = [];
    }

    addColumn(name: string, timeTracking: boolean): void {
        this.columns.push(new Column(name, timeTracking));
    }

    addCardToColumn(card: Card, destinyColumnName: string): void {
        for (const column of this.columns) {
            if (column.name === destinyColumnName) {
                column.addCard(card);
                break;
            }
        }
    }

    computeEstimate(columnName: string): number {
        for (let column of this.columns) {
            if (column.name === columnName) {
                return column.computeEstimate();
            }
        }
        return 0;
    }

}
