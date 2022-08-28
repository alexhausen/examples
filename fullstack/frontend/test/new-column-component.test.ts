import { mount } from "@vue/test-utils"
import Board from "../src/entities/board";
import NewColumnComponentVue from "../src/components/new-column-component.vue"
import DomaninEvent from "../src/events/DomainEvent";

test("Deve testar o column component", async function () {
    const board = new Board(1, "Projeto 1");
    board.addColumn("Todo", true);
    board.addColumn("Doing", true);
    board.addColumn("Done", false);
    board.addCard("Todo", "Atividade 1", 3);
    board.addCard("Todo", "Atividade 2", 2);
    board.addCard("Todo", "Atividade 3", 1);

    const events: DomaninEvent[] = [];
    board.on("addColumn", function (event: DomaninEvent) {
        events.push(event);
        // console.log(event);
    });
    const wrapper = mount(NewColumnComponentVue, {
        props: {
            board
        }
    });

    await wrapper.get(".new-column-input").setValue("Todo");
    await wrapper.get(".new-column-add").trigger("click");
    expect(board.columns).toHaveLength(4);
    expect(events).toHaveLength(1);
    const [event] = events;
    expect(event.name).toBe("addColumn");
    expect(event.data.column.name).toBe("Todo");
});
