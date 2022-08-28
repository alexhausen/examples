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
            const boards = await boardService.getBoards();
            return boards;
        });

        http.route("get", "/boards/:idBoard", async function (params: any, body: any) {
            const boardRepository = new BoardRepositoryDatabase(connection);
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const cardRepository = new CardRepositoryDatabase(connection);
            const boardService = new BoardService(boardRepository, columnRepository, cardRepository);
            const board = await boardService.getBoard(params.idBoard);
            return board;
        });


        http.route("get", "/boards/:idBoard/columns", async function (params: any, body: any) {
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const columnService = new ColumnService(columnRepository);
            const columns = await columnService.getColumns(parseInt(params.idBoard));
            return columns;
        });

        http.route("get", "/boards/:idBoard/columns/:idColumn", async function (params: any, body: any) {
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const columnService = new ColumnService(columnRepository);
            const column = await columnService.getColumn(parseInt(params.idColumn));
            return column;
        });

        http.route("post", "/boards/:idBoard/columns", async function (params: any, body: any) {
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const columnService = new ColumnService(columnRepository);
            const idColumn = await columnService.saveColumn(body);
            return idColumn;
        });

        http.route("delete", "/boards/:idBoard/columns/:idColumn", async function (params: any, body: any) {
            console.log(params);
            const columnRepository = new ColumnRepositoryDatabase(connection);
            const columnService = new ColumnService(columnRepository);
            await columnService.deleteColumn(parseInt(params.idColumn));
        });

        http.route("get", "/boards/:idBoard/columns/:idColumn/cards", async function (params: any, body: any) {
            const cardRepository = new CardRepositoryDatabase(connection);
            const cardService = new CardService(cardRepository);
            const cards = await cardService.getCards(parseInt(params.idColumn));
            return cards;
        });


        http.route("post", "/boards/:idBoard/columns/:idColumn/cards", async function (params: any, body: any) {
            const cardRepository = new CardRepositoryDatabase(connection);
            const cardService = new CardService(cardRepository);
            const cardId = await cardService.saveCard(body);
            return cardId;
        });

        http.route("delete", "/boards/:idBoard/columns/:idColumn/cards/:idCard", async function (params: any, body: any) {
            const cardRepository = new CardRepositoryDatabase(connection);
            const cardService = new CardService(cardRepository);
            await cardService.deleteCard(parseInt(params.idCard));
        });

        http.route("put", "/boards/:idBoard/columns/:idColumn/cards/:idCard", async function (params: any, body: any) {
            const cardRepository = new CardRepositoryDatabase(connection);
            const cardService = new CardService(cardRepository);
            await cardService.updateCard(body);
        });

    }
}
