import Board from "../domain/entity/board";

export default interface BoardRepository {

    findAll(): Promise<Board[]>;

}
