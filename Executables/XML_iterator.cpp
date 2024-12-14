#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main(){
    string filepath, rootname, childname;
    vector<string> child_attributes;
    int childnum;
    cout << " XML iterator: " << endl;
    cout << " Enter file name/path (without extension): ";
    cin >> filepath;
    cout << " Enter root element's name: ";
    cin >> rootname;
    cout << " Enter child element's name: ";
    cin >> childname;
    cout << " Enter number of children: ";
    cin >> childnum;
    int iterator = 0;
    string buffer;
    do{
        iterator++;
        cout << " Enter attributes_" << iterator << " (or \"`\" to terminate): ";
        cin >> buffer;
        if(buffer != "`")child_attributes.push_back(buffer);
    }
    while(buffer != "`");
    int size = child_attributes.size();
    vector<string> attribute_values(size);
    for(int i = 0; i < size; i++){
        cout << " Enter attribute values_" << (i + 1) << ": ";
        cin >> attribute_values[i];
    }
    system("cls");
    cout << " creating file\n";
    ofstream file(filepath + string(".xml"), ios::out|ios::trunc);
    if(!file){
        cout << " file creation failed\n";
        return 1;
    }
    //cout << " writing version\n";
    file << "<?xml version = \'1.0\'?>\n" ;
    //cout << " writing root\n";
    file << '<' << rootname << ">\n" ;
    //// cout << " writing children\n";
    for(int i = 0; i < childnum; i++){
        file << "\t <" << childname << (i + 1);
        for(int j = 0; j < size; j++){
            // cout << " writing attributes for child_" << (i + 1) << "\n";
            file << ' ' << child_attributes[j] << " = " << "\"" << attribute_values[j] << "\"";
        }
        // cout << " attributes for child_" << (i + 1) << " finished\n";
        file << " />\n";
    }
    // cout << " writing children finished\n";
    file << "</" << rootname << ">\n" ;
    // cout << " writing root finished\n";
    cout << " file created successfully" << endl;
    file.close();
    return 0;
}