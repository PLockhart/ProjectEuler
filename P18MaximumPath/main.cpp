#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct DijkstraNode {

	//what number did we come from to get here? Not an index, just a value to help me debug
	int Parent = 0;
	//what was the total cost to get here
	int Cost = 0;
	//the value we represent
	int Value = 0;
};

int populatePrymarid(char* fileToLoad, DijkstraNode**& nodes) {

	int numLines = 0;
	std::string line;

	std::ifstream inputFile(fileToLoad);
	//first pass to get total size of prymarid
	while (std::getline(inputFile, line))
		++numLines;

	inputFile.clear();
	inputFile.seekg(0);

	nodes = new DijkstraNode*[numLines];
	
	for (int row = 0; row < numLines; ++row) {

		//set up array for this row
		nodes[row] = new DijkstraNode[row + 1];

		//read the line, then read the input one by one 
		std::getline(inputFile, line);
		std::istringstream iss(line);

		//push values one by one into prymarid row
		int columnIndex = 0;
		int number;
		while (iss >> number)
			nodes[row][columnIndex++].Value = number;
	}

	return numLines;
}

void checkAndUpdateNewPath(DijkstraNode& rootNode, DijkstraNode& target) {

	int costToTarget = rootNode.Cost + target.Value;

	if (target.Cost < costToTarget) {

		target.Cost = costToTarget;
		target.Parent = rootNode.Value;
	}
}

int main(int argc, char** args) {

	DijkstraNode** nodes;

	char* fileInput = "p067_triangle.txt";
	//char* fileInput = "p18Input.txt";
	//char* fileInput = "TestInput.txt";

	int numLinesRead = populatePrymarid(fileInput, nodes);

	//set up base case
	nodes[0][0].Cost = nodes[0][0].Value;

	int lastLineWithChildren = numLinesRead - 2;

	//go through line by line and flood the map, until we get near the bottom
	for (int row = 0; row <= lastLineWithChildren; ++row) {

		int numIndexesInRow = row + 1;
		for (int i = 0; i < numIndexesInRow; ++i) {

			//go to the 2 bottom children under this node, and update their cost if we have beaten their previous best
			checkAndUpdateNewPath(nodes[row][i], nodes[row + 1][i]);
			checkAndUpdateNewPath(nodes[row][i], nodes[row + 1][i + 1]);
		}
	}

	int numNodesInLastLine = numLinesRead;
	int lastLineIndex = numLinesRead - 1;
	int largestCost = 0;

	//now go along the bottom row and find the end node that has the largest cost
	for (int i = 0; i < numNodesInLastLine; ++i) {

		if (nodes[lastLineIndex][i].Cost > largestCost)
			largestCost = nodes[lastLineIndex][i].Cost;
	}

	std::cout << "Largest Cost " << largestCost << std::endl;
}