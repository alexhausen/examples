export default class Column {

    constructor(readonly idBoard: number, readonly idColumn: number | undefined, readonly name: string, readonly hasEstimate: boolean) {
        if (name === "") {
            throw new Error("Name is required");
        }
    }
}
