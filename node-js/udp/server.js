#!/usr/bin/env node
'use_strict'

const dgram = require('dgram')
const server = dgram.createSocket('udp4')

server.on('error', (err) => {
  console.log(`server error:\n${err.stack}`)
  server.close()
})

server.on('message', (msg, rinfo) => {
  console.log(`server got: '${msg}' (${msg.length} bytes) from ${rinfo.address}:${rinfo.port}`)
  const reply = new Buffer('message replied from server')
  server.send(reply, 0, reply.length, rinfo.port, rinfo.address)
})

server.on('listening', () => {
  var listening = server.address()
  console.log(`server listening ${listening.address}:${listening.port}`)
})

server.bind(41234, () => { console.log('binded') })
// server listening 0.0.0.0:41234
