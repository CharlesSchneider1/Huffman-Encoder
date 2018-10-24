#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include "bitstream.h"
///////////////////////////////////////////////////////////////////////////
//HUFFMAN CLASS HEADER/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
 
class HuffmanTree{
 private:

///////////////////////////////////////////////////////////////////////////
//HUFFNODE CLASS DEFINITION////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
  class Huffnode {
   private:

   public:
    //huffnode constructor.
    Huffnode(char sym, int freq) :
      zero(NULL), one(NULL), parent(NULL), symbol(sym), weight(freq) { }

    //huffnode merge constructor 
    Huffnode(Huffnode* child1, Huffnode* child2) : 
      zero(child1), one(child2), parent(NULL), symbol('\0'), weight(0) {
      if (child1 != NULL) {
        weight += child1->weight;
        child1->parent = this;
      }
      if (child2 != NULL) {
        weight += child2->weight;
        child2->parent = this;
      }
    }
	  
	Huffnode* zero, *one, *parent;
    char symbol;
    float weight;
	  
	void printTree(std::ostream& out){
		if(symbol=='\0'){
			out<<"NODE: "<<weight<<std::endl;
			if(zero){
				zero->printTree(out);
			}
			if(one){
				one->printTree(out);
			}
		}
		else{
			out<<"LEAF: "<<symbol<<" "<<weight<<std::endl;
		}
		
	}
		
		
		

  };
	
	void getEncodingsRecursive(Huffnode* root,std::map<char,std::vector<int> >& theMap, 		std::vector<int> path){
		if(root->zero==NULL && root->one ==NULL){
			theMap[root->symbol]=path;
		}
		else{
			path.push_back(0);
			getEncodingsRecursive(root->zero,theMap,path);
			path[path.size()-1]=1;
			getEncodingsRecursive(root->one,theMap,path);

			return;
		}
	}
	
	
	
 public:
	
	Huffnode* root;
	
    HuffmanTree(const std::map<char, float>& theMap){
	std::priority_queue<std::pair<float, Huffnode*>,std::vector<std::pair<float, Huffnode*> >,std::greater<std::pair<float, Huffnode*> > > myQ;
	for (auto it= theMap.begin();it!=theMap.end();++it){
		Huffnode* treenode= new Huffnode(it->first, it->second);
		myQ.push(std::pair<float, Huffnode*>(treenode->weight,treenode ) );
  	}
    while (myQ.size()>1){
		float freq1 = myQ.top().first;
		Huffnode* min = myQ.top().second;
		myQ.pop();
		float freq2 = myQ.top().first;
		Huffnode* min2 = myQ.top().second;
		myQ.pop();
		Huffnode* mergetree= new Huffnode(min, min2);
		myQ.push(std::pair<float, Huffnode*>(mergetree->weight,mergetree ) );
		root = mergetree;
	}

	}
			
	void writeTree(std::ostream& out) {   //, HuffmanTree theTree
		root->printTree(out);
	}
	
	
	HuffmanTree(std::istream& in){
	std::map<char, float> streamMap;
	while (!in.eof()){
		 std::string kind;
		 in>>kind;
		 in.get();
		 if (kind=="LEAF:"){
			char symbol;
			in>>symbol;
			float weight;
			in>>weight;
			streamMap.insert(std::pair<char, float>(symbol,weight));
		}
		
		else if(kind=="NODE:"){
			std::string restOfLine;
			std::getline(in, restOfLine);
		}
	}
	HuffmanTree* theTree = new HuffmanTree(streamMap);
	root = theTree->root;
	in.clear();
	in.seekg(0, std::ios::beg);
	}
	
	char decode(ibitstream& bits){
		Huffnode* traverse = root;
		while(traverse->zero != NULL && traverse->one != NULL) {
			int result = bits.readBit();
			if  (result == 0){
				traverse=traverse->zero;				
			}
			else if(result == 1){
				traverse=traverse->one;
			}
			
		}
		return traverse->symbol;
	
	}
	
	
	
	
	std::map<char, std::vector<int> > getEncodings() {
		std::map<char, std::vector<int> > theMap;
		std::vector<int> path;
		getEncodingsRecursive(root,theMap,path);
		return theMap;
	}


	
};

