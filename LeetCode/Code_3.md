# Code_3


## 1.单词接龙（Leetcode 127）

```
// C++
// BFS

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (0 ==beginWord.size()) return 0;
        // 建立映射
        unordered_map<string,vector<string>> allWordMap;
        for (auto word : wordList) {
            string key = word;
            for (int i = 0, size = word.size(); i < size; i++) {
                char c = key[i];
                key[i] = '*'; 
                allWordMap[key].push_back(word);
                key[i] = c;
            }
        }

        // BFS
        queue<pair<string,int>> q;
        q.push(make_pair(beginWord, 1));
        set<string> visitedSet;          // 记录已遍历字符串，避免重复遍历
        visitedSet.insert(beginWord);
        while(!q.empty()) {
            pair<string,int> wordPair = q.front();
            q.pop();
            string word = wordPair.first;
            int level = wordPair.second;
            for (int i = 0, size = word.size(); i < size; i++) {
                char c = word[i];
                word[i] = '*';
                for (auto w : allWordMap[word]) {
                    if (w == endWord) return level + 1;
                    if (visitedSet.find(w) != visitedSet.end()) continue;
                    q.push(make_pair(w, level + 1));
                    visitedSet.insert(w);
                }
                word[i] = c;
            }
        }
        return 0;
    }
};

```

```
// C++
// DBFS

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (0 ==beginWord.size()) return 0;
        
        // 建立映射
        bool hasEndWord = false;
        unordered_map<string,vector<string>> wordMap;
        for (auto word : wordList) {
            if (word == endWord) hasEndWord = true;
            string key = word;
            for (int i = 0, size = word.size(); i < size; i++) {
                char c = key[i];
                key[i] = '*'; 
                wordMap[key].push_back(word);
                key[i] = c;
            }
        }
        if (false == hasEndWord) return 0;

        // DBFS
        queue<pair<string,int>> beginQ;
        beginQ.push(make_pair(beginWord, 1));
        unordered_map<string,int> beginVis;           // 记录 begin 已遍历字符串，避免重复遍历
        beginVis[beginWord] = 1;

        queue<pair<string,int>> endQ;
        endQ.push(make_pair(endWord, 1));
        unordered_map<string,int> endVis;             // 记录 end 已遍历字符串，避免重复遍历
        endVis[endWord] = 1;

        // 两边同时走
        // while(!beginQ.empty() && !endQ.empty()) {
        //     int beginAns = visitWord(beginQ, beginVis, endVis, wordMap);
        //     if (beginAns > -1) return beginAns;
        //     int endAns = visitWord(endQ, endVis, beginVis, wordMap);
        //     if (endAns > -1) return endAns;
        // }

        // 走分支少的一端
        while(!beginQ.empty() && !endQ.empty()) {
            int beginSize = wordMap[beginQ.front().first].size();
            int endSize = wordMap[endQ.front().first].size();
            int ans = (beginSize < endSize) ? visitWord(beginQ, beginVis, endVis, wordMap) : visitWord(endQ, endVis, beginVis, wordMap);
            if (ans > -1) return ans;
        }
        // 如果有一端没验证完，验证另一端
        int ans = -1;
        if (!beginQ.empty()) {
            ans = visitWord(beginQ, beginVis, endVis, wordMap);
        }
        if (!endQ.empty()) {
            ans = visitWord(endQ, endVis, beginVis, wordMap);
        }
        if (ans > -1) return ans;

        return 0;
    }

private:
    int visitWord(queue<pair<string,int>>& q, unordered_map<string,int>& visited, unordered_map<string,int>& otherVis, unordered_map<string,vector<string>>& wordMap) {
        pair<string,int> wordPair = q.front();
        q.pop();
        string word = wordPair.first;
        int level = wordPair.second;
        for (int i = 0, size = word.size(); i < size; i++) {
            char c = word[i];
            word[i] = '*';
            for (auto w : wordMap[word]) {
                if (otherVis.find(w) != otherVis.end()) { 
                    return level + otherVis[w];
                }
                if (visited.find(w) != visited.end()) continue;
                q.push(make_pair(w, level + 1));
                visited[w] = level + 1;
            }
            word[i] = c;
        }
        return -1;
    }
};

```