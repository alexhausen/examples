import { mount } from "@vue/test-utils"
import Board from "../src/entities/board";
import CardComponentVue from "../src/components/card-component.vue"

test("Deve testar o card component", async function () {
    const board = new Board(1, "Projeto 1");
    board.addColumn("Todo", true);
    board.addColumn("Doing", true);
    board.addColumn("Done", false);
    board.addCard("Todo", "Atividade 1", 3);
    board.addCard("Todo", "Atividade 2", 2);
    board.addCard("Todo", "Atividade 3", 1);
    const [column] = board.columns;
    const [card] = column.cards;

    const wrapper = mount(CardComponentVue, {
        props: {
            board,
            column,
            card
        }
    });

    expect(wrapper.get(".card-title").text()).toBe("Atividade 1");
    expect(wrapper.get(".card-estimate").text()).toBe("3");
    await wrapper.get(".card-increment-estimate").trigger("click");
    await wrapper.get(".card-increment-estimate").trigger("click");
    await wrapper.get(".card-increment-estimate").trigger("click");
    expect(wrapper.get(".card-estimate").text()).toBe("6");
});
