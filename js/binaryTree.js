class Node {
    constructor(val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

class BST {
    constructor(val) {
        this.root = new Node(val);
    }

    addNode(val) {
        let temp = this.root;
        while (true) {
            if (val < temp.val) {
                if (temp.left) {
                    temp = temp.left;
                }
                else {
                    temp.left = new Node(val); 
                    console.log("added node " + val);
                    break;
                }
            }
            else if (val > temp.val) {
                if (temp.right) {
                    temp = temp.right;
                }
                else {
                    temp.right = new Node(val);
                    console.log("added node " + val); 
                    break;
                }
            }
            else {
                throw new Error("Value " + val +  " already exists in BST\n");
            }
        }
    }

    search(val) {
        let temp = this.root;
        while (temp) {
            if (val < temp.val) {
                temp = temp.left;
            }
            else if (val > temp.val) {
                temp = temp.right;
            }
            else {
                return temp;
            }
        }
        throw new Error("Key does not exist in this BST\n");
    }

    //left, root, right
    inOrderTraversal(node) {
        if (!node) return;
        this.inOrderTraversal(node.left);
        console.log(node.val + " ");
        this.inOrderTraversal(node.right);
    }

    //root, left, right
    preOrderTraversal(node) {
        if (!node) return;
        console.log(node.val + " ");
        this.preOrderTraversal(node.left);
        this.preOrderTraversal(node.right);
    }

    //left, right, root
    postOrderTraversal(node) {
        if (!node) return;
        this.postOrderTraversal(node.left);
        this.postOrderTraversal(node.right);
        console.log(node.val + " ");
    }
}

let bst = new BST(3);
try {
    bst.addNode(1);
    bst.addNode(2);
    bst.addNode(5);
    bst.addNode(4);
}
catch (err) {
    console.log(err.message);
}
let key = bst.search(3);
console.log("Key " + key.val + " has left child " + (key.left ? key.left.val : null) 
 + " and right child " + (key.right ? key.right.val : null));

console.log("\nIn order traversal: \n");
bst.inOrderTraversal(bst.root);
console.log("\nPre order traversal: \n");
bst.preOrderTraversal(bst.root);
console.log("\nPost order traversal: \n");
bst.postOrderTraversal(bst.root);

