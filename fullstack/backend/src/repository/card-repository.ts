import Card from "../domain/entity/card";

export default interface CardRepository {

    findAllByIdColumn(idColumn: number): Promise<Card[]>;
    insert(card: Card): Promise<number>;
    delete(idCard: number): Promise<void>;
    update(card: Card): Promise<void>;
}
