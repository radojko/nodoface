#!/usr/bin/env ts-node
import * as nodoface from '../';
import * as path from 'path';
import { SequenceCapture, FaceDetectorMTCNN } from '../';

let sequenceCapture = new SequenceCapture();
let mtcnn = new FaceDetectorMTCNN();

const argv = process.argv.slice(2);

sequenceCapture.openVideoFile(argv[0]);
mtcnn.load(argv[1]);
let progress = 0;
for (let i = 0; progress < 1; i++) {
    let img = sequenceCapture.getNextFrame();
    let res = mtcnn.detectFaces(img);
    let bboxes = res.detections;
    progress = sequenceCapture.getProgress();
    console.log(`Frame ${i} detections [Progress ${(100 * progress).toFixed(2)}%]:`);
    
    for (let j = 0; j < bboxes.length; j++) {
        let rect = bboxes[j];
        console.log(`
        Detection ${j}: 
            x:${rect.x.toFixed(0)}, y:${rect.y.toFixed(0)}, 
            width:${rect.width.toFixed(0)}, height:${rect.height.toFixed(0)} 
        `);
        nodoface.drawRect(img, bboxes[j], [0, 255, 0]);
    }
    nodoface.showImage(img);
    nodoface.waitKey(1000 / sequenceCapture.fps);
}
nodoface.destroyAllWindows();

