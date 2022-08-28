import Card from "../domain/entity/card";
import CardRepository from "../repository/card-repository";

export default class CardService {

    constructor(readonly cardRepository: CardRepository) {
    }

    async getCards(idColumn: number) {
        const cards = await this.cardRepository.findAllByIdColumn(idColumn);
        return cards;
    }

    async saveCard(input: SaveInput): Promise<number> {
        const card = new Card(input.idColumn, undefined, input.title, input.estimate);
        const idCard = await this.cardRepository.insert(card);
        return idCard;
    }

    async updateCard(input: UpdateInput): Promise<void> {
        const card = new Card(input.idColumn, input.idCard, input.title, input.estimate);
        await this.cardRepository.update(card);
    }

    async deleteCard(idCard: number): Promise<void> {
        await this.cardRepository.delete(idCard);
    }
}

type SaveInput = {
    idColumn: number,
    title: string,
    estimate: number
}

type UpdateInput = {
    idColumn: number,
    idCard: number,
    title: string,
    estimate: number
}
