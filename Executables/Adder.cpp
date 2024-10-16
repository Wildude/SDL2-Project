#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ofstream out("../sample_codes/makefile", ios::app);
    cout << " Enter filename (no extension): ";
    string filename;
    cin >> filename;
    string mainpath = "../source_codes/";
    string extension = ".cpp";
    string fullname = mainpath + filename + extension;
    ofstream out2(fullname, ios::out);
    out2 << "//g++ -I../src/Include -L../src/Lib -o ../Executables/ " << filename << ".exe " << filename << ".cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net" << endl;
    out2 << "#include \"../Headers/inclusions.hpp\"\nint main(int argn, char** args)\n{\n}";
    out2.close();
    out << endl;
    out << "g++ -I../src/Include -L../src/Lib -o ../Executables/";
    out << filename << ".exe " << filename << ".cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net";
}