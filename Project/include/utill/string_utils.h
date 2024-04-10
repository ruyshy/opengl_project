#pragma once

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace string_utils
{

    inline vector<string> split(string s, char t)
    {
        vector<string> res;
        while (true)
        {
            auto pos = s.find(t);
            if (pos == -1)
            {
                if (s.size() > 0)
                    res.push_back(s);
                break;
            }
            string tp = s.substr(0, pos);
            if (tp.size() != 0)
                res.push_back(tp);
            s = s.substr(pos + 1, s.size() - pos - 1);
        }
        return res;
    }

    inline string upOneDirectory(const string& originalPath, char slashCharacter)
    {
        bool isTrailingSlash = originalPath.back() == slashCharacter;
        vector<string> subPaths = split(originalPath, slashCharacter);
        string result = "";
        for (size_t i = 0; i < subPaths.size() - 1; i++)
        {
            if (i > 0)
                result += slashCharacter;
            result += subPaths[i];
        }
        if (isTrailingSlash && result.size() > 0)
            result += slashCharacter;

        return result;
    }

    inline string normalizeSlashes(const string& originalPath, char slashCharacter)
    {
        string result = originalPath;
        for (char& c : result)
        {
            if (c == '\\' || c == '/')
                c = slashCharacter;
        }

        return result;
    }

    inline string getDirectoryPath(const string& filePath)
    {
        auto lastSlashIndex = filePath.find_last_of('\\');
        if (lastSlashIndex == string::npos) {
            lastSlashIndex = filePath.find_last_of('/');
        }

        if (lastSlashIndex == string::npos) {
            return "";
        }

        return filePath.substr(0, lastSlashIndex + 1);
    }

    inline string formatStringImpl(const char* s, stringstream& ss)
    {
        ss << s;
        return ss.str();
    }

    template <typename T, typename... Args>
    inline string formatStringImpl(const char* s, stringstream& ss, T arg, const Args&... args)
    {
        string result;
        while (*s != 0)
        {
            if (*s == '{' && *(s + 1) == '}')
            {
                ss << arg;
                result = formatStringImpl(s + 2 * sizeof(char), ss, args...);
                break;
            }
            else ss << *s;
            s++;
        }
        return result;
    }

    template <typename... Args>
    inline string formatString(const string& fmt, const Args&... args)
    {
        stringstream ss;
        return formatStringImpl(fmt.c_str(), ss, args...);
    }
}
#endif // !STRING_UTILS_H_
