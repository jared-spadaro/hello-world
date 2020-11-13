function longest(target, vals) {
    let ret = "";
    for (let word of vals) {
        let sIndex = 0, inputIndex = 0;
        let temp = "";
        while (sIndex < word.length && inputIndex < target.length) {
            if (word[sIndex] === target[inputIndex]) {
                temp += word[sIndex];
                sIndex++;
                inputIndex++;
            }
            else {
                inputIndex++;
            }
        }
        if (temp === word) {
            if (word.length > ret.length) {
                ret = word;
            }
        }
    }
    return ret;
}

let target = "abpppleee";
let dict = ["able","ale","apple","bale","kangaroo"];
console.log(longest(target, dict));