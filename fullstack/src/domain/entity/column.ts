export default class Column {

    constructor(readonly idColumn: number, readonly name: string, readonly hasEstimate: boolean) {
        if (name === "") {
            throw new Error("Name is required");
        }
    }
}
