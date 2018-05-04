const $ = require('assert')
const _ = require('./index')

const chr = n => String.fromCharCode(n)
const ord = c => c.charCodeAt(0)

const str = 'Hello DCrypto!'

for (let seed = 0; seed < 256; seed++) {
    for (let a = ord('A'); a < ord('z'); a++)
        for (let b = ord('A'); b < ord('z'); b++) {
            let ab = chr(a) + chr(b)
            let enc = _.encrypt(str, seed, ab)
            let dec = _.decrypt(enc, seed, ab)
            $.equal(str, dec, 'test fail')
        }
    process.stdout.write(`test success: ${seed}/255\r`)
}

console.log('test finished')
