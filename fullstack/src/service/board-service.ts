import Board from "../domain/entity/board";
import BoardRepository from "../repository/board-repository";
import CardRepository from "../repository/card-repository";
import ColumnRepository from "../repository/column-repository";

export default class BoardService {

    constructor(
        readonly boardRepository: BoardRepository,
        readonly columnRepository: ColumnRepository,
        readonly cardRepository: CardRepository) {
    }

    async getBoards(): Promise<Board[]> {
        const boards = await this.boardRepository.findAll();
        return boards;
    }

    async getBoard(idBoard: number): Promise<BoardOutput> {
        const board = await this.boardRepository.get(idBoard);
        const output: BoardOutput = {
            name: board.name,
            estimate: 0,
            columns: []
        };
        const columns = await this.columnRepository.findAllByIdBoard(idBoard);
        for (const column of columns) {
            const columnOutput: ColumnOutput = {
                name: column.name,
                estimate: 0,
                hasEstimate: column.hasEstimate,
                cards: []
            };
            const cards = await this.cardRepository.findAllByIdColumn(column.idColumn);
            for (const card of cards) {
                columnOutput.estimate += card.estimate;
                columnOutput.cards.push({
                    title: card.title,
                    estimate: card.estimate
                });
            }
            output.estimate += columnOutput.estimate;
            output.columns.push(columnOutput);
        }
        return output;
    }

}

type ColumnOutput = {
    name: string,
    estimate: number
    hasEstimate: boolean,
    cards: {
        title: string,
        estimate: number
    }[]
};

type BoardOutput = {
    name: string,
    estimate: number,
    columns: ColumnOutput[]
};
