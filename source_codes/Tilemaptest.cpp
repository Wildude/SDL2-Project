//g++ -I../src/Include -L../src/Lib -o ../Executables/ Tilemaptest.exe Tilemaptest.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net
//
#include "../Headers/inclusions.hpp"
#include <map>
void testTileDecode(XMLElement* pTileElement){
    int m_width = 20, m_height = 15;
    vector<vector<int>> data;
        string decodedIDs;
        XMLElement* pDataNode;
        for(XMLElement* e = pTileElement->FirstChildElement(); e != 
        NULL; e = e->NextSiblingElement()){
            cout << e->Value() << endl;
            if(e->Value() == string("layer")){
                pDataNode = e->FirstChildElement();
                cout << "Layer name: " << e->Attribute("name") << endl;
            }
        }
        //cout << "Layer idf: " << pDataNode->Attribute("id") << endl;
        for(XMLNode* e = pDataNode->FirstChild(); e != NULL; e = 
        e->NextSibling())
        {
            XMLText* text = e->ToText();
            string t = text->Value();
            string ey;
            for(int i = 0; i < t.size(); i++){
                if(t[i] > 32)ey += t[i];
            }
            cout << t ;
            decodedIDs = base64_decode(ey);
        }
        // uncompress zlib compression
        uLongf numGids = m_width * m_height * sizeof(int);
        vector<unsigned> gids(numGids);
        uncompress((Bytef*)&gids[0], &numGids,(const 
        Bytef*)decodedIDs.c_str(), decodedIDs.size());
        vector<int> layerRow(m_width);
        for(int j = 0; j < m_height; j++)
            data.push_back(layerRow);
        for(int rows = 0; rows < m_height; rows++){
            for(int cols = 0; cols < m_width; cols++){
                data[rows][cols] = gids[rows * m_width + cols];
                cout << " [" << data[rows][cols] << ']';
            }
            cout << endl;
        } 
}
void parseTileset(XMLElement* mapelt, Tileset& tileset){
    const char* buffer;
    //
    buffer = mapelt->Attribute("tilewidth");
    
    tileset.tileWidth = atoi(buffer);
    
    buffer = mapelt->Attribute("width");
    
    tileset.width = atoi(buffer);
    
    buffer = mapelt->Attribute("height");
    
    tileset.height = atoi(buffer);
    
    //
    tileset.tiles.clear();
    //cout << " entering loop for tiles: \n";
    for(XMLElement* e = mapelt->FirstChildElement(); e !=NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("tileset")){
            //cout << " tileset found\n";
            const char* buffer = e->Attribute("source");
            XMLDocument xdoc;
            xdoc.LoadFile(buffer);
            //cout << "loading status: " << xdoc.ErrorName() << endl;
            for(XMLElement* e = xdoc.RootElement()->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
                if(e -> Value() == string("tile")){
                    buffer = e->FirstChildElement()->Attribute("source");
                    tileset.tiles.push_back(buffer);
                }
            }
        }
    }
    /*
    cout << "tileset details: \n";
    cout << " width: " << tileset.tileWidth << endl;
    cout << " width: " << tileset.height << endl;
    cout << " width: " << tileset.width << endl;
    cout << " tiles: \n";
    for(int i = 0; i < tileset.tiles.size(); i++){
        cout << ' ' << tileset.tiles[i] << endl;
    }
    //*/
}
void parseLayerdata(XMLElement* mapelt, vector<vector<vector<int>>>& table_array, const Tileset& tileset){
    table_array.clear();
    for(XMLElement* e = mapelt->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("layer")){
            //cout << " Layer found\n";
            vector<vector<int>> tablei;
            XMLText* text = e->FirstChildElement()->FirstChild()->ToText();
            string t = text->Value();
            string ey;
            for(int i = 0; i < t.size(); i++){
                if(t[i] > 32)ey += t[i];
            }
            string decodedIDs = base64_decode(ey);
            //cout << tileset.width << endl;
            uLongf numGids = tileset.width * tileset.height * sizeof(int);
            vector<unsigned> gids(numGids);
            uncompress((Bytef*)&gids[0], &numGids,(const 
            Bytef*)decodedIDs.c_str(), decodedIDs.size());
            vector<int> layerRow(tileset.width);
            for(int j = 0; j < tileset.height; j++)
                tablei.push_back(layerRow);
            for(int rows = 0; rows < tileset.height; rows++){
                for(int cols = 0; cols < tileset.width; cols++){
                    tablei[rows][cols] = gids[rows * tileset.width + cols];
                //    cout << tablei[rows][cols] << ' ';
                }
              //  cout << endl;
            } 
            //cout << "================================\n";
            table_array.push_back(tablei);
        }
    }
}
void setTileParams(XMLDocument& doc, Tileset& tileset, vector<vector<vector<int>>>& table_array){
    XMLElement* e = doc.RootElement();
    cout << " doc root value: " << e -> Value() << endl;
    parseTileset(e, tileset);
    parseLayerdata(e, table_array, tileset);
}
struct tileData{
    int tileID;
    SDL_FRect rect;
};
int main(int argn, char** args)
{
    XMLDocument doc;
    doc.LoadFile("../Files/XML/StageX.tmx");
    vector<vector<vector<int>>> Layers;
    Tileset tileset;
    setTileParams(doc, tileset, Layers);
    WINDOW win("Tilemaptest");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    float speed = 10;
    weapon wep;
    wep.load("../Images/Weapons/AK 47/AK_47.png", win.getren());
    wep.setmaincenter(Vflt2(9, 6));
    wep.Position = Vflt2(win.getw()/2, win.geth()/2);
    wep.setbool(true);
    wep.magnify(0.3, 0.7);
    SDL_Event event;
    simpledoll man(win.getren());
    man.body[Upper_bod].Position = Vflt2(win.getw()/2, win.geth() * 0.8);
    man.magnify(2);
    Vflt2 vel(0, 0);
    int layers = Layers.size(), rows = Layers[0].size(), columns = Layers[0][0].size();
    map<int, SDL_Texture*> tex_maps;
    for(int i = 0; i < tileset.tiles.size(); i++){
        tex_maps[i] = IMG_LoadTexture(win.getren(), tileset.tiles[i].c_str());
    }
    man.body[Head].image.load("../Images/Characters/head.png");
    man.body[Lower_bod].image.load("../Images/Characters/lower_bod.png");
    man.body[Lower_armL].image.load("../Images/Characters/lower_arm.png");
    man.body[Upper_armL].image.load("../Images/Characters/upper_arm.png");

    man.body[Lower_armR].image.load("../Images/Characters/lower_arm.png");
    man.body[Upper_armR].image.load("../Images/Characters/upper_arm.png");

    man.body[Upper_legL].image.load("../Images/Characters/upper_leg.png");
    man.body[Lower_legL].image.load("../Images/Characters/lower_leg.png");

    man.body[Upper_legR].image.load("../Images/Characters/upper_leg.png");
    man.body[Lower_legR].image.load("../Images/Characters/lower_leg.png");

    man.body[FeetL].image.load("../Images/Characters/Feet.png");
    man.body[HandL].image.load("../Images/Characters/hand.png");

    man.body[FeetR].image.load("../Images/Characters/Feet.png");
    man.body[HandR].image.load("../Images/Characters/hand.png");
    man.body[Upper_bod].image.load("../Images/Characters/upper_bod.png");
    man.queryset();
    
    ofstream file("../Files/logTilesize.txt");
    for(int i = 0; i < layers; i++)
        for(int j = 0; j < Layers[i].size(); j++){
            for(int k = 0; k < Layers[i][j].size(); k++)
                file << ' ' << Layers[i][j][k];
            file << endl;
        }
    //
    wep.magnify(2);
    man.magnify(2);
    cout << layers << ' ' << rows << ' ' << columns << endl;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        //
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){
             man.animate2();
            vel.getx() -= speed ;// * physx::delta;;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){
           man.animate();
            vel.getx() += speed ;// * physx::delta;;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]){
            man.animate2();
            vel.gety() += speed ;// * physx::delta;;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]){
            man.animate();
            vel.gety() -= speed ;// * physx::delta;;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]){
            speed += (speed >= 100 ? 0 : 1);
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]){
            speed -= (speed <= 0 ? 0 : 1);
        }
        if(event.type == SDL_KEYUP){
            vel = Vflt2_0;
            cout << "nothing pressed\n";
        }
        if(vel == Vflt2_0){
           man.stabilize();
        }
        for(int i = 0; i < layers; i++){
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < columns; k++){
                    SDL_FRect* rect = new SDL_FRect({(float)k * tileset.tileWidth - (float)vel.getx(), (float)j * tileset.tileWidth + (float)vel.gety(), (float)tileset.tileWidth, (float)tileset.tileWidth});
                    if(
                        rect->x <= win.getw() &&
                        rect->y <= win.geth() &&
                        rect->x + rect->w > 0 &&
                        rect->y + rect->h > 0 &&
                        Layers[i][j][k] > 0
                    )
                    SDL_RenderCopyF(win.getren(), tex_maps[Layers[i][j][k] - 1], NULL, rect);
                    delete rect;
                }
            }
        }
        wep.set_target(mousepos);
        wep.Position = man.body[HandL].Position;
        wep.aim();
        //wep.draw();
        float width = 0, height = 0;
        ofstream ofs("../Files/Data/LogsMANSIZE.txt");
        for(int i = 0; i < 15; i++){
            ofs << body_list[i] << " size: " << man.body[i].Dimension << endl;
            width += man.body[i].image.getdst().w;
            height += man.body[i].image.getdst().h;
        }
        TXT txt(string("speed = " + to_string(vel.getx()) + " , " + to_string(vel.gety())).c_str(), win.getren(), 15, 0, 0, 0, 255);
        txt.board.set_dstpos(0, 0);
        txt.board.drawC();
        man.drawI();
        win.pst();
        win.clr();
        SDL_Delay(10);
        
    }
    return 0;
}
/*
                        SDL_Texture* texture = IMG_LoadTexture(win.getren(), tileset.tiles[Layers[i][j][k] - 1].c_str());
                        SDL_Rect dst = {k * tileset.tileWidth, j * tileset.tileWidth, tileset.tileWidth, tileset.tileWidth};
                        //cout << dst.x << ' ' << dst.y << ' '  << dst.w << ' '  << dst.h << endl;
                        SDL_RenderCopy(win.getren(), texture, NULL, &dst);
                        SDL_DestroyTexture(texture);
                    */