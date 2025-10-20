#pragma once
#include <iostream>
#include <vector>
#include <tinyxml2.hpp>
#include <texture2D.hpp>
#include <map>
//std::ofstream file("../Files/Data/logTileMap.log");
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
    std::vector<SDL_Point> pos;
    std::string name, src;
    void display();
    void parseTileset(XMLElement* mapelt);
};
class Layer
{
    public:
        virtual void render(SDL_Renderer*, std::map<int, SDL_Texture*>&) = 0;
        virtual void Frender(SDL_Renderer*, std::map<int, SDL_Texture*>&, const SDL_FRect&, const SDL_Point&) = 0;
        virtual void update() = 0;
        virtual void display() = 0;
        protected:
        virtual ~Layer() = 0;
};
class TileLayer : public Layer
{
    public:
        TileLayer(const TileLayer& layer);
        TileLayer(int tileSize, std::map<int, Tileset*> &tilesets);
        virtual void update();
        virtual void render(SDL_Renderer* rend, std::map<int, SDL_Texture*>& tex_maps);
        void Frender(SDL_Renderer* rend, std::map<int, SDL_Texture*>& texmap, const SDL_FRect& camera, const SDL_Point& mapsize);
        void setTileIDs(const std::vector<std::vector<int>>& data);
        void setTileSize(int tileSize);
        int getTilesetByID(int tileID);
        void setid(int id);
        void setname(std::string sname);
        void display();
        private:
        int layerid;
        std::string name;
        int m_numColumns;
        int m_numRows;
        int m_tileSize;
        std::map<int, Tileset*>& m_tilesets;
        std::vector<std::vector<int>> m_tileIDs;
};
class Level
{
    public:
        Level();
        ~Level();
        void update();
        void render(SDL_Renderer* rend);
        void Frender(SDL_Renderer* rend, const SDL_FRect& camera);
        std::vector<Tileset>* getTilesets();
        std::vector<Layer*>* getLayers();
        void mapTilesets(SDL_Renderer* rend);
        void parseLevel(const char* levelFile, SDL_Renderer* rend);
        int getwidth() const ;
        int getheight() const ;
        int getMapWidth() const ;
        int getMapHeight() const ;
        int gettilesize() const ;
        void display();
        private:
        void mapTilesets(std::vector<Tileset>& tilesets);
        void parseLayerdata(XMLElement* mapelt, std::vector<Layer*>* layers, int width, int height, int tileSize, std::map<int, Tileset*>& mapTilesets);
        void parseTilesets(XMLElement* pTilesetRoot,
        std::vector<Tileset>* pTilesets);
    private:
        // friend class LevelParser;
        //Level(){}
        std::vector<Tileset> tilesets;
        std::vector<Layer*> layers;
        std::map<int, SDL_Texture*> texMap;
        std::map<int, Tileset*> tilesetMap;
        int m_tileSize, m_width, m_height;
};
