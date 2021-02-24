#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <direct.h>
#include <io.h>
#include <vector>
#include <cstring>

using namespace std;

template <typename T>
void print_vector(vector<T>);
string find_files(vector<string>&); // Finds files' names
void collect_data(vector<string>&, vector<vector<string>>&, string, int&); // Collects data from all files to one vector
float calculate_min_score(); // Calculates min score for CTEIIYXA
void form_results(vector<vector<string>>&, string); // Forms .csv file with 40% happy dudes, who'll get CTEIIYXA

int main() {
    vector<vector<string>> all_data; //data from all files
    vector <string> files; // Files' names
    int students_count = 0;
    float min_score;
    string path;

    path = find_files(files);
    print_vector(files);

}

template <typename T>
void print_vector(vector<T> vct) {
    for (auto i = vct.begin(); i != vct.end(); ++i)
    {
        cout << *i << endl;
    }
}

string find_files(vector<string>& files) {
    string out_path;
    _finddata_t data;
    char dir[40];
    char path[60] = "../";
    cout << "Enter dir (type 'files'): ";
    cin >> dir;

    strcat(path, dir);
    out_path = (const char * )path;
    strcat(path, "/*.csv");

    cout << "Dir path: " << path << endl;
    intptr_t handle = _findfirst(path, &data);
    do
    {
        files.emplace_back(data.name);
    } while (_findnext(handle, &data) == 0);
    _findclose(handle);

    return out_path;
}
