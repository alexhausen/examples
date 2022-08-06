<script setup lang="ts">
import { computed, reactive } from "@vue/reactivity";
import { onMounted } from "@vue/runtime-core";
import axios from "axios";

let data: any = reactive({});

let cardTitle = "";
let columnName = "";

function addColumn(columnName: string) {
    data.board.columns.push({ name: columnName, cards: [] });
}

function addCard(column: any, cardTitle: string) {
    column.cards.push({ title: cardTitle, estimate: 3 });
}

function incrementEstimate(card: any) {
    card.estimate++;
}

function decreaseEstimate(card: any) {
    card.estimate--;
}

onMounted(async () => {
    const response = await axios({
        url: "http://localhost:3000/boards/1",
        method: "get"
    });
    data.board = response.data;
});

const boardEstimate = computed(() => data.board.columns.reduce(
    (totalColumn: number, column: any) => totalColumn + column.cards.reduce(
        (totalCard: number, card: any) => totalCard + card.estimate,
        0),
    0)
);

</script>

<template>
    <div v-if="data.board">
        <h3>{{ data.board.name }} {{ boardEstimate }}</h3>
        <div class="columns">
            <div class="column" v-for="column in data.board.columns">
                <h3>{{ column.name }} {{ column.estimate }}</h3>
                <div class="card" v-for="card in column.cards">
                    {{ card.title }} {{ card.estimate }}
                    <br />
                    <button @click="incrementEstimate(card)">+</button>
                    <button @click="decreaseEstimate(card)">-</button>
                </div>
                <div class="card new-card">
                    {{ cardTitle }}
                    <input type="text" v-model="cardTitle" />
                    <button v-on:click="addCard(column, cardTitle)">Add</button>
                </div>
            </div>
            <div class="column new-column">
                {{ columnName }}
                <input type="text" v-model="columnName" />
                <button v-on:click="addColumn(columnName)">Add</button>
            </div>
        </div>
    </div>
</template>

<style scoped>
.columns {
    display: flex;
    flex-direction: row;
}

.column {
    width: 200px;
    text-align: center;
    background-color: #CCC;
    margin-right: 5px;
    padding: 10px;
    border: 1px solid #000;
}

.new-column {
    background-color: #EEE;
    border: 1px dashed #CCC;
    display: block;
}

.card {
    text-align: center;
    width: 100%;
    height: 80px;
    background-color: #F3E779;
    border: 1px solid #000;
    margin-bottom: 10px;
    display: flex;
    align-items: center;
    justify-content: space-around;
}

.new-card {
    background-color: #EEE;
    border: 1px dashed #CCC;
    display: block;
}
</style>
