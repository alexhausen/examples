import Card from "../../../domain/entity/card";
import CardRepository from "../../../repository/card-repository";
import Connection from "../connection";

export default class CardRepositoryDatabase implements CardRepository {

    constructor(readonly connection: Connection) {
    }

    async findAllByIdColumn(idColumn: number): Promise<Card[]> {
        const cardsData = await this.connection.query("select * from card where id_board_column = $1 order by id_card", [idColumn]);
        const cards: Card[] = [];
        for (const cardData of cardsData) {
            cards.push(new Card(
                cardData.id_board_column,
                cardData.id_card,
                cardData.title,
                cardData.estimate));
        }
        return cards;
    }

    async insert(card: Card): Promise<number> {
        const [cardData] = await this.connection.query(
            "insert into card (id_board_column, title, estimate) values ($1, $2, $3) returning *",
            [card.idColumn, card.title, card.estimate]
        );
        return cardData.id_card;
    }

    async delete(idCard: number): Promise<void> {
        await this.connection.query("delete from card where id_card = $1", [idCard]);
    }

    async update(card: Card): Promise<void> {
        await this.connection.query("update card set title = $1, estimate = $2 where id_card = $3", [card.title, card.estimate, card.idCard]);
    }
}
