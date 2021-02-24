#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <direct.h>
#include <io.h>
#include <vector>
#include <cstring>

using namespace std;

template <typename T>
void print_vector(vector<T> vct);
void find_files(vector<string>&);

int main() {
    vector <string> files;
    find_files(files);
    print_vector(files);
}

template <typename T>
void print_vector(vector<T> vct) {
    for (auto i = vct.begin(); i != vct.end(); ++i)
    {
        cout << *i << endl;
    }
}

void find_files(vector<string>& files) {
    _finddata_t data;
    char dir[40];
    char path[60] = "../";
    cout << "Enter dir (type 'files'): ";
    cin >> dir;

    strcat(path, dir);
    strcat(path, "/*");
    cout << "Dir path: " << path << endl;
    intptr_t handle = _findfirst(path, &data);
    do
    {
        files.emplace_back(data.name);
    } while (_findnext(handle, &data) == 0);
    _findclose(handle);
}
