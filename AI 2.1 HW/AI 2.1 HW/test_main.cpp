#include <iostream>   //cin,cout
#include <queue>     
#include <vector>
#include <stack>
#include <map>
#include <iomanip>


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
void display(bool boat, int m, int c, int M , int C , int B )
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

vector<mcNode> getSuccesors(mcNode curr)
{


	int oneCannibal = 1, twoCannibals = 2, oneMissionary = 10, twoMissionaries = 20, oneOfEach = 11; //defining the states 

	//set the integers for the x,y and z 
	int x = curr.state / 100, y = (curr.state - x * 100) / 10, z = curr.state - (x * 100) - (y * 10);
	vector<mcNode> theChildren;

	if (z - 2 <= y && z - 2 >= 0) {
		//the case for when two cannibles go to the other side

		int newState = returnState(changeXState(x), y, z - 2);
		mcNode newNode = createNode(newState, twoCannibals, curr.state, curr.parent);
		theChildren.push_back(newNode);
	}

	if (y - 1 >= z && y >= 0) {
		//the case for 1 missionarie goes to the other side

		int newState = returnState(changeXState(x), y - 1, z);
		mcNode newNode = createNode(newState, oneMissionary, curr.state, curr.parent);
		theChildren.push_back(newNode);
	}

	if (y - 2 >= z && y >= 0) {
		//the case for 2 missionaries to the other side

		int newState = returnState(changeXState(x), y - 2, z);
		mcNode newNode = createNode(newState, twoMissionaries, curr.state, curr.parent);
		theChildren.push_back(newNode);
	}

	if (y - 1 >= z - 1 && y - 1 >= 0 && z - 1 >= 0) {
		//the case of one missionary and one cannible to the other side

		int newState = returnState(changeXState(x), y - 1, z - 1);
		mcNode newNode = createNode(newState, oneOfEach, curr.state, curr.parent);
		theChildren.push_back(newNode);
	}

	if (z - 1 <= y && z - 1 >= 0) {
		int newState = returnState(changeXState(x), y, z - 1);
		mcNode newNode = createNode(newState, oneCannibal, curr.state, curr.parent);
		theChildren.push_back(newNode);

	}



	return theChildren;
}

