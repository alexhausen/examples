import BoardController from "./infra/controller/board-controller";
import PgPromiseConnection from "./infra/database/pg-promise-connection";
import ExpressAdapter from "./infra/http/express-adapter";

const connection = new PgPromiseConnection();
const http = new ExpressAdapter();
new BoardController(http, connection);
http.listen(3000);
