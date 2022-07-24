export default class Column {

    constructor(readonly name: string, readonly hasEstimate: boolean) {
        if (name === "") {
            throw new Error("Name is required");
        }
    }
}
