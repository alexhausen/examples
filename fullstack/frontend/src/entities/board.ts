import DomaninEvent from "../events/DomainEvent";
import BaseEntity from "./base-entity";
import Card from "./card";
import Column from "./column";

export default class Board extends BaseEntity {
    columns: Column[];

    constructor(readonly idBoard: number, readonly name: string) {
        super();
        this.columns = [];
    }

    addColumn(columnName: string, hasEstimate: boolean) {
        const column = new Column(columnName, hasEstimate);
        this.columns.push(column);
        // publica um evento para desacoplar o serviço
        this.publish(new DomaninEvent("addColumn", {
            idBoard: this.idBoard,
            column,
        }));
    }

    addCard(columnName: string, cardTitle: string, cardEstimate: number) {
        const column = this.columns.find(column => columnName === column.name);
        if (!column) throw new Error("Column not found");
        const card = new Card(cardTitle, cardEstimate);
        column.addCard(card);
        this.publish(new DomaninEvent("addCard", {
            idBoard: this.idBoard,
            idColumn: column.idColumn,
            card
        }));
    }

    deleteColumn(idColumn: number) {
        // console.log(idColumn);
        const column = this.columns.find(column => column.idColumn === idColumn);
        if (!column) throw new Error("Column not found");
        this.columns.splice(this.columns.indexOf(column), 1);
        this.publish(new DomaninEvent("deleteColumn", { idBoard: this.idBoard, idColumn }));
    }

    deleteCard(idColumn: number, idCard: number) {
        // console.log(`delete card ${idCard} from column ${idColumn}`);
        const column = this.columns.find(column => column.idColumn === idColumn);
        if (!column) throw new Error("Column not found");
        const card = column.cards.find(card => card.idCard === idCard);
        if (!card) throw new Error("Card not found");
        column.cards.splice(column.cards.indexOf(card), 1);
        this.publish(new DomaninEvent("deleteCard", {
            idBoard: this.idBoard,
            idColumn: column.idColumn,
            idCard: card.idCard
        }));
    }

    incrementEstimate(idColumn: number, card: Card) {
        card.incrementEstimate();
        this.publish(new DomaninEvent("incrementEstimate", {
            idBoard: this.idBoard,
            idColumn,
            card
        }));
    }

    decrementEstimate(idColumn: number, card: Card) {
        card.decrementEstimate();
        this.publish(new DomaninEvent("decrementEstimate", {
            idBoard: this.idBoard,
            idColumn,
            card
        }));
    }

    getEstimate() {
        return this.columns.reduce(
            (total: number, column: Column) => total + column.getEstimate(), 0
        );
    }
}
