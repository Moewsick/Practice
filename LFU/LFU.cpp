#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int parent(int i) {
	return (i - 1) / 2;
}

int left(int p) {
	return p * 2 + 1;
}

int right(int p) {
	return p * 2 + 2;
}

class LFUCache {
	vector<pair<int, int>> freqHeap;  // elem is (cache ID, freq)
	int n;  // current size of cache
	unordered_map<int, int> index;  // key is cache ID, val is pos in freqHeap
public:
	LFUCache(int cacheLim) : 
		freqHeap(cacheLim), 
		n(0) {
		index.reserve(cacheLim);
	}
	~LFUCache() {
	}
	void updateCache(int cacheID) {
		unordered_map<int, int>::const_iterator item = index.find(cacheID);
		if (item == index.end()) {
			if (n == freqHeap.size()) {
				index[freqHeap[n - 1].first] = 0;
				index.erase(freqHeap[0].first);
				swap(freqHeap[0], freqHeap[n - 1]);
				n--;
				int j = 0;
				while (left(j) < n) {
					int k = left(j);
					if (right(j) < n && freqHeap[left(j)].second > freqHeap[right(j)].second) {
						k = right(j);
					}
					if (freqHeap[j].second >= freqHeap[k].second) {
						index[freqHeap[j].first] = k;
						index[freqHeap[k].first] = j;
						swap(freqHeap[j], freqHeap[k]);
					}
					j = k;
				}
			}
			freqHeap[n] = {cacheID, 1};
			index[cacheID] = n++;
			int j = n - 1;
			while (j > 0) {
				if (freqHeap[j].second < freqHeap[parent(j)].second) {
					index[freqHeap[j].first] = parent(j);
					index[freqHeap[parent(j)].first] = j;
					swap(freqHeap[j], freqHeap[parent(j)]);
				}
				j = parent(j);
			}
		}
		else {
			int j = item->second;
			freqHeap[j].second++;
			while (left(j) < n) {
				int k = left(j);
				if (right(j) < n && freqHeap[left(j)].second > freqHeap[right(j)].second) {
					k = right(j);
				}
				if (freqHeap[j].second > freqHeap[k].second) {
					index[freqHeap[j].first] = k;
					index[freqHeap[k].first] = j;
					swap(freqHeap[j], freqHeap[k]);
				}
				j = k;
			}
		}
	}
	void printCache() const {
		cout << "Current cache size: " << n << endl;
		cout << "Cache limit: " << freqHeap.size() << endl;
		cout << "Heap: " << endl;
		for (int i = 0; i < n; i++) {
			cout << "ID = " << freqHeap[i].first << ", freq = " << freqHeap[i].second << endl;
		}
		cout << "Index map: " << endl;
		for (const auto& item : index) {
			cout << "ID = " << item.first << ", heap pos = " << item.second << endl;
		}
	}
};

int main() {
	LFUCache cache(5);

	cache.updateCache(1001);
	cache.updateCache(1002);
	cache.updateCache(1003);
	cache.updateCache(1001);
	cache.updateCache(1001);
	cache.updateCache(1003);
	cache.updateCache(1004);

	cache.printCache();

	return 0;
}