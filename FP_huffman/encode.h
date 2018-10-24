#include <fstream>


class HuffmanEncoder{
  private:
	HuffmanTree* decodetree;
	std::istream& stream;
  public:
	HuffmanEncoder(std::istream& input) : decodetree(NULL), stream(input){
		std::map<char, float> eMap;
		char f;
		while (!stream.eof()){
			stream.get(f);
			if (!stream.eof()){
				eMap[f]+=1;
			}
		}
		decodetree = new HuffmanTree(eMap);
		input.clear();
		input.seekg(0, std::ios::beg);
		
	}	
	int writeEncodedText(obitstream& writebits){
		std::map<char, std::vector<int> >theMap = decodetree->getEncodings();
		char f;
		stream.get(f);
		while(!stream.eof()){
				for(int i=0;i<(theMap[f].size());i++){
					writebits.writeBit(theMap[f][i]);
				}	
						stream.get(f);
		} 
	}
	

	void writeTree(std::ostream& out){
		decodetree->writeTree(out);
	}
	
};


class HuffmanDecoder{
	private:
		HuffmanTree* decodetree;
	public:
		HuffmanDecoder(std::istream& input) {
			decodetree = new HuffmanTree(input);
		}
	
		void decodeText(int numchars, ibitstream& ibits, std::ostream& out) {
			char f;
			for(int i=0;i<numchars;i++){
				f = decodetree->decode(ibits);
				out<<f;
			}
		}	
		void writeTree(std::ostream& out){
			decodetree->writeTree(out);
		}

};

