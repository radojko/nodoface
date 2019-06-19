const nodoface = require("../api/nodoface");
let imageCapture = new nodoface.ImageCapture();

const argv = process.argv.slice(1);

imageCapture.open(argv);

console.log('Actual properties',
    '\nprogress', imageCapture.getProgress(),
    '\nImage Ht', imageCapture.getImageHeight(),
    '\nImage Wd', imageCapture.getImageWidth(),
    '\nFx', imageCapture.getFx(),
    '\nFy', imageCapture.getFy(),
    '\nCx', imageCapture.getCx(),
    '\nCy', imageCapture.getCy(),
);
let img = imageCapture.getNextImage();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
nodoface.showImage(img, 'output', 0);
let grayImg = imageCapture.getGrayFrame();
console.log(`grayFrame is Uint8Array: ${grayImg instanceof Uint8Array}| size: ${grayImg.length}`);

console.log('New properties',
    '\nprogress', imageCapture.getProgress(),
    '\nImage Ht', imageCapture.getImageHeight(),
    '\nImage Wd', imageCapture.getImageWidth(),
    '\nFx', imageCapture.getFx(),
    '\nFy', imageCapture.getFy(),
    '\nCx', imageCapture.getCx(),
    '\nCy', imageCapture.getCy(),
);
img = imageCapture.getNextImage();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
nodoface.showImage(img, 'output', 0);
nodoface.showImage(img, 'output', 0);
let bboxes = imageCapture.getBoundingBoxes();
console.log(`bboxes is Array: ${Array.isArray(bboxes)}| size: ${bboxes.length}`);
for(let rect of bboxes) {
    console.log(`x:${rect.x}, y:${rect.y}, w:${rect.width}, h:${rect.height}`);
}