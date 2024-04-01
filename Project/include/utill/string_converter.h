#pragma once

#ifndef STRING_CONVERTER_H_
#define STRING_CONVERTER_H_

class string_utill
{
public:
	static wstring s2ws(const string& s)
    {
        int len;
        int slength = (int)s.length() + 1;
        len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
        wchar_t* buf = new wchar_t[len];
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
        wstring r(buf);
        delete[] buf;
        return r;
    }

	static string Utf8ToMultiByte(string utf8_str)
	{
		string resultString;
		char* pszIn = new char[utf8_str.length() + 1];
		strncpy_s(pszIn, utf8_str.length() + 1, utf8_str.c_str(), utf8_str.length());

		int nLenOfUni = 0, nLenOfANSI = 0;
		wchar_t* uni_wchar = NULL;
		char* pszOut = NULL;

		if ((nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
			return 0;

		uni_wchar = new wchar_t[nLenOfUni + 1];
		memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

		nLenOfUni = MultiByteToWideChar(CP_UTF8, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);

		if ((nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
		{
			delete[] uni_wchar;
			return 0;
		}

		pszOut = new char[nLenOfANSI + 1];
		memset(pszOut, 0x00, sizeof(char) * (nLenOfANSI + 1));

		nLenOfANSI = WideCharToMultiByte(CP_ACP, 0, uni_wchar, nLenOfUni, pszOut, nLenOfANSI, NULL, NULL);
		pszOut[nLenOfANSI] = 0;
		resultString = pszOut;

		delete[] uni_wchar;
		delete[] pszOut;

		return resultString;
	}

	static string MultiByteToUtf8(string multibyte_str)
	{
		char* pszIn = new char[multibyte_str.length() + 1];
		strncpy_s(pszIn, multibyte_str.length() + 1, multibyte_str.c_str(), multibyte_str.length());

		string resultString;

		int nLenOfUni = 0, nLenOfUTF = 0;
		wchar_t* uni_wchar = NULL;
		char* pszOut = NULL;

		if ((nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), NULL, 0)) <= 0)
			return 0;

		uni_wchar = new wchar_t[nLenOfUni + 1];
		memset(uni_wchar, 0x00, sizeof(wchar_t) * (nLenOfUni + 1));

		nLenOfUni = MultiByteToWideChar(CP_ACP, 0, pszIn, (int)strlen(pszIn), uni_wchar, nLenOfUni);

		if ((nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, NULL, 0, NULL, NULL)) <= 0)
		{
			delete[] uni_wchar;
			return 0;
		}

		pszOut = new char[nLenOfUTF + 1];
		memset(pszOut, 0, sizeof(char) * (nLenOfUTF + 1));

		nLenOfUTF = WideCharToMultiByte(CP_UTF8, 0, uni_wchar, nLenOfUni, pszOut, nLenOfUTF, NULL, NULL);
		pszOut[nLenOfUTF] = 0;
		resultString = pszOut;

		delete[] uni_wchar;
		delete[] pszOut;

		return resultString;
	}

	static void string_to_file_save(string path, string text)
	{
		ofstream textFile;
		textFile.open(path);
		textFile.write(text.c_str(), text.size());
		textFile.close();
	}

};

#endif // !STRING_CONVERTER_H_
