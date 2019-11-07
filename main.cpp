#include<iostream>
#include<string>
#include"picosha2.h"
#include<random>

using namespace std;

struct Transaction{
    string Id;
    unsigned int timestamp;
    string from;
    string to;
};  

class Block{
    public:
        Block(){
            previousHash = "";
            myHash = "";
        }
        string getPrevHash(){
            return previousHash;
        }
        vector<Transaction> getTransactions(){
            return transactions;
        }
        void addTransaction(Transaction trans);
        string getHash(){
            return myHash;
        }
        string hashBlock(){

        }
    private:
        string previousHash;
        string myHash;
        vector<Transaction> transactions;
};

void Block::

string hashTrans(Transaction trans){
    string completeString = "";
    completeString.append(trans.from);
    completeString.append(trans.to);
    completeString.append(to_string(trans.timestamp));
    return picosha2::hash256_hex_string(completeString);
}

int main(){
    Transaction trans1;
    Block newBlock;
    cout << newBlock.getPrevHash() << endl;
    srand(time(NULL));
    trans1.from = "Christian";
    trans1.to = "John";
    trans1.timestamp = time(NULL);
    trans1.Id = hashTrans(trans1);
    cout << trans1.Id << endl;
}