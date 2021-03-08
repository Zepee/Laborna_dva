#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <direct.h>
#include <io.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
void print_vector(vector<T>);
void infoout(vector<vector<string>> ,vector<string> &,vector<float>&);
void student_sort(vector<string>&,vector<float>&);
void stependiru(vector<string>&,vector<float>&,vector<string>&);
void vuvid_v_fayl(vector<string>,vector<float>);
string find_files(vector<string>&); // Finds files' names
void collect_data(vector<string>&, vector<vector<string>>&, string); // Collects data about non-contractors

int main() {
    setlocale(LC_ALL, "Rus");
    vector<vector<string>> all_data; //data from all files
    vector <string> files; // Files' names
    float* average_scores;
    string* only_names;
    int not_contractors;
    float min_score;
    string path;

    path = find_files(files);
    print_vector(files);

    collect_data(files, all_data, path);

    not_contractors = all_data.size();

    vector<string> names;
    vector<float> avg_score;
    infoout( all_data,names,avg_score);

    student_sort( names, avg_score);
    vector<string> students_z_stepoyu;

    stependiru( names, avg_score, students_z_stepoyu);
    vuvid_v_fayl( students_z_stepoyu, avg_score);
}

template <typename T>
void print_vector(vector<T> vct) {
    for (auto i = vct.begin(); i != vct.end(); ++i)
    {
        cout << *i << "\n";
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

void collect_data(vector<string>& file_names, vector<vector<string>>& data, string path){
    ifstream file;
    string n_str; // Number of student
    int n; // That number, but integer
    vector<string> temp;
    string log;

    for (auto it = file_names.begin(); it != file_names.end() ; ++it) {

        file.open(path + "/" + *it);

        if (!file.is_open())
        {
            cout << "Failed to open file '" << *it << "' " << endl;
        }

        getline(file, n_str, '\n');
        n = stoi(n_str);

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < 6; j++)
            {
                getline(file, log, ',');
                temp.push_back(log);
            }

            getline(file, log, '\n');

            //temp.push_back(log);
            if (log == "FALSE" || !log[0] == '+')
                data.push_back(temp);

            temp.clear();
        }

        file.close();
    }
}

void infoout(vector<vector<string>> students,vector<string>& names,vector<float>& avg_scrore )
{
    int grades;
    float sum = 0;
    vector<string> temp;
    for(int i=0;i<students.size();i++)
    {
        temp=students[i];
        grades=temp.size()-1;
        for(int j=0;j<temp.size();j++)
        {
            if(j==0)
                names.push_back(temp[j]);
            if(j!=0)
            {
                 stringstream num(temp[j]);
                float n=0;
                num >> n;
                sum+=n;
            }
        }
         sum/=grades;
        avg_scrore.push_back(sum);
        sum=0;
        //cout<<endl;
    }
}

void student_sort(vector<string>& names,vector<float>& avg_score)
{
    for(int i=0;i<avg_score.size();i++)
    {
        for(int j=0;j<avg_score.size()-1-i;j++)
        {
            if(avg_score[j]<avg_score[j+1])
            {
                float temp=avg_score[j];
                avg_score[j]=avg_score[j+1];
                avg_score[j+1]=temp;
                string tempstr= names[j];
                names[j]=names[j+1];
                names[j+1]=tempstr;
            }
        }
    }
}

void stependiru(vector<string>& names,vector<float>& avg_score,vector<string>& students_z_stepoyu)
{
    int number_of_st = names.size()*0.4;

    for(int i=0;i<number_of_st;i++)
        students_z_stepoyu.push_back(names[i]);
}

void vuvid_v_fayl(vector<string> students_z_stepoyu,vector<float> avg_score)
{
    ofstream fout;
    fout.open("../rating.csv", ios_base::out | ios_base::trunc);

    fout<<"Minimal score to get grand :"<<avg_score[int(avg_score.size()*0.4)]<<endl;

    if (!fout.is_open()){
        cout << "Failed to open/create output file!" << endl;
    }else {
        for (int i = 0; i < students_z_stepoyu.size(); i++)
            fout << students_z_stepoyu[i] << "," << avg_score[i] << endl;
    }
    fout.close();
}