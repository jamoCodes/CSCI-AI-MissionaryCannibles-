#include <iostream>   //cin,cout
#include <queue>     
#include <vector>
#include <stack>
#include <map>
#include <iomanip>
#include <string>

using namespace std;

struct mcNode    //structure of each node in the tree
{
	int state;
	//state of the node
	// x =1 if boat is on the original side of the river, x=0 otherwise
	// y = "number of missionaries on the original side of the river"
	// z = "number of cannibals on the original side of the river"
	//state=x*100+y*10+z
	int parent;         //the state of the parent node
	double costG;       //g(n), cost (1 per step) from start to present
	int action;   //1=one cannibal on the boat; 2=two cannibals; 10=one missionary; 20=two missionaries; 11=one missionary+one cannibal 
};



vector<mcNode> getSuccesors(mcNode curr);
vector<mcNode> getSuccesors35(mcNode curr);
vector<mcNode> breadth_first_search_MC();
vector<mcNode> breadth_first_search_MC35();

void display(bool boat, int m, int c, int M = 3, int C = 3, int B = 2);




int main()
{


	vector<mcNode> path = breadth_first_search_MC();
	int n = path.size();
	if (n > 0)
	{

		cout << "Pathsize=" << n << endl;
		for (int i = n - 1; i >= 0; i--)
		{
			system("cls");
			int z = path[i].state;
			int boat = z / 100;
			z = z % 100;
			int x = z / 10;
			int y = z % 10;
			cout << "Testing 3 couples, boat capacity 2 case....\n";
			display(boat > 0, x, y);
			system("pause");
		}
	}
	else
	{
		cout << "No solution!!!" << endl;
	}
	system("pause");

	vector<mcNode> path2 = breadth_first_search_MC35();
	int n2 = path2.size();
	if (n2 > 0)
	{

		cout << "Pathsize=" << n2 << endl;
		for (int i = n2 - 1; i >= 0; i--)
		{
			system("cls");
			int z = path2[i].state;
			int boat = z / 100;
			z = z % 100;
			int x = z / 10;
			int y = z % 10;
			cout << "Testing 5 couples, boat capacity  case....\n";
			display(boat > 0, x, y, 5, 5, 3);
			system("pause");
		}
	}
	else
	{
		cout << "No solution!!!" << endl;
	}
	system("pause");
	return 0;
}
/////////////////////////////////////////////////////////////////////
void display(bool boat, int m, int c, int M, int C, int B)
{
	string Sm = "MMMMMMMMMMMMMMMMMMMM", Sc = "CCCCCCCCCCCCCCCCCCC", Sb = "___________", Ss = "         ";

	if (boat)
		cout << "\n\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "\n      " << Ss.substr(0, B);
	cout << Sm.substr(0, m) << " " << Sc.substr(0, c) << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (!boat)
		cout << "\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "      " << Ss.substr(0, B);
	cout << Sm.substr(0, M - m) << " " << Sc.substr(0, C - c) << endl;

}



/////
//OTHER FUNCTIONS
/////////////////

bool validState(int m, int c, int M = 3, int C = 3)
{
	int mo = M - m, co = C - c; //numbers of the other side of the river
	if (m < 0 || c < 0 || mo < 0 || co < 0) //numbers have gotten negative
		return false;
	if (co > mo && mo > 0)
		return false;
	if (c > m && m > 0)
		return false;
	return true;
}



vector<mcNode> getSuccesors(mcNode curr)
{
	int t = curr.state;
	bool boat = t / 100; //1 if boat on the original side
	t = t % 100;
	int m = t / 10; //number of missionaries on the original side
	int c = t % 10; //number of cannibals on the original side

	int new_b, new_m, new_c; //new state
	mcNode newnode;
	vector<mcNode> children;
	newnode.parent = curr.state;
	newnode.costG = curr.costG + 1;
	if (boat > 0)
	{
		new_b = 0; //boat on original side, numbers can only decrease
				   //1=one cannibal on the boat;
		new_m = m; new_c = c - 1;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -1;
			children.push_back(newnode);
		}
		//2=two cannibals;
		new_m = m; new_c = c - 2;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -2;
			children.push_back(newnode);
		}
		//10=one missionary;
		new_m = m - 1; new_c = c;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -10;
			children.push_back(newnode);
		}
		//20=two missionaries;
		new_m = m - 2; new_c = c;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -20;
			children.push_back(newnode);
		}
		//11=one missionary+one cannibal
		new_m = m - 1; new_c = c - 1;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -11;
			children.push_back(newnode);
		}
	}
	else
	{
		new_b = 1; //boat on the other side, numbers can only increase
				   //1=one cannibal on the boat;
		new_m = m; new_c = c + 1;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 1;
			children.push_back(newnode);
		}
		//2=two cannibals;
		new_m = m; new_c = c + 2;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 2;
			children.push_back(newnode);
		}
		//10=one missionary;
		new_m = m + 1; new_c = c;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 10;
			children.push_back(newnode);
		}
		//20=two missionaries;
		new_m = m + 2; new_c = c;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 20;
			children.push_back(newnode);
		}
		//11=one missionary+one cannibal
		new_m = m + 1; new_c = c + 1;
		if (validState(new_m, new_c))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 11;
			children.push_back(newnode);
		}
	}

	return children;

}






