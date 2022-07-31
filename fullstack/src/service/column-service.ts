
import Column from "../domain/entity/column";
import ColumnRepository from "../repository/column-repository";

export default class ColumnService {

    constructor(readonly columnRepository: ColumnRepository) {
    }

    async getColumns(idBoard: number) {
        const columns = await this.columnRepository.findAllByIdBoard(idBoard);
        return columns;
    }
}
