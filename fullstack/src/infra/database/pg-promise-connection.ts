import pgp from "pg-promise";

import Connection from "./connection";

export default class PgPromiseConnection implements Connection {

    connection: any;

    constructor() {
        this.connection = pgp()("postgres://postgres:12345@172.17.0.1:5432/db");
    }

    async query(statement: string, params: any): Promise<any> {
        return await this.connection.query(statement, params);
    }

    async close(): Promise<void> {
        return this.connection.$pool.end();
    }

}
