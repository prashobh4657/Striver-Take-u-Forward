/*
Given a source node.
Find distance to all nodes

Dijkstra's algorithm can be implmented by 3 methods :
1. Priority queue (We will discuss this in this video);
2. Set (Best) (We will discuss in next video);
3. Queue (It will take more time) (Will not discuss this);

Intially we will be having min-heap. (priority queue) and distance array  dist[i] denotes minimum distance from source to ith node;
==> Pairs will be stored {dist,node} (Shorter distance will be at the top)
==> Put {0,source} (because distance will be zero from source to source) and mark dist[src]=0;
==> Apply BFS to this queue and keep updating dist[] array.

*/
/*
GFG Link : https://practice.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
==> Just see latest submission;
*/
/*
It will not work negative weight or negative weight cycle.
Consider a node 0 and 1 having edge of -2 as weight b/w them.
Dry run the algorithm as node 0 as source. It will go into infinite loop. 
*/
/*
Time complexity : ElogV
Derivation of this complexity we will discuss in next video.
Why only Priority queue is used? We will discuss in next video. 
*/