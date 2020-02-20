#include <iostream>
#include <string.h>
using namespace std;
int L;
int mark[11][26];
int64_t max_t[11];

struct Node
{
    Node* p;
    Node* next[26];
    int64_t total;
    int level;
    Node()
    {
        p = NULL;
        for (int i = 0; i < 26; ++i)
        {
            next[i] = NULL;
        }
        total = 0;
        level = 0;
    }

    void insert(const string& word)
    {
        char c = word[0];
        int ix = c - 'A';
        if (next[ix] == NULL)
        {
            next[ix] = new Node();
            next[ix]->level = level + 1;
            next[ix]->p = this;
        }
        if (next[ix]->level == L)
        {
            next[ix]->total += 1;
            Node* parent = this;
            while (parent)
            {
                parent->total += 1;
                parent = parent->p;
            }
        }
        else
        {
            string w = word.substr(1, word.length() - 1);
            next[ix]->insert(w);
        }
    }

    string find_word()
    {
        int64_t max_word = max_t[this->level];
        //cout << "cur_level"<< level << " cur num:" << total << " max_word:" << max_word <<endl;
        if (total >= max_word) return "-";
        string res = "-";
        for (int i = 0; i < 26; ++i)
        {
            if (mark[this->level + 1][i] == 0) continue;
            if (next[i] == NULL)
            {
                if (this->level + 1 == L)
                {
                    res = "";
                    res.push_back(char('A' + i));
                    return res;
                }
                string sub = get_string_from(this->level + 2);
                if (sub.length() >= L - (this->level + 2) + 1)
                {
                    res = "";
                    res.push_back(char('A' + i));
                    res += sub;
                    return res;
                }
            }
            string sub = next[i]->find_word();
            if (sub == "-") continue;
            res = "";
            res.push_back(char('A' + i));
            res += sub;
            break;
        }
        return res;
    }

    string get_string_from(int level)
    {
        string res = "";
        for (int i = level; i <= L; ++i)
        {
            for (int j = 0; j < 26; ++j)
            {
                if (mark[i][j])
                {
                    res.push_back(char(j + 'A'));
                    break;
                }
            }
        }
        return res;
    }
};

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
    {
        Node root;
        memset(mark, 0, 11 * 26 * sizeof(int));
        memset(max_t, 0, 11 * sizeof(int64_t));
        int N;
        cin >> N >> L;
        for (int i = 0; i < N; ++i)
        {
            string word;
            cin >> word;
            root.insert(word);
            for (int j = 0; j < word.length(); ++j)
            {
                int ix = word[j] - 'A';
                mark[j + 1][ix] = 1;
            }
        }

        max_t[L] = 1;
        for (int i = L - 1; i >= 0; --i)
        {
            int64_t cur = 0;
            for (int j = 0; j < 26; ++j)
            {
                if (mark[i + 1][j]) cur += 1;
            }
            if (i == L - 1)
            {
                max_t[i] = cur;
            }
            else
            {
                max_t[i] = cur * max_t[i + 1];
            }
        }

        string res = root.find_word();
        printf("Case #%d: %s\n", t, res.c_str());
    }
}
