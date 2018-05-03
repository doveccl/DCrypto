# DCrypto

Simple string crypto library

## Installation

Use npm:

```bash
$ npm i dcrypto
```

Use yarn:

```bash
yarn add dcrypto
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

- C/C++: include header file https://github.com/doveccl/DCrypto/blob/master/lib/dcrypto.h
- PHP: require file https://github.com/doveccl/DCrypto/blob/master/php/dcrypto.php
