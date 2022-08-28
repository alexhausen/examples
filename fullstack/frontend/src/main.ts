import { createApp } from 'vue'
import App from './app.vue'
import AxiosAdapter from './infra/http/axios-adapter';
import BoardServiceHttp from "./services/board-service-http";

const app = createApp(App);
const httpClient = new AxiosAdapter();
const baseUrl = "http://localhost:3000"
app.provide("boardService", new BoardServiceHttp(httpClient, baseUrl));
app.mount('#app');
