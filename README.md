Node.js - execpe
================

[![build status](https://api.travis-ci.org/jakubskopal/node-execpe.svg)](http://travis-ci.org/jakubskopal/node-execpe)
[![JavaScript Style Guide](https://img.shields.io/badge/code%20style-standard-brightgreen.svg)](http://standardjs.com/)

This module causes your current Node.js process to be replaced by the process invoked by the parameter of this function. It's like the Ruby exec function. It currently does not work on Windows.
It is a fork of [JP Richardson's execpe](https://github.com/jprichardson/node-execpe) with ability to override environment.


Usage
-----

```js
var execpe = require('execpe')

execpe('top') // your process now becomes top. equivalent of execpe('top', [], process.env);
```

```javascript
var execpe = require('execpe')

execpe('du', [ '-sh', '/etc/fstab' ]) // your process now becomes du, with the arguments indicated
```

```javascript
var execpe = require('execpe')

// your process now becomes du, with the arguments and environment as indicated
execpe('du', [ '-sh', '/etc/fstab' ], Object.assign({}, process.env, { TERM: 'bare' }))
```


Details
-------

`execpe` can be called with one argument, where the first is the name of the executable,
second is a list of params and third is a map of environment variables. Map of variables
defaults to process.env.

License
-------

(The MIT License)

Copyright (c) 2011-2017 JP Richardson & Jakub Skopal
