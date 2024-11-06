/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TicTacToe.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:25:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/07 00:55:19 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TicTacToe.hpp"

TicTacToe::TicTacToe()
{
	window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Tic Tac Toe");
	currentPlayer = Player::X;
	grid.resize(GRID_SIZE, std::vector<Player>(GRID_SIZE, Player::None));
	if (!font.loadFromFile("resources/fonts/Arial.ttf"))
	{
		throw std::runtime_error("Could not load font");
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
}

void TicTacToe::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void TicTacToe::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				handleMouseClick(event.mouseButton.x, event.mouseButton.y);
			}
		}
	}
}

void TicTacToe::handleMouseClick(int x, int y)
{
	int row = y / CELL_SIZE;
	int col = x / CELL_SIZE;
	if (grid[row][col] == Player::None)
	{
		grid[row][col] = currentPlayer;
		if (checkWin(currentPlayer))
		{
			std::cout << "Player " << (currentPlayer == Player::X ? "X" : "O") << " wins!" << std::endl;
			window.close();
		}
		else if (checkDraw())
		{
			std::cout << "Draw!" << std::endl;
			window.close();
		}
		else
		{
			currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
		}
	}
}

bool TicTacToe::checkWin(Player player)
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player)
		{
			return true;
		}
		if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player)
		{
			return true;
		}
	}
	if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
	{
		return true;
	}
	if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player)
	{
		return true;
	}
	return false;
}

bool TicTacToe::checkDraw()
{
	for (const auto& row : grid)
	{
		for (const auto& cell : row)
		{
			if (cell == Player::None)
			{
				return false;
			}
		}
	}
	return true;
}

void TicTacToe::update()
{
}

void TicTacToe::render()
{
	window.clear(sf::Color::White);
	drawGrid();
	drawMarks();
	window.draw(text);
	window.display();
}

void TicTacToe::drawGrid()
{
	for (int i = 1; i < GRID_SIZE; ++i)
	{
		sf::RectangleShape line(sf::Vector2f(WINDOW_SIZE, 5));
		line.setFillColor(sf::Color::Black);
		line.setPosition(0, i * CELL_SIZE - 2.5f);
		window.draw(line);
		line.setSize(sf::Vector2f(5, WINDOW_SIZE));
		line.setPosition(i * CELL_SIZE - 2.5f, 0);
		window.draw(line);
	}
}

void TicTacToe::drawMarks()
{
	for (int row = 0; row < GRID_SIZE; ++row)
	{
		for (int col = 0; col < GRID_SIZE; ++col)
		{
			if (grid[row][col] == Player::X)
			{
				sf::Text mark("X", font, 100);
				mark.setFillColor(sf::Color::Red);
				mark.setPosition(col * CELL_SIZE + 50, row * CELL_SIZE + 50);
				window.draw(mark);
			}
			else if (grid[row][col] == Player::O)
			{
				sf::Text mark("O", font, 100);
				mark.setFillColor(sf::Color::Blue);
				mark.setPosition(col * CELL_SIZE + 50, row * CELL_SIZE + 50);
				window.draw(mark);
			}
		}
	}
}