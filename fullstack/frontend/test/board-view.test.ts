import { mount } from "@vue/test-utils"
import Board from "../src/entities/board";
import BoardService from "../src/services/board-service";
import BoardViewVue from "../src/views/board-view.vue"

function waitNextTick() {
    return new Promise(
        (resolve, _reject) => {
            setImmediate(
                () => {
                    resolve(true);
                }
            );
        }
    );
}

test("Deve testar o board view", async function () {
    const boardService: BoardService = {
        async getBoard(_idBoard: number) {
            const board = new Board(1, "Projeto 1");
            board.addColumn("Todo", true);
            board.addColumn("Doing", true);
            board.addColumn("Done", false);
            board.addCard("Todo", "Atividade 1", 3);
            board.addCard("Todo", "Atividade 2", 2);
            board.addCard("Todo", "Atividade 3", 1);
            return board;
        },
        // async saveColumn(column: SaveColumnInput) {
        //     throw new Error("Function not implemented.");
        // }
    };
    const wrapper = mount(BoardViewVue, {
        global: {
            provide: {
                boardService
            }
        }
    });
    await waitNextTick();
    expect(wrapper.get("#estimate").text()).toBe("6");
});
