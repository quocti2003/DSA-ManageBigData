#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string IN_FILE = "Books_rating.csv";
string TEMP_OUT_FILE = "TEMP_SORTED_FILE";
string OUT_FILE = "MERGE_SORTED";
string TITLE = "Id,Title,Price,User_id,profileName,review/helpfulness,review/score,review/time,review/summary,review/text";

long long halfGB = 805306368;
long long sizeofFile = 2859504349;
long long totalID = 3000000;
//sort string
void quickSort(string* str, int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right;
    string mid = str[(left + right) / 2];
    do
    {
        while (str[i] < mid)
            i++;
        while (str[j] > mid)
            j--;
        if (i <= j)
            swap(str[i++], str[j--]);
    } while (i <= j);
    quickSort(str, left, j);
    quickSort(str, i, right);
}

long long NumofFiles(long long size) {
    long long numberofFiles = (size + halfGB - 1) / halfGB;
    return numberofFiles;
}
//divide file and sort each file
void sortFile(string fileName, string outFileName) {
    long long numberofFiles = NumofFiles(sizeofFile);
    fstream inFile;
    inFile.open(fileName, ios_base::in | ios_base::binary);
    string titleofFiles;
    getline(inFile, titleofFiles);
    for (int i = 0; i < numberofFiles; i++) {
        string* str = new string[totalID];
        int j = 0;
        for (j; j < totalID / numberofFiles; j++)
            getline(inFile, str[j]);
        //get all lines of 1 file
        quickSort(str, 0, j - 1);
        //sort line
        string FileName = outFileName + to_string(i) + ".csv";
        fstream outFile;
        outFile.open(FileName, ios_base::out | ios_base::binary);
        //write into divided file
        for (int k = 0; k < j; k++) {
            outFile << str[k] << endl;
        }
        delete[] str;
        outFile.close();
    }
    inFile.close();
}
//get id from each string and compare to sort 
int CompareId(string str1, string str2)
{
    int i = 0;
    while (str1[i] != ',' && i < str1.length())
        i++;
    string id1 = str1.substr(0, i - 1);
    int j = 0;
    while (str2[j] != ',' && j < str2.length())
        j++;
    string id2 = str2.substr(0, j - 1);
    return id1.compare(id2);
}
//merge 2 file
void MergeFile(string fileName1, string fileName2, string fileoutName)
{
    fstream file_1, file_2, out;
    file_1.open(fileName1, ios::in | ios::binary);
    file_2.open(fileName2, ios::in | ios::binary);
    out.open(fileoutName, ios::out | ios::binary);

    string temp1, temp2;
    getline(file_1, temp1);
    getline(file_2, temp2);

    while (!file_1.eof() || !file_2.eof())
    {
        //write the line of 2 files which has smaller id into the merge file
        //compare until the end of 1 file and write all of the remain file to merge file
        if (CompareId(temp1, temp2) == -1) {
            out << temp1 << endl;
            getline(file_1, temp1);
        }
        else {
            out << temp2 << endl;
            getline(file_2, temp2);
        }
        if (file_2.eof()) {
            out << temp1 << endl;
            getline(file_1, temp1);
        }
        if (file_1.eof()) {
            out << temp2 << endl;
            getline(file_2, temp2);
        }
    }
    file_1.close();
    file_2.close();
    out.close();
}
//merge 2 last files
void MergeFinalFile(string fileName_1, string fileName_2, fstream& out)
{
    fstream file_1, file_2;
    file_1.open(fileName_1, ios::in | ios::binary);
    file_2.open(fileName_2, ios::in | ios::binary);
    string temp1, temp2;
    getline(file_1, temp1);
    getline(file_2, temp2);
    while (!file_1.eof() && !file_2.eof())
    {
        //write the line of 2 files which has smaller id into the merge file
        //compare until the end of 1 file and write all of the remain file to merge file
        if (CompareId(temp1, temp2) == -1) {
            out << temp1 << endl;
            getline(file_1, temp1);
        }
        else {
            out << temp2 << endl;
            getline(file_2, temp2);
        }
        if (file_2.eof()) {
            out << temp1 << endl;
            getline(file_1, temp1);
        }
        if (file_1.eof()) {
            out << temp2 << endl;
            getline(file_2, temp2);
        }
    }

    file_1.close();
    file_2.close();
    out.close();
}
//call to merge all files together
void MergeAllFiles(long long numberofFiles)
{
    fstream* Files = new fstream[numberofFiles];
    fstream out;
    for (int i = 0; i < numberofFiles; i++) {
        string fileName = TEMP_OUT_FILE + to_string(i);
        Files[i].open(fileName, ios_base::in | ios_base::binary);
    }
    string file0 = TEMP_OUT_FILE + to_string(0) + ".csv";
    string file1 = TEMP_OUT_FILE + to_string(1) + ".csv";
    string mergefile = OUT_FILE + to_string(0) + ".csv";
    //merge first 2 files
    MergeFile(file0, file1, mergefile);
    for (int i = 2; i < numberofFiles; i++)
    {
        string Nextmergefile = OUT_FILE + to_string(i) + ".csv";
        string file = TEMP_OUT_FILE + to_string(i) + ".csv";
        if (i != numberofFiles - 1)
        {
            //merge with the next file
            MergeFile(mergefile, file, Nextmergefile);
            mergefile = Nextmergefile;
        }
        else
        {
            out.open(Nextmergefile, ios::out | ios::binary);
            out << TITLE << endl;
            //merge 2 last files
            MergeFinalFile(mergefile, file, out);
        }
    }
    string result = OUT_FILE + to_string(numberofFiles - 1) + ".csv";
    if (rename(result.c_str(), "sorted_books_rating.csv") != 0)
        perror("Failed");
    else
        cout << "Sorting complete!";
    delete[] Files;
    out.close();
}
//remove all files which were created
void RemoveFiles(long long numberofFiles)
{
    for (int i = 0; i <= numberofFiles; i++)
    {
        string tempfile = TEMP_OUT_FILE + to_string(i) + ".csv";
        remove(tempfile.c_str());
    }

    for (int i = 0; i < numberofFiles - 1; i++)
    {
        string mergefile = OUT_FILE + to_string(i) + ".csv";
        remove(mergefile.c_str());
    }
}

int main() {
    long long numberofFiles = NumofFiles(sizeofFile);

    sortFile(IN_FILE, TEMP_OUT_FILE);

    cout << "Start merging sorted files....\n";

    MergeAllFiles(numberofFiles);

    RemoveFiles(numberofFiles);

    return 0;
}
