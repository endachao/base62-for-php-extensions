# base62-for-php-extensions

> base62 for php extensions

## Build Setup

``` bash

# download code 
git@github.com:yccphp/base62-for-php-extensions.git
cd base62-for-php-extensions/

# run phpize
phpize


# build extensions
./configure
make && make install


# Add the configuration to php.ini
[base62]
extension=base62.so

# Restart service
service php-fpm restart

```

## Usage

```

# encode

string base62_encode(int number);
$str = base62_encode(123);

# decode

int base62_decode(string str);
$str = base62_decode($str);


```
