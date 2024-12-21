#include "bilimerge.h"

int main() {
    char ch;
    create_directories(wstring(curpath) + L"\\output");
    mergeBiliCacheBatch(
        getAllSubdirectories()
    );
    cout << endl << "All tasks completed. Press ENTER to exit." << endl;
    cin >> noskipws >> ch;
    return 0;
}

