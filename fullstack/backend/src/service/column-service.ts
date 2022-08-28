import Column from "../domain/entity/column";
import ColumnRepository from "../repository/column-repository";

export default class ColumnService {

    constructor(readonly columnRepository: ColumnRepository) {
    }

    async getColumns(idBoard: number) {
        const columns = await this.columnRepository.findAllByIdBoard(idBoard);
        return columns;
    }

    async getColumn(idColumn: number) {
        const column = await this.columnRepository.get(idColumn);
        return column;
    }

    async saveColumn(input: SaveInput): Promise<number> {
        const idColumn = await this.columnRepository.insert(
            new Column(input.idBoard, undefined, input.name, input.hasEstimate)
        );
        return idColumn;
    }

    async deleteColumn(idColumn: number): Promise<void> {
        await this.columnRepository.delete(idColumn);
    }
}

type SaveInput = {
    idBoard: number,
    name: string,
    hasEstimate: boolean
};
