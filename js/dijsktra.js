class Graph {
  constructor() {
    this.nodes = [];
    this.adjacencyList = {};
  }

  addNode(node) {
    this.nodes.push(node);
    this.adjacencyList[node] = [];
  }

  addEdge(node1, node2, weight) {
    this.adjacencyList[node1].push({ node: node2, weight: weight });
    this.adjacencyList[node2].push({ node: node1, weight: weight });
  }

  findPathWithDijkstra(startNode, endNode) {
    let times = {}; //represents shortest times
    let backtrace = {}; //represents shortest path sequence
    let pq = new PriorityQueue();
    times[startNode] = 0;

    this.nodes.forEach((node) => {
      if (node !== startNode) {
        times[node] = Number.MAX_SAFE_INTEGER;
      }
    });

    //start with first node
    pq.enqueue([startNode, 0]);

    while (!pq.isEmpty()) {
      let shortestStep = pq.dequeue();
      let currentNode = shortestStep[0];
      this.adjacencyList[currentNode].forEach((neighbor) => {
        //time it took to get here + weight of the neighbor
        let time = times[currentNode] + neighbor.weight;
        //if this path is shorter than the one already stored for this neighbor,
        //update times and backtrace, and enqueue this node for further exploration
        if (time < times[neighbor.node]) {
          times[neighbor.node] = time;
          backtrace[neighbor.node] = currentNode;
          pq.enqueue([neighbor.node, time]);
        }
      });
    }

    let path = [endNode];
    let lastStep = endNode;
    while (lastStep !== startNode) {
      path.unshift(backtrace[lastStep]);
      lastStep = backtrace[lastStep];
    }
    return `Path is ${path} and time is ${times[endNode]}`;
  }
}

class PriorityQueue {
  constructor() {
    this.collection = [];
  }

  //0th index = value, 1st index = weight
  enqueue(element) {
    if (this.isEmpty()) {
      this.collection.push(element);
    } else {
      let added = false;
      for (let i = 1; i <= this.collection.length; i++) {
        //if weight of this element is less than current, insert before
        if (element[1] < this.collection[i - 1][1]) {
          this.collection.splice(i - 1, 0, element);
          added = true;
          break;
        }
      }
      //insert at end of list
      if (!added) {
        this.collection.push(element);
      }
    }
  }

  dequeue() {
    let value = this.collection.shift();
    return value;
  }

  isEmpty() {
    return this.collection.length === 0;
  }
}

let map = new Graph();
map.addNode(0);
map.addNode(1);
map.addNode(2);
map.addNode(3);
map.addNode(4);
map.addNode(5);
map.addNode(6);
map.addNode(7);
map.addNode(8);



map.addEdge(0, 1, 4);
map.addEdge(0, 7, 8);
map.addEdge(1, 7, 11);
map.addEdge(1, 2, 8);
map.addEdge(2, 3, 7);
map.addEdge(2, 8, 2);
map.addEdge(3, 4, 9);
map.addEdge(3, 5, 14);
map.addEdge(4, 5, 10);
map.addEdge(5, 6, 2);
map.addEdge(2, 5, 4);
map.addEdge(6, 8, 6);
map.addEdge(6, 7, 1);
map.addEdge(7, 8, 7);

console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[1]));
console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[2]));
console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[3]));
console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[4]));
console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[5]));
console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[6]));
console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[7]));
console.log(map.findPathWithDijkstra(map.nodes[0], map.nodes[8]));
console.log(map.findPathWithDijkstra(map.nodes[3], map.nodes[4]));





