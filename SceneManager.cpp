#include "SceneManager.hpp"
#include <iostream>

SceneManager::SceneManager()
{
    //ctor
}

SceneManager::~SceneManager()
{
    std::cout << "Deleting scenes\n";
    //We only need to clear the map as the scene map uses smart pointers
    m_scenes.clear();
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
    //check if scene already exists by checking the scene name with the scene map
    if(m_scenes.find(scene->GetName()) == m_scenes.end())
    {
        //scene doesn't exist, add it to the scene map
        m_scenes[scene->GetName()] = scene;
        std::cout << "Added new scene: " << scene->GetName() << std::endl;
    }
    else
        std::cout << "Scene '" << scene->GetName() << "' already exists!\n";
}

void SceneManager::RemoveScene(const std::string& sceneName)
{
    //check if scene exists by checking the scene name with the scene map
    if(m_scenes.find(sceneName) != m_scenes.end())
    {
        //erase the scene from the scene map (Deletes memory for us due to smart pointers)
        m_scenes.erase(sceneName);
        std::cout << "Deleted scene: " << sceneName << std::endl;
    }
    else
        std::cout << "Scene '" << sceneName << "' does not exist exists!\n";
}


void SceneManager::LoadScene(const std::string& sceneName)
{
    //check if scene exists by checking the scene name with the scene map
    if(m_scenes.find(sceneName) != m_scenes.end())
    {
        //unload the current scene
        unloadCurrentScene();
        //set current scene to the new scene
        m_currentScene = m_scenes[sceneName];
        //Initialise scene and start it
        m_currentScene->Initialize();
        m_currentScene->Start();
        std::cout << "Loaded new scene: " << sceneName << std::endl;
    }
    else
        std::cout << "Scene '" << sceneName << "' does not exist exists!\n";
}

void SceneManager::ReloadScene()
{
    //check if current scene is not null
    if(m_currentScene != nullptr)
    {
        //get the current scene name
        std::string currentSceneName = m_currentScene->GetName();
        //unload the current scene
        unloadCurrentScene();
        //set current scene to the new scene
        m_currentScene = m_scenes[currentSceneName];
        //Initialise scene and start it
        m_currentScene->Initialize();
        m_currentScene->Start();
        std::cout << "Reloaded scene: " << currentSceneName << std::endl;
    }
    else
        std::cout << "Unable to reload scene as no current scene loaded!\n";
}


void SceneManager::Update(sf::RenderWindow& window)
{
    //check if current scene has not been set
    if(m_currentScene == nullptr)
    {
        std::cout << "Can't update scene as current scene equals nullptr\n";
        return;
    }
    //update the current scene
    m_currentScene->Update(window);

}

void SceneManager::Render(sf::RenderWindow& window)
{
    //check if current scene has not been set
    if(m_currentScene == nullptr)
    {
        std::cout << "Can't render scene as current scene equals nullptr\n";
        return;
    }

    // We must clear the window each time round the loop
    window.clear(m_currentScene->GetBackgorundColor());
    //render the current scene
    m_currentScene->Render(window);

    // Get the window to display its contents
    window.display();
}

void SceneManager::unloadCurrentScene()
{
    //check if current scene does not equal null
    if(m_currentScene != nullptr)
    {
        std::cout << "Unloading scene: " << m_currentScene->GetName() << std::endl;
        m_currentScene->Unload();
        std::cout << "Unloaded scene: " << m_currentScene->GetName() << std::endl;
        m_currentScene = nullptr; //set current scene pointer to null
    }
}
