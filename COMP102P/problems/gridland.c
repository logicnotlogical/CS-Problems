// gridland.c
// A SOLUTION FOR COMP102P PROBLEM #2
//
// Created by Matthew Bell, latest version made
// on 2015-10-17 on a busy train :)
//
// This program takes the coordinates on n nodes on a grid
// (I do not know the maximum that n can be, play around
// and see if you can break the program!). Negative
// integer input is wholeheartedly not recommended
// and will lead to public shaming. Shame on you!
//
// The program will make an adjacency matrix which assumes
// that the graph is 'complete', i.e. all vertices have a
// direct edge between every other one (there are 1/2*n*(n-1)
// edges in this graph). I chose to use an adjacency matrix rather
// than an adjacency list because we are not modifying the edges
// of the graph (no adding/removing), and the chosen algorithm
// favours an adjacency matrix as well.
//
// I use prim's algorithm to find the minimum spanning tree. It
// is child's play to implement on a matrix, and I have been using the
// length=-1 as a flag to prevent the algorithm from trying to use the same
// node again and again. If I let this be the case, the program would
// run until the forces of entropy flip some bits around in main memory.
// Alternatively, you could rub a high power magnet on the hard drive
// for the same effect. I'm waffling here.
//
// It should be noted that currently, the program will print out
// the contents of the adjacency matrix, so be prepared for extreme
// verbosity. If you want, you could just go through the code
// and remove anything that begins with printf(). Apart from the
// final output, obviously.
//
// Final note: I use the terms 'node' and 'vertex' interchangeably.
// So sue me. It's my code, I DO WHAT I WANT.
//
// EXAMPLE USAGE
// Graph:
// --X------
// ---------
// -----X---
// -X-------
// Points at (1,0), (2,3) and (5,1). Input would be:
// $ ./gridland2.c 1 0 2 3 5 1
//
// And output would be:
// ADDED: (0 -> 1), dist=4
// ADDED: (0 -> 2), dist=5
// -1	4	5
// 4	-1	5
// 5	5	-1
// 9
//
// So the result for this would be 9. Wow, I should write a
// manual page.

// stdbool.h is used here so that I can use a cool boolean
// array.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// adjMatrix is the adjacency matrix. Double the pointers,
// double the fun.
int **adjMatrix;

int main(int argc, char **argv) {
	// cheekily remove the pointless first argument we don't need.
	argc--; argv++;
	if (argc % 2 == 0) {
		// Set up adjacency matrix.
		int n = argc / 2;
		adjMatrix = calloc(n, sizeof(int *));
		for (int i = 0; i < n; i++) {
			adjMatrix[i] = calloc(n, sizeof(int));
		}
		
		// Now, let's populate the adjacency matrix.
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i==j)  {
					// -1 means that this is not an edge.
					adjMatrix[i][j] = -1;
				}
				else {
					// EXAMPLE
					// X-----
					// ---X--
					// input: 0 1 3 0
					// adjacency matrix for [0][1]: |3 - 0| + |0 - 1|
					// abs() is the modulus function, short for absolute.
					// Not abdominals.
					adjMatrix[i][j] = abs(atoi(argv[2*j]) - atoi(argv[2*i])) + abs(atoi(argv[(2*j)+1]) - atoi(argv[(2*i)+1]));
				}
			}
		}

		// I make it Prim's o' clock!

		// sumDist = The total wire used thus far.
		int sumDist = 0;
		// MST. The minimum spanning tree. We probably
		// could do without this, but it's cool to have still.
		int MST[n][n];
		// isNodeDiscovered is the cool boolean array
		// I mentioned earlier. True if the given node
		// has been discovered.
		bool isNodeDiscovered[n];
		// Counting the number of nodes discovered,
		// so you don't have to.
		int nDiscovered = 1;
		
		// Initialising the MST 2d array.
		for (int i; i < n; i++) {
			for (int j; j < n; j++) {
				MST[i][j]=0;
			}
			isNodeDiscovered[i] = false;
		}
		// You discover the first node.
		isNodeDiscovered[0] = true;
		
		while (nDiscovered < n) {
			// cheapestNodeTo: Where we start.
			int cheapestNodeTo = -1;
			// cheapestNodeFrom: Where we end.
			int cheapestNodeFrom = -1;
			// shortestDist: the value of the shortest path.
			int shortestDist = 10000;
			// We look through all the discovered nodes to see where the next
			// closest one is.
			for (int i = 0; i < n; i++) {
				if (isNodeDiscovered[i]) {
					for (int j = 0; j < n; j++) {
						// If the node is node itself, and it is not discovered.
						if ((adjMatrix[i][j] >= 0) && (!isNodeDiscovered[j])) {
							// If the given edge is the shortest one yet.
							if (adjMatrix[i][j] < shortestDist) {
								cheapestNodeTo = j;
								cheapestNodeFrom = i;
								shortestDist = adjMatrix[i][j];
							}
						}
					}

				}
			}
			// If we actually found something:
			if (cheapestNodeTo>=0 && cheapestNodeFrom>=0) {
				// Add this to the MST, pronto.
				MST[cheapestNodeTo][cheapestNodeFrom] = shortestDist;
				// We have discovered this node now.
				isNodeDiscovered[cheapestNodeTo] = true;
				// We should also increase this value as well.
				nDiscovered++;
				// Increasing the sum of wire being used.
				sumDist+= shortestDist;
				// Print it at you.
				printf("ADDED: (%i -> %i), dist=%i\n",cheapestNodeFrom,cheapestNodeTo,shortestDist);
			}
		}
		
		// Should remove this. But I love spamming stdout,
		// so it shall stay.
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%i\t",adjMatrix[i][j]);
			}
			printf("\n");
		}

		printf("%i\n",sumDist);


		return 0;
	}
	else {
		// Boo hoo, you can't count.
		printf("Please enter valid coordinates (i.e., even number of values.).\n");
		return 1;
	}
}