vector<mcNode> getSuccesors35(mcNode curr)
{
	int t = curr.state;
	bool boat = t / 100; //1 if boat on the original side
	t = t % 100;
	int m = t / 10; //number of missionaries on the original side
	int c = t % 10; //number of cannibals on the original side

	int new_b, new_m, new_c; //new state
	mcNode newnode;
	vector<mcNode> children;
	newnode.parent = curr.state;
	newnode.costG = curr.costG + 1;
	if (boat > 0)
	{
		new_b = 0; //boat on original side, numbers can only decrease
				   //1=one cannibal on the boat;
		new_m = m; new_c = c - 1;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -1;
			children.push_back(newnode);
		}
		//2=two cannibals;
		new_m = m; new_c = c - 2;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -2;
			children.push_back(newnode);
		}
		//10=one missionary;
		new_m = m - 1; new_c = c;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -10;
			children.push_back(newnode);
		}
		//20=two missionaries;
		new_m = m - 2; new_c = c;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -20;
			children.push_back(newnode);
		}
		//11=one missionary+one cannibal
		new_m = m - 1; new_c = c - 1;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -11;
			children.push_back(newnode);
		}
		//3=three cannibals
		new_m = m; new_c = c - 3;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -3;
			children.push_back(newnode);
		}
		//30=three missionaries
		new_m = m - 3; new_c = c;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -30;
			children.push_back(newnode);
		}
		//21=two missionaries+one cannibal
		new_m = m - 2; new_c = c - 1;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -21;
			children.push_back(newnode);
		}
		//12=one missionary+two cannibals
		new_m = m - 1; new_c = c - 2;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = -12;
			children.push_back(newnode);
		}
	}
	else
	{
		new_b = 1; //boat on the other side, numbers can only increase
				   //1=one cannibal on the boat;
		new_m = m; new_c = c + 1;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 1;
			children.push_back(newnode);
		}
		//2=two cannibals;
		new_m = m; new_c = c + 2;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 2;
			children.push_back(newnode);
		}
		//10=one missionary;
		new_m = m + 1; new_c = c;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 10;
			children.push_back(newnode);
		}
		//20=two missionaries;
		new_m = m + 2; new_c = c;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 20;
			children.push_back(newnode);
		}
		//11=one missionary+one cannibal
		new_m = m + 1; new_c = c + 1;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 11;
			children.push_back(newnode);
		}
		//3=three cannibals
		new_m = m; new_c = c + 3;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 3;
			children.push_back(newnode);
		}
		//30=three missionaries
		new_m = m + 3; new_c = c;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 30;
			children.push_back(newnode);
		}
		//21=two missionaries+one cannibal
		new_m = m + 2; new_c = c + 1;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 21;
			children.push_back(newnode);
		}
		//12=one missionary+two cannibals
		new_m = m + 1; new_c = c + 2;
		if (validState(new_m, new_c, 5, 5))
		{
			newnode.state = new_b * 100 + new_m * 10 + new_c;
			newnode.action = 12;
			children.push_back(newnode);
		}
	}

	return children;

}

vector<mcNode> breadth_first_search_MC()
{
	const int theGoal = 0;
	
	mcNode start = { 133,-1, 0, 0 }; //the start node
	queue<mcNode> frontier; //Frontier is a queue for BFS
	map<int, mcNode> explored; //Explored set implemented as STL map
	vector<mcNode> solution; //solution implemented as a vector
	frontier.push(start); //initialize the frontier with the start node
	while (!frontier.empty())
	{
		mcNode curr = frontier.front(); frontier.pop(); //take next node from frontier
		if (explored.find(curr.state) != explored.end())
			continue;
		if (curr.state == theGoal) {

			//reached the goal state, return solution

			while (curr.state != start.state)
			{
				solution.push_back(curr); curr = explored[curr.parent];
			}
			solution.push_back(curr);
			return solution;
		}
		explored[curr.state] = curr; //add the current node to the explored set
		vector<mcNode> children = getSuccesors(curr); //get the children nodes
		int n = children.size();
		for (int i = 0; i < n; i++)
			//insert the children nodes into frontier if not explored yet
			if (explored.find(children[i].state) == explored.end())
				frontier.push(children[i]);
	}
	return solution;
}



vector<mcNode> breadth_first_search_MC35()
{
	const int theGoal = 0;

	mcNode start = { 155,-1, 0, 0 }; //the start node
	queue<mcNode> frontier; //Frontier is a queue for BFS
	map<int, mcNode> explored; //Explored set implemented as STL map
	vector<mcNode> solution; //solution implemented as a vector
	frontier.push(start); //initialize the frontier with the start node
	while (!frontier.empty())

	{
		mcNode curr = frontier.front(); frontier.pop(); //take next node from frontier
		if (explored.find(curr.state) != explored.end())
			continue;
		if (curr.state == theGoal) {

			//reached the goal state, return solution

			while (curr.state != start.state)
			{
				solution.push_back(curr); curr = explored[curr.parent];
			}
			solution.push_back(curr);
			return solution;
		}
		explored[curr.state] = curr; //add the current node to the explored set
		vector<mcNode> children = getSuccesors35(curr); //get the children nodes
		int n = children.size();
		for (int i = 0; i < n; i++)
			//insert the children nodes into frontier if not explored yet
			if (explored.find(children[i].state) == explored.end())
				frontier.push(children[i]);
	}
	return solution;
}


