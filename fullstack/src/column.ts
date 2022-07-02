import Card from "./card";

export default class Column {
    name: string;
    timeTracking: boolean;
    cards: Card[];

    constructor(name: string, timeTracking: boolean) {
        this.name = name;
        this.timeTracking = timeTracking;
        this.cards = [];
    }

    addCard(card: Card): void {
        this.cards.push(card);
    }

    computeEstimate(): number {
        if (this.timeTracking) {
            return this.cards.reduce(
                (total: number, current: Card): number => current.hours + total
                , 0);
        }
        return 0;
    }
}
