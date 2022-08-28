<script setup lang="ts">

defineProps(["board", "column", "card"]);
</script>

<template>
    <div class="card">
        <span class="card-title">{{ card.title }}</span> <span class="card-estimate">{{ card.estimate }}</span>
        <br />
        <button @click="board.incrementEstimate(column.idColumn, card)" class="card-increment-estimate">+</button>
        <button @click="board.decrementEstimate(column.idColumn, card)" class="card-decrease-estimate">-</button>
        <button @click="board.deleteCard(column.idColumn, card.idCard)">delete</button>
    </div>
</template>

<style scoped>
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
</style>
