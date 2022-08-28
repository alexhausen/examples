import HttpClient from "./http-client";
import axios from "axios";

export default class AxiosAdapter implements HttpClient {

    async get(url: string): Promise<any> {
        const response = await axios({ url, method: "get" });
        return response.data;
    }

    async post(url: string, data: any): Promise<any> {
        const response = await axios({ url, data, method: "post" });
        return response.data;
    }

    async put(url: string, data: any): Promise<any> {
        const response = await axios({ url, data, method: "put" });
        return response.data;
    }

    async delete(url: string): Promise<any> {
        const response = await axios({ url, method: "delete" });
        return response.data;
    }
}
