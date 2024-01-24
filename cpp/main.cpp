#include <iostream>
#include <stack>
#include <map>
#include <vector>

using namespace std;

class TweetCounts {
public:
    TweetCounts() {
    }

    void recordTweet(string tweetName, int time) {
        tweetNameSecondsCountMap[tweetName][time]++;
    }

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        int delimiter = this->getChunkSizeByFrequency(freq);
        int size = ceil(static_cast<double>(endTime - startTime + 1) / delimiter);
        vector<int> arr(size, 0);

        map<int, int> secondsCountMap = this->tweetNameSecondsCountMap[tweetName];
        if (secondsCountMap.empty()) {
            return arr;
        }

        auto it = secondsCountMap.lower_bound(startTime);
        auto end = secondsCountMap.upper_bound(endTime);

        for (; it != end; ++it) {
            arr[(it->first - startTime) / delimiter] += it->second;
        }
        return arr;
    }

private:
    unordered_map<string, map<int, int>> tweetNameSecondsCountMap;

    int getChunkSizeByFrequency(string freq) {
        if (freq == "minute") {
            return 60;
        }
        if (freq == "hour") {
            return 3600;
        }
        return 86400;
    }

};

void printVector(vector<int> vector) {
    for (const auto &element: vector) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
    TweetCounts *tweetCounts = new TweetCounts();
    tweetCounts->recordTweet("tweet3", 0);                              // New tweet "tweet3" at time 0
    tweetCounts->recordTweet("tweet3", 60);                             // New tweet "tweet3" at time 60
    tweetCounts->recordTweet("tweet3", 10);                             // New tweet "tweet3" at time 10

    auto res1 = tweetCounts->getTweetCountsPerFrequency("minute", "tweet3", 0,
                                                        59); // return [2]; chunk [0,59] had 2 tweets
    printVector(res1);
    auto res2 = tweetCounts->getTweetCountsPerFrequency("minute", "tweet3", 0,
                                                        60); // return [2,1]; chunk [0,59] had 2 tweets, chunk [60,60] had 1 tweet
    printVector(res2);

    tweetCounts->recordTweet("tweet3", 120);                            // New tweet "tweet3" at time 120

    auto res3 = tweetCounts->getTweetCountsPerFrequency("hour", "tweet3", 0,
                                                        210);  // return [4]; chunk [0,210] had 4 tweets

    printVector(res3);

    return 0;
}


/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */