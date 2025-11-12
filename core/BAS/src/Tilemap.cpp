#include <Tilemap.hpp>
#include <vector>
#include <zlib/zlib.h>
#include <base64.hpp>
std::ofstream file("../Files/Data/logTileMap.log");
// Tileset
void Tileset::display(){
    std::cout << "Tileset Name: " << name << std::endl;
    //std::cout << "First Grid ID: " << firstGridID << std::endl;
    std::cout << "Tile Width: " << tileWidth << std::endl;
    std::cout << "Tile Height: " << tileHeight << std::endl;
    //std::cout << "Spacing: " << spacing << std::endl;
    //std::cout << "Margin: " << margin << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Number of Columns: " << numColumns << std::endl;
    std::cout << "Tiles: " << src << std::endl;
    for (const auto& ps : pos) {
        std::cout << "(" << ps.x << ", " << ps.y << "\n";
    }
    std::cout << std::endl;
}
void Tileset::parseTileset(XMLElement* mapelt){
    file << " parsing Tileset:\n";
    const char* buffer;
    //
    buffer = mapelt->Attribute("tilewidth");
    if(!buffer)file << " attribute tilewidth not found\n";
    else {
        tileWidth = atoi(buffer);
        file << " tilewidth: " << tileWidth << std::endl;
    }
    //
    buffer = mapelt->Attribute("tileheight");
    if(!buffer)file << " attribute tileheight not found\n";
    else{
        tileHeight = atoi(buffer);
        file << " tileheight: " << tileHeight << std::endl;
    }
    //
    buffer = mapelt->Attribute("name");
    if(!buffer)file << " attribute name not found\n";
    else{
        name = buffer;
        file << " name: " << name << std::endl;
    }
    //
    buffer = mapelt->Attribute("columns");
    if(!buffer)file << " attribute columns not found\n";
    else{
        numColumns = atoi(buffer);
        file << " columns: " << numColumns << std::endl;
    }
    //
    buffer = mapelt->Attribute("tilecount");
    if(!buffer)file << " attribute tilecount not found\n";
    else{
        tilecount = atoi(buffer);
        file << " tilecount: " << tilecount << std::endl;
    }
    file << " entering loop for tilesets: \n";
    for(XMLElement* e = mapelt->FirstChildElement(); e !=NULL; e = e->NextSiblingElement()){
        if(e->Value() == std::string("image")){
            file << " image atlas found\n";
            buffer = e->Attribute("source");
            if(!buffer)file << " attribute source not found\n";
            else{
                file << " source: " << buffer << std::endl;
                src = buffer;
            }
            //
            buffer = e->Attribute("width");
            if(!buffer)file << " attribute width not found\n";
            else{
                file << " width: " << buffer << std::endl;
                width = atoi(buffer);
            }
            //
            buffer = e->Attribute("height");
            if(!buffer)file << " attribute width not found\n";
            else{
                file << " width: " << buffer << std::endl;
                height = atoi(buffer);
            }
        }
    }
    file << " parsing Tileset finished\n";
    file << " setting UV positions:\n";
    int rows = height / tileHeight, cols = width / tileWidth;
    int size = rows * cols;
    for(int i = 0; i < size; i++){
        SDL_Point uv = {i % rows, i / cols};
        file << ' ' << i << ' ' << uv.x << ", " << uv.y << std::endl;
        pos.push_back(uv);
    }
}
// Layer
//virtual void render(SDL_Renderer*, std::map<int, SDL_Texture*>&) = 0;
//virtual void Frender(SDL_Renderer*, std::map<int, SDL_Texture*>&, const SDL_FRect&, const SDL_Point&) = 0;
//virtual void update() = 0;
//virtual void display() = 0;
Layer::~Layer() {}
// TileLayer
TileLayer::TileLayer(const TileLayer& layer): m_tileIDs(layer.m_tileIDs), 
name(layer.name), layerid(layer.layerid), m_tileSize(layer.m_tileSize), m_tilesets(layer.m_tilesets){
    m_numColumns = (640 / m_tileSize);
    m_numRows = (480 / m_tileSize);
}
TileLayer::TileLayer(int tileSize, std::map<int, Tileset*> &tilesets) : m_tileSize(tileSize), m_tilesets(tilesets){
    m_numColumns = (640 / m_tileSize);
    m_numRows = (480 / m_tileSize);
}
/* virtual */ void TileLayer::update(){

}
/* virtual */ void TileLayer::render(SDL_Renderer* rend, std::map<int, SDL_Texture*>& tex_maps){
    for(int i = 0; i < m_numRows; i++)
        for(int j = 0; j < m_numColumns; j++)
        {
            int id = m_tileIDs[i][j];
            if(id <= 0)continue;
            int firstgid = getTilesetByID(id);
            Tileset tileset = *m_tilesets[firstgid];
            id -= (firstgid - 1);
            id--;
            SDL_FRect rect = SDL_FRect({
                (float)(j * m_tileSize), // x position on screen
                (float)(i * m_tileSize), // y position on screen
                (float)m_tileSize, // width of the tile
                (float)m_tileSize // height of the tile
            });
            SDL_Rect srcrect = SDL_Rect({
                tileset.pos[id].x * tileset.tileWidth,
                tileset.pos[id].y * tileset.tileHeight,
                m_tileSize, // width of the tile
                m_tileSize
            });
            SDL_RenderCopyExF(rend, tex_maps[firstgid], &srcrect, &rect, 0, NULL, SDL_FLIP_NONE);
        }
}
void TileLayer::Frender(SDL_Renderer* rend, std::map<int, SDL_Texture*>& texmap, const SDL_FRect& camera, const SDL_Point& mapsize){
    Tileset sampTileset = *m_tilesets[1];
    SDL_Rect range = {
        std::max((int)(camera.x / sampTileset.tileWidth), 0),
        std::min((int)(camera.x + camera.w) / sampTileset.tileWidth, mapsize.x - 1),
        std::max((int)(camera.y / sampTileset.tileHeight), 0),
        std::min((int)((camera.y + camera.h) / sampTileset.tileHeight), mapsize.y - 1)
    };
    // loop over visible tile grid
        for (int x = range.x; x <= range.y; ++x) {
            for (int y = range.w; y <= range.h; ++y) {
                int id = m_tileIDs[y][x];
                if(id <= 0)continue;
                int firstgid = getTilesetByID(id);
                Tileset tileset = *m_tilesets[firstgid];
                id -= (firstgid - 1);
                id--;
                // Calculate the position of the tile
                float xpos = x * (float)tileset.tileWidth - camera.x;
                float ypos = y * (float)tileset.tileHeight - camera.y;
                SDL_FRect rect = SDL_FRect({
                    xpos, // x position on screen
                    ypos, // y position on screen
                    x != range.y ? (float)tileset.tileWidth : (float)(camera.w - xpos), // width of the tile
                    y != range.h ? (float)tileset.tileHeight : (float)(camera.h - ypos) // height of the tile
                });
                SDL_Rect src = SDL_Rect({
                    tileset.pos[id].x * tileset.tileWidth,
                    tileset.pos[id].y * tileset.tileHeight,
                    x != range.y ? tileset.tileWidth : (int)(camera.w - xpos), // width of the tile
                    y != range.h ? tileset.tileHeight : (int)(camera.h - ypos) // height of the tile
                });
                // Render the tile if it's within the camera view
                SDL_RenderCopyExF(rend, texmap[firstgid], &src, &rect, 0, NULL, SDL_FLIP_NONE);
            }
        }
}
void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{ 
    m_tileIDs = data; 
}
void TileLayer::setTileSize(int tileSize) 
{ 
    m_tileSize = tileSize; 
}
int TileLayer::getTilesetByID(int tileID){
    int id = 1;
    while(m_tilesets.find(id) != m_tilesets.end()){
        Tileset tileset = *m_tilesets[id];
        if(tileID >= id && tileID < id + tileset.tilecount)
        return id;
        else id += tileset.tilecount;
    }
    return 0;
}
void TileLayer::setid(int id){
    layerid = id;
}
void TileLayer::setname(std::string sname){
    name = sname;
}
void TileLayer::display(){
    std::cout << " Tile layer details:\n";
    std::cout << "Layer ID: " << layerid << std::endl;
    std::cout << "Layer Name: " << name << std::endl;
    std::cout << "Tile Size: " << m_tileSize << std::endl;
    std::cout << "Number of Columns: " << m_numColumns << std::endl;
    std::cout << "Number of Rows: " << m_numRows << std::endl;
    std::cout << "Tile IDs: " << std::endl;
    for (const auto& row : m_tileIDs) {
        for (const auto& id : row) {
            std::cout << " " << id;
        }
        std::cout << std::endl;
    }
    std::cout << "Tilesets: " << std::endl;
    for (const auto& tileset : m_tilesets) {
        std::cout << "Tileset ID: " << tileset.first << std::endl;
        tileset.second->display();
    }
}
// Level
Level::Level() {}
Level::~Level() {}
void Level::update(){
    for(int i = 0; i < layers.size(); i++)
        layers[i]->update();
}
void Level::render(SDL_Renderer* rend){
    for(int i = 0; i < layers.size(); i++)
        layers[i]->render(rend, texMap);
}
void Level::Frender(SDL_Renderer* rend, const SDL_FRect& camera){
    SDL_Point mapsize = {m_width, m_height};
    for(int i = 0; i < layers.size(); i++)
        layers[i]->Frender(rend, texMap, camera, mapsize);
}
std::vector<Tileset>* Level::getTilesets(){
    return &tilesets;
}
std::vector<Layer*>* Level::getLayers(){
    return &layers;
}
void Level::mapTilesets(SDL_Renderer* rend){
    for(Tileset& tileset: tilesets){
        SDL_Texture* texture = IMG_LoadTexture(rend, tileset.src.c_str());
        if(!texture){
            file << " texture loading ("<< '\"' << tileset.src << "\") error in level: " << SDL_GetError() << std::endl;
            texMap[tileset.firstGridID] = NULL;
        }
        else texMap[tileset.firstGridID] = texture;
    }
}
void Level::parseLevel(const char* levelFile, SDL_Renderer* rend){
    file << " parsing level\n";
    // create a TinyXML document and load the map XML
    XMLDocument levelDocument;
    if(levelDocument.LoadFile(levelFile)){
        file << " loading level failed\n";
        return;
    }
    else file << " level loading success\n";
    // create the level object
    // get the root node 
    XMLElement* pRoot = levelDocument.RootElement();
    const char* buffer;
    //
    buffer = pRoot->Attribute("tilewidth");
    if(!buffer)file << " attribute tileSize not found\n";
    else{
        file << " tilesize: " << buffer << std::endl;
        m_tileSize = atoi(buffer);
    }
    //
    buffer = pRoot->Attribute("width");
    if(!buffer)file << " attribute width not found\n";
    else{
        file << " width: " << buffer << std::endl;
        m_width = atoi(buffer);    
    }
    //
    buffer = pRoot->Attribute("height");
    if(!buffer)file << " attribute height not found\n";
    else {
        file << " height: " << buffer << std::endl;
        m_height = atoi(buffer);    
    }
    // parse the tilesets
    parseTilesets(pRoot->FirstChildElement(), getTilesets());
    mapTilesets(rend);
    mapTilesets(*getTilesets());
    // parse any object layers
    parseLayerdata(pRoot->FirstChildElement(), getLayers(), m_width, m_height, m_tileSize, tilesetMap);
}
int Level::getwidth() const {
    return m_width;
}
int Level::getheight() const {
    return m_height;
}
int Level::getMapWidth() const {
    return m_width * m_tileSize;
}
int Level::getMapHeight() const {
    return m_height * m_tileSize;
}
int Level::gettilesize() const {
    return m_tileSize;
}
void Level::display(){
    std::cout << "Level Details:\n";
    std::cout << "Width: " << m_width << std::endl;
    std::cout << "Height: " << m_height << std::endl;
    std::cout << "Tile Size: " << m_tileSize << std::endl;
    std::cout << "Mapwidth: " << getMapWidth() << std::endl;
    std::cout << "Mapheight: " << getMapHeight() << std::endl;
    std::cout << "Layers:\n";
    for (int i = 0; i < layers.size(); i++) {
        layers[i]->display();
    }
}
void Level::mapTilesets(std::vector<Tileset>& tilesets){
    for(Tileset& tileset: tilesets)
    tilesetMap[tileset.firstGridID] = &tileset;
}
void Level::parseLayerdata(XMLElement* mapelt, std::vector<Layer*>* layers, 
    int width, int height, int tileSize, std::map<int, Tileset*>& mapTilesets){
    file << " parsing layers\n";
    file << " Entering Layer loop:\n";
    for(XMLElement* e = mapelt; e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == std::string("layer")){
            file << " Layer found\n";
            TileLayer layer(tileSize, mapTilesets);
            const char* buffer = NULL;
            //
            buffer = e->Attribute("id");
            if(!buffer)file << " attribute id not found\n";
            else{
                file << " id: " << buffer << std::endl;
                layer.setid(atoi(buffer));
            }
            //
            buffer = e->Attribute("name");
            if(!buffer)file << " attribute name not found\n";
            else {
                layer.setname(buffer);
                file << " name: " << buffer << std::endl;
            }
            std::vector<std::vector<int>> data;
            XMLText* text = e->FirstChildElement()->FirstChild()->ToText();
            std::string t = text->Value();
            file << " raw text: {\n " << t << "\n }\n";
            std::string ey;
            file << " filtering out whitespace characters...\n";
            for(int i = 0; i < t.size(); i++){
                if(t[i] > 32)ey += t[i];
            }
            file << " now text: {\n " << ey << "\n }\n";
            file << " decoding text\n";
            std::string decodedIDs = base64_decode(ey);
            // file << " decodedIDs: {\n " << decodedIDs << "\n }\n";
            unsigned long numGids = width * height * sizeof(int);
            file << " making numGids = width * height * sizeof(int): " << width 
            << " * " << height << " * " << sizeof(int) << std::endl; // << " = " << numGids << std::endl;
            file << " uncompressing\n";
            std::vector<unsigned> gids(numGids);
            uncompress((Bytef*)&gids[0], &numGids,(const 
            Bytef*)decodedIDs.c_str(), decodedIDs.size());
            std::vector<int> layerRow(width);
            for(int j = 0; j < height; j++)
                data.push_back(layerRow);
            for(int rows = 0; rows < height; rows++){
                for(int cols = 0; cols < width; cols++){
                    data[rows][cols] = gids[rows * width + cols];
                    //file << tablei[rows][cols] << ' ';
                }
                //file << std::endl;
            } 
            // file << "================================\n";
            layer.setTileIDs(data);
            layers->push_back(new TileLayer(layer));
        }
    }
    file << " parsing Layers finished\n";
}
void Level::parseTilesets(XMLElement* pTilesetRoot,
std::vector<Tileset>* pTilesets){
    file << " parsing tilesets:\n";
    for(XMLElement* e = pTilesetRoot; e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == std::string("tileset")){
            file << " tileset found\n";
            const char* buffer = NULL;
            Tileset tileset;
            buffer = e->Attribute("firstgid");
            if(!buffer)file << " attribute firstgid not found\n";
            else{
                tileset.firstGridID = atoi(buffer);
                file << " firstgid: " << buffer << std::endl;
            } 
            buffer = e->Attribute("source");
            if(!buffer)file << " attribute source not found\n";
            else{
                file << " loading tileset: " << buffer << std::endl;
                XMLDocument doc;
                if(doc.LoadFile(buffer)){
                    file << " tileset loading error\n";
                }
                else file << " tileset loading success\n";
                tileset.parseTileset(doc.RootElement());
                pTilesets->push_back(tileset);
                file << " tileset pushed\n";
            }            
        }
    }
    file << " parsing tilesets finished\n";
}