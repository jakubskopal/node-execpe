const process = require('process')
const execpe = require('./build/Release/execpe.node').execpe

function realExecpe (path, args, env) {
  var realenv = []
  args = args || []
  env = env || process.env
  Object.keys(env)
    .forEach(function (key) {
      realenv.push(key + '=' + env[key])
    })
  return execpe(path, args, realenv)
}

module.exports = realExecpe
