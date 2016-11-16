#!/usr/bin/env node
'use_strict'

const dgram = require('dgram')
const client = dgram.createSocket('udp4')

const message = new Buffer('message sent from client')

client.send(message, 0, message.length, 41234, 'localhost')

client.on('message', (msg, rinfo) => {
  console.log(`client got: '${msg}' (${msg.length} bytes) from ${rinfo.address}:${rinfo.port}`)
  client.close()
})

client.on('error', (err) => {
  console.log(`client error:\n${err.stack}`)
  client.close()
})
