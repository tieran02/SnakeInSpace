#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include "Scene.hpp"

class SceneManager
{
public:
    //Singleton to get the instance of the scene manager (ONLY ONE SCENEMANAGER CAN EXIST)
    static SceneManager& Instance()
    {
        static SceneManager instance;
        return instance;
    }

    SceneManager();
    ~SceneManager();

    //Add a scene to the scene map
    void AddScene(std::shared_ptr<Scene> scene);
    //Remove a scene from the scene map using the scenes name
    void RemoveScene(const std::string& sceneName);
    //Load a scene from the scene map using the scenes name
    void LoadScene(const std::string& sceneName);
    //Reload the current scene
    void ReloadScene();
    //Get the current scene loaded
    std::shared_ptr<Scene> GetCurrentScene() {return m_currentScene;}

    //Update the current scene
    void Update(sf::RenderWindow& window);
    //Render the current scene
    void Render(sf::RenderWindow& window);

protected:
    //map of all the scenes (use shared pointers to manager the memory for us)
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
    //Shared pointer to the current scene (nullptr by default)
    std::shared_ptr<Scene> m_currentScene{nullptr};
private:
    //unloads the current scene
    void unloadCurrentScene();
};

#endif // SCENEMANAGER_HPP
