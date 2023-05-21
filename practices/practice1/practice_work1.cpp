#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Encription
{
private:
    std::vector<int> i_StdandardFib;
    std::vector<int> i_key;

    bool is_standard_fib(std::vector<int> key)
    {
        std::sort(key.begin(), key.end());
        for (int i = 0; i < key.size(); ++i)
        {
            if (i_StdandardFib[i] != key[i])
            {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> SplitWords(std::string message)
    {
        std::vector<std::string> words;
        std::stringstream tmp(message);
        std::string word;
        while (tmp >> word)
        {
            words.push_back(word);
        }
        return words;
    }

public:
    Encription()
    {
        for (int i = 0; i < 30; ++i)
        {
            if (i == 0)
            {
                i_StdandardFib.push_back(1);
            }
            else if (i == 1)
            {
                i_StdandardFib.push_back(2);
            }
            else
            {
                i_StdandardFib.push_back(i_StdandardFib[i - 2] + i_StdandardFib[i - 1]);
            }
        }
    }

    void SetKey(std::vector<int> new_key)
    {
        if (is_standard_fib(new_key) && new_key.size() <= 30)
        {
            i_key = new_key;
        }
        else
        {
            throw std::exception("Wrong key");
        }
    }

    std::vector<int> get_key()
    {
        return i_key;
    }

    std::string encode(std::string message)
    {
        std::vector<std::string> words = SplitWords(message);
        std::stringstream tmp;
        if (words.size() != i_key.size())
        {
            throw std::exception("key and message length mismatch");
        }
        for (int i = 0; i < words.size(); ++i)
        {
            for (int j = 0; j < words.size(); ++j)
            {
                if (i_key[i] == i_StdandardFib[j])
                {
                    if (i != 0)
                    {
                        tmp << " ";
                    }
                    tmp << words[j];
                    break;
                }
            }
        }

        return tmp.str();
    }

    std::string decode(std::string message)
    {
        std::vector<std::string> words = SplitWords(message);
        std::stringstream tmp;
        if (words.size() != i_key.size())
        {
            throw std::exception("key and message length mismatch");
        }
        for (int i = 0; i < words.size(); ++i)
        {
            for (int j = 0; j < words.size(); ++j)
            {
                if (i_key[j] == i_StdandardFib[i])
                {
                    if (i != 0)
                    {
                        tmp << " ";
                    }
                    tmp << words[j];
                    break;
                }
            }
        }

        return tmp.str();
    }
};

int main()
{
    Encription code;
    std::string text = "Hello, it's my message.";
    try
    {
        code.SetKey({ 5, 2, 3, 1 });
        std::cout << code.encode(text) << "\n";
    }
    catch(std::exception error)
    {
        std::cout << error.what();
    }
}