import Column from "../domain/entity/column";

export default interface ColumnRepository {

    findAllByIdBoard(idBoard: number): Promise<Column[]>;

}
