/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TicTacToe.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:25:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/10 16:40:10 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TicTacToe.hpp"
#include <random>


TicTacToe::TicTacToe()
{
	window.create(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE + INFO_HEIGHT), "Tic Tac Toe");
	currentPlayer = Player::X;
	grid.resize(GRID_SIZE, std::vector<Player>(GRID_SIZE, Player::None));
	fs::path exePath = fs::canonical("/proc/self/exe").parent_path();
	fs::path fontPath = exePath / "resources/fonts/Arial.ttf";
	if (!font.loadFromFile(fontPath.string()))
	{
		throw std::runtime_error("Could not load font");
	}
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);

	turnIndicator.setFont(font);
	turnIndicator.setCharacterSize(24);
	turnIndicator.setFillColor(sf::Color::Black);
	turnIndicator.setPosition(10, 10);

	resultText.setFont(font);
	resultText.setCharacterSize(50);
	resultText.setFillColor(sf::Color::Black);
	resultText.setPosition(WINDOW_SIZE / 2 - 70, WINDOW_SIZE / 2 - 50);

	rematchPrompt.setFont(font);
	rematchPrompt.setCharacterSize(22);
	rematchPrompt.setFillColor(sf::Color::White);
	rematchPrompt.setOutlineColor(sf::Color::Black);
	rematchPrompt.setOutlineThickness(2);
	rematchPrompt.setPosition(WINDOW_SIZE / 2 - 100, WINDOW_SIZE / 2 + 50);
	rematchPrompt.setString("Press R to rematch");

	WinDrawText.setFont(font);
	WinDrawText.setCharacterSize(24);
	WinDrawText.setFillColor(sf::Color::Black);
	WinDrawText.setPosition(100, 10);

	startPrompt.setFont(font);
	startPrompt.setCharacterSize(24);
	startPrompt.setFillColor(sf::Color::Black);
	startPrompt.setPosition(WINDOW_SIZE / 2 - 100, WINDOW_SIZE / 2 - 100);
	startPrompt.setString("Choose game mode:");
	
	PlayerVsPlayerPrompt.setFont(font);
	PlayerVsPlayerPrompt.setCharacterSize(24);
	PlayerVsPlayerPrompt.setFillColor(sf::Color::Black);
	PlayerVsPlayerPrompt.setPosition(WINDOW_SIZE / 2 - 100, WINDOW_SIZE / 2 - 50);
	PlayerVsPlayerPrompt.setString("1. Player vs Player");

	PlayerVsBeginnerAIPrompt.setFont(font);
	PlayerVsBeginnerAIPrompt.setCharacterSize(24);
	PlayerVsBeginnerAIPrompt.setFillColor(sf::Color::Black);
	PlayerVsBeginnerAIPrompt.setPosition(WINDOW_SIZE / 2 - 100, WINDOW_SIZE / 2);
	PlayerVsBeginnerAIPrompt.setString("2. Player vs Beginner AI");

	PlayerVsAdvancedAIPrompt.setFont(font);
	PlayerVsAdvancedAIPrompt.setCharacterSize(24);
	PlayerVsAdvancedAIPrompt.setFillColor(sf::Color::Black);
	PlayerVsAdvancedAIPrompt.setPosition(WINDOW_SIZE / 2 - 100, WINDOW_SIZE / 2 + 50);
	PlayerVsAdvancedAIPrompt.setString("3. Player vs Advanced AI");
	
	gameMode = GameMode::None;
	xWins = 0;
	oWins = 0;
	draws = 0;

	updateTurnIndicator();
	
	window.setVerticalSyncEnabled(false);
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
				if (gameMode == GameMode::None)
				{
					handleStartScreenClick(event.mouseButton.x, event.mouseButton.y);
				}
				else
				{
					handleMouseClick(event.mouseButton.x, event.mouseButton.y);
				}
			}
		}
	}
}

bool TicTacToe::handleRematchPrompt()
{
	if (checkWin(currentPlayer))
	{
		handleWin();
		return true;
	}
	else if (checkDraw())
	{
		handleDraw();
		return true;
	}
	return false;
}

void TicTacToe::handleWin()
{
	if (currentPlayer == Player::X)
		{
			++xWins;
		}
		else
		{
			++oWins;
		}
		window.clear(sf::Color::White);
		drawGrid();
		drawMarks();
		updateTurnIndicator();
		resultText.setString(std::string(currentPlayer == Player::X ? "X" : "O") + " wins!");
		WinDrawText.setString("X wins: " + std::to_string(xWins) + " O wins: " + std::to_string(oWins) + " Draws: " + std::to_string(draws));
		window.draw(resultText);
		window.draw(WinDrawText);
		window.draw(rematchPrompt);
		window.display();
		while (true && window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::R)
					{
						resetGame();
						return;
					}
				}
			}
		}
}

