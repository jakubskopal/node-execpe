#!/usr/bin/env node

var execpe = require('../../');

execpe('/bin/sh', ['-c', 'echo $HELLO'], { HELLO: 'hello world' });
