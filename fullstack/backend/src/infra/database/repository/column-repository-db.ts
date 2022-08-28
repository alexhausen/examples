import Column from "../../../domain/entity/column";
import ColumnRepository from "../../../repository/column-repository";
import Connection from "../connection";

export default class ColumnRepositoryDatabase implements ColumnRepository {

    constructor(readonly connection: Connection) { }

    async findAllByIdBoard(idBoard: number): Promise<Column[]> {
        const columnsData = await this.connection.query("select * from board_column where id_board = $1", [idBoard]);
        const columns: Column[] = [];
        for (const columnData of columnsData) {
            columns.push(new Column(columnData.id_board, columnData.id_board_column, columnData.name, columnData.has_estimate));
        }
        return columns;
    }

    async get(idColumn: number): Promise<Column> {
        const [columnData] = await this.connection.query(
            "select * from board_column where id_board_column = $1",
            [idColumn]
        );
        if (!columnData) throw new Error("Column not found");
        return new Column(columnData.id_board, columnData.id_board_column, columnData.name, columnData.has_estimate);
    }

    async insert(column: Column): Promise<number> {
        const [columnData] = await this.connection.query(
            "insert into board_column (id_board, name, has_estimate) values ($1, $2, $3) returning id_board_column",
            [column.idBoard, column.name, column.hasEstimate]
        );
        return columnData.id_board_column;
    }

    async delete(idColumn: number): Promise<void> {
        await this.connection.query(
            "delete from board_column where id_board_column = $1",
            [idColumn]
        );
    }

    async update(column: Column): Promise<void> {
        //TODO
    }
}
