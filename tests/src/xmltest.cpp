//g++ -I../src/Include -L../src/Lib -o ../Executables/xmltest.exe xmltest.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
#include <tinyxml2.hpp>
#include <iostream>
#include <fstream>
int main(int argn, char** args)
{
    std::cout << " xml test: " << std::endl;
    XMLDocument doc;
    FILE* fp = fopen("../Files/XML/test2.xml", "rb");
    if(!fp)std::cout << " error opening file.";
    else std::cout << " file opened for reading mode.\n";
    if(doc.LoadFile(fp))
    {
        std::cerr << doc.ErrorName() << "\n";
        return false;
    }
    else std::cout << " file loaded to doc variable\n";
    // get the root element
    std::cout << " total children: " << doc.ChildElementCount() << std::endl;
    XMLElement* pRoot = doc.RootElement();
    // pre declare the states root node
    XMLElement* pStateRoot = 0;
    // get this states root node and assign it to pStateRoot
    for(XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = 
    e->NextSiblingElement())
    {
        std::cout << e->Value() << std::endl;
        std::cout << " Name: " << e->Attribute("Name") << std::endl;
        std::cout << " Age: " << e->Attribute("Age") << std::endl;
        std::cout << " Sex: " << e->Attribute("Sex") << std::endl;
    }
    fclose(fp);
    return 0;
}