import Card from "./card";

export default class Column {

    cards: Card[];
    idColumn?: number;

    constructor(readonly name: string, readonly hasEstimate: boolean) {
        this.cards = [];
    }

    addCard(card: Card) {
        this.cards.push(card);
    }

    getEstimate() {
        return this.cards.reduce((totalCard: number, card: Card) => totalCard + card.estimate, 0);
    }
}
