
import Card from "../domain/entity/card";
import CardRepository from "../repository/card-repository";

export default class CardService {

    constructor(readonly cardRepository: CardRepository) {
    }

    async getCards(idColumn: number) {
        const cards = await this.cardRepository.findAllByIdColumn(idColumn);
        return cards;
    }


}
