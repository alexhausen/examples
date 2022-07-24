import Board from "../domain/entity/board";
import BoardRepository from "../repository/board-repository";

export default class BoardService {

    constructor(readonly boardRepository: BoardRepository) {
    }

    async getBoards(): Promise<Board[]> {
        const boards = await this.boardRepository.findAll();
        return boards;
    }

}
