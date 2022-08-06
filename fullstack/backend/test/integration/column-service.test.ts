import PgPromiseConnection from "../../src/infra/database/pg-promise-connection";
import ColumnRepositoryDatabase from "../../src/infra/database/repository/column-repository-db";
import ColumnService from "../../src/service/column-service";

test("Deve listar as colunas", async function () {
    const connection = new PgPromiseConnection();
    const columnRepository = new ColumnRepositoryDatabase(connection);
    const columnService = new ColumnService(columnRepository);
    const columns = await columnService.getColumns(1);
    expect(columns).toHaveLength(3);
});
