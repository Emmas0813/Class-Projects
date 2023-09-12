// Emma Smith
// Project 5
// CS 2413 Data Structures
// Spring 2023

// apologizing in advance because this code is atrocious and not efficient but we gotta do what we gotta do...

#include <iostream>
#include <string> // for the fields in the class
#include <vector> // for the flowchart structures
#include <stack>  // for conversion

using namespace std;

// class to store node information
class Node
{
private:
	int nodeNumber;    // to store the node number
	string type;       // can either be START, END, IF, BLOCK
	string textWithin; // can be expression or statement - for START and END this will be empty string
public:
	// Constructors
    Node();
    Node(int nodeNumber, string type, string textWithin);
    
    // setters and getters
    int getNodeNumber(){ return nodeNumber; }
    string getType(){ return type; }
    string getTextWithin(){ return textWithin; }
    void setNodeNumber(int nodeNum){ nodeNumber = nodeNum; }
    void setType(string t){ type = t; }
    void setTextWithin(string text){ textWithin = text; }
   
    // other methods as needed
    void display();
};
Node::Node(){
    this->nodeNumber = 0;
    this->type = "";
    this->textWithin = "";
}
Node::Node(int node, string t, string tw){
    this->nodeNumber = node;
    this->type = t;
    this->textWithin = tw;
}
void Node::display(){
    if(textWithin != ""){ // check if there is text within the Node
        cout << nodeNumber << ": " << type << " node - " << textWithin << endl; // display the node information with its text
    } else{ 
       cout << nodeNumber << ": " << type << " node" << endl; // if no textWithin exists, display node info without text
    }
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// function to convert the given flowchart to generate code
void convertFlowChart(vector<Node> allNodes, vector<vector<int>> adjList) {
    stack<Node> s; // stack used to hold Node objects
    vector<int> tFlow; // vector used to hold the node Number for directed trueFlow
    vector<int> fFlow; // vector used to hold the node Number for directed falseFlow
    int trueFlow, falseFlow; //ints representing node number
    vector<int> ifStmt; // stores the FALSE flows of if statements

    for(int i = 0; i < allNodes.size(); i++){
        trueFlow = adjList[i][1]; // set the true flow as the second element of each row
        falseFlow = adjList[i][2]; // set the false flow as the third element of each row (only used for if statements)
        if(allNodes.at(i).getType() == "START"){ // if the current node type is a start
            trueFlow = adjList[0][0]; // add start to the true Flow vector
            tFlow.push_back(trueFlow); // add the start vector to the trueFlow
            trueFlow = adjList[0][1]; // add its flow to true flow vector 
            tFlow.push_back(trueFlow); // add its corresponding flow to trueFlow
        }
        if(allNodes.at(i).getType() == "BLOCK" && allNodes[adjList[i][1]].getType() == "IF"){ // check if the current block directs to an IF statement
            tFlow.push_back(trueFlow); // add the IF stmt to the vector of true flows
        }
        if(allNodes.at(i).getType() == "IF"){ // check the start of the row is an IF statement
            tFlow.push_back(trueFlow); // push the second element of the row to true flow
            ifStmt.push_back(allNodes[falseFlow].getNodeNumber()); // push the false flow onto the ifStmt of false flows
        }
        if (allNodes.at(i).getType() == "END"){ // check if end has been reached
            for(int i = ifStmt.size()-1; i >= 0; i--){ // reverse iterate the ifStmt of flase flows variable
                fFlow.push_back(ifStmt[i]); // add them to vector of false flows in reverse order
            }
            
            falseFlow = allNodes[adjList[i - 1][0]].getNodeNumber(); // set false flow to the previous first element in the row
            bool exists = false; // boolean variable to determine if an element already exists within the false flow
 
            for(int i = 0; i < ifStmt.size(); i++){  // check through the false statements in ifStmt
                if(ifStmt[i] == falseFlow){ // if the previous first element of row i already exists in the false flows of ifStmts
                    exists = true; // set exists to true
                }
            }

            if(!exists){ // if the element does not exist
                fFlow.push_back(falseFlow); // add it to the false flows vector
            }

            falseFlow = allNodes[adjList[i][0]].getNodeNumber(); // set the false flow to the last element in allNodes
            fFlow.push_back(falseFlow); // add it to the vector of false flows
        }
    }

    for(int i = fFlow.size() - 1; i>=0; i--){ // reverse iterate the false flow vector
        s.push(allNodes[fFlow[i]]); // push elements onto the stack
    }
    for(int i = tFlow.size() - 1; i>=0; i--){ // reverse iterate the true flow vector
        s.push(allNodes[tFlow[i]]); // push elements onto the stack
    }
    
    int nestedCount = 0; // counter for nested if statements
    int elseStmt = 0; // counter for "else" statements
    while(!s.empty()){ // while the stack is not empty
        Node previous = s.top(); // set a "previous node" for comparison
        s.pop();
        Node current; // set a "current" node for comparison
        if(!s.empty()) {
            current = s.top();
        }
        if(previous.getType() == "START"){ // if first node is "START"
            cout << "start" << endl; // print the start statement
        }
        if(current.getType() == "BLOCK" && previous.getType() == "START"){ // check if the flow from start goes to a block statement
            cout << current.getTextWithin() << endl; // print the block alone
        }
        if(current.getType() == "IF" && previous.getType() == "IF"){ // check if there is a nested if statement
            cout << "if(" << previous.getTextWithin() << ")\n{" << endl; // display the if and its expression
            nestedCount++; // increment number of nested if statements
            elseStmt++; // increment number of else statements needed
        }
        if(current.getType() == "BLOCK" && previous.getType() == "IF"){ // display statement inside of if statement
            cout << "if(" << previous.getTextWithin() << ")\n{" << endl << // display the if statement from previous node
            current.getTextWithin() << endl << "}\n"; // display the block within the if statement
            elseStmt++; // increment number of else statements to display
        }
        if(current.getType() == "BLOCK" && previous.getType() != "IF" && previous.getType() != "START"){ // print else statement 
            if(elseStmt > 0){ // if there are still "else" statements to be displayed
                cout << "else\n{\n" << current.getTextWithin() << "\n}" << endl; // display the else
            } 
            if(elseStmt == 0){ // otherwise if there are no more else statements needed, display the current block
                cout << current.getTextWithin() << endl;
            }
            for(int i = 0; i < nestedCount; i++){ // traverse the number of nested if statements
                cout << "\n}\n"; // display their brackets
            } 
            nestedCount--; // decrement the nested if statements
            elseStmt--; // decrement the else statements
        }
        if(previous.getType() == "END"){ // if the previous node is an end node
            cout << "end" << endl; // display the end
        } 
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string trim(const std::string& s) { // trim whitespace method for getting Text within in main. PULLED FROM INTERNET
    size_t first = s.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) {
        return ""; // the string is all whitespace
    }
    size_t last = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(first, last - first + 1);
}
void displayAllNodes(vector<Node> allNodes){ //display all nodes method
    for(int i = 0; i < allNodes.size(); i++){ // for each nodein allNodes
        allNodes.at(i).display(); // display Node info
    }
}
void displayAdjList(vector<vector<int>> adjList){ // display info in adjList
    cout << "AdjList:" << endl; 
    int n = adjList.size(); // set n to the size of adjList
    for (int i = 0; i < adjList.size(); i++) { // traverse rows of adjList
        cout << i << ": ";
        for (int j = 1; j < adjList[i].size(); j++) { // traverse elements in each row
            cout << adjList[i][j]; // display the current  "node number"
            if (j != adjList[i].size() - 1) { // check if the last element has been reach
                cout << " "; // display spaces between each element
            }
        }
        cout << endl;
    }
}

int main()
{
	int numNodesInFlowChart; // number of nodes in the flow chart

	cin >> numNodesInFlowChart; // read number of nodes from file
	cout << "Number of nodes: " << numNodesInFlowChart << endl;

	vector<Node> allNodes; // Node objects array to store all the information

    for(int i = 0; i < numNodesInFlowChart; i++){ // read in the information about the nodes and store it in allNodes
        int n; // node number
        string sub;
        string type, text; // type and text to be stored in Node
        cin >> n >> type; // read the node number, type, and text
        getline(cin, sub); //get full text for "text within"
        text = trim(sub);

        Node node(n, type, text); // create new Node object 
        allNodes.push_back(node); // add node to vector allNodes
    }

	vector<vector<int>> adjList; // adjacency list to store the flow chart
    vector<int> vectorOfNodes; // nodes represented by integers to be stores in adj list

    for(int i = 0; i < numNodesInFlowChart; i++){ // read in the adjacency list

        int inNode, outNode, countIfStmt; // integers to represent the "in" and "out" nodes
        cin >> inNode; // read first, aka "in", node of the line
        vectorOfNodes.push_back(inNode); // add the node to vector of nodes

        if(allNodes.at(i).getType() == "START"){// case for a START statement
            cin >> outNode; // read in its flow
            vectorOfNodes.push_back(outNode); // add outNode to vector of nodes
        } 
        else if(allNodes.at(i).getType() == "IF"){ // case for an IF statement
            //allNodes.at(i).isParentIfStmt(allNodes.at(i), countIfStmt);
            cin >> outNode;
            vectorOfNodes.push_back(outNode);
            cin >> outNode;
            vectorOfNodes.push_back(outNode); 
            countIfStmt++;
        } 
        else if(allNodes.at(i).getType() == "BLOCK"){ // case for a BLOCK statement
            cin >> outNode;
            vectorOfNodes.push_back(outNode);
        }
        else if(allNodes.at(i).getType() == "END"){ // case for an END statement
            // nothing happens here 
        }

        adjList.push_back(vectorOfNodes); // add current vectorOfNodes to the adjList
        vectorOfNodes.clear();// clear contents of vector
    }

    displayAllNodes(allNodes);
    displayAdjList(adjList);
	// TODO: call the convertFlowChart function with the allNodes and adjList parameters
    convertFlowChart(allNodes, adjList);

	return 0;
}
