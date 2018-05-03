<?php

require_once 'dcrypto.php';

$str = 'Hello World';
$seed = 0;

$enc = dc_encrypt($str, $seed);
$dec = dc_decrypt($enc, $seed);

echo "string: $str\n";
echo "encrypt: $enc\n";
echo "decrypt: $dec\n";
