
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
        Block(string previousH){
            previousHash = previousH;
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
        string getHash(){
            return myHash;
        }
        void setPreviousHash(string previousH){
            previousHash = previousH;
        }
    private:
        string previousHash;
        string myHash;
        vector<Transaction*> transactions;
};

class BlockChain{
    public:
        BlockChain(){
            hashIntegrity = true;
        }
        void printChain(){
            for (int i = 0; i < blocks.size(); i++){
                cout << "Block " << i << ":\n\tHash: " << blocks[i]->getHash() << endl;
            }
        }
        Block* getBlock(int blockIndex){
            return blocks[blockIndex];
        }
        bool VerifyChain(){
            for(int i = 0; i < blocks.size(); i++){
                if(i != 0){
                    if(blocks[i-1]->hashBlock() != blocks[i]->getPrevHash()){
                        hashIntegrity = false;
                        return false;
                    }
                }
            }
            return true;
        }
        void addBlock(Block& newBlock){
            if(newBlock.getHash() == ""){
                cout << "Please Hash Block before adding!" << endl;
            }else{
                if (blocks.size() != 0)
                {
                    newBlock.setPreviousHash(blocks[blocks.size()-1]->getHash());
                }
                blocks.push_back(&newBlock);
            }
            if(VerifyChain()){
                cout << "Block Added Succesfully!" << endl;
            }else{
                cout << "Block Added But Chain is Invalid Removing Block..." << endl;
                blocks.pop_back();
            }
        }
    private:
        vector<Block*>  blocks;
        bool hashIntegrity;
};

int main(){
    Transaction trans1;
    Block newBlock;
    BlockChain* newBC = new BlockChain();
    srand(time(NULL));
    newBlock.addTransaction("Christian", "John");
    newBlock.addTransaction("John", "Jane");
    newBlock.hashBlock();
    newBC->addBlock(newBlock);
    Block block2;
    block2.addTransaction("Christian", "Finch");
    block2.addTransaction("Anna", "Finch");
    block2.hashBlock();
    newBlock.addTransaction("Jane", "Chris");
    newBC->addBlock(block2);
    newBC->printChain();
}