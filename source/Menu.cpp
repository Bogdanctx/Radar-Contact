#include "Menu.hpp"
#include "Game.hpp"
#include "StateMachine.hpp"
#include "MockAPI.hpp"
#include "ResourcesManager.hpp"

Menu::Menu() : AppWindow(512, 512)
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

    for(auto &regionsButton: m_regionsButtons) {
        if(regionsButton.first.getGlobalBounds().contains(positionRelativeToView(mousePosition))) {
            regionsButton.first.setOutlineColor(sf::Color::White);
        }
        else {
            regionsButton.first.setOutlineColor(sf::Color::Transparent);
        }
    }
}

void Menu::handleEvent() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
    sf::Event event{};

    while(m_window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed: {
                m_window.close();

                break;
            }
            case sf::Event::KeyPressed: {
                const sf::Keyboard::Key key_code = event.key.code;

                printf("%d\n", key_code);

                if(key_code == sf::Keyboard::Escape) {
                    m_window.close();
                }

                break;
            }
            case sf::Event::Resized:
            {
                updateWindowView(event.size.width, event.size.height);
                break;
            }
            case sf::Event::MouseButtonPressed: {
                for(const std::pair<sf::RectangleShape, std::string>& regionButton: m_regionsButtons) {
                    if(regionButton.first.getGlobalBounds().contains(positionRelativeToView(mousePosition))) {
                        Region region(regionButton.second);

                        std::shared_ptr<LiveAPI> api;

                        if(m_liveApi) {
                            printf("created live\n");
                            api = std::make_shared<LiveAPI>(region);
                        }
                        else
                        {
                            printf("created mock\n");
                            api = std::make_shared<MockAPI>(region);
                        }

                        StateMachine::Instance().pushState(std::make_shared<Game>(regionButton.second, api));

                        m_window.close();
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
}
