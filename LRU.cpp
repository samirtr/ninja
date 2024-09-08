Problem statement
There is a cache that can hold up to ‘N’ elements. Initially, it is empty. There are two types of operations:-

Operation 1: [ 1 ‘U_ID’ ‘VAL’ ] - where 1 represents an insert/update operation is being performed in the cache.

If the element with a particular ‘U_ID’ already exists in cache:
 - Update its mapped value with ‘VAL’. 

If it does not exist and the cache is not full then 
 - Simply insert this element. 

If it does not exist and the cache is already full then 
 - We remove an element and insert this element into the cache. The element to be removed is selected as the least frequently used element.
Note:
  1) The frequency of use of an element is calculated by a number of operations with its ‘U_ID’ performed after it is inserted in the cache.

  2) If multiple elements have the least frequency then we remove the element which was least recently used. 
Operation 2: [ 2 'UID' ] - where 2 represents, mapped value of this 'UID'

If present in cache otherwise return -1.
You have been given ‘M’ operations which you need to perform in the cache. Your task is to return a vector/list that contains the answer of all the operations of type 2 and in the order in which they were asked.

Example:
We perform the following operations on an empty cache which has capacity 2:

When operation 1 2 3 is performed, the element with 'U_ID' 2 and value 3 is inserted in the cache.

When operation 1 2 1 is performed, the element with 'U_ID' 2’s value is updated to 1.  

When operation 2 2 is performed then value of 'U_ID' 2 is returned i.e. 1.

When operation 2 1 is performed then the value of 'U_ID' 1 is to be returned but it is not present in cache therefore -1 is returned.

When operation 1 1 5 is performed, the element with 'U_ID' 1 and value 5 is inserted in the cache. 

When operation 1 6 4 is performed, the cache is full so we need to delete an element.First, we check the number of times each element is used. Element with 'U_ID' 2 is used 3 times (2 times operation of type 1 and 1-time operation of type 1). Element with 'U_ID' 1 is used 1 time (1-time operation of type 1). So element with 'U_ID' 1 is deleted. The element with 'U_ID' 6 and value 4 is inserted in the cache. 
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= T <= 10
1 <= N <= 1000
1 <= M <= 1000
1 <= U_ID <= 10^3
1 <= VAL<= 10^6

Time Limit: 1sec
Sample Input 1:
2
3 3
1 4 1
2 2
2 4    
3 6
1 2 7
1 1 8
1 2 6
2 1
2 5
2 2 
Sample Output 1:
-1 1
8 -1 6
Sample Output 1 Explanation:
Test case1:

Let’s say i’th operation takes place at t=i. Status after each operation is as follows.
1 4 1 - Element with 'U_ID' 4 and value 1 is inserted in the cache.
2 2 - No element with 'U_ID' 2 is present in the cache so -1 is returned.
2 4 - Element with 'U_ID' 4 is present in the cache so its value i.e 1 is returned.

Therefore the answer is -1 1.




Test case 2:

Let’s say i’th operation takes place at t=i. Status after each operation is as follows.
1 2 7 - Element with 'U_ID' 2 and value 7 is inserted in the cache.
1 1 8 - Element with 'U_ID' 1 and value 8 is inserted in the cache.
1 2 6 - Element with 'U_ID' 2 is already present in the cache so value is updated to 6.
2 1 - Element with 'U_ID' 1 is present in the cache so its value i.e 8 is returned. 
2 5 - No element with 'U_ID' 5 is present in cache so -1 is returned.
2 2 - Element with 'U_ID' 2 is present in cache so its value i.e 6 is returned.
Sample Input 2:
2
1 3 
1 1 1
1 3 91
2 1
4 6
1 1 7
1 3 1
1 2 6
2 2
1 2 1
2 2
Sample Output 2:
-1
6 1


Solution:

class LFUCache {
	public:
	  unordered_map<int,pair<int,int>> cache;
	  unordered_map<int,list<int>> freq_map;
	  unordered_map<int,list<int>::iterator> pos_map;
	  int capacity,minFreq;
	  LFUCache(int capacity){
		  this->capacity = capacity;
		  this->minFreq = 0;
	  }
	  void updateFrequency(int U_ID) {
		  int freq = cache[U_ID].second;
		  freq_map[freq].erase(pos_map[U_ID]);
		  if(freq_map[freq].empty() && freq == minFreq){
			  minFreq++;
		  }
		  cache[U_ID].second++;
		  freq++;
		  freq_map[freq].push_back(U_ID);
		  pos_map[U_ID] = --freq_map[freq].end();
	  }
	  int get(int U_ID){
		  if(cache.find(U_ID)==cache.end()){
			  return -1;
		  }
		  updateFrequency(U_ID);
		  return cache[U_ID].first;
	  }
	  void put(int U_ID,int value){
		  if(capacity == 0)return;
		  if(cache.find(U_ID)!=cache.end()){
			  cache[U_ID].first = value;
			  updateFrequency(U_ID);
		  }else {
			  if(cache.size() == capacity) {
				  int evict_U_ID = freq_map[minFreq].front();
				  freq_map[minFreq].pop_front();
				  cache.erase(evict_U_ID);
				  pos_map.erase(evict_U_ID);

			  }
			  cache[U_ID] = {value,1};
			  freq_map[1].push_back(U_ID);
			  pos_map[U_ID] = --freq_map[1].end();
			  minFreq = 1;
		  }
	  }
};

vector<int> findCacheValue(vector<vector<int>> &arr, int m, int n)
{
	// Write Your Code here.
	vector<int> result;
	LFUCache cache(n);
	for(auto &op : arr) {
		if(op[0] == 1){
			int U_ID = op[1], val = op[2];
			cache.put(U_ID,val);
		} else if(op[0] == 2) {
			int U_ID = op[1];
			result.push_back(cache.get(U_ID));
		}
	}
	return result;
}
