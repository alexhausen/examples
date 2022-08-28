import Board from "../entities/board";

export default interface BoardService {
    getBoard(idBoard: number): Promise<Board>;
    saveColumn(column: SaveColumnInput): Promise<number>;
    saveCard(card: SaveCardInput): Promise<number>;
    deleteColumn(idBoard: number, idColumn: number): Promise<void>;
    deleteCard(idBoard: number, idColumn: number, idCard: number): Promise<void>;
    updateCard(card: UpdateCardInput): Promise<void>;
}

export type SaveColumnInput = {
    idBoard: number,
    name: string,
    hasEstimate: boolean
};

export type SaveCardInput = {
    idBoard: number,
    idColumn: number,
    title: string,
    estimate: number
}

export type UpdateCardInput = {
	idBoard: number,
	idColumn: number,
	idCard: number,
	title: string,
	estimate: number
}
