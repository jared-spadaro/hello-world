class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedList {
    constructor() {
        this.head = null;
    }

    insertTail(data) {
        if (!this.head) {
            this.head = new Node(data);
        }
        else {
            let temp = head;
            while (temp.next) {
                temp = temp.next;
            }
            temp.next = new Node(data); 
        }
    }

    insertHead(data) {
        if (!this.head) {
            this.head = new Node(data);
        }
        else {
            let n = new Node(data);
            n.next = this.head;
            this.head = n;
        }
    }

    insertAfter(prev, data) {
        if (!prev) {
            console.error("Insert after -- bad previous given");
        }
        let n = new Node(data);
        n.next = prev.next;
        prev.next = n;
    }
}