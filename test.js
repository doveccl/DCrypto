const _ = require('./index')

let seed = 0
let enc_ab = 'ab'
let str = 'Hello World'

let enc = _.encrypt(str, seed, enc_ab)
let dec = _.decrypt(enc, seed, enc_ab)

console.log('string:', str)
console.log('encrypt:', enc)
console.log('decrypt:', dec)
