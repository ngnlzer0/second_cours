#include "Game.h"

Game::Game()
	:window(windowSize, windowTitle)
{
	window_icon.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/Icon_Games.png");
	window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());

	Mfont.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf");

	sf::Vector2f window_middle_point(windowSize.width / 2, windowSize.height / 2 );

	sf::Vector2f standart_size_button = { 300,200 };
	Play = Buttons({window_middle_point.x,window_middle_point.y - 250}, standart_size_button, "First Button", Mfont, 
		"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Buttons/Rect/PlayIcon/Default.png");

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
		}
	}
}

void Game::Update(float delta_Time)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	Play.Deselect();

	if (Play.Get_global_bounds().contains(sf::Vector2f(mouse_pos.x, mouse_pos.y)))
	{
		Play.Select();
	}
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
