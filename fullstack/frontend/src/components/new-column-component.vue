<script setup lang="ts">
import { ref } from 'vue';

defineProps(["board"]);
const columnName = ref("");
</script>

<template>
    <div class="new-column">
        <!-- {{ columnName }} -->
        <input class="new-column-input" type="text" v-model="columnName" />
        <button class="new-column-add" v-on:click="board?.addColumn(columnName, true)">Add</button>
    </div>
</template>

<style scoped>
.new-column {
    width: 200px;
    text-align: center;
    margin-right: 5px;
    padding: 10px;
    background-color: #EEE;
    border: 1px dashed #CCC;
    display: block;
}
</style>