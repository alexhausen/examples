export default class Card {

    constructor(readonly idColumn: number, readonly idCard: number | undefined, readonly title: string, readonly estimate: number) {
        if (title === "") {
            throw new Error("Title is required");
        }
        if (estimate < 0) {
            throw new Error("Estimate must be positive");
        }
    }
}
