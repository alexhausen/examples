import Column from "../../../domain/entity/column";
import ColumnRepository from "../../../repository/column-repository";
import Connection from "../connection";

export default class ColumnRepositoryDatabase implements ColumnRepository {

    constructor(readonly connection: Connection) { }

    async findAllByIdBoard(idBoard: number): Promise<Column[]> {
        const columnsData = await this.connection.query("select * from board_column where id_board = $1", [idBoard]);
        const columns: Column[] = [];
        for (const columnData of columnsData) {
            columns.push(new Column(columnData.name, columnData.has_estimate));
        }
        return columns;
    }

}
