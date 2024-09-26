function findLargestDouble(list) {
 let doubles  = [];
    for (let value in list) {
        doubles.append(value*2);
    }

    let max = Number.NEGATIVE_INFINITY;
    for (let value in doubles) {
        if (value > max) {
            max = value;
        }
    }
    return max
}