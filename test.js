const dcrypto = require('./build/Release/dcrypto')

let seed = 0
let enc_ab = 'ab'
let str = 'Hello World'

let enc = dcrypto.encrypt(str, 0, enc_ab)
let dec = dcrypto.decrypt(enc, 0, enc_ab)

console.log('string:', str)
console.log('encrypt:', enc)
console.log('decrypt:', dec)
