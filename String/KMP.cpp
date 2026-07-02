#include <bits/stdc++.h>
using namespace std;

vector<int> findPrefixArray(string &s)
{
    vector<int> lps((int)s.size(), 0);
    int pre = 0, suf = 1;
    while (suf < (int)s.size())
    {
        if (s[pre] == s[suf])
        {
            lps[suf] = pre + 1;
            pre++;
            suf++;
        }
        else
        {
            if (pre == 0)
            {
                lps[suf] = 0;
                suf++;
            }
            else
                pre = lps[pre - 1];
        }
    }

    return lps;
}
int main()
{
    string s = "buildingarunningcar";
    string t = "ing";
    vector<int> lps = findPrefixArray(t);
    int i = 0, j = 0;
    while (i < (int)s.size())
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }

        if (j == (int)t.size())
        {
            cout << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < (int)s.size() && s[i] != t[j])
        {
            if (j)
                j = lps[j - 1];
            else
                i++;
        }
    }
}