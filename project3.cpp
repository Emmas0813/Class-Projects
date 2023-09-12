// Emma Smith
// Project 3 
// CS 2413 Data Structures
// Spring 2023
#include <iostream>
#include <vector> // for array of transactions
#include <list> // for blockchain
using namespace std;
class transaction{
    int tID; // transaction id
    int fromID; // source ID
    int toID; // target ID
    int tAmount; // how much is being transfered
    string timeStamp; // time of the transaction read from the input file
public: 
    transaction(); // default constructor
    transaction(int temptID, int tempfromID, int temptoID, int temptAmount,
    string temptimeStamp); // non default constructor
    void toString(); // to string method
    // all setters and getters
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
};
transaction::transaction(){
    // default constructor initialization
    this->tID = 100;
    this->fromID = 100;
    this->toID = 100;
    this->tAmount = 100;
    this->timeStamp = "";
}
transaction::transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp){
    //non-default constructor initialization
    this->tID = temptID;
    this->fromID = tempfromID;
    this->toID = temptoID;
    this->tAmount = temptAmount;
    this->timeStamp = temptimeStamp;
}
void transaction::toString(){
    cout << tID << " " << fromID << " " << toID << " " << tAmount << " " << timeStamp << endl;
}
class block{
    int blockNumber; // block number of the current block
    int currentNumTransactions; // how many transactions are currently in the block
    int maxNumTransactions; // how many maximum transactions can be in the block
    vector<transaction> bTransactions; // vector of transaction objects
public:
    block(); // default constructor
    block(int bNumber, int maxTransactions); // non default constructor
    transaction* search(vector<transaction>& trans, int numTrans, int tID){// search method for searching through array of transactions for project 4...
        for(int i = 0; i < numTrans; i++){
            if(trans.at(i).getTID() == tID){
                return &trans.at(i);
            }
        }
        return nullptr;
    }
    void insertTrans(transaction t); // insert method to insert a new transaction
    
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
    bTransactions.push_back(t);
    currentNumTransactions++;
}
class blockChain{
    int currentNumBlocks; // maintain the size of the list/block chain list
    list<block> bChain; // blockchain as a linked list
public: 
    blockChain(); // default constructor
    blockChain(int tPerB); // non default constructor
    void insertBlocks(block b); // insert method to insert new block into the block chain
   
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
};
blockChain::blockChain(){
    this->currentNumBlocks = 0;
}
blockChain::blockChain(int tPerB){
    this->currentNumBlocks = 0;
}
void blockChain::insertBlocks(block b){
    bChain.push_back(b);
    currentNumBlocks++;
}
int main(){
    
    int numTransactionsPerBlock; // max transactions per block
    cin >> numTransactionsPerBlock;
    cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;
    int totalNumTransactions; // total transactions to be read from the input file
    cin >> totalNumTransactions;
    cout << "Total number of transactions: " << totalNumTransactions << endl;
    
    blockChain* bc = new blockChain(numTransactionsPerBlock); // object of block chain
    block* b = new block(1, numTransactionsPerBlock); // block object used to store transactions
    transaction* trans; // transaction object used to store transaction info
    
    cout << "Adding block #" << b->getBlockNumber() << endl;

    for(int i = 0; i < totalNumTransactions; i++){ // iterate through number of transactions
        //transaction variables
        int tID, fromID, toID, tAmount;
        string timestamp;

        cin >> tID >> fromID >> toID >> tAmount >> timestamp; // read transaction variables from input file
        trans = new transaction(tID, fromID, toID, tAmount, timestamp); // store transaction info into transaction object

        if(b->getCurrentNumTransactions() == b->getMaxNumTransactions()){ // check if capacity has been reached
            bc->insertBlocks(*b); // add block to the blockchain
            b = new block(b->getBlockNumber() + 1, numTransactionsPerBlock); //create a new block with incremented block num
            cout << "Adding block #" << b->getBlockNumber() << endl;
        }
        b->insertTrans(*trans); // insert transaction into block
        cout << "Inserting transaction to block #" << b->getBlockNumber() << endl;
    }

    bc->insertBlocks(*b); // add remaining block to the chain
    cout << "Current number of blocks: " << bc->getCurrentNumBlocks()<< endl;

    for(block _block : bc->getBlockChain()){ // for each block within the block chain, display its info
        cout << "Block Number: " << _block.getBlockNumber() << " -- Number of Transaction: " << _block.getCurrentNumTransactions() << endl;
        for(int i = 0; i < _block.getCurrentNumTransactions(); i++){ // iterate through each block and display transaction info
            _block.getTransactions().at(i).toString(); 
        }
    }

    // delete all dynamically allocated memory 
    delete trans;
    delete bc;
    delete b;
    return 0;
}