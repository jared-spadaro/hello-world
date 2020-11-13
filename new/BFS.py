from collections import defaultdict

class Graph:
    def __init__(self):
        self.graph = defaultdict(list)

    def addEdge(self, u, v):
        self.graph[u].append(v)

    # print BFS of graph. s = source vertex
    def BFS(self, s):
        # Mark all vertices as not visited
        visited = [False] * (len(self.graph))
        # Create a queue for BFS
        queue = []
        # Mark source vertex as visited and enqueue it
        queue.append(s)
        visited[s] = True

        while queue:
            # Dequeue vertex and print it
            s = queue.pop(0)
            print (s, end = " ")

            # Get all adjacent vertices of the dequeued "s".
            # If an adjacent vertex has not been visited,
            # mark it as visited and enqueue
            for i in self.graph[s]:
                if visited[i] == False:
                    queue.append(i)
                    print("for vertex " + str(s) + ", found " + str(i))
                    visited[i] = True

# Driver
g = Graph() 
g.addEdge(0, 1) 
g.addEdge(0, 2) 
g.addEdge(1, 3) 
g.addEdge(1, 4) 
g.addEdge(2, 4) 
g.addEdge(3, 4)
g.addEdge(5, 3)
g.addEdge(4, 5)
  
print ("Following is Breadth First Traversal"
                  " (starting from vertex 2)") 
g.BFS(0) 

            