void TicTacToe::handleDraw()
{
	draws++;
	window.clear(sf::Color::White);
	drawGrid();
	drawMarks();
	updateTurnIndicator();
	resultText.setString("Draw!");
	WinDrawText.setString("X wins: " + std::to_string(xWins) + " O wins: " + std::to_string(oWins) + " Draws: " + std::to_string(draws));
	window.draw(resultText);
	window.draw(WinDrawText);
	window.draw(rematchPrompt);
	window.display();
	while (true && window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					resetGame();
					return;
				}
			}
		}
	}
}

void TicTacToe::handleMouseClick(int x, int y)
{
	sf::Vector2u windowSize = window.getSize();

	float scaleX = static_cast<float>(windowSize.x) / WINDOW_SIZE;
	float scaleY = static_cast<float>(windowSize.y - INFO_HEIGHT) / WINDOW_SIZE;

	int adjustedX = static_cast<int>(x / scaleX);
	int adjustedY = static_cast<int>(y / scaleY - INFO_HEIGHT);
	
	if (adjustedX < 0 || adjustedX >= WINDOW_SIZE || adjustedY < 0 || adjustedY >= WINDOW_SIZE)
	{
		return;
	}

	int row = adjustedY / CELL_SIZE;
	int col = adjustedX / CELL_SIZE;
	if (grid[row][col] == Player::None)
	{
		grid[row][col] = currentPlayer;
		if (handleRematchPrompt())
		{
			return;
		}
		else
		{
			currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
			updateTurnIndicator();
			if (gameMode != GameMode::PlayerVsPlayer)
			{
				makeBotMove();
			}
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
	if (gameMode == GameMode::None)
	{
		showStartScreen();
	}
	else
	{
	window.clear(sf::Color::White);
	drawGrid();
	drawMarks();
	updateTurnIndicator();
	window.draw(WinDrawText);
	window.draw(turnIndicator);
	window.draw(text);
	window.display();
	}
}

void TicTacToe::drawGrid()
{
	for (int i = 0; i < GRID_SIZE; ++i)
	{
		sf::RectangleShape hLine(sf::Vector2f(WINDOW_SIZE, 5));
		hLine.setFillColor(sf::Color::Black);
		hLine.setPosition(0, i * CELL_SIZE + INFO_HEIGHT - 2.5f);
		window.draw(hLine);
		
		sf::RectangleShape vLine(sf::Vector2f(5, WINDOW_SIZE));
		vLine.setFillColor(sf::Color::Black);
		vLine.setPosition(i * CELL_SIZE - 2.5f, INFO_HEIGHT);
		window.draw(vLine);	
	}
	sf::RectangleShape bottomLine(sf::Vector2f(WINDOW_SIZE, 5));
	bottomLine.setFillColor(sf::Color::Black);
	bottomLine.setPosition(0, WINDOW_SIZE + INFO_HEIGHT - 2.5f);
	window.draw(bottomLine);
	sf::RectangleShape rightLine(sf::Vector2f(5, WINDOW_SIZE));
	rightLine.setFillColor(sf::Color::Black);
	rightLine.setPosition(WINDOW_SIZE - 2.5f, INFO_HEIGHT);
	window.draw(rightLine);
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
				mark.setPosition(col * CELL_SIZE + 60, row * CELL_SIZE + 40 + INFO_HEIGHT);
				window.draw(mark);
			}
			else if (grid[row][col] == Player::O)
			{
				sf::Text mark("O", font, 100);
				mark.setFillColor(sf::Color::Blue);
				mark.setPosition(col * CELL_SIZE + 60, row * CELL_SIZE + 40 + INFO_HEIGHT);
				window.draw(mark);
			}
		}
	}
}

void TicTacToe::updateTurnIndicator()
{
	turnIndicator.setString("Turn: " + std::string(currentPlayer == Player::X ? "X" : "O"));
	turnIndicator.setFillColor(currentPlayer == Player::X ? sf::Color::Red : sf::Color::Blue);
}

void TicTacToe::resetGame()
{
	grid = std::vector<std::vector<Player>>(GRID_SIZE, std::vector<Player>(GRID_SIZE, Player::None));
	currentPlayer = Player::X;
	resultText.setString("");
	updateTurnIndicator();
}

void TicTacToe::showStartScreen()
{
	window.clear(sf::Color::White);
	window.draw(startPrompt);
	window.draw(PlayerVsPlayerPrompt);
	window.draw(PlayerVsBeginnerAIPrompt);
	window.draw(PlayerVsAdvancedAIPrompt);
	window.display();
}

