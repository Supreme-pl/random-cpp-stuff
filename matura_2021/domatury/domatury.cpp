#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

string text = "";
vector<string> lines;
string lastStr = "";
string mostOccuredStr = "";
int occCount, mostOccCount = 0;

int mostOccuredCharCount = 0;
char mostOccuredChar = ' ';

map<char, int> chars;

int main()
{
    string line;
    ifstream file;
    file.open("przyklad.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
    }
    for (string line_ : lines)
    {
        string str = "";
        char str2 = ' ';
        bool nextStr = false;
        for (int i = 0; i < line_.length(); i++)
        {
            if (line_[i] != ' ' && !nextStr)
            {
                str += line_[i];
            }
            else nextStr = true;

            if (nextStr)
            {
                str2 = line_[i];
            }
        }
        if (str == "DOPISZ")
        {
            text += str2;
        }
        else if (str == "USUN" && text.length() != 0)
        {
            text = text.substr(0, text.length() - 1);
        }
        else if (str == "PRZESUN")
        {
            bool firstChanged = false;
            for (int i = 0; i < text.length(); i++)
            {
                if (!firstChanged && text[i] == 'Z')
                {
                    text[i] = 'A';
                    firstChanged = true;
                }
                if (!firstChanged && text[i] == str2)
                {
                    text[i] = text[i] + 1;
                    firstChanged = true;
                }
            }
        }
        else if (str == "ZMIEN")
        {
            text[text.length() - 1] = str2;
        }

        if (lastStr == "")
        {
            lastStr = str;
            mostOccuredStr = str;
            occCount += 1;
        }

        if (lastStr == str)
        {
            mostOccuredStr = str;
            occCount += 1;
        }
        else
        {
            lastStr = str;
            if (occCount > mostOccCount)
                mostOccCount = occCount;
            occCount = 1;
        }

        if (str == "DOPISZ" && chars.find(str2) == chars.end())
        {
            chars.insert(pair<char,int> (str2, 1));
        }
        else if (str == "DOPISZ") {
            auto iterator = chars.find(str2);
            iterator->second += 1;
        }
    }
    for (auto e : chars)
    {
        if (mostOccuredCharCount < e.second)
        {
            mostOccuredChar = e.first;
            mostOccuredCharCount = e.second;
        }
    }
	

    cout << text.length() << endl << mostOccuredStr << endl << mostOccCount << endl << mostOccuredChar << endl << mostOccuredCharCount;

    return 0;

}
