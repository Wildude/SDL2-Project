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
    doc.LoadFile("../Files/XML/Stage1.tmx");
    vector<vector<vector<int>>> Layers;
    Tileset tileset;
    setTileParams(doc, tileset, Layers);
    WINDOW win("Tilemaptest");
    win.crtB();
    win.pstcol(255, 255, 255, 255);
    SDL_Event event;
    simpledoll man(win.getren());
    man.body[Upper_bod].Position = Vflt2(win.getw()/2, win.geth()/2);
    man.magnify(2);
    Vflt2 vel(0, 0);
    int layers = Layers.size(), rows = Layers[0].size(), columns = Layers[0][0].size();
    map<int, SDL_Texture*> tex_maps;
    //ofstream file("../Files/logTilesize.txt");
    for(int i = 0; i < layers; i++)
        for(int j = 0; j < Layers[i].size(); j++){
            for(int k = 0; k < Layers[i][j].size(); k++);
              //  file << ' ' << Layers[i][j][k];
            //file << endl;
        }
    //
    cout << layers << ' ' << rows << ' ' << columns << endl;
    vector<tileData> drawnTiles;//(Layers.size() * Layers[0].size() * Layers[0][0].size());
    //ofstream ofs("../Files/Data/LogTiles.txt");
    for(int i = Layers.size() - 1; i >= 0; i--){
        for(int j = 0; j < Layers[i].size(); j++){
            for(int k = 0; k < Layers[i][j].size(); k++){
                /*
                drawnTiles[i * Layers[0].size() * Layers[0][0].size() + j * Layers[0][0].size() + k].tileID = Layers[i][j][k] - 1;
                drawnTiles
                [
                    i * Layers[0].size() * Layers[0][0].size() 
                    + j * Layers[0][0].size() + k
                ].rect 
                = 
                {
                    (float)k * tileset.tileWidth, 
                    (float)j * tileset.tileWidth, 
                    (float)tileset.tileWidth, 
                    (float)tileset.tileWidth
                };
                */
                ///*
                static int prevID = Layers[i][j][k] - 1;
                static int count = 0;
                int nowID = Layers[i][j][k] - 1;
                //ofs << "prevID = " << prevID << endl;
                if(nowID == prevID){
                    //ofs << "skipped\n";
                    count++;
                    continue;
                }
                else {
                    tex_maps[prevID] = IMG_LoadTexture(win.getren(), tileset.tiles[prevID].c_str());
                    drawnTiles.push_back(tileData{prevID, {(float)(k - count) * tileset.tileWidth, (float)j * tileset.tileWidth, (float)count * tileset.tileWidth, (float)tileset.tileWidth}});
                    //ofs << "tile changed(k = " << k << ", count = " << count <<" )\n";
                    prevID = nowID;
                    count = 1;
                } 
                //*/               
            }
        }
    }
    /*
    drawnTiles[i * Layers[0].size() * Layers[0][0].size() + j * Layers[0][0].size() + k].tileID = Layers[i][j][k] - 1;
                drawnTiles
                [
                    i * Layers[0].size() * Layers[0][0].size() 
                    + j * Layers[0][0].size() + k
                ].rect 
                = 
                {
                    (float)k * tileset.tileWidth, 
                    (float)j * tileset.tileWidth, 
                    (float)tileset.tileWidth, 
                    (float)tileset.tileWidth
                };
    */
    for(int i = 0; i < drawnTiles.size(); i++){
        if(drawnTiles[i].tileID == 5 || drawnTiles[i].tileID == 4)
        cout << " rect(" << drawnTiles[i].tileID << "): " << drawnTiles[i].rect.x / 32 << "x " << drawnTiles[i].rect.y / 32 << "x " << drawnTiles[i].rect.w / 32 << "x " << drawnTiles[i].rect.h << endl;
    }
    //ofs.close();
    while(event.type != SDL_QUIT){
        SDL_PollEvent(&event);
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE])break;
        //
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]){
             man.animate2();
            vel.getx() -= 10;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]){
           man.animate();
            vel.getx() += 10;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]){
            man.animate2();
            vel.gety() += 10;
        }
        if(SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]){
            man.animate();
            vel.gety() -= 10;
        }
        if(vel == Vflt2_0){
           man.stabilize();
        }
        ///*
        for(int i = 0; i < drawnTiles.size(); i++){
            if(drawnTiles[i].tileID >= 0){
                drawnTiles[i].rect.x -= vel.getx();
                drawnTiles[i].rect.y += vel.gety();
                if
                (
                    drawnTiles[i].rect.x > win.getw() ||
                    drawnTiles[i].rect.x + drawnTiles[i].rect.w < 0 ||
                    drawnTiles[i].rect.y > win.geth() ||
                    drawnTiles[i].rect.y + drawnTiles[i].rect.h < 0
                )
                continue;
                SDL_RenderCopyF(win.getren(), tex_maps[drawnTiles[i].tileID], NULL, &drawnTiles[i].rect);
                //
            }
        }
        //*/
        man.draw();
        win.pst();
        win.clr();
        SDL_Delay(10);
        vel = Vflt2_0;
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