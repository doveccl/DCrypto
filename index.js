const _ = require('./build/Release/dcrypto')

/**
 * Encrypt a string
 * @param {string} t text to encrypt
 * @param {number} s crypto seed, 0 - 255
 * @param {string} [e] two letters used in crypto, default is 'ab'
 * @return {string} encrypted string
 */
exports.encrypt = (t, s, e = 'ab') => _.encrypt(t, s, e)

/**
 * Decrypt a string
 * @param {string} t text to decrypt
 * @param {number} s crypto seed, 0 - 255
 * @param {string} [e] two letters used in crypto, default is 'ab'
 * @return {string} decrypted string
 */
exports.decrypt = (t, s, e = 'ab') => _.decrypt(t, s, e)
