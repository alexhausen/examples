import Card from "../../../domain/entity/card";
import CardRepository from "../../../repository/card-repository";
import Connection from "../connection";

export default class CardRepositoryDatabase implements CardRepository {

    constructor(readonly connection: Connection) {
    }

    async findAllByIdColumn(idColumn: number): Promise<Card[]> {
        const cardsData = await this.connection.query("select * from card where id_board_column = $1", [idColumn]);
        const cards: Card[] = [];
        for (const cardData of cardsData) {
            cards.push(new Card(cardData.title, cardData.estimate));
        }
        return cards;
    }

}
