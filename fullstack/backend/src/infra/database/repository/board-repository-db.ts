import Board from "../../../domain/entity/board";
import BoardRepository from "../../../repository/board-repository";
import Connection from "../connection";

export default class BoardRepositoryDatabase implements BoardRepository {

    constructor(readonly connection: Connection) {
    }

    async findAll(): Promise<Board[]> {
        const boardsData = await this.connection.query("select id_board, name from board", []);
        const boards: Board[] = [];
        for (const boardData of boardsData) {
            boards.push(new Board(boardData.id_board, boardData.name));
        }
        return boards;
    }

    async get(idBoard: number): Promise<Board> {
        const [boardData] = await this.connection.query("select * from board where id_board = $1", [idBoard]);
        if (!boardData) throw new Error("Board not found");
        const board = new Board(boardData.id_board, boardData.name);
        return board;
    }
}
