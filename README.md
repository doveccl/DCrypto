# DCrypto

  [![NPM version][npm-image]][npm-url]
  [![npm][download-image]][download-url]
  [![Build status][travis-image]][travis-url]
  [![GitHub license][license-image]][license-url]

Simple string crypto library

## Installation

Use npm:

```bash
$ npm i dcrypto
```

Use yarn:

```bash
$ yarn add dcrypto
```

## Usage

```js
var DCrypto = require('dcrypto');

var seed = 0; // 0 - 255
var text = 'Hello World';

var encrypted = DCrypto.encrypt(text, seed);
var decrypted = DCrypto.decrypt(encrypted, seed);

console.log('encrypted:', encrypted);
console.log('decrypted:', decrypted);
```

## Use in other language

- C/C++ header file: [dcrypto.h][cpp-header]
- PHP library file: [dcrypto.php][php-library]

[npm-image]: https://img.shields.io/npm/v/dcrypto.svg
[npm-url]: https://www.npmjs.com/package/dcrypto

[download-image]: https://img.shields.io/npm/dt/dcrypto.svg
[download-url]: https://www.npmjs.com/package/dcrypto

[travis-image]: https://img.shields.io/travis/doveccl/DCrypto/master.svg
[travis-url]: https://travis-ci.org/doveccl/DCrypto

[license-image]: https://img.shields.io/github/license/doveccl/DCrypto.svg
[license-url]: https://github.com/doveccl/DCrypto/blob/master/LICENSE

[cpp-header]: https://github.com/doveccl/DCrypto/blob/master/lib/dcrypto.h
[php-library]: https://github.com/doveccl/DCrypto/blob/master/php/dcrypto.php
