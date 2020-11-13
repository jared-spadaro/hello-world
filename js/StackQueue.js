class Stack {
    constructor() {
        this.items = [];
    }

    push(element) {
        this.items.push(element);
    }

    pop() {
        if (!this.items.length) return "Underflow";
        return this.items.pop();
    }

    peek() {
        return this.items[this.items.length-1];
    }

    isEmpty() {
        return this.items.length === 0;
    }

    printStack() {
        let str = ""; 
        for (let i = 0; i < this.items.length; i++) 
            str += this.items[i] + " "; 
        return str; 
    } 

}

class Queue {
    constructor() {
        this.items = [];
    }

    enqueue(element) {
        this.items.push(element);
    }

    dequeue() {
        return this.items.shift();
    }

    front() {
        if (!this.items.length) return "Underflow";
        return this.items[0];
    }

    rear() {
        if (!this.items.length) return "Underflow";
        return this.items[this.items.length-1];
    }

    printQueue() {
        let str = ""; 
        for (let i = 0; i < this.items.length; i++) 
            str += this.items[i] + " "; 
        return str; 
    } 
}

module.exports = { Stack, Queue }
