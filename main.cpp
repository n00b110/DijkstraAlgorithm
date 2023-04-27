//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <climits>
#include <stack>

using namespace std;

#define V 6		//No of vertices

int findIndexCity(string nameCity)
{
    int indexOfCity;
    if (nameCity == "Kansas City")
        indexOfCity = 0;
    else if (nameCity == "St. Lious")
        indexOfCity = 1;
    else if (nameCity == "Denver")
		indexOfCity = 2;
	else if (nameCity == "Minneapolis")
        indexOfCity = 3;
	else if (nameCity == "Eureka Springs")
        indexOfCity = 4;
	else if (nameCity == "Houston")
		indexOfCity = 5;
	else 
		indexOfCity = 0;
    
    return indexOfCity;
}

string selectCityName(int number)
{
    string nameofCity;
    switch (number) {
        case 0:
            nameofCity = "Kansas City";
            break;
        case 1: 
            nameofCity = "St. Lious";
            break;
        case 2:
            nameofCity = "Denver";
            break;
        case 3:
            nameofCity = "Minneapolis";
            break;
        case 4:
            nameofCity = "Eureka Springs";
            break;
        case 5:
            nameofCity = "Houston";
            break;
        default:
            nameofCity = "Nowhere";
    }
    return nameofCity;
}

int selectMinVertex(vector<int>& value,vector<bool>& processed)
{
	cout << "select min vertex" << endl;
	int minimum = INT_MAX;
	int vertex;
	for(int i=0;i<V;++i)
	{
		if(processed[i]==false && value[i]<minimum)
		{
			vertex = i;
			minimum = value[i];
		}
	}
	return vertex;
}

void dijkstra(int graph[V][V], string lastCity)
{
	int Fnsh = findIndexCity(lastCity);
	cout << Fnsh << endl;
	int parent[V];		//Stores Shortest Path Structure
	vector<int> value(V,INT_MAX);	//Keeps shortest path values to each vertex from source
	vector<string> nameCity(V, "KC");
	vector<bool> processed(V,false);	//TRUE->Vertex is processed

	//Assuming start point as Node-0
	parent[0] = -1;	//Start node has no parent
	value[0] = 0;	//start node has value=0 to get picked 1st

    for(int i = 0; i< V;i++){
	    string name = selectCityName(i);
	    nameCity[i] = name;        
    }

	//Include (V-1) edges to cover all V-vertices
	for(int i=0;i<V-1;++i)
	{

		//Select best Vertex by applying greedy method
		int U = selectMinVertex(value,processed);
		processed[U] = true;	//Include new Vertex in shortest Path Graph

		//Relax adjacent vertices (not yet included in shortest path graph)
		for(int j=0;j<V;++j)
		{
			/* 3 conditions to relax:-
			      1.Edge is present from U to j.
			      2.Vertex j is not included in shortest path graph
			      3.Edge weight is smaller than current edge weight
			*/
			if(graph[U][j]!=0 && processed[j]==false && value[U]!=INT_MAX
			&& (value[U]+graph[U][j] < value[j]))
			{
				value[j] = value[U]+graph[U][j];
				parent[j] = U;
			}
		}
	}
	//Print Shortest Path Graph, currently shows the previous city visited to reach that city using the shortest path
	for(int i=1;i<V;++i) {
		cout<<"U->V: "<<nameCity[parent[i]]<<"->"<<nameCity[i]<<"  wt = "<<graph[parent[i]][i]<<"\n";		
	}
	stack<int> stack;

	cout << "\n" << " " << endl;
	int i = Fnsh;
	
	while (i > 0) {
		cout<<"U->V: "<<nameCity[parent[i]]<<"->"<<nameCity[i]<<"  wt = "<<graph[parent[i]][i]<<"\n";
		stack.push(i);
		i = parent[i];	
			
	}
	cout << "\n";
	stack.push(i);
	int k = 0;
	while (!stack.empty()) {
		if (k != 0)
			cout << " -> ";
		cout << nameCity[stack.top()];
		stack.pop();
		k++;
	}
	cout <<"\n";



	cout << "\n" << " " << endl;

	// Prints distance from each city to adjacent cities
	for(int i=0;i<V;++i) {
		for(int j = 1;j <V;++j) {
			if (i == j && j + 1 < V)
				j = j + 1;
			if (graph[i][j] > 0) {
			cout<<"U->V: "<<nameCity[i]<<"->"<< nameCity[j]<<"  wt = "<<graph[i][j]<<"\n";				
			}	
		}
	}

}
//Users should be able to pick a city to go to and the entire shortest path should be shown to that city
int main()
{
	//cout << "Hello World";
	int graph[V][V] = { {0, 1, 4, 0, 0, 0},
						{1, 0, 4, 2, 7, 0},
						{4, 4, 0, 3, 5, 0},
						{0, 2, 3, 0, 4, 6},
						{0, 7, 5, 4, 0, 7},
						{0, 0, 0, 6, 7, 0} };


    // City must be spelled correctly, still not working for cities with a space in name
	string finish;
	cout << "What city are you going to? " << "\n";
	cin >>finish;

	dijkstra(graph, finish);
	
	return 0;
}

//TIME COMPLEXITY: O(V^2)
//TIME COMPLEXITY: (using Min-Heap + Adjacency_List): O(ElogV)
