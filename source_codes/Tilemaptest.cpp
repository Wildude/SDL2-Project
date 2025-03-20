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
    //cout << " doc root value: " << e -> Value() << endl;
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
    int mapWidth = tileset.tileWidth * tileset.width;
    WINDOW win("Tilemaptest");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    float speed = 10;
    SDL_Event event;
    TEXTURE man;
    SDL_Surface* surf = SDL_CreateRGBSurface(0, 10, 30, 8, 0, 0, 0, 0);
    SDL_SetSurfaceColorMod(surf, 255, 0, 0);
    man.setren(win.getren());
    man.surfcpy(surf);
    man.queryF();
    man.magnify(2);
    //
    Vflt2 vel(0, 0);
    int layers = Layers.size(), rows = Layers[0].size(), columns = Layers[0][0].size();
    map<int, SDL_Texture*> tex_maps;
    for(int i = 0; i < tileset.tiles.size(); i++){
        tex_maps[i] = IMG_LoadTexture(win.getren(), tileset.tiles[i].c_str());
    }
    ofstream file("../Files/logTilesize.txt");
    for(int i = 0; i < layers; i++)
        for(int j = 0; j < Layers[i].size(); j++){
            for(int k = 0; k < Layers[i][j].size(); k++)
                file << ' ' << Layers[i][j][k];
            file << endl;
        }
    //
    // cout << layers << ' ' << rows << ' ' << columns << endl;
    Vflt2 velrel = Vflt2(0, 0);
    SDL_FRect camera = {0, 0, (float)win.getw(), (float)win.geth()};
    int FrameStarter = 0;
    man.set_cenpos(win.getw()/2, win.geth()/2);
    bool usescale = false;
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vflt2 mousepos(x, y);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        if(event.type != SDL_KEYDOWN){
            int ticksnow = SDL_GetTicks() - FrameStarter;
            if(ticksnow > 100)vel = Vflt2_0;
        }
        //
        else{
            FrameStarter = SDL_GetTicks();
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){
                vel.getx() -= speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){
                vel.getx() += speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]){
                vel.gety() += speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]){
                vel.gety() -= speed * physx::delta;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]){
                speed += (speed >= 100 ? 0 : 1);
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]){
                speed -= (speed <= 0 ? 0 : 1);
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]){
                vel = Vflt2_0;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_MINUS]){
                if(camera.w > win.getw() / 10)camera.w-=5;
                //camera.h--;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_EQUALS]){
                if(camera.w < win.getw() * 3)camera.w+=5;
                //camera.h++;
            }
            if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_BACKSPACE]){
                usescale = !usescale;
            }
        }
        float scalex = camera.w / win.getw();
        float xoff = win.getw() * (1 - scalex) / 2;
        man.getdst().x += vel.getx();
        man.getdst().y -= vel.gety();
        camera.x = (int)(man.get_cenpos().x <= win.getw() / 2 ? 0 : 1) * (man.get_cenpos().x - win.getw()/2);
        camera.x = (man.get_cenpos().x >= (mapWidth - camera.w / 2) ? mapWidth - camera.w : camera.x);
        int tilewidth = tileset.tileWidth / scalex;
        int k1 = (int)(xoff/tileset.tileWidth);
        int playfac = (int)(man.get_cenpos().x / (win.getw() / 2));
        int camfac = (int)(camera.x / win.getw());
        float camoff = camera.x + camera.w/2 >= win.getw()/2 ? xoff : camera.x;
        float cammarg1 = win.getw()/2 - camera.w/2, cammarg2 = win.getw()/2 + camera.w/2;
        float campoints = man.get_cenpos().x < camera.w/2 ? 0 : win.getw()/2 - camera.w/2;
        float camend = man.get_cenpos().x < camera.w/2 ? camera.w : win.getw()/2 + camera.w/2;
        if(man.get_cenpos().x > camera.w/2) camera.x = man.get_cenpos().x - win.getw()/2;
        camera.x = std::max(0.0f, std::min(camera.x, (float)(mapWidth - win.getw()) * (1 / scalex)));
        for(int i = 0; i < layers; i++){
            for(int j = 0; j < rows; j++){
                for(int k = 0; k < columns; k++){
                    SDL_FRect* rect = new SDL_FRect({((float)k * (usescale ? tilewidth : 32) - (float)camera.x) * (1 / scalex), (float)j * tileset.tileWidth, (float)tileset.tileWidth / scalex, (float)tileset.tileWidth});
                    if(
                        rect->x <= camend &&
                        rect->y <= camera.h &&
                        rect->x + rect->w > campoints &&
                        rect->y + rect->h > camera.y &&
                        Layers[i][j][k] > 0
                    )
                    {
                        SDL_RenderCopyF(win.getren(), tex_maps[Layers[i][j][k] - 1], NULL, rect);
                    }
                    delete rect;
                }
            }
        }
        SDL_SetRenderDrawColor(win.getren(), 50, 190, 10, 255); // Set color to red
        SDL_RenderDrawLine(win.getren(), win.getw()/2 * (camfac + 1), 0, win.getw()/2 * (camfac + 1), win.geth());
        float width = 0, height = 0;
        //string stats1 = string("camera(x, y, w, h): (" + to_string(camera.x) + ", " + to_string((int)camera.y) + ", " + to_string((int)camera.w) + ", " + to_string((int)camera.h) + ")");
        //string stats2 = string(" camoff, playfac = " + to_string(camoff) + ", " + to_string(playfac)); 
        string stats3 = "usemag: " + to_string((int)usescale);
        string stats4 = "speed: " + to_string(speed);
        SDL_Color red = {255, 0, 0, 255};
        FONT font(DEF_FONT, 20);
        TextList list;
        list.setxpos(0);
        //list.add(stats3);
        //list.add(stats4);
        //list.add(string("pos: " + to_string(man.get_cenpos().x) + ", " + to_string(man.get_cenpos().y)));
        //list.add(string("off(x): " + to_string(xoff)));
        list.draw(win.getren(), 1);
        SDL_Rect cam = {(int)camera.x, (int)camera.y, (int)camera.w, (int)camera.h};
        //SDL_RenderDrawRect(win.getren(), &cam);
        man.drawOF(&camera, NULL, 1 / scalex);
        win.pst();
        win.clr();
        SDL_Delay(10);
    }
    return 0;
}