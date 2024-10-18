#include "Game.h"

Game::Game()
	:window(windowSize, windowTitle)
{
	window_icon.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/Icon_Games.png");
	window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());

	Mfont.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf");

}

void Game::HandleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
				if (Main_Menu.Get_Exit().getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
				{
					exit(0);
					window.close();
				}
				if (Main_Menu.Get_Play().getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
				{
					Main_menu_open = false;
				}
			}
		}
	}
}

void Game::Update(float delta_Time)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

	Main_Menu.Deselect_exit();
	Main_Menu.Deselect_Setting();
	Main_Menu.Deselete_Play();

	if(Main_Menu.Get_Exit().getGlobalBounds().contains(sf::Vector2f(mouse_pos))) 
		Main_Menu.Select_exit();
	if (Main_Menu.Get_Play().getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
		Main_Menu.Select_Play();
	if (Main_Menu.Get_Setting().getGlobalBounds().contains(sf::Vector2f(mouse_pos)))
		Main_Menu.select_Setting();
	
}

void Game::Render()
{
	window.clear();

	if(Main_menu_open)
	{
		window.draw(Main_Menu.Get_Back_fon());
		window.draw(Main_Menu.Get_Play());
		window.draw(Main_Menu.Get_Setting());
		window.draw(Main_Menu.Get_Exit());
		window.draw(Main_Menu.Get_Ex_text());
	}

	window.display();
}

void Game::Run()
{
	sf::Clock delta_time_clock;
	while(window.isOpen())
	{
		sf::Time delta_time = delta_time_clock.restart();
		HandleInput();
		Update(delta_time.asSeconds());
		Render();
	}
}
