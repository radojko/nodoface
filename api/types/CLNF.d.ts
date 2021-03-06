import {Image} from "./Image";
import {FaceModelParameters} from "./FaceModelParameters";
import {Rect} from "./Rect";
import {FloatImage} from "./FloatImage";
import {IntImage} from "./IntImage";

export class CLNF {
    constructor();
    constructor(modelFile: string);

    read(modelFile: string): undefined;

    detectLandmarks(image: Image, parameters: FaceModelParameters): boolean;

    getShape(fx: number, fy: number, cx: number, cy: number): FloatImage;

    getBoundingBox(): Rect;

    getVisibilities(): IntImage;

    reset(): undefined;
    reset(x: number, y: number): undefined;
}