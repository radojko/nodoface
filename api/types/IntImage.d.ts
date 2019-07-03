export class IntImage {
    constructor(data: Int32Array, rows: number, columns: number, type: number);

    width(): number;

    height(): number;

    channels(): number;

    type(): number;

    toInt32Array(): Int32Array;
}