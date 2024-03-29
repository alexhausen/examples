import express, { Request, Response } from "express";

import Http from "./http";

export default class ExpressAdapter implements Http {

    app: any;

    constructor() {
        this.app = express();
        this.app.use(express.json());
        this.app.use(function (req: any, res: any, next: any) {
            res.header("Access-Control-Allow-Origin", "*");
            res.header("Access-Control-Allow-Headers", "Origin, X-Request-With, Content-Type, Accept, Authorization");
            res.header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            next();
        });
    }

    route(method: string, url: string, callback: Function): void {
        this.app[method](url, async function (req: Request, res: Response) {
            const output = await callback(req.params, req.body);
            res.json(output);
        })
    }

    listen(port: number): void {
        this.app.listen(port);
    }

};
