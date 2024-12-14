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
    vector<string> tiles;
    string name;
};
class Layer
{
    public:
        virtual void render() = 0;
        virtual void update() = 0;
        protected:
        virtual ~Layer() {}
};
class Level
{
    public:
        //Level();
        ~Level() {}
        void update(){
            for(int i = 0; i < layers.size(); i++)
                layers[i]->update();
        }
        void render(){
            for(int i = 0; i < layers.size(); i++)
                layers[i]->render();
        }
        vector<Tileset>* getTilesets(){
            return &tilesets;
        }
        vector<Layer*>* getLayers(){
            return &layers;
        }
        
    private:
        friend class LevelParser;
        Level();
        vector<Tileset> tilesets;
        vector<Layer*> layers;
};
class TileLayer : public Layer
{
    public:
        TileLayer(int tileSize, const vector<Tileset> &tilesets) : m_tileSize(tileSize), m_tilesets(tilesets){
            //m_numColumns = (WinWidth / m_tileSize);
            //m_numRows = (WinHeight / m_tileSize);
        }
        virtual void update(){
            m_position += m_velocity;
        }
        virtual void render(){
            int x, y, x2, y2 = 0;
            x = m_position.getx() / m_tileSize;
            y = m_position.gety() / m_tileSize;
            x2 = int(m_position.getx()) % m_tileSize;
            y2 = int(m_position.gety()) % m_tileSize;
            for(int i = 0; i < m_numRows; i++)
                for(int j = 0; j < m_numColumns; j++)
                {
                    int id = m_tileIDs[i][j + x];
                    if(id == 0)continue;
                    Tileset tileset = getTilesetByID(id);
                    id--;
                    /*
                    board.drawTile(2, 2, 
                    (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize, 
                    m_tileSize, (id - (tileset.firstGridID - 1)) / 
                    tileset.numColumns, (id - (tileset.firstGridID - 1)) % 
                    tileset.numColumns, rend);
                    */
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
        Tileset getTilesetByID(int tileID);
        private:
        int m_numColumns;
        int m_numRows;
        int m_tileSize;
        Vflt2 m_position;
        Vflt2 m_velocity;
        const vector<Tileset> &m_tilesets;
        vector<vector<int>> m_tileIDs;
};
class LevelParser
{
    public:
        Level* parseLevel(const char* levelFile){
            // create a TinyXML document and load the map XML
            XMLDocument levelDocument;
            levelDocument.LoadFile(levelFile);
            // create the level object
            Level* pLevel = new Level();
            // get the root node 
            XMLElement* pRoot = levelDocument.RootElement();
            const char* buffer;
            pRoot->Attribute("tilewidth", buffer);
            m_tileSize = atoi(buffer);
            pRoot->Attribute("width", buffer);
            m_width = atoi(buffer);
            pRoot->Attribute("height", buffer);
            m_height = atoi(buffer);
            // parse the tilesets
            for(XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = 
            e->NextSiblingElement())
                if(e->Value() == string("tileset"))
                    parseTilesets(e, pLevel->getTilesets());
            // parse any object layers
            for(XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = 
            e->NextSiblingElement())
                if(e->Value() == string("layer"))
                    parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
            return pLevel;
        }
        TEXTURE board;
        private:
        void parseTilesets(XMLElement* pTilesetRoot,
        vector<Tileset>* pTilesets, SDL_Renderer* rend = NULL){
            board.setren(rend ? rend : board.getren());
            board.load(pTilesetRoot->FirstChildElement()->Attribute("source"));
            board.queryF();
            // create a tileset object
            Tileset tileset;
            const char* buffer;
            pTilesetRoot->FirstChildElement()->Attribute("width", buffer);
            tileset.width = atoi(buffer);
            pTilesetRoot->FirstChildElement()->Attribute("height", buffer);
            tileset.height= atoi(buffer);
            pTilesetRoot->Attribute("firstgid", buffer);
            tileset.firstGridID= atoi(buffer);
            pTilesetRoot->Attribute("tilewidth", buffer);
            tileset.tileWidth= atoi(buffer);
            pTilesetRoot->Attribute("tileheight", buffer);
            tileset.tileHeight= atoi(buffer);
            pTilesetRoot->Attribute("spacing", buffer);
            tileset.spacing= atoi(buffer);
            pTilesetRoot->Attribute("margin", buffer);
            tileset.margin= atoi(buffer);
            tileset.name = pTilesetRoot->Attribute("name");
            tileset.numColumns = tileset.width / (tileset.tileWidth + 
            tileset.spacing);
            pTilesets->push_back(tileset);
        }
        void parseTileLayer(XMLElement* pTileElement, vector<Layer*> *pLayers, const vector<Tileset>* pTilesets){
            TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
            // tile data
            vector<vector<int>> data;
            string decodedIDs;
            XMLElement* pDataNode;
            for(XMLElement* e = pTileElement->FirstChildElement(); e != 
            NULL; e = e->NextSiblingElement())
                if(e->Value() == string("data"))
                    pDataNode = e;
            for(XMLNode* e = pDataNode->FirstChild(); e != NULL; e = 
            e->NextSibling())
            {
                XMLText* text = e->ToText();
                string t = text->Value();
                cout << " text: " << t << endl;
                decodedIDs = base64_decode(t);
                cout << "decodedIds: " << decodedIDs << endl;
            }
            // uncompress zlib compression
            size_t numGids = m_width * m_height * sizeof(int);
            vector<unsigned> gids(numGids);
            /*
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
            pTileLayer->setTileIDs(data);
            pLayers->push_back(pTileLayer);
            */
        }
        int m_tileSize;
        int m_width;
        int m_height;
};