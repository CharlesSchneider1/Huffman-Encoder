#include "bitstream.h"
#include <iostream>
#include <string>

void test_fake_bitstream() {
  ostringbitstream test;
  test.setFake(true);

  std::string s("1100001011001010");
  for (int i = 0; i < s.length(); i++) {
    test.writeBit(s[i] == '1' ? 1 : 0);
  }
  std::cout << "Storing output as 'fake' ASCII bits: " << test.str() << std::endl;
}

void test_compressed_bitstream() {
  ostringbitstream test;

  std::string s("1100001011001010");
  for (int i = 0; i < s.length(); i++) {
    test.writeBit(s[i] == '1' ? 1 : 0);
  }
  
  std::cout << "Raw bits interpreted as ASCII characters: " << test.str() << std::endl;

  std::cout << "Each bit read individually through ibitstream: ";
  istringbitstream test_in(test.str());
  int theBit;
  while ( (theBit = test_in.readBit()) != -1 ) {
    std::cout << theBit;
  }
  std::cout << std::endl;
}

int main() {
  test_fake_bitstream();
  test_compressed_bitstream();
}
