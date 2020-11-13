import java.util.*;
import java.lang.*;
import java.util.concurrent.LinkedTransferQueue;
public class Graph {

    public ArrayList<ArrayList<Integer>> adjList;

    public Graph(int numVertices) {
        adjList = new ArrayList<ArrayList<Integer>>();
        for (int i = 0; i < numVertices; i++) {
            adjList.add(new ArrayList<Integer>());
        }
    }

    //print the graph in BFS order
    private void BFS(int start) {
        Queue<Integer> q = new LinkedTransferQueue<Integer>();
        Boolean[] visited = new Boolean[adjList.size()];
        Arrays.fill(visited, false);
        for (int i = 0; i < adjList.get(start).size(); i++) {
            q.add(adjList.get(start).get(i));
        }
        visited[start] = true;
        System.out.print(start + " ");
        while (!q.isEmpty()) {
            int curr = q.poll();
            if (!visited[curr]) {
                for (int i = 0; i < adjList.get(curr).size(); i++) {
                    if (!visited[adjList.get(curr).get(i)]) {
                        q.add(adjList.get(curr).get(i));
                    }
                }
                System.out.print(curr + " ");
                visited[curr] = true;
            }

        }
        System.out.print("\n");
    }

    private void DFSUtil(int start, Boolean[] visited) {
        visited[start] = true; 
        System.out.print(start + " "); 
        Iterator<Integer> i = adjList.get(start).listIterator(); 
        while (i.hasNext()) { 
            int n = i.next(); 
            if (!visited[n]) DFSUtil(n, visited); 
        }
    }

    private void DFS(int start) {
        Boolean[] visited = new Boolean[adjList.size()];
        Arrays.fill(visited, false);
        DFSUtil(start, visited);
    }

    private void shortestPath(int start, int end) {
        Boolean[] visited = new Boolean[adjList.size()];
        ArrayList<Integer> path = new ArrayList<Integer>();
    
    }

    private void printGraph() {
        for (int i = 0; i < adjList.size(); i++) {
            for (int j = 0; j < adjList.get(i).size(); j++) {
                System.out.println("(" + i + " --> " + adjList.get(i).get(j) + ")");
            }
        }
    }

    private void addEdge(int from, int to) {
        adjList.get(from).add(to);
    }

    public static void main(String[] args) {
        Graph g = new Graph(4);
            
        g.addEdge(0, 1); 
        g.addEdge(0, 2); 
        g.addEdge(1, 2); 
        g.addEdge(2, 0); 
        g.addEdge(2, 3); 
        g.addEdge(3, 3);
        
        g.printGraph();
        System.out.print("\n");
        g.BFS(2);
        g.DFS(2);
        System.out.print("\n");
    }
}