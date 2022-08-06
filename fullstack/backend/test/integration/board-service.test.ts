import PgPromiseConnection from "../../src/infra/database/pg-promise-connection";
import BoardRepositoryDatabase from "../../src/infra/database/repository/board-repository-db";
import CardRepositoryDatabase from "../../src/infra/database/repository/card-repository-db";
import ColumnRepositoryDatabase from "../../src/infra/database/repository/column-repository-db";
// import BoardRepositoryMemory from "../../src/infra/database/repository/board-repository-mem";
import BoardService from "../../src/service/board-service"

test("Deve listar os quadros", async function () {
    const connection = new PgPromiseConnection();
    const boardRepository = new BoardRepositoryDatabase(connection);
    const columnRepository = new ColumnRepositoryDatabase(connection);
    const cardRepository = new CardRepositoryDatabase(connection);
    // const boardRepository = new BoardRepositoryMemory();
    const boardService = new BoardService(boardRepository, columnRepository, cardRepository);
    const boards = await boardService.getBoards();
    expect(boards).toHaveLength(1);
    const [board] = boards;
    expect(board.name).toBe("Projeto 1");
    await connection.close();
});

test("Deve retornar um quadro", async function () {
    const connection = new PgPromiseConnection();
    const boardRepository = new BoardRepositoryDatabase(connection);
    const columnRepository = new ColumnRepositoryDatabase(connection);
    const cardRepository = new CardRepositoryDatabase(connection);
    const boardService = new BoardService(boardRepository, columnRepository, cardRepository);
    const board = await boardService.getBoard(1);
    expect(board.name).toBe("Projeto 1");
    expect(board.columns).toHaveLength(3);
    const [a,b,c] = board.columns;
    expect(a.name).toBe("Coluna A");
    expect(b.name).toBe("Coluna B");
    expect(c.name).toBe("Coluna C");
    expect(board.estimate).toBe(6);
    expect(a.estimate).toBe(6);
    expect(b.estimate).toBe(0);
    expect(c.estimate).toBe(0);
    expect(a.cards).toHaveLength(3);
    const [card1, card2, card3] = a.cards;
    expect(card1.title).toBe("Atividade 1");
    expect(card2.title).toBe("Atividade 2");
    expect(card3.title).toBe("Atividade 3");
    expect(card1.estimate).toBe(3);
    expect(card2.estimate).toBe(2);
    expect(card3.estimate).toBe(1);
    await connection.close();
});
