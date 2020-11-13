function waterProblem(input) {
    let maxLeft = 0, maxRight = 0, total = 0;
    for (let i = 1; i < input.length - 1; i++) {
        //get the max wall to the left
        for (let j = 0; j < i; j++) {
            maxLeft = Math.max(input[j], maxLeft);
        }
        //get the max wall to the right
        for (let j = i + 1; j < input.length; j++) {
            maxRight = Math.max(input[j], maxRight);
        }
        let diff = Math.min(maxLeft, maxRight) - input[i];
        total += diff > 0 ? diff : 0;
        maxLeft = 0;
        maxRight = 0;
    }
    return total;
}

console.log('water total = ' + waterProblem(new Array(0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1)));
console.log('water total = ' + waterProblem(new Array(3, 0, 2, 0, 4)));
console.log('water total = ' + waterProblem(new Array(2, 0, 2)));