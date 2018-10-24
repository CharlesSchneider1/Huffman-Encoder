#include <iostream> 
#include <fstream>
#include <string>
#include <cstdlib>

int hashcode(const char* bytes, int len) {
  int hashcode = 0;
	for (int i=0;i<len;i++){
		hashcode=hashcode+bytes[i];
	}
		int randmult = rand() % 10000534544500;
		hashcode=hashcode*randmult;
  return hashcode;
}

int main() {
  int TABLESIZE = 390000;
  int counts[TABLESIZE];
  for (int i = 0; i < TABLESIZE; i++) {
    counts[i] = 0;
  }

  std::ifstream words("words.txt");
  if (!words.is_open()) {
    std::cerr << "Error reading file words.txt" << std::endl;
    return -1;
  }

  std::string word;

  while (std::getline(words, word)) {
    int code = hashcode(word.c_str(), word.length());
    //Compression function is simple modulus operation on table size
    counts[((unsigned int)code) % TABLESIZE]++;
  }

  int max = 0, sum = 0, num_conflicting = 0, unused = 0;
  for (int i = 0; i < TABLESIZE; i++) {
    if (counts[i] > max) {
      max = counts[i];
    }
    if (counts[i] == 0) {
      unused++;
    }
    if (counts[i] > 1) {
      sum += counts[i];
      num_conflicting++;
    }
  }

  std::cout << "Maximum number of conflicts: " << max << std::endl;
  std::cout << "Average number of conflicts: " 
            << float(sum) / num_conflicting << std::endl;
  std::cout << "Number of unused buckets: " << unused << std::endl;
}
