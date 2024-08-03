#include "Menu.hpp"
#include "Game.hpp"
#include "StateMachine.hpp"

#include "DataFetcher.hpp"
#include "MockAPI.hpp"

Menu::Menu() : Window({512, 512}, "Radar Contact - Menu")
{
    const std::array<std::string, 10> flags = {"Poland", "Iceland", "Cyprus", "Austria", "Turkey",
                                            "UK", "Denmark", "France", "Spain", "Greece"};

    sf::RectangleShape button{sf::Vector2f(50,30)};
    button.setOutlineThickness(2.3f);

    for(int i = 0; i < static_cast<int>(flags.size()); i++) {
        sf::Texture texture;
        texture.loadFromFile("./resources/flags/" + flags[i] + ".png");

        sf::Text text(flags[i], ResourcesManager::Instance().getFont("Poppins-Regular.ttf"), 12);

        float positionX = 50 + 95 * (i % 5);
        float positionY = 140;

        if (5 <= i && i <= 9) {
            positionY = 220;
        }

        button.setPosition(positionX, positionY);
        text.setPosition(positionX, positionY + 30);

        m_flagsTexture[i] = (texture);
        button.setTexture(&m_flagsTexture[i]);

        m_regionsButtons[i] = std::make_pair<>(button, flags[i]);

        if(flags[i] == "UK") {
            text.setString("UK & Ireland");
            text.setPosition(positionX - 10, positionY + 30);
        }
        else if(flags[i] == "Spain") {
            text.setString("Spain & Portugal");
            text.setPosition(positionX - 25, positionY + 30);
        }

        m_flagsLabel[i] = text;
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

void Menu::render() {
    m_window.clear();

    m_window.draw(m_background);

    for(auto &regionsButton: m_regionsButtons) {
        m_window.draw(regionsButton.first);
    }
    for(auto &label: m_flagsLabel) {
        m_window.draw(label);
    }

    m_window.draw(liveData);
    m_window.draw(localData);

    m_window.display();
}

void Menu::update() {
    if(ResourcesManager::Instance().isMockingEnabled()) {
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
    sf::Vector2i intMousePosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f floatMousePosition = {static_cast<float>(intMousePosition.x), static_cast<float>(intMousePosition.y)};

    for(auto &regionsButton: m_regionsButtons) {
        if(regionsButton.first.getGlobalBounds().contains(floatMousePosition)) {
            regionsButton.first.setOutlineColor(sf::Color::White);
        }
        else {
            regionsButton.first.setOutlineColor(sf::Color::Transparent);
        }
    }
}

void Menu::handleEvent() {
    sf::Vector2i intMousePosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f floatMousePosition{static_cast<float>(intMousePosition.x), static_cast<float>(intMousePosition.y)};
    sf::Event menu_event{};

    while(m_window.pollEvent(menu_event)) {
        switch(menu_event.type) {
            case sf::Event::Closed: {
                m_window.close();

                break;
            }
            case sf::Event::KeyPressed: {
                const sf::Keyboard::Key key_code = menu_event.key.code;

                if(key_code == sf::Keyboard::Escape) {
                    m_window.close();
                }

                break;
            }
            case sf::Event::MouseButtonPressed: {
                for(const auto &regionButtons: m_regionsButtons) {
                    if(regionButtons.first.getGlobalBounds().contains(floatMousePosition)) {

                        std::shared_ptr<LiveAPI> api = std::make_shared<LiveAPI>();

                        if(ResourcesManager::Instance().isMockingEnabled()) {
                            api = std::make_shared<MockAPI>();
                        }

                        DataFetcher::setAPI(api);

                        ResourcesManager::Instance().loadRegion(regionButtons.second);
                        StateMachine::Instance().pushState(std::make_shared<Game>());

                        m_window.close();
                    }
                }

                if(liveData.getGlobalBounds().contains(floatMousePosition)) {
                    ResourcesManager::Instance().setMocking(false);
                }
                else if(localData.getGlobalBounds().contains(floatMousePosition)) {
                    ResourcesManager::Instance().setMocking(true);
                }

                break;
            }

            default:
                break;
        }
    }
}
