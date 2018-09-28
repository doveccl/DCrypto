const _ = require('./build/Release/dcrypto')

exports.encrypt = (t, s, e = 'ab') => _.encrypt(t, s, e)
exports.decrypt = (t, s, e = 'ab') => _.decrypt(t, s, e)
