import Board from "../domain/entity/board";

export default interface BoardRepository {

    findAll(): Promise<Board[]>;
    get(idBoard: number): Promise<Board>;
}
