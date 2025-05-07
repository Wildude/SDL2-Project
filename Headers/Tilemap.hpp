ofstream file("../Files/Data/logTileMap.log");
struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    int tilecount;
    vector<Vint2> pos;
    string name, src;
    void display(){
        cout << "Tileset Name: " << name << endl;
        //cout << "First Grid ID: " << firstGridID << endl;
        cout << "Tile Width: " << tileWidth << endl;
        cout << "Tile Height: " << tileHeight << endl;
        //cout << "Spacing: " << spacing << endl;
        //cout << "Margin: " << margin << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Number of Columns: " << numColumns << endl;
        cout << "Tiles: " << src << endl;
        for (const auto& ps : pos) {
            cout << ps << "\n";
        }
        cout << endl;
    }
    void parseTileset(XMLElement* mapelt){
        file << " parsing Tileset:\n";
        const char* buffer;
        //
        buffer = mapelt->Attribute("tilewidth");
        if(!buffer)file << " attribute tilewidth not found\n";
        else {
            tileWidth = atoi(buffer);
            file << " tilewidth: " << tileWidth << endl;
        }
        //
        buffer = mapelt->Attribute("tileheight");
        if(!buffer)file << " attribute tileheight not found\n";
        else{
            tileHeight = atoi(buffer);
            file << " tileheight: " << tileHeight << endl;
        }
        //
        buffer = mapelt->Attribute("name");
        if(!buffer)file << " attribute name not found\n";
        else{
            name = buffer;
            file << " name: " << name << endl;
        }
        //
        buffer = mapelt->Attribute("columns");
        if(!buffer)file << " attribute columns not found\n";
        else{
            numColumns = atoi(buffer);
            file << " columns: " << numColumns << endl;
        }
        //
        buffer = mapelt->Attribute("tilecount");
        if(!buffer)file << " attribute tilecount not found\n";
        else{
            tilecount = atoi(buffer);
            file << " tilecount: " << tilecount << endl;
        }
        file << " entering loop for tilesets: \n";
        for(XMLElement* e = mapelt->FirstChildElement(); e !=NULL; e = e->NextSiblingElement()){
            if(e->Value() == string("image")){
                file << " image atlas found\n";
                buffer = e->Attribute("source");
                if(!buffer)file << " attribute source not found\n";
                else{
                    file << " source: " << buffer << endl;
                    src = buffer;
                }
                //
                buffer = e->Attribute("width");
                if(!buffer)file << " attribute width not found\n";
                else{
                    file << " width: " << buffer << endl;
                    width = atoi(buffer);
                }
                //
                buffer = e->Attribute("height");
                if(!buffer)file << " attribute width not found\n";
                else{
                    file << " width: " << buffer << endl;
                    height = atoi(buffer);
                }
            }
        }
        file << " parsing Tileset finished\n";
        file << " setting UV positions:\n";
        int rows = height / tileHeight, cols = width / tileWidth;
        int size = rows * cols;
        for(int i = 0; i < size; i++){
            Vint2 uv(i % rows, i / cols);
            file << ' ' << i << ' ' << uv << endl;
            pos.push_back(uv);
        }
    }
};
class Layer
{
    public:
        virtual void render(SDL_Renderer*, map<int, SDL_Texture*>&) = 0;
        virtual void Frender(SDL_Renderer*, map<int, SDL_Texture*>&, const SDL_FRect&, const SDL_Point&) = 0;
        virtual void update() = 0;
        virtual void display() = 0;
        protected:
        virtual ~Layer() {}
};
class TileLayer : public Layer
{
    public:
        TileLayer(const TileLayer& layer): m_tileIDs(layer.m_tileIDs), name(layer.name), layerid(layer.layerid), m_tileSize(layer.m_tileSize), m_tilesets(layer.m_tilesets){
            m_numColumns = (640 / m_tileSize);
            m_numRows = (480 / m_tileSize);
        }
        TileLayer(int tileSize, map<int, Tileset*> &tilesets) : m_tileSize(tileSize), m_tilesets(tilesets){
            m_numColumns = (640 / m_tileSize);
            m_numRows = (480 / m_tileSize);
        }
        virtual void update(){

        }
        virtual void render(SDL_Renderer* rend, map<int, SDL_Texture*>& tex_maps){
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
                        tileset.pos[id].getx() * tileset.tileWidth,
                        tileset.pos[id].gety() * tileset.tileHeight,
                        m_tileSize, // width of the tile
                        m_tileSize
                    });
                    SDL_RenderCopyExF(rend, tex_maps[firstgid], &srcrect, &rect, 0, NULL, SDL_FLIP_NONE);
                }
        }
        void Frender(SDL_Renderer* rend, map<int, SDL_Texture*>& texmap, const SDL_FRect& camera, const SDL_Point& mapsize){
            Tileset sampTileset = *m_tilesets[1];
            SDL_Rect range = {
                max((int)(camera.x / sampTileset.tileWidth), 0),
                min((int)(camera.x + camera.w) / sampTileset.tileWidth, mapsize.x - 1),
                max((int)(camera.y / sampTileset.tileHeight), 0),
                min((int)((camera.y + camera.h) / sampTileset.tileHeight), mapsize.y - 1)
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
                            tileset.pos[id].getx() * tileset.tileWidth,
                            tileset.pos[id].gety() * tileset.tileHeight,
                            x != range.y ? tileset.tileWidth : (int)(camera.w - xpos), // width of the tile
                            y != range.h ? tileset.tileHeight : (int)(camera.h - ypos) // height of the tile
                        });
                        // Render the tile if it's within the camera view
                        SDL_RenderCopyExF(rend, texmap[firstgid], &src, &rect, 0, NULL, SDL_FLIP_NONE);
                    }
                }
        }
        void setTileIDs(const vector<vector<int>>& data)
        { 
            m_tileIDs = data; 
        }
        void setTileSize(int tileSize) 
        { 
            m_tileSize = tileSize; 
        }
        int getTilesetByID(int tileID){
            int id = 1;
            while(m_tilesets.find(id) != m_tilesets.end()){
                Tileset tileset = *m_tilesets[id];
                if(tileID >= id && tileID < id + tileset.tilecount)
                return id;
                else id += tileset.tilecount;
            }
            return 0;
        }
        void setid(int id){
            layerid = id;
        }
        void setname(string sname){
            name = sname;
        }
        void display(){
            cout << " Tile layer details:\n";
            cout << "Layer ID: " << layerid << endl;
            cout << "Layer Name: " << name << endl;
            cout << "Tile Size: " << m_tileSize << endl;
            cout << "Number of Columns: " << m_numColumns << endl;
            cout << "Number of Rows: " << m_numRows << endl;
            cout << "Tile IDs: " << endl;
            for (const auto& row : m_tileIDs) {
                for (const auto& id : row) {
                    cout << " " << id;
                }
                cout << endl;
            }
            cout << "Tilesets: " << endl;
            for (const auto& tileset : m_tilesets) {
                cout << "Tileset ID: " << tileset.first << endl;
                tileset.second->display();
            }
        }
        private:
        int layerid;
        string name;
        int m_numColumns;
        int m_numRows;
        int m_tileSize;
        map<int, Tileset*>& m_tilesets;
        vector<vector<int>> m_tileIDs;
};
class Level
{
    public:
        Level() {}
        ~Level() {}
        void update(){
            for(int i = 0; i < layers.size(); i++)
                layers[i]->update();
        }
        void render(SDL_Renderer* rend){
            for(int i = 0; i < layers.size(); i++)
                layers[i]->render(rend, texMap);
        }
        void Frender(SDL_Renderer* rend, const SDL_FRect& camera){
            SDL_Point mapsize = {m_width, m_height};
            for(int i = 0; i < layers.size(); i++)
                layers[i]->Frender(rend, texMap, camera, mapsize);
        }
        vector<Tileset>* getTilesets(){
            return &tilesets;
        }
        vector<Layer*>* getLayers(){
            return &layers;
        }
        void mapTilesets(SDL_Renderer* rend){
            for(Tileset& tileset: tilesets){
                SDL_Texture* texture = IMG_LoadTexture(rend, tileset.src.c_str());
                if(!texture){
                    file << " texture loading ("<< '\"' << tileset.src << "\") error in level: " << SDL_GetError() << endl;
                    texMap[tileset.firstGridID] = NULL;
                }
                else texMap[tileset.firstGridID] = texture;
            }
        }
        void parseLevel(const char* levelFile, SDL_Renderer* rend){
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
                file << " tilesize: " << buffer << endl;
                m_tileSize = atoi(buffer);
            }
            //
            buffer = pRoot->Attribute("width");
            if(!buffer)file << " attribute width not found\n";
            else{
                file << " width: " << buffer << endl;
                m_width = atoi(buffer);    
            }
            //
            buffer = pRoot->Attribute("height");
            if(!buffer)file << " attribute height not found\n";
            else {
                file << " height: " << buffer << endl;
                m_height = atoi(buffer);    
            }
            // parse the tilesets
            parseTilesets(pRoot->FirstChildElement(), getTilesets());
            mapTilesets(rend);
            mapTilesets(*getTilesets());
            // parse any object layers
            parseLayerdata(pRoot->FirstChildElement(), getLayers(), m_width, m_height, m_tileSize, tilesetMap);
        }
        int getwidth() const {
            return m_width;
        }
        int getheight() const {
            return m_height;
        }
        int getMapWidth() const {
            return m_width * m_tileSize;
        }
        int getMapHeight() const {
            return m_height * m_tileSize;
        }
        int gettilesize() const {
            return m_tileSize;
        }
        void display(){
            cout << "Level Details:\n";
            cout << "Width: " << m_width << endl;
            cout << "Height: " << m_height << endl;
            cout << "Tile Size: " << m_tileSize << endl;
            cout << "Mapwidth: " << getMapWidth() << endl;
            cout << "Mapheight: " << getMapHeight() << endl;
            cout << "Layers:\n";
            for (int i = 0; i < layers.size(); i++) {
                layers[i]->display();
            }
        }
        private:
        void mapTilesets(vector<Tileset>& tilesets){
            for(Tileset& tileset: tilesets)
            tilesetMap[tileset.firstGridID] = &tileset;
        }
        void parseLayerdata(XMLElement* mapelt, vector<Layer*>* layers, int width, int height, int tileSize, map<int, Tileset*>& mapTilesets){
            file << " parsing layers\n";
            file << " Entering Layer loop:\n";
            for(XMLElement* e = mapelt; e != NULL; e = e->NextSiblingElement()){
                if(e->Value() == string("layer")){
                    file << " Layer found\n";
                    TileLayer layer(tileSize, mapTilesets);
                    const char* buffer = NULL;
                    //
                    buffer = e->Attribute("id");
                    if(!buffer)file << " attribute id not found\n";
                    else{
                        file << " id: " << buffer << endl;
                        layer.setid(atoi(buffer));
                    }
                    //
                    buffer = e->Attribute("name");
                    if(!buffer)file << " attribute name not found\n";
                    else {
                        layer.setname(buffer);
                        file << " name: " << buffer << endl;
                    }
                    vector<vector<int>> data;
                    XMLText* text = e->FirstChildElement()->FirstChild()->ToText();
                    string t = text->Value();
                    file << " raw text: {\n " << t << "\n }\n";
                    string ey;
                    file << " filtering out whitespace characters...\n";
                    for(int i = 0; i < t.size(); i++){
                        if(t[i] > 32)ey += t[i];
                    }
                    file << " now text: {\n " << ey << "\n }\n";
                    file << " decoding text\n";
                    string decodedIDs = base64_decode(ey);
                    // file << " decodedIDs: {\n " << decodedIDs << "\n }\n";
                    uLongf numGids = width * height * sizeof(int);
                    file << " making numGids = width * height * sizeof(int): " << width 
                    << " * " << height << " * " << sizeof(int) << endl; // << " = " << numGids << endl;
                    file << " uncompressing\n";
                    vector<unsigned> gids(numGids);
                    uncompress((Bytef*)&gids[0], &numGids,(const 
                    Bytef*)decodedIDs.c_str(), decodedIDs.size());
                    vector<int> layerRow(width);
                    for(int j = 0; j < height; j++)
                        data.push_back(layerRow);
                    for(int rows = 0; rows < height; rows++){
                        for(int cols = 0; cols < width; cols++){
                            data[rows][cols] = gids[rows * width + cols];
                            //file << tablei[rows][cols] << ' ';
                        }
                        //file << endl;
                    } 
                    // file << "================================\n";
                    layer.setTileIDs(data);
                    layers->push_back(new TileLayer(layer));
                }
            }
            file << " parsing Layers finished\n";
        }
        void parseTilesets(XMLElement* pTilesetRoot,
        vector<Tileset>* pTilesets){
            file << " parsing tilesets:\n";
            for(XMLElement* e = pTilesetRoot; e != NULL; e = e->NextSiblingElement()){
                if(e->Value() == string("tileset")){
                    file << " tileset found\n";
                    const char* buffer = NULL;
                    Tileset tileset;
                    buffer = e->Attribute("firstgid");
                    if(!buffer)file << " attribute firstgid not found\n";
                    else{
                        tileset.firstGridID = atoi(buffer);
                        file << " firstgid: " << buffer << endl;
                    } 
                    buffer = e->Attribute("source");
                    if(!buffer)file << " attribute source not found\n";
                    else{
                        file << " loading tileset: " << buffer << endl;
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
    private:
        // friend class LevelParser;
        //Level(){}
        vector<Tileset> tilesets;
        vector<Layer*> layers;
        map<int, SDL_Texture*> texMap;
        map<int, Tileset*> tilesetMap;
        int m_tileSize, m_width, m_height;
};
