#ifndef __BILIMERGE_H__
#define __BILIMERGE_H__

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include "wstrhelp.h"

using namespace std;
using namespace std::filesystem;

// 考虑到路径有可能含全角符号，必须使用wstring；此外path默认也是使用wstring存储的
typedef vector<wstring> vwstring;

const path curpath = filesystem::current_path();

bool isInvalidDirectorySymbol(wchar_t);
vwstring getAllSubdirectories(path = curpath);
void mergeBiliCacheBatch(vwstring);
void mergeBiliCache(wstring);
wstring getCachePartTitle(wstring);


bool isInvalidDirectorySymbol(wchar_t wch) {
    switch (wch) {
        case L'\\':
        case L'/':
        case L':':
        case L'*':
        case L'?':
        case L'"':
        case L'>':
        case L'<':
        case L'|':
            return true;
    }
    return false;
}
vwstring getAllSubdirectories(path p) {
    vwstring vwstr;

    for (const auto& entry : directory_iterator(p)) {
        if (entry.is_directory()) {
            vwstr.push_back(entry.path());
        }
    }
    return vwstr;
}
void mergeBiliCacheBatch(vwstring dirs) {
    for (wstring ds : dirs) mergeBiliCache(ds);
}
void mergeBiliCache(wstring ds) {
    for (wstring subds : getAllSubdirectories(ds)) {
        wstring numds = getAllSubdirectories(subds)[0];

        system(wstr2str(
            L"ffmpeg -i \"" + numds + L"\\video.m4s\" -i \"" + numds + L"\\audio.m4s\" -c:v copy -c:a copy \"" + wstring(curpath) + L"\\output\\" + getCachePartTitle(subds) + L".mp4\""
        ).c_str());
    }
}
wstring getCachePartTitle(wstring ds) {
    ifstream ifile(wstr2str(ds + L"\\entry.json"));
    string str;
    getline(ifile, str);
    wstring wstr_raw = str2wstr(str), wstr;

    auto pos = wstr_raw.find(L"\"title\":") + 9;
    auto pos_e = wstr_raw.find(L'\"', pos);
    for (wchar_t wch : wstr_raw.substr(pos, pos_e-pos)) {
        if (isInvalidDirectorySymbol(wch)) wch = L'_';
        wstr.append(1, wch);
    }
    
    wstr.append(1, L' ');

    pos = wstr_raw.find(L"\"part\":") + 8;
    pos_e = wstr_raw.find(L'\"', pos);
    for (wchar_t wch : wstr_raw.substr(pos, pos_e-pos)) {
        if (isInvalidDirectorySymbol(wch)) wch = L'_';
        wstr.append(1, wch);
    }

    return wstr;
}

#endif