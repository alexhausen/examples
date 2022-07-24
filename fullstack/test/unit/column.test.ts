import Column from "../../src/domain/entity/column"

test("Deve criar uma coluna", function () {
    const column = new Column("Coluna A", true);
    expect(column.name).toBe("Coluna A");
    expect(column.hasEstimate).toBeTruthy();
});

test("Não deve criar uma coluna sem nome", function () {
    expect(
        () => new Column("", false)
    ).toThrow(new Error("Name is required"));
});
