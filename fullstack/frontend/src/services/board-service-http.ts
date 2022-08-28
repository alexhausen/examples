import Board from "../entities/board";
import Column from "../entities/column";
import Card from "../entities/card";
import HttpClient from "../infra/http/http-client";
import BoardService, { SaveCardInput, SaveColumnInput, UpdateCardInput } from "./board-service";

export default class BoardServiceHttp implements BoardService {

    constructor(readonly httpClient: HttpClient, readonly baseUrl: string) {
    }

    async getBoard(idBoard: number): Promise<Board> {
        const boardData: GetBoardDTO = await this.httpClient.get(`${this.baseUrl}/boards/${idBoard}`);
        const board = new Board(boardData.idBoard, boardData.name);
        for (const columnData of boardData.columns) {
            const column = new Column(columnData.name, columnData.estimate);
            column.idColumn = columnData.idColumn;
            board.columns.push(column);
            for (const cardData of columnData.cards) {
                const card = new Card(cardData.title, cardData.estimate);
                card.idCard = cardData.idCard;
                column.cards.push(card);
            }
        }
        return board;
    }

    async saveColumn(column: SaveColumnInput): Promise<number> {
        const idColumn = await this.httpClient.post(
            `${this.baseUrl}/boards/${column.idBoard}/columns`,
            column
        );
        return idColumn;
    }

    async saveCard(card: SaveCardInput): Promise<number> {
        const idCard = await this.httpClient.post(
            `${this.baseUrl}/boards/${card.idBoard}/columns/${card.idColumn}/cards`,
            card
        );
        return idCard;
    }

    async deleteColumn(idBoard: number, idColumn: number): Promise<void> {
        await this.httpClient.delete(
            `${this.baseUrl}/boards/${idBoard}/columns/${idColumn}`
        );
    }

    async deleteCard(idBoard: number, idColumn: number, idCard: number): Promise<void> {
        await this.httpClient.delete(
            `${this.baseUrl}/boards/${idBoard}/columns/${idColumn}/cards/${idCard}`
        );
    }
    async updateCard(card: UpdateCardInput): Promise<void> {
        // console.log(card);
        await this.httpClient.put(
            `${this.baseUrl}/boards/${card.idBoard}/columns/${card.idColumn}/cards/${card.idCard}`,
            card
        );
    }
}

// DTO = Data Transfer Object
type GetBoardDTO = {
    idBoard: number,
    name: string,
    columns: ColumnDTO[]
}

type ColumnDTO = {
    idColumn: number,
    name: string,
    estimate: boolean,
    cards: CardDTO[]
}

type CardDTO = {
    idCard: number,
    title: string,
    estimate: number
}
