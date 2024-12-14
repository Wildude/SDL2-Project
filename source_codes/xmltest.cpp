//g++ -I../src/Include -L../src/Lib -o ../Executables/xmltest.exe xmltest.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include "../Headers/inclusions.hpp"
int main(int argn, char** args)
{
    cout << " xml test: " << endl;
    XMLDocument doc;
    FILE* fp = fopen("../Files/XML/test2.xml", "rb");
    if(!fp)cout << " error opening file.";
    else cout << " file opened for reading mode.\n";
    if(doc.LoadFile(fp))
    {
        cerr << doc.ErrorName() << "\n";
        return false;
    }
    else cout << " file loaded to doc variable\n";
    // get the root element
    cout << " total children: " << doc.ChildElementCount() << endl;
    XMLElement* pRoot = doc.RootElement();
    // pre declare the states root node
    XMLElement* pStateRoot = 0;
    // get this states root node and assign it to pStateRoot
    for(XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = 
    e->NextSiblingElement())
    {
        cout << e->Value() << endl;
        cout << " Name: " << e->Attribute("Name") << endl;
        cout << " Age: " << e->Attribute("Age") << endl;
        cout << " Sex: " << e->Attribute("Sex") << endl;
    }
    fclose(fp);
    return 0;
}