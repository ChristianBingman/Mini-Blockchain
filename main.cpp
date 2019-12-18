
#include<iostream>
#include<string>
#include"picosha2.h"
#include<random>
#include<time.h>

using namespace std;

struct Transaction{
    long long Id;
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
        vector<Transaction*> getTransactions(){
            return transactions;
        }
        void addTransaction(string from, string to, long long id = rand() * rand()){
            Transaction* newTrans = new Transaction;
            newTrans->from = from;
            newTrans->to = to;
            newTrans->Id = id;
            newTrans->timestamp = time(NULL);
            transactions.push_back(newTrans);
        }
        string stringifyAndFormatTransactions(){
            string transString = "";
            for (int i = 0; i < transactions.size(); i++){
                transString.append("Id: ");
                transString.append(to_string(transactions[i]->Id));
                transString.append(": ");
                transString.append("\n");
                transString.append("\t");
                transString.append("To: ");
                transString.append(transactions[i]->to);
                transString.append("\n");
                transString.append("\t");
                transString.append("From: ");
                transString.append(transactions[i]->from);
                transString.append("\n");
                transString.append("\t");
                transString.append("Time: ");
                transString.append(to_string(transactions[i]->timestamp));
                transString.append("\n");
            }
            return transString;
        }
        string stringifyTransactions(){
            string transString = "";
            for (int i = 0; i < transactions.size(); i++){
                transString.append(to_string(transactions[i]->Id));
                transString.append(transactions[i]->to);
                transString.append(transactions[i]->from);
                transString.append(to_string(transactions[i]->timestamp));
            }
            return transString;
        }
        string hashBlock(){
            string hashStr = "";
            hashStr.append(stringifyTransactions());
            hashStr.append(previousHash);
            hashStr = picosha2::hash256_hex_string(hashStr);
            myHash = hashStr;
            return hashStr;
        }
    private:
        string previousHash;
        string myHash;
        vector<Transaction*> transactions;
};

int main(){
    Transaction trans1;
    Block newBlock;
    srand(time(NULL));
    newBlock.addTransaction("Christian", "John");
    cout << newBlock.stringifyTransactions() << endl;
    cout << newBlock.hashBlock() << endl;
}