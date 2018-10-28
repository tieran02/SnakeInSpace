#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>


class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    //Destroy and clear all resources
    void DestroyResources();
    //Add a texture to the the texture map
    void AddTexture(std::string name);
    //Find and return a texture pointer from the map
    sf::Texture* GetTexture(std::string name);

    //Add a font to the the font map
    void AddFont(std::string name);
    //Find and return a font pointer from the map
    sf::Font* GetFont(std::string name);

    //Resource maps to hold the resources
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;
};

#endif // RESOURCEMANAGER_HPP
