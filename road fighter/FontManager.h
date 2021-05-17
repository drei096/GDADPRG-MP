#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace std;
using namespace sf;

class FontManager
{
public:
    static FontManager* getInstance();
    void loadAll();
    Font* getFont(string);

private:
    // set constructor to private
    FontManager() {};
    // set copy contructor to private
    FontManager(FontManager const&) {};
    // assignment operator is private
    FontManager& operator=(FontManager const&) {};
    static FontManager* sharedInstance;

    void loadFont(string, string);
    std::unordered_map<string, Font*> fontMap;
};



