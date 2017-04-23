#include <string>
#include <unordered_map>
#include "../include/common.h"

// You are given a string, s, and a list of words, words, that are all of the
// same length. Find all starting indices of substring(s) in s that is a
// concatenation of each word in words exactly once and without any intervening
// characters.

// For example, given:
// s: "barfoothefoobarman"
// words: ["foo", "bar"]

// You should return the indices: [0,9].
// (order does not matter).

// Hint: use hashmaps to record word-count expected and word-count seen. code is
// self-explanatory
using namespace std;

typedef unordered_map<string, int> Map;

vector<int> findSubstring(const string& s, vector<string>& words) {
  Map counts;  // word-count map in words
  for (auto&& w : words) {
    counts[w]++;
  }
  vector<int> result;
  int n = s.size();
  int m = words.size();
  int wsize = words[0].size();  // size of a single word in words
  for (int i = 0; i < n - m * wsize + 1; i++) {
    Map seen;
    // check at starting index i
    int j = 0;
    for (; j < m; j++) {
      string word = s.substr(i + j * wsize, wsize);
      // if word is not in words, break and check next index
      if (counts.count(word) == 0)
        break;
      else {
        seen[word]++;
        if (seen[word] > counts[word]) break;
      }
    }
    if (j == m) {
      result.push_back(i);
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  string s = "barfoothefoobarman";
  vector<string> words{"foo", "bar"};
  auto actual = findSubstring(s, words);
  ASSERT(actual[0] == 0 && actual[1] == 9, "mismatch!");
  return 0;
}
