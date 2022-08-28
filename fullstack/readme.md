# Curso Fullstack

[Link](https://app.branas.io/public/products/f78126e7-40f1-4a7f-a64d-aaa9e8c5e016)

## TL;DR

```sh
$ cd backend
$ docker compose start
$ npx nodemon src/main.ts
```

```sh
$ cd frontend
$ npm run dev
```

## Setup node

O `npx` executa as dependências do projeto.

```sh
$ npm init -y
$ npm install typescript
$ npm install jest
$ npx tsc
$ npx jest

# cria o tsconfig.json
$ npx tsc --init

# transpila o código
$ npx tsc

# executa o código transpilado (ver outDir do tsconfig.json)
node dist/main.js

# executa com JIT sem precisar transpilar
npm install --save-dev ts-node
npx ts-node src/main.ts
```

---

## Back-end

O `nodemon` monitora alterações no arquivo.

```sh
$ npx nodemon src/main.js
```
O `pm2` é o _process manager_ , usado em produção
```sh
$ npx pm2 list

# inicia 4 instâncias (load balancer)
$ npx pm2 start <arquivo.js> -i 4

# inicia n instâncias (n = número de cores)
$ npx pm2 start <arquivo.js> -i max

# reload da página similar ao nodemon (não usar em produção)
$ npx pm2 start <arquivo.js> --watch

# exibe logs (console)
$ npx pm2 log

# monitor básico
$ npx pm2 monit

# dependências projeto
npm install --save jest @types/jest nodemon ts-node ts-jest express @types/express axios pg-promise

# habilita o jest para o typescript
npx ts-jest config:init

# roda os testes
npx jest

```

Arquivo de config do `pm2`: `ecosystem.config.js`

```sh
$ npm install --save-dev nodemon
$ npm install pm2
```

> Executa com o ts-node e nodemon
```sh
$ npx nodemon src/main.ts
```

### Docker

https://docs.docker.com/engine/install/ubuntu/
```
$ sudo groupadd docker
$ sudo usermod -aG docker $USER

$ docker run hello-world
$ docker compose version

$ docker compose up -d

$ docker compose start

$ docker container ls --all

```

### Postgres e PgAdmin

> 172.17.0.1 === docker's localhost

>  pgadmin config:
```
name: local-db
host: 172.17.0.1
port: 5432
user: postgres
password: 12345
```
http://localhost:9080/login

---

## Front-end

Plugin vscode: `volar`

```sh
# install vue + vite
npm create vite

# executa o vue + vite
npm run dev

# testes do view
npm install vitest

npm install vue-router

# cliente http
npm install axios

# store, aka vue-x
npm install pinia

# graphql
npm install apolo-server graphql

# testa componentes
npm install @vue/test-utils
npm install happy-dom
```
