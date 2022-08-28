<script setup lang="ts">
import { reactive, onMounted, inject } from "vue";
import Board from "../entities/board";
import BoardService from "../services/board-service";
import BoardComponent from "../components/board-component.vue";
import DomainEvent from "../events/DomainEvent";

const data: { board: Board | undefined } = reactive({ board: undefined });

onMounted(async () => {
    const boardService = inject("boardService") as BoardService;
    const board = await boardService.getBoard(1);
    data.board = board;
    // se registra como listener dos eventos
    board.on("addColumn", async function (event: DomainEvent) {
        // console.log(event.data);
        const idColumn = await boardService.saveColumn({
            idBoard: event.data.idBoard,
            name: event.data.column.name,
            hasEstimate: event.data.column.hasEstimate
        });
        event.data.column.idColumn = idColumn;
    });
    board.on("addCard", async function (event: DomainEvent) {
        const idCard = await boardService.saveCard({
            idBoard: event.data.idBoard,
            idColumn: event.data.idColumn,
            title: event.data.card.title,
            estimate: event.data.card.estimate
        });
        event.data.card.idCard = idCard;
    });
    board.on("deleteColumn", async function (event: DomainEvent) {
        await boardService.deleteColumn(event.data.idBoard, event.data.idColumn);
    });
    board.on("deleteCard", async function (event: DomainEvent) {
        console.log("on deleteCard");
        await boardService.deleteCard(event.data.idBoard, event.data.idColumn, event.data.idCard);
    });
    board.on("incrementEstimate", async function (event: DomainEvent) {
        await boardService.updateCard({
            idBoard: event.data.idBoard,
            idColumn: event.data.idColumn,
            idCard: event.data.card.idCard,
            title: event.data.card.title,
            estimate: event.data.card.estimate
        });
    });
    board.on("decrementEstimate", async function (event: DomainEvent) {
        await boardService.updateCard({
            idBoard: event.data.idBoard,
            idColumn: event.data.idColumn,
            idCard: event.data.card.idCard,
            title: event.data.card.title,
            estimate: event.data.card.estimate
        });
    });
});
</script>

<template>
    <BoardComponent :board="data.board"></BoardComponent>
</template>

<style scoped>
</style>
