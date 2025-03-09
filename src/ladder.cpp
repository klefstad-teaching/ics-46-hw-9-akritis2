#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << msg << word1 << " " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int s1_len = str1.length();
    int s2_len = str2.length();

    if(abs(s1_len - s2_len) > d)
        return false;

    int distance = 0;
    int s1_i = 0;
    int s2_i = 0;

    while(s1_i < s1_len && s2_i < s2_len)
    {
        if(str1[s1_i] != str2[s2_i])
        {
            ++distance;

            if(distance > d)
                return false;

            if(s1_len > s2_len) // There was a char deletion from str1 to str2
                ++s1_i; // Skip the char that was deleted
            
            else if(s2_len > s1_len) // There was a char insertion from str1 to str2
                ++s2_i; // Skip the char that was inserted

            else
            {
                ++s1_i;
                ++s2_i;
            }
        }
        else
        {
            ++s1_i;
            ++s2_i;
        }
    }

    distance += abs(s1_len - s1_i) + abs(s2_len - s2_i);

    // Add back in the skipped char(s) that were deleted/inserted
    return distance <= d;
}   

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);   
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for(string word : word_list)
        {
            if(is_adjacent(last_word, word))
            {
                if(visited.find(word) == visited.end())
                {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    
                    if(word == end_word)
                        return new_ladder;

                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    // Empty ladder if no ladder found
    error(begin_word, end_word, "No ladder found for these words. ");
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    fstream in(file_name);

    if (!in)
        throw runtime_error("Can't open input file");

    string word;

    while(in >> word)
        word_list.insert(word);

    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    int ladder_len = ladder.size();

    if(ladder_len == 0)
        cout << "No word ladder found." << endl;

    cout << "Word ladder found: ";
    
    for(int i = 0; i < ladder_len; ++i)
        cout << ladder[i] << ' ';

    cout << endl;

}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}