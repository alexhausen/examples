import PgPromiseConnection from "../../src/infra/database/pg-promise-connection";
import BoardRepositoryDatabase from "../../src/infra/database/repository/board-repository-db";
import BoardRepositoryMemory from "../../src/infra/database/repository/board-repository-mem";
import BoardService from "../../src/service/board-service"

test("Deve listar os quadros", async function () {
    const boardRepository = new BoardRepositoryMemory();
    const boardService = new BoardService(boardRepository);
    const boards = await boardService.getBoards();
    expect(boards).toHaveLength(1);
    const [board] = boards;
    expect(board.name).toBe("Projeto 1");
});