vector<mcNode> getSuccesors35(mcNode curr)
{


	int oneCannibal = 1, twoCannibals = 2, threeCannibles = 3, oneMissionary = 10, twoMissionaries = 20, threeMissionaries = 30, oneOfEach = 11, twoCandOneM = 12, twoMandOneC = 21; //defining the states 

																									 //set the integers for the x,y and z 
	int x = curr.state / 100, y = (curr.state - x * 100) / 10, z = curr.state - (x * 100) - (y * 10);
	vector<mcNode> theChildren;

	if (z - 2 <= y && z - 2 >= 0) {
		//the case for when two cannibles go to the other side

		int newState = returnState(changeXState(x), y, z - 2);
		mcNode newNode = createNode(newState, twoCannibals, curr.state, curr.parent);
		theChildren.push_back(newNode);

	}

	if (y - 1 >= z && y >= 0) {
		//the case for 1 missionarie goes to the other side

		int newState = returnState(changeXState(x), y - 1, z);
		mcNode newNode = createNode(newState, oneMissionary, curr.state, curr.parent);
		theChildren.push_back(newNode);
	}

	if (y - 2 >= z && y >= 0) {
		//the case for 2 missionaries to the other side

		int newState = returnState(changeXState(x), y - 2, z);
		mcNode newNode = createNode(newState, twoMissionaries, curr.state, curr.parent);
		theChildren.push_back(newNode);
	}

	if (y - 1 >= z - 1 && y - 1 >= 0 && z - 1 >= 0) {
		//the case of one missionary and one cannible to the other side

		int newState = returnState(changeXState(x), y - 1, z - 1);
		mcNode newNode = createNode(newState, oneOfEach, curr.state, curr.parent);
		theChildren.push_back(newNode);
	}

	if (z - 1 <= y && z - 1 >= 0) {
		//the case in which one cannible leaves to the other side
		int newState = returnState(changeXState(x), y, z - 1);
		mcNode newNode = createNode(newState, oneCannibal, curr.state, curr.parent);
		theChildren.push_back(newNode);

		cout << "Broken 1" << endl;
	}

	if (z - 3 <= y && z - 3 >= 0) {
		// when 3 cannibles leave to the other side
		int newState = returnState(changeXState(x), y, z - 3);
		mcNode newNode = createNode(newState, threeCannibles, curr.state, curr.parent);
		theChildren.push_back(newNode);
		if (newNode.state == 43) {
			cout << "Broken 2" << endl;
		}

	}

	if (y - 3 >= z && y - 3 >= 0) {
		//when 3 missionaries go on a daring adventure to the other side
		int newState = returnState(changeXState(x), y - 3, z);
		mcNode newNode = createNode(newState, threeMissionaries, curr.state, curr.parent);
		theChildren.push_back(newNode);
		if (newNode.state == 43) {
			cout << "Broken 3" << endl;
		}

	}

	if (z - 2 < y - 2 && z - 2 >= 0 && y - 3 >= 0) {
		//when the holy spirit steps in, two cannibles are converted by one missionary (and one powerful HS))

		int newState = returnState(changeXState(x), y - 1, z - 2);
		mcNode newNode = createNode(newState, twoCandOneM, curr.state, curr.parent);
		theChildren.push_back(newNode);

		if (newNode.state == 43) {
			cout << "Broken 4" << endl;
		}


	}

	if (y - 2 >= z - 1 && y - 2 >= 0 && z - 1 >= 0) {
		//when the two missionaries outnumber the single cannible and guess what the holy spirit still shows up (even in the mundaness of a non 2-1 ratio lol))
		int newState = returnState(changeXState(x), y - 2, z - 1);
		mcNode newNode = createNode(newState, twoMandOneC, curr.state, curr.parent);
		theChildren.push_back(newNode);

		if (newNode.state == 43) {
			cout << "Broken 5" << endl;
		}
	}



	return theChildren;
}



///////
//HELPER FUNCTIONS 
/////////////


int changeXState(int x) {
	if (x == 1)
		return 0;
	else
		return 1;
}
int returnState(int xState, int yState, int zState) {

	return (xState * 100) + (yState * 10) + zState;
}

mcNode createNode(int state, int action, int parentState, int parentCost) {

	mcNode nodeFinal;

	nodeFinal.state = state;
	nodeFinal.action = action;
	nodeFinal.parent = parentState;
	nodeFinal.costG = parentCost + 1;

	return nodeFinal;
}



vector<mcNode> breadth_first_search_MC()
{
	mcNode start = { 0,-1,-1,0 }; //the start node
	queue<mcNode> frontier; //Frontier is a queue for BFS
	map<int, mcNode> explored; //Explored set implemented as STL map
	vector<mcNode> solution; //solution implemented as a vector
	frontier.push(start); //initialize the frontier with the start node
	while (!frontier.empty())
	{
		mcNode curr = frontier.front(); frontier.pop(); //take next node from frontier
		if (explored.find(curr.stateId) != explored.end())
			continue;
		if ((curr.stateId / 100 == goal) || (curr.stateId % 100 == goal))
			//reached the goal state, return solution
		{
			while (curr.stateId != start.stateId)
			{
				solution.push_back(curr); curr = explored[curr.parent];
			}
			solution.push_back(curr);
			return solution;
		}
		explored[curr.stateId] = curr; //add the current node to the explored set
		vector<mcNode> children = getSuccesor(curr, A, B); //get the children nodes
		int n = children.size();
		for (int i = 0; i < n; i++)
			//insert the children nodes into frontier if not explored yet
			if (explored.find(children[i].stateId) == explored.end())
				frontier.push(children[i]);
	}

	return vector<mcNode>();
}

vector<mcNode> breadth_first_search_MC35()
{
	return vector<mcNode>();
}



//Put here your function implementations, including getSuccessors functions
