const nodoface = require('../api/nodoface');
let argv = process.argv.slice(2);
console.log(argv);
let img = nodoface.readImage(argv[0]);
nodoface.showImage(img);