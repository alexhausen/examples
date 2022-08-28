<script setup lang="ts">
import ColumnComponent from './column-component.vue';
import NewCardComponent from './new-card-component.vue';
import NewColumnComponent from './new-column-component.vue';
defineProps(["board"]);
</script>

<template>
    <div v-if="board">
        <h3>{{ board.name }} <span id="estimate">{{ board.getEstimate() }}</span></h3>
        <div class="columns">
            <div v-for="column in board.columns">
                <ColumnComponent :board="board" :column="column"></ColumnComponent>
                <NewCardComponent :board="board" :column="column"></NewCardComponent>
            </div>
            <NewColumnComponent :board="board"></NewColumnComponent>
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