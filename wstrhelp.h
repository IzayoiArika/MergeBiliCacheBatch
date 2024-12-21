#ifndef __WSTR_HELP
#define __WSTR_HELP

#include <bits/stdc++.h>
#include <stringapiset.h>
using namespace std;

wstring str2wstr(const string& s)
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

string wstr2str(const wstring& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0); 
    char* buf = new char[len];
    WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0); 
    string r(buf);
    delete[] buf;
    return r;
}

ostream& operator<< (ostream& os, const wstring wstr) {
    os << wstr2str(wstr);
    return os;
}

#endif