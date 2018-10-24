#ifndef CS270_HASHTABLE
#define CS270_HASHTABLE

#include <string>
#include <list>
#include <utility>
#include <vector>
#include <exception>
#include <iostream>


int hashCode(const char* bytes, int len) {
  int hash = 0;
  for (int i=0;i<len;i++){
	  hash=hash+bytes[i];
	  hash=hash*bytes[i];
  }
   return hash;
}

template<class K>
int hashCode(const K& key) {
  //Convert any object into an array of "characters"
  const char* bytes = reinterpret_cast<const char*>(&key);
  int size = sizeof(K);
  return hashCode(bytes, size);
}

template<class K, class V>
class HashTable {
 public:
  typedef std::pair<K, V> Entry;
  typedef const std::pair<K, V> ConstEntry;
  typedef std::pair<K, V>* EntryPtr;

 private:
  std::vector< std::list<Entry> > theTable;
  int _size;

  void resize() {
	//for each entry in the original table
    //hash that entry into the new table
    //Do we need to grow the array?
    if (theTable.size() > _size) {
      //Nope
      return;
    } else {
      _size = 0;
      std::vector< std::list<Entry> > oldTable = theTable;
      theTable.clear();
      theTable.resize(oldTable.size()*2);
	  for (int i=0;i<oldTable.size();i++){
		    for (auto it=  oldTable[i].begin();it!= oldTable[i].end();++it){
		     this->insert(it->first,it->second);
	
				
		    }
	  }
	  
    }
  }

  //Return a valid iterator if this list contains an entry matching the given key
  //Return an invalid iterator (bucket.end()) otherwise
  //for each entry in bucket
  //  if entry key matches given key return that entry
  //Otherwise return invalid entry
  typename std::list<Entry>::iterator 
  find_in_bucket(std::list<Entry>& bucket, const K& key) {
	for (auto it= bucket.begin();it!=bucket.end();++it){
		if (key==(*it).first){ 
			return it;
		}     
	}
    return bucket.end();
  }

 public:
  //Interfaces
  //void insert(ConstEntry e);
  HashTable() : theTable(3), _size(0) { };


  int compress(int hashcode) {
    return hashcode % theTable.size();
  }

  V& find(const K& key) {
	//call hashcode which converts key to int; 
    //Return the associated value if found, or throw an exception if not
	 int bucketindex = compress(hashCode(key));
	  auto it = find_in_bucket(theTable[bucketindex],key);
	  if (it!=theTable[bucketindex].end()){
	  	  if (key==(*it).first){
		  
	  	  return (*it).second;
	      }
	  }


    throw std::exception();
  }

  void insert(const K& key, const V& value) {
	//If an entry with this key already exists, replace the value
    //otherwise, create a new entry
	 int bucketindex=compress(hashCode(key));
	 auto it = find_in_bucket(theTable[bucketindex],key);
	  if (it!=theTable[bucketindex].end()){
		 if  (key==(*it).first){ 
			 (*it).second=value;
		 }
	  }
	else{
		 
	     theTable[bucketindex].push_back(Entry (key,value));
		resize();
		_size++;
	}
  }
	
	   
       
	   
	 

  void remove(const K& key) { 
	 int bucketindex=compress(hashCode(key));
	 auto it = find_in_bucket(theTable[bucketindex],key);
	 if (key==(*it).first){
	    theTable[bucketindex].erase(it);
	 }
    //Find and remove the entry for this key, if it exists
  }

  int size() const {
    return _size;
  }
  bool isEmpty() const { return size() == 0; };

};

/*
 * Fancy stuff!  Want a hash code that specifically works for one type of key?
 * You can totally do that!
 */

/*
template<>
int hashCode(const int& key) {
  std::cout << "Using specialized int hashcode";
  return key;
}

template<>
int hashCode(const std::string& key) {
  return hashCode(key.c_str(), key.length());
}
*/


#endif //CS270_HASHTABLE
