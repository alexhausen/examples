import Board from "../../domain/entity/board";
import Card from "../../domain/entity/card";
import Column from "../../domain/entity/column";
import BoardService from "../../service/board-service";
import CardService from "../../service/card-service";
import ColumnService from "../../service/column-service";
import Connection from "../database/connection";
import BoardRepositoryDatabase from "../database/repository/board-repository-db";
import CardRepositoryDatabase from "../database/repository/card-repository-db";
import ColumnRepositoryDatabase from "../database/repository/column-repository-db";
import Http from "../http/http";

export default class BoardController {

    constructor(readonly http: Http, readonly connection: Connection) {
        http.route("get", "/boards", async function (params: any, body: any) {
            const boardRepository = new BoardRepositoryDatabase(connection);
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const cardRepository = new CardRepositoryDatabase(connection);
            const boardService = new BoardService(boardRepository, columnRepository, cardRepository);
            const boards: Board[] = await boardService.getBoards();
            return boards;
        });

        http.route("get", "/boards/:idBoard", async function (params: any, body: any) {
            const boardRepository = new BoardRepositoryDatabase(connection);
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const cardRepository = new CardRepositoryDatabase(connection);
            const boardService = new BoardService(boardRepository, columnRepository, cardRepository);
            const board: Board = await boardService.getBoard(params.idBoard);
            return board;
        });


        http.route("get", "/boards/:idBoard/columns", async function (params: any, body: any) {
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const columnService = new ColumnService(columnRepository);
            const columns: Column[] = await columnService.getColumns(parseInt(params.idBoard));
            return columns;
        });

        http.route("get", "/boards/:idBoard/columns/:idColumn/cards", async function (params: any, body: any) {
            const cardRepository = new CardRepositoryDatabase(connection);
            const cardService = new CardService(cardRepository);
            const cards: Card[] = await cardService.getCards(parseInt(params.idColumn));
            return cards;
        });
    }
}
