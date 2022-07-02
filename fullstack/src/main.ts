import Board from "./board";
import Card from "./card";

const board = new Board("my board", "a description");
board.addColumn("Todo", true);
board.addColumn("Doing", true);
board.addColumn("Done", false);
board.addCardToColumn(new Card("Ir na farmácia", 1), "Todo");
board.addCardToColumn(new Card("Varrer a casa", 2), "Todo");
board.addCardToColumn(new Card("Estudar Typescript", 5), "Doing");
board.addCardToColumn(new Card("Almoçar", 1), "Done");
console.log("Todo: ", board.computeEstimate("Todo"));
console.log("Doing: ", board.computeEstimate("Doing"));
console.log("Done: ", board.computeEstimate("Done"));

console.log(board);
