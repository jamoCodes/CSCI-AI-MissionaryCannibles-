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
	int action;   //1=one cannibal on the boat; 2=two cannibals; 10=one missionary; 20=two mis66sionaries; 11=one missionary+one cannibal 
};


int returnState(int xState, int yState, int zState);
vector<mcNode> getSuccesors(mcNode curr);
vector<mcNode> getSuccesors35(mcNode curr);

void printNode(mcNode x)
{
	cout << "State: " << x.state << "; Parent:" << x.parent << "; Cost: " << x.costG << "; Action: " << x.action << endl;
}

int main()
{
	mcNode curr = { 133,-1, 0, 0 };
	vector<mcNode> children;
	cout << "Testing 3 couples and boat capacity 2....\n\n";
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors(curr);
	cout << "Possible child nodes :\n";
	int n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	cout << "Enter a node (apace separated: state parent cost action)\n";
	cin >> curr.state >> curr.parent >> curr.costG >> curr.action;
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	system("pause");
	cout << "\nTesting 5 couples and boat capacity 3....\n\n";
	curr = { 155,-1, 0, 0 };
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors35(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	cout << "Enter a node (apace separated: state parent cost action)\n";
	cin >> curr.state >> curr.parent >> curr.costG >> curr.action;
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors35(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);


	return 0;
}

//To test your functions, place them below

vector<mcNode> getSuccesors(mcNode curr)
{
	int state = curr.state;
	int newState = 131;
	int finalState = 123;
	int n = 0;
	int states[] = { state, newState, finalState };
	vector<mcNode> failSafe;

	int perspectiveXValue = 0; //saves the x value for the state varialbe in mcNode
	if (state == 0) {
		return failSafe; //as the problem has been solved 
	}
	else if (state < 100) {
		//if its less than 100 than its on the side of the river, now changing to th 
		perspectiveXValue = 1;
		cout << "Changed to the orignial side\n " << endl;
	}
	else {
		perspectiveXValue = 0;
		cout << "Changed to the ending side\n " << endl;
	}



	if (state % 100 == 33) {
		//then 
	}

	while (n < 3) {
		cout << "The current action is " << states[n] << endl;
		cout << " The action % 100 is " << states[n] % 100 << endl;
		cout << " The action % 10 / 10 is " << (states[n] % 10) / 10 << endl;
		cout << " The action % 100 / 10 is " << (states[n] % 100) / 10 << endl;
		cout << "The action % 3 is " << states[n] % 3 << endl;
		n++;
	}

	char d;
	cin >> d;

	return vector<mcNode>();
}

vector<mcNode> getSuccesors35(mcNode curr)
{
	return vector<mcNode>();
}



int returnState(int xState, int yState, int zState) {

	return (xState * 100) + (yState * 10) + zState;
}

void checkStates(int state) {

	
}

