var execpe = require('../')

console.log(process.pid + ' - PID before exec')

execpe('sh', [ '-c', 'echo "$$ - PID after exec" && env' ], { a: 1 })
