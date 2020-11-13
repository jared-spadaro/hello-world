// you can write to stdout for debugging purposes, e.g.
// console.log('this is a debug message');

function solution(A, K) {
    // write your code in JavaScript (Node.js 8.9.4)
    let lastIndex = A.length - 1;
    for (let i = 0; i < K; i++) {
        let lost = A[lastIndex]; //save the lost element
        //perform the shift
        let temp = A[lastIndex-1]; //7
        for (let j = lastIndex + 1; j > 1; j--) {
            A[j-1] = temp; //set 6 to 7
            if (j > 2) temp = A[j-3]; //set temp to 9
        }
        A[0] = lost;
    }
    return A;
}


