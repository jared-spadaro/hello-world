function solution(A) {
    // write your code in JavaScript (Node.js 8.9.4)
    let sorted = A.sort((a,b) => {
        return a - b;
    });
    let ret = 0; 
    let ndx = sorted.length-1;
    let max = 0;
    let temp = 0;
    while (!ret) {
        max = sorted[ndx]; //6
        temp = max-1; //5
        //check max-- until we reach another element
        while (!ret) {
            console.log('temp is ' + temp);
            if (!sorted.includes(temp)) {
                ret = temp;
            }
            else temp--;
        }
        ndx--;
    }
    return ret;
}
console.log(solution([3,4,2,1,1,6]));