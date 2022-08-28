export default class Card {

    idCard?: number;

    constructor(readonly title: string, public estimate: number) {
    }

    incrementEstimate() {
        this.estimate++;
    }

    decrementEstimate() {
        if (this.estimate > 0) this.estimate--;
    }

}
