var exec = require('child_process').exec
var path = require('path')
var assert = require('assert')

/* global suite, test */

suite('execpe')

test('echo one argument, default environment', function (done) {
  var echoFile = path.join(__dirname, './files/echo.sh')

  exec(echoFile, function (error, stdout, stderr) {
    assert(stdout.trim() === 'hello world')
    assert(stderr.trim() === '')
    assert(error === null)
    done()
  })
})

test('echo one argument, try to override environment', function (done) {
  var echoFile = path.join(__dirname, './files/echo+override.sh')

  exec(echoFile, function (error, stdout, stderr) {
    assert(stdout.trim() === 'hello world')
    assert(stderr.trim() === '')
    assert(error === null)
    done()
  })
})
