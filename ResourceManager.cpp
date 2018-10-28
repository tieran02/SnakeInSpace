#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager()
{
    std::cout << "Resource Manager constructed\n";
}

ResourceManager::~ResourceManager()
{
    std::cout << "Resource Manager destructed\n";
}
void ResourceManager::DestroyResources()
{
    std::cout << "Clearing all resources in resource manager.\n";

    m_textures.clear();
    m_fonts.clear();
}

void ResourceManager::AddTexture(std::string name)
{
    //check if texture already exist and if it does return out of this function
    if(m_textures.find(name) != m_textures.end())
    {
        //std::cout << "Texture: " << name << " already exists (using cached copy)\n";
        return;
    }

    //load texture from file
    sf::Texture texture;
    //check if texture loads successfully and if not return
    if(!texture.loadFromFile("resources/textures/" + name))
    {
        std::cout << "Couldn't load " << name << " texture\n";
        return;
    }
    //add new texture to the map
    m_textures.insert(std::make_pair(name, texture));
}

sf::Texture* ResourceManager::GetTexture(std::string name)
{
    //find texture in map and return it
    if(m_textures.find(name) != m_textures.end())
    {
        return &m_textures[name];
    }
    //returns nullptr if the texture doesn't exist
    std::cout << "Texture " << name << " doesn't exist!\n";
    return nullptr;
}

void ResourceManager::AddFont(std::string name)
{
    //check if font already exist and if it does return out of this function
    if(m_fonts.find(name) != m_fonts.end())
    {
        //std::cout << "Font: " << name << " already exists (using cached copy)\n";
        return;
    }
    //load font from file
    sf::Font font;
    //check if font loads successfully and if not return
    if(!font.loadFromFile("resources/fonts/" + name))
    {
        std::cout << "Couldn't load " << name << " font\n";
        return;
    }
    //add new font to the map
    m_fonts.insert(std::make_pair(name, font));
}

sf::Font* ResourceManager::GetFont(std::string name)
{
    //find font in map and return it
    if(m_fonts.find(name) != m_fonts.end())
    {
        return &m_fonts[name];
    }
    //returns nullptr if the font doesn't exist
    std::cout << "Font " << name << " doesn't exist!\n";
    return nullptr;
}



