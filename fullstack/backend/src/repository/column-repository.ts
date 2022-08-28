import Column from "../domain/entity/column";

export default interface ColumnRepository {

    findAllByIdBoard(idBoard: number): Promise<Column[]>;
    get(idColumn: number): Promise<Column>;
    insert(column: Column): Promise<number>;
    delete(idColumn: number): Promise<void>;
    update(column: Column): Promise<void>;
}