void TicTacToe::handleStartScreenClick(int x, int y)
{
	sf::Vector2u windowSize = window.getSize();

	float scaleX = static_cast<float>(windowSize.x) / WINDOW_SIZE;
	float scaleY = static_cast<float>(windowSize.y - INFO_HEIGHT) / WINDOW_SIZE;

	int adjustedX = static_cast<int>(x / scaleX);
	int adjustedY = static_cast<int>(y / scaleY - INFO_HEIGHT);

	if (adjustedX < 0 || adjustedX >= WINDOW_SIZE || adjustedY < 0 || adjustedY >= WINDOW_SIZE)
	{
		return;
	}

	if (adjustedX >= PlayerVsPlayerPrompt.getPosition().x && adjustedX <= PlayerVsPlayerPrompt.getPosition().x + PlayerVsPlayerPrompt.getGlobalBounds().width &&
		adjustedY >= PlayerVsPlayerPrompt.getPosition().y && adjustedY <= PlayerVsPlayerPrompt.getPosition().y + PlayerVsPlayerPrompt.getGlobalBounds().height)
	{
		gameMode = GameMode::PlayerVsPlayer;
	}
	else if (adjustedX >= PlayerVsBeginnerAIPrompt.getPosition().x && adjustedX <= PlayerVsBeginnerAIPrompt.getPosition().x + PlayerVsBeginnerAIPrompt.getGlobalBounds().width &&
		adjustedY >= PlayerVsBeginnerAIPrompt.getPosition().y && adjustedY <= PlayerVsBeginnerAIPrompt.getPosition().y + PlayerVsBeginnerAIPrompt.getGlobalBounds().height)
	{
		gameMode = GameMode::PlayerVsBeginnerAI;
	}
	else if (adjustedX >= PlayerVsAdvancedAIPrompt.getPosition().x && adjustedX <= PlayerVsAdvancedAIPrompt.getPosition().x + PlayerVsAdvancedAIPrompt.getGlobalBounds().width &&
		adjustedY >= PlayerVsAdvancedAIPrompt.getPosition().y && adjustedY <= PlayerVsAdvancedAIPrompt.getPosition().y + PlayerVsAdvancedAIPrompt.getGlobalBounds().height)
	{
		gameMode = GameMode::PlayerVsAdvancedAI;
	}
}

void TicTacToe::makeBotMove()
{
	if (gameMode == GameMode::PlayerVsBeginnerAI)
	{
		std::vector<std::pair<int, int>> availableMoves;
		for (int row = 0; row < GRID_SIZE; ++row)
		{
			for (int col = 0; col < GRID_SIZE; ++col)
			{
				if (grid[row][col] == Player::None)
				{
					availableMoves.push_back(std::make_pair(row, col));
				}
			}
		}
		if (availableMoves.empty())
		{
			return;
		}
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, availableMoves.size() - 1);
		int index = dis(gen);
		grid[availableMoves[index].first][availableMoves[index].second] = currentPlayer;
		if (handleRematchPrompt())
		{
			return;
		}
		else
		{
			currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
			updateTurnIndicator();
		}
	}
	else if (gameMode == GameMode::PlayerVsAdvancedAI)
	{
		int bestScore = -1000;
		std::pair<int, int> bestMove;
		for (int row = 0; row < GRID_SIZE; ++row)
		{
			for (int col = 0; col < GRID_SIZE; ++col)
			{
				if (grid[row][col] == Player::None)
				{
					grid[row][col] = currentPlayer;
					int score = minimax(grid, false);
					grid[row][col] = Player::None;
					if (score > bestScore)
					{
						bestScore = score;
						bestMove = std::make_pair(row, col);
					}
				}
			}
		}
		grid[bestMove.first][bestMove.second] = currentPlayer;
		if (handleRematchPrompt())
		{
			return;
		}
		else
		{
			currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
			updateTurnIndicator();
		}
	}
}

int TicTacToe::minimax(std::vector<std::vector<Player>> grid, bool isMaximizing)
{
	if (checkWin(Player::X))
	{
		return -10;
	}
	else if (checkWin(Player::O))
	{
		return 10;
	}
	else if (checkDraw())
	{
		return 0;
	}
	if (isMaximizing)
	{
		int bestScore = -1000;
		for (int row = 0; row < GRID_SIZE; ++row)
		{
			for (int col = 0; col < GRID_SIZE; ++col)
			{
				if (grid[row][col] == Player::None)
				{
					grid[row][col] = Player::O;
					int score = minimax(grid, false);
					grid[row][col] = Player::None;
					bestScore = std::max(bestScore, score);
				}
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 1000;
		for (int row = 0; row < GRID_SIZE; ++row)
		{
			for (int col = 0; col < GRID_SIZE; ++col)
			{
				if (grid[row][col] == Player::None)
				{
					grid[row][col] = Player::X;
					int score = minimax(grid, true);
					grid[row][col] = Player::None;
					bestScore = std::min(bestScore, score);
				}
			}
		}
		return bestScore;
	}
}