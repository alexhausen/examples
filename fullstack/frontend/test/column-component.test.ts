import { mount } from "@vue/test-utils"
import Board from "../src/entities/board";
import ColumnComponentVue from "../src/components/column-component.vue"

test("Deve testar o column component", async function () {
    const board = new Board(1, "Projeto 1");
    board.addColumn("Todo", true);
    board.addColumn("Doing", true);
    board.addColumn("Done", false);
    board.addCard("Todo", "Atividade 1", 3);
    board.addCard("Todo", "Atividade 2", 2);
    board.addCard("Todo", "Atividade 3", 1);
    board.addCard("Todo", "Atividade 4", 2);
    const [todo] = board.columns;
    const wrapper = mount(ColumnComponentVue, {
        props: {
            board,
            column: todo
        }
    });

    expect(wrapper.get(".estimate").text()).toBe("8");
});
