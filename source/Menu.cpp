#include "Menu.hpp"
#include "Game.hpp"
#include "StateMachine.hpp"
#include "MockAPI.hpp"
#include "ResourcesManager.hpp"

Menu::Menu() : AppWindow(512, 512)
{
    const std::array<std::string, 10> flags = {"Poland", "Iceland", "Cyprus", "Austria", "Turkey",
                                            "UK", "Denmark", "France", "Spain", "Greece"};


    for(int i = 0; i < 10; i++) { // 10 regions
        float positionX = 50 + 95 * (i % 5);
        float positionY = 140;

        if (5 <= i && i <= 9) {
            positionY = 220;
        }
        // if(10 <= i && i <= 14) {} -> if more regions will be added

        m_buttons[i].init(flags[i], positionX, positionY);
    }

    m_background.setTexture(ResourcesManager::Instance().getTexture("menu.png"));

    liveData.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));
    localData.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));

    liveData.setString("Live Data");
    localData.setString("Offline");

    liveData.setPosition(20, 485);
    localData.setPosition(85, 485);

    liveData.setCharacterSize(13);
    localData.setCharacterSize(13);
}

void Menu::internalRender() {
    m_window.draw(m_background);

    for(Button& button: m_buttons) {
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

    for(Button& button: m_buttons) {
        if(button.getButton().getGlobalBounds().contains(positionRelativeToView(mousePosition))) {
            button.getButton().setOutlineColor(sf::Color::White);
        }
        else {
            button.getButton().setOutlineColor(sf::Color::Transparent);
        }
    }
}

void Menu::internalHandleEvent(const sf::Event& event)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

    switch(event.type)
    {
        case sf::Event::KeyPressed: {
            sf::Keyboard::Key key = event.key.code;

            if(key == sf::Keyboard::R) // select a random region
            {
                m_window.close();
                int randomNumber = Utility::randomNumber(0, 9);
                StateMachine::Instance().pushState(std::make_shared<Game>(m_buttons[randomNumber].getName(), m_liveApi));
            }
            else if(key == sf::Keyboard::T)
            {
                m_liveApi = !m_liveApi;
            }

            break;
        }
        case sf::Event::MouseButtonPressed: {
            for(Button& button: m_buttons) {
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

            break;
        }

        default:
            break;
    }
}

void Menu::Button::init(const std::string& regionName, float x, float y)
{
    m_regionName = regionName;
    m_rectangle.setSize(sf::Vector2f(50, 30));
    m_rectangle.setOutlineThickness(2.3f);

    m_texture.loadFromFile("./resources/flags/" + regionName + ".png");

    m_label.setFont(ResourcesManager::Instance().getFont("Poppins-Regular.ttf"));
    m_label.setCharacterSize(12);

    m_rectangle.setTexture(&m_texture);
    m_rectangle.setPosition(x, y);

    if(regionName == "UK") {
        m_label.setString("UK & Ireland");
        x = x - 10;
    }
    else if(regionName == "Spain") {
        m_label.setString("Spain & Portugal");
        x = x - 25;
    }
    else {
        m_label.setString(regionName);
    }

    m_label.setPosition(x, y + 30);
}


const std::string& Menu::Button::getName() const
{
    return m_regionName;
}

sf::RectangleShape& Menu::Button::getButton()
{
    return m_rectangle;
}

const sf::Text& Menu::Button::getLabel() const
{
    return m_label;
}
