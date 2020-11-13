const { Stack, Queue } = require('./StackQueue');

function testQueue() {
    q = new Queue();
    q.enqueue('test');
    q.enqueue('test2');
    q.enqueue('test3');
    console.log(q.printQueue());
    console.log(q.front());
    console.log(q.rear());
    console.log(q.dequeue());
    console.log(q.printQueue());
}

function reverseString(str) {
    stk = new Stack();
    ret = '';
    for (let i = 0; i < str.length; i++) {
        let c = str[i];
        stk.push(c);
    }
    for (let i = 0; i < str.length; i++) {
        ret += stk.pop();
    }
    return ret;
}

function testStack() {
    console.log(reverseString('jared'));
    console.log(reverseString('spadaro'));
}

testQueue();