// Emma Smith
// Project 4
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <vector> // for array of transactions and array of blockChains
#include <list>   // for blockchain

using namespace std;

class transaction
{
    int node;
    int tID;          // transaction id
    int fromID;       // source ID
    int fromValue;    // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int toID;         // target ID
    int toValue;      // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int tAmount;      // how much is being transfered
    string timeStamp; // time of the transaction read from the input file
public:
    transaction(); // default constructor
    transaction(int node, int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp); // non default constructor - P4: default 100 for from and to values
    
    // all setters and getters
    void setNode(int val){
        node = val;
    }
    void setTID(int val){
        tID = val;
    }
    void setFromID(int val){
        fromID = val;
    }
    void setToID(int val){
        toID = val;
    }
    void setTAmount(int val){
        tAmount = val;
    }
    void setTimeStamp(string time){
        timeStamp = time;
    }
    void setFromValue(int from){ // set the from value to the sum of current fromValue and the value passed
        fromValue += from;
    }
    void setToValue(int to){// set the to value to the sum of current fromValue and the value passed
        toValue += to;
    }
    int getNode(){
        return node;
    }
    int getTID(){
        return tID;
    }
    int getFromID(){
        return fromID;
    }
    int getToID(){
        return toID;
    }
    int getTAmount(){
        return tAmount;
    }
    string getTimeStamp(){
        return timeStamp;
    }
    int getFromValue(){
        return fromValue;
    }
    int getToValue(){
        return toValue;
    }
    
