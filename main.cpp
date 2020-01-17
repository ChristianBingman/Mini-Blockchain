
#include<iostream>
#include<string>
#include"picosha2.h"
#include<random>
#include<time.h>
#include<math.h>

using namespace std;

struct Transaction{
    long long Id;
    unsigned int timestamp;
    string from;
    string to;
};  

uint32_t decToHex(string hexStr){
    int decLength = hexStr.length();
    uint32_t sum = 0;
    for(int i = 0; i < hexStr.length(); i++){
        switch (hexStr[i])
        {
        case 'a':
            sum += pow(10, decLength);
            break;
        case 'b':
            sum += pow(11, decLength);
            break;
        case 'c':
            sum += pow(12, decLength);
            break;
        case 'd':
            sum += pow(13, decLength);
            break;
        case 'e':
            sum += pow(14, decLength);
            break;
        case 'f':
            sum += pow(15, decLength);
            break;
        default:
            sum += pow(hexStr[i], decLength);
            break;
        }
        decLength--;
    }
    return sum;
}

class Block{
    public:
        Block(){
            previousHash = "";
            myHash = "";
            PoWNonce = 0;
        }
        Block(string previousH){
            previousHash = previousH;
            myHash = "";
            PoWNonce = 0;
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
        string hashWithNonce(){
            string hashStr = "";
            hashStr.append(stringifyTransactions());
            hashStr.append(previousHash);
            hashStr.append(to_string(PoWNonce));
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
        void incPoW(){
            PoWNonce++;
        }
        int getNonce(){
            return PoWNonce;
        }

    private:
        string previousHash;
        string myHash;
        vector<Transaction*> transactions;
        int PoWNonce;
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
        Block* getBlock(int blockIndex, int powLevel){
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
        string doPoW(Block& newBlock, int PoWLevel){
            string hashStr;
            while(true){
                hashStr = newBlock.hashWithNonce();
                uint32_t newHex = decToHex(hashStr);
                newBlock.incPoW();
                if(newHex < PoWLevel){
                    return hashStr;
                }
            }
            return hashStr;
        }
        void addBlock(Block& newBlock, int PoWLevel){
            if(newBlock.getHash() == ""){
                cout << "Please Hash Block before adding!" << endl;
            }else{
                if (blocks.size() != 0)
                {
                    newBlock.setPreviousHash(blocks[blocks.size()-1]->getHash());
                }
                string isPoW = doPoW(newBlock, PoWLevel);
                cout << "Hash: " << isPoW << "\nNonce: " << newBlock.getNonce() << endl;
                if(isPoW != ""){
                    blocks.push_back(&newBlock);
                    if(VerifyChain()){
                        cout << "Block Added Succesfully!" << endl;
                    }else{
                        cout << "Block Added But Chain is Invalid Removing Block..." << endl;
                        blocks.pop_back();
                    }
                }else{
                    cout << "Proof of Work Failed! Block will not be added!" << endl;
                }
                
            }
            
        }
    private:
        vector<Block*>  blocks;
        bool hashIntegrity;
};

int main(){
    int PoWLevel;
    BlockChain newBC;
    srand(time(NULL));
    Block* newBlock = new Block();
    newBlock->addTransaction("Christian", "John");
    newBlock->hashBlock();
    newBC.addBlock(*newBlock, 1000000000);
    newBlock = new Block();
    newBlock->stringifyAndFormatTransactions();
    newBlock->addTransaction("Christian", "Jane");
    newBlock->hashBlock();
    newBC.addBlock(*newBlock, 1000000000);
    cout << newBlock->getPrevHash() << endl;
    return 0;

}