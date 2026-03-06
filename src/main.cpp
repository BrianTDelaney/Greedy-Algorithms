#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

// TODO: Insert FIFO declaration
// TODO: Insert LRU declaration
int optff(int k, vector<int> &requests);

int fifo(int k, vector<int> requests) {
    deque<int> cache;
    int misses = 0;
    for (int request : requests) {
        if (find(cache.begin(), cache.end(), request) == cache.end()) {
            misses++;
            if (cache.size() == k) {
                cache.pop_front();
            }
            cache.push_back(request);
        }
    }
    return misses;
}

int lru(int k, vector<int> requests) {
    deque<int> cache;
    int misses = 0;
    for (int request : requests) {
        auto it = find(cache.begin(), cache.end(), request);
        if (it == cache.end()) {
            misses++;
            if (cache.size() == k) {
                cache.pop_front();
            }
            cache.push_back(request);
        }
        else {
            cache.erase(it);
            cache.push_back(request);
        }
    }
    return misses;
}

int main() {

    int k;
    int m;
    cin >> k >> m;

    // cout << "k=" << k << " m=" << m << endl; // debugging

    vector<int> requests; 
    // NOTE: Initialization as a finite size led to issues trailing 0 in requests 
    // and an incorrect number of misses (added extra miss because 0 shouldn't be a request)
    int req;

    for (int i = 0; i < m; i++) {
        cin >> req;
        requests.push_back(req);
    }
    // cout << "size: " << requests.size() << endl; // debugging

    // // debugging
    // for (int i = 0; i < requests.size(); i++) {
    //     cout << requests[i] << " ";
    // }
    // cout << endl;

    cout << "FIFO misses: " << fifo(k, requests) << endl
    << "LRU misses: " << lru(k, requests) << endl
    << "OPTFF misses: " << optff(k, requests) << endl;

    return 0;
}



// TODO: Insert FIFO definition

// TODO: Insert LRU definition

int optff(int k, vector<int> &requests) {
    // Parameters:
        // k: cache capacity
        // requests: reference to request sequence array

    // Return:
        // misses: integer value of the number of misses

    vector<int> cache;
    int misses = 0;
    
    // iterate through request array
    for (int i = 0; i < requests.size(); i++) {
        int req = requests[i];

        // hit
        if (find(cache.begin(), cache.end(), req) !=cache.end()) {
            continue;
        }

        misses++;

        if (cache.size() < k) { // add req to cache
            cache.push_back(req);
            continue;
        }

        // Farthest-in-Future Eviction Policy
        int farthest = -1;
        int evict_idx = -1;

        // iterate through each element in cache
        // determine which element is reused furthest in future and evict it
        for (int j = 0; j < cache.size(); j++) {
            int item = cache[j];
            int next_use = -1;

            // see when j is next called in request sequence
            for (int t = i+1; t < requests.size(); t++) {
                if (requests[t] == item) {
                    next_use = t;
                    break;
                }
            }

            if (next_use == -1) { // never used again
                evict_idx = j;
                break;
            }

            if (next_use > farthest) {
                farthest = next_use;
                evict_idx = j;
            }
        }

        cache[evict_idx] = req;
    }


    return misses;
}
