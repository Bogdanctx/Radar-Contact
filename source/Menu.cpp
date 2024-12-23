#include "Menu.hpp"
#include "Game.hpp"
#include "StateMachine.hpp"
#include "MockAPI.hpp"
#include "ResourcesManager.hpp"

Menu::Menu() : AppWindow(512, 512),
               m_background(ResourcesManager::Instance().getTexture("menu.png")),
               liveData(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), "Live Data", 13),
               localData(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), "Offline", 13)
{
    const std::array<std::string, NUMBER_OF_REGIONS> flags = {
        "Poland", "Iceland", "Cyprus", "Austria", "Turkey",
        "UK", "Denmark", "France", "Spain", "Greece"
    };

    m_buttons.resize(NUMBER_OF_REGIONS);
    m_flagTextures.resize(NUMBER_OF_REGIONS);

    for (int i = 0; i < NUMBER_OF_REGIONS; i++)
    {
        m_flagTextures[i].loadFromFile(std::filesystem::path("resources") / "flags" / (flags[i] + ".png"));

        float positionX = 50 + 95 * (i % 5);
        float positionY = 140;

        // if(5 <= i && i <= 9) {}
        if (5 <= i)
        {
            positionY = 220;
        }
        // if(10 <= i && i <= 14) {} -> if more regions will be added
        m_buttons[i] = RegionButton(flags[i], positionX, positionY, &m_flagTextures[i]);
    }

    liveData.setPosition(sf::Vector2f(20, 485));
    localData.setPosition(sf::Vector2f(85, 485));
}

void Menu::internalRender() {
    m_window.draw(m_background);

    for(const RegionButton& button: m_buttons) {
        m_window.draw(button.getButton());
        m_window.draw(button.getLabel());
    }

    m_window.draw(liveData);
    m_window.draw(localData);
}

void Menu::internalUpdate() {
    if(!m_liveApi) {
        liveData.setFillColor(sf::Color(209, 206, 199, 100));
        localData.setFillColor(sf::Color::Green);
    }
    else {
        localData.setFillColor(sf::Color(209, 206, 199, 100));
        liveData.setFillColor(sf::Color::Green);
    }

    checkHovers();
}

//-----------------------------------------------------------
// Purpose: Check if a flag is hovered
//-----------------------------------------------------------
void Menu::checkHovers() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

    for(RegionButton& button: m_buttons) {
        if(button.getButton().getGlobalBounds().contains(positionRelativeToView(mousePosition))) {
            button.setOutlineColor(sf::Color::White);
        }
        else {
            button.setOutlineColor(sf::Color::Transparent);
        }
    }
}

void Menu::internalHandleEvent(const std::optional<sf::Event>& event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

    if(event->is<sf::Event::KeyPressed>())
    {
        sf::Keyboard::Key key = event->getIf<sf::Event::KeyPressed>()->code;

        if(key == sf::Keyboard::Key::R) // select a random region
        {
            m_window.close();
            int randomNumber = Utility::randomNumber(0, 9);
            StateMachine::Instance().pushState(std::make_shared<Game>(m_buttons[randomNumber].getName(), m_liveApi));
        }
        else if(key == sf::Keyboard::Key::T)
        {
            m_liveApi = !m_liveApi;
        }

    }
    if(event->is<sf::Event::MouseButtonPressed>())
    {
        for(const RegionButton &button: m_buttons) {
            if(button.getButton().getGlobalBounds().contains(positionRelativeToView(mousePosition))) {
                m_window.close();

                StateMachine::Instance().pushState(std::make_shared<Game>(button.getName(), m_liveApi));
            }
        }

        if(liveData.getGlobalBounds().contains(positionRelativeToView(mousePosition))) {
            m_liveApi = true;
        }
        else if(localData.getGlobalBounds().contains(positionRelativeToView(mousePosition))) {
            m_liveApi = false;
        }
    }
}