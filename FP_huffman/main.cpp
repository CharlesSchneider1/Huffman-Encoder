/*
Charlie Schneider and Jeffrey Fix
CS270 Final
Huffman Tree
*/


#include "huffmantree.h"
#include <fstream>
#include <string>
#include <iostream>
#include "encode.h"


//CONSTRUCT AND WRITETREE
void test_construct() {
	std::map<char, float> testmap;
	testmap['a']=10;
	testmap['b']=30;
	testmap['c']=50;
	testmap['d']=70;
	HuffmanTree theTree = HuffmanTree(testmap);
	std::cout<<"write file"<<std::endl;
	std::string file;
	std::cin>>file;
	std::ofstream outfile(file.c_str());
	theTree.writeTree(outfile);
}


void test_construct_Huffman() {
	std::ifstream dstream("const.txt");
	HuffmanTree iTree = HuffmanTree(dstream);
	iTree.writeTree(std::cout);
}
	

void test_getEncodings() {
	std::map<char, float> testmap;
	testmap['a']=10;
	testmap['b']=30;
	testmap['c']=50;
	testmap['d']=70;
	HuffmanTree theTree = HuffmanTree(testmap);
	std::map<char, std::vector<int>> emap = theTree.getEncodings();
	for(auto it=emap.begin(); it!=emap.end(); ++it){
		std::vector<int> binNums = it->second;
		for(int i=0;i<binNums.size();i++){
			std::cout<<binNums[i]<<std::endl;
		}
	}
}

	
void test_decode(){
	std::map<char, float> testmap;
	testmap['a']=10;
	testmap['b']=30;
	testmap['c']=50;
	testmap['d']=70;
	HuffmanTree theTree = HuffmanTree(testmap);
	theTree.writeTree(std::cout);
	std::string d = "0";
	istringbitstream streamd(d);
	streamd.setFake(true);
	char dchar= theTree.decode(streamd);
	std::cout<<dchar<<std::endl;
	std::string b = "101";
	istringbitstream streamb(b);
	streamb.setFake(true);
	char bchar= theTree.decode(streamb);
	std::cout<<bchar<<std::endl;
	std::string c = "11";
	istringbitstream streamc(c);
	streamc.setFake(true);
	char cchar= theTree.decode(streamc);
	std::cout<<cchar<<std::endl;
	std::string a = "100";
	istringbitstream streama(a);
	streama.setFake(true);
	char achar= theTree.decode(streama);
	std::cout<<achar<<std::endl;
}

void test_decoder() {
	std::cout<<"write file to save to"<<std::endl;
	std::string file;
	std::cin>>file;
	std::ofstream ofs(file);
//	ofs.setFake(true);
	std::ifstream dstream("encodertest.txt");  // a tree
	HuffmanDecoder decodetest(dstream);   //decode tree
	std::string f = "0110110111011000";    
	istringbitstream stream(f);
	stream.setFake(true);
	decodetest.decodeText(7,stream,ofs);
}


void test_encoder() {
	std::istringstream instream("decoder");
	HuffmanEncoder encodetest(instream);
	std::cout<<"write file"<<std::endl;
	std::string nfile;
	std::cin>>nfile;
	std::ofstream outfile(nfile.c_str());
	encodetest.writeTree(outfile);
}


void test_writeencoded() {
	std::istringstream instream("decoder");
	HuffmanEncoder encodetest(instream);
	std::cout<<"write file"<<std::endl;
	std::string file;
	std::cin>>file;
	ofbitstream ofs(file);
	ofs.setFake(true);
	encodetest.writeEncodedText(ofs);
}


void user_interface() {
	char choice;
	std::cout<<"Would you like to encode(e) or decode(d) a file"<<std::endl;
	std::cin>>choice;
	if  (choice=='e'){
		
		std::cout<<"What string would you like to encode?"<<std::endl;
		std::string encodestr;
		std::cin>>encodestr;
		std::istringstream dstream(encodestr);
		HuffmanEncoder encodetest(dstream);
		std::cout<<"What file would you like to save it to?"<<std::endl;
		std::string file;
		std::cin>>file;
		ofbitstream ofs(file);
		ofs.setFake(true);
		encodetest.writeEncodedText(ofs);

		
		
	}
		
	else if(choice=='d'){
		std::cout<<"To decode, please save the tree you would like to decode as 'decodethis.txt' in the same folder as this application."<<std::endl;
		std::cout<<"Write file to save to"<<std::endl;
		std::string file;
		std::cin>>file;
		std::ofstream ofs(file);
		std::ifstream dstream("decodethis.txt");  // a tree
		HuffmanDecoder decodetest(dstream);   //decode tree
		std::string decodestr;
		std::cout<<"What string would you like to decode?"<<std::endl;
		std::cin>>decodestr;
		istringbitstream stream(decodestr);
		stream.setFake(true);
		decodetest.decodeText(7,stream,ofs);
		
	}

	else{
		std::cout<<"Invalid input"<<std::endl;
		user_interface();
	}
		
}

	

int main(int argc, char** argv) {
	user_interface();
//	test_construct();
//  test_construct_Huffman();
//	test_getEncodings();
//	test_decode();
//	test_decoder();	//must run test_encoder first
//	test_encoder();
//	test_writeencoded();
}



