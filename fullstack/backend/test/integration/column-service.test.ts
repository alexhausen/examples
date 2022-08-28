import PgPromiseConnection from "../../src/infra/database/pg-promise-connection";
import ColumnRepositoryDatabase from "../../src/infra/database/repository/column-repository-db";
import ColumnService from "../../src/service/column-service";
import Column from "../../src/domain/entity/column";

test("Deve listar as colunas", async function () {
    const connection = new PgPromiseConnection();
    const columnRepository = new ColumnRepositoryDatabase(connection);
    const columnService = new ColumnService(columnRepository);
    const columns = await columnService.getColumns(1);
    expect(columns).toHaveLength(3);
    await connection.close();
});


test("Deve salvar uma coluna", async function () {
    const connection = new PgPromiseConnection();
    const columnRepository = new ColumnRepositoryDatabase(connection);
    const columnService = new ColumnService(columnRepository);
    const idColumn = await columnService.saveColumn(new Column(1, 1, "Todo", true));
    const column = await columnService.getColumn(idColumn);
    expect(column.name).toBe("Todo");
    await columnService.deleteColumn(idColumn);
    await connection.close();
});

