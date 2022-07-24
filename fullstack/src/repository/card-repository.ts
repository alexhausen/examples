import Card from "../domain/entity/card";

export default interface CardRepository {

    findAllByIdColumn(idColumn: number): Promise<Card[]>;

}