    // helper methods
    void displayTransaction(); // display transaction info
};
transaction::transaction(){
    // default constructor initialization
    this->tID = -1;
    this->fromID = -1;
    this->toID = -1;
    this->tAmount = 100;
    this->timeStamp = "";
}
transaction::transaction(int node, int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp)
{
    this->node = node;
    this->tID = temptID;
    this->fromID = tempfromID;
    this->toID = temptoID;
    this->tAmount = temptAmount;
    this->timeStamp = temptimeStamp;
    this->fromValue = 100;
    this->toValue = 100;
}
void transaction::displayTransaction(){
    cout << tID << " " << fromID << " " << fromValue << " " << toID << " " 
    << toValue << " " << tAmount << " " << timeStamp << endl;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class block
{
    int blockNumber;                   // block number of the current block
    int currentNumTransactions;        // how many transactions are currently in the block
    int maxNumTransactions;            // how many maximum transactions can be in the block
    vector<transaction> bTransactions; // vector of transaction objects
public:
    block();                                 // default constructor
    block(int bNumber, int maxTransactions); // non default constructor

    // setters and getters
    void setBlockNumber(int val){
        blockNumber = val;
    }
    void setCurrentNumTransactions(int val){
        currentNumTransactions = val;
    }
    void setMaxNumTransactions(int val){
        maxNumTransactions = val;
    }
    int getBlockNumber(){
        return blockNumber;
    }
    int getCurrentNumTransactions(){
        return currentNumTransactions;
    }
    int getMaxNumTransactions(){
        return maxNumTransactions;
    }
    vector<transaction> getTransactions(){
        return bTransactions;
    }

    // helper methods
    void displayBlock(); // display method to display all transactions within the given block
    bool isFull(); // check if the block has maximum transactions
    void searchID(transaction& trans); // search for an ID in the bTransaction vector
    void insertTrans(transaction t); // insert method to insert a new transaction
};
block::block(){
    this->blockNumber = 100;
    this->currentNumTransactions = 0;
    this->maxNumTransactions = 10;
}
block::block(int bNumber, int maxTransactions){
    this->blockNumber = bNumber;
    this->currentNumTransactions = 0;
    this->maxNumTransactions = maxTransactions;
}
void block::insertTrans(transaction t){
    bTransactions.push_back(t); // add transaction to end of the vector of transactions
    currentNumTransactions++; // increment current number of transactions
}
void block::searchID(transaction& trans){
    for (transaction& t2 : this->getTransactions()) { // traverse each transaction inside the vector of transactions
        if (t2.getToID() == trans.getFromID()) { // is the previous toID the same as current fromID?
            trans.setFromValue(t2.getTAmount()); // update its fromValue
        }
        if (t2.getToID() == trans.getToID()) { // is the previous toID the same as the current toID?
            trans.setToValue(t2.getTAmount()); // updates its toValue
        }
        if (t2.getFromID() == trans.getFromID()) { //is the previous fromID the same as the current fromID?
            trans.setFromValue(-t2.getTAmount()); // update its fromValue
        }
        if (t2.getFromID() == trans.getToID()) { //is the previous from ID the same as the current to ID?
            trans.setToValue(-t2.getTAmount()); // updates its toValue
        }
    }
}
void block::displayBlock(){
    cout << "Block Number: " << blockNumber << " -- Number of Transaction: " << currentNumTransactions << endl; 
    for(transaction t : bTransactions){ // check each transaction inside bTransactions
        t.displayTransaction(); // display each transaction
    } 
}
bool block::isFull(){
    if(currentNumTransactions == maxNumTransactions) // check if block has reached it capacity
        return true; // block is full
    else
        return false; // block is not full
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class blockChain
{
    int currentNumBlocks; // maintain the size of the list/block chain list
    list<block> bChain;   // blockchain as a linked list
public:
    blockChain();          // default constructor
    blockChain(int tPerB); // non default constructor
    
    // setters and getters
    void setCurrentNumBlocks(int val){
        currentNumBlocks = val;
    }
    int getCurrentNumBlocks(){
        return currentNumBlocks;
    }
    list<block> getBlockChain(){
        return bChain;
    }

    // helper methods
    void searchID(transaction& trans); // this searches a block chain for previous transactions and sets the to and from values accordingly
    void displayBlockChain(); // display method to display each "node"
    void insertBlocks(block b); // insert blocks into chain
};
blockChain::blockChain(){
    currentNumBlocks = 0;
}
blockChain::blockChain(int tPerB){
    this->currentNumBlocks = 0; // set currrentNumBlocks to zero upon object creation
}
void blockChain::insertBlocks(block b){
    bChain.push_back(b); // insert block at the end of bChain list
    currentNumBlocks++; // increment number of blocks
}
void blockChain::displayBlockChain(){
    cout << "Current number of blocks: " << currentNumBlocks << endl;
    for(block b : bChain){ // traverse each block in the block chain
        b.displayBlock(); // display every block
    }
}
void blockChain::searchID(transaction& trans){ // search each block in block chain
    for(block& b : bChain){ // traverse block chain
        b.searchID(trans); // traverse the transactions of each block
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class blockNetwork
{
    int numNodes;                // maintain the number of nodes in the network
    vector<blockChain> allNodes; // vector of all the blockChains in the network
    vector<int> u;               // edge list u node
    vector<int> v;               // edge list v node

public:
    blockNetwork();                  // default constructor
    blockNetwork(int numberOfNodes); // non default constructor
    // insert method to insert new blockchain into the block network in a specific node - there will be a block chain existent in each node (allNodes vector)
    void insertBC(blockChain bc);
    // setters and getters as needed
    void setNumNodes(int nodes){
        numNodes = nodes;
    }
    int getNumNodes(){
        return numNodes;
    }
    vector<blockChain> getAllNodes(){
        return allNodes;
    }
    vector<int> getU(){
        return u;
    }
    vector<int> getV(){
        return v;
    }
    // other methods as needed
    void displayBlockNetwork();
    void insertU(int i);
    void insertV(int j);
};
blockNetwork::blockNetwork(){
    this->numNodes = 0;
}
blockNetwork::blockNetwork(int numberOfNodes){ 
    this->numNodes = numberOfNodes;
}
void blockNetwork::insertU(int i){ // insert edge into U
    u.push_back(i);
}
void blockNetwork::insertV(int j){ // insert edge into V
    v.push_back(j);
}
void blockNetwork::insertBC(blockChain bc){ // add block chain to the end of the network
    allNodes.push_back(bc);
}
void blockNetwork::displayBlockNetwork(){
    for(int i = 0; i < numNodes; i++){ // traverse through each node within the network
        cout << "~~~ Node " << i << ": " << endl; // display node number
        allNodes.at(i).displayBlockChain(); // display the block chain at the node
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{

    int numNodesInNetwork; // number of nodes, or "blockchains" in the network
    int numEdges, nodes; // u and v node info

    int node, transID, fromID, toID, tAmount; // transaction info to be read
    string timestamp;

    cin >> numNodesInNetwork; // read number of nodes within the network
    cout << "Number of nodes: " << numNodesInNetwork << endl;

    int numTransactionsPerBlock; // max transactions per block

    cin >> numTransactionsPerBlock; // read in number of transactions allowed per block
    cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;

    int totalNumTransactions; // total transactions to be read from the input file

    cin >> totalNumTransactions;  // read number of transactions
    cout << "Total number of transactions: " << totalNumTransactions << endl;

    cin >> numEdges; // number of list edges

    transaction* trans; // object of transaction
    blockChain* bc = new blockChain(numTransactionsPerBlock); // object of blockChain
    blockNetwork *bn = new blockNetwork(numNodesInNetwork); // object of block network
    
    for(int i = 0; i < (numEdges * 2); i++){ // read in u and v nodes
        cin >> node; // read node
        if(i % 2 == 0){ // if the current "cin" is an even time, insert into U
            bn->insertU(node);
        } else{ // if the current "cin" is odd, insert into V
            bn->insertV(node);
        }
    }

    block* b = new block(1, numTransactionsPerBlock); // create new block
    int currentNode = 0; // assuming every current node starts at 0...
    
    for(int i = 0; i < totalNumTransactions; i++) { // traverse every transaction in the input file
        cin >> node >> transID >> fromID >> toID >> tAmount >> timestamp; // read file to store transaction info
        
        trans = new transaction(node, transID, fromID, toID, tAmount, timestamp); // read input into new transaction
        if(currentNode == node){ // ensure transactions occur within the same node
            if(bc->getCurrentNumBlocks() >= 1){ // if the block chain has more than one block, search for IDs across all blocks in the chain.
                b->searchID(*trans); // search the transactions of the current block
                bc->searchID(*trans); // call search ID on the block chain
            }
            else if(bc->getCurrentNumBlocks() == 0){ // if there are not any blocks present in the block chain yet, search for ID within the same block
                b->searchID(*trans); // call search ID on the current block
            }
        }

        if(currentNode != node){ // check if the current node changed from the previous one
            currentNode++; // increment the current node to match the current 
            bc->insertBlocks(*b); // insert current block into the block chain
            bn->insertBC(*bc); // insert the block chain into the network
            bc = new blockChain(numTransactionsPerBlock); // create an empty block chain
            b = new block(1, numTransactionsPerBlock); // create a new block for the first block in new block chain
        }

        if(b->isFull()){ // check if current transactions is maxed out
            bc->insertBlocks(*b); // insert the block in the block chain
            b = new block(b->getBlockNumber() + 1, numTransactionsPerBlock); // create a new block with incremented block number
        }
        cout << "Inserting transaction to block #" << b->getBlockNumber() << " in node " << node << endl; 
        b->insertTrans(*trans); // insert transaction into current block
    }

    bc->insertBlocks(*b); // insert blocks in block chain
    bn->insertBC(*bc); // insert block chain in block network
    bn->displayBlockNetwork(); // display network

    // delete all dynamically created data
    delete trans;
    delete b;
    delete bc;
    delete bn;
    return 0;
}

