/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TicTacToe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:25:08 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/07 22:09:52 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

const int GRID_SIZE = 3;
const int CELL_SIZE = 200;
const int WINDOW_SIZE = GRID_SIZE * CELL_SIZE;
const int INFO_HEIGHT = 50;

enum class Player { None, X, O };

class TicTacToe
{
	public:
		TicTacToe();
		void run();
	private:
		sf::RenderWindow window;
		std::vector<std::vector<Player>> grid;
		Player currentPlayer;
		sf::Font font;
		sf::Text text;
		sf::Text turnIndicator;
		sf::Text resultText;
		sf::Text rematchPrompt;
		sf::Text WinDrawText;
		int xWins;
		int oWins;
		int draws;

		void processEvents();
		void handleMouseClick(int x, int y);
		bool checkWin(Player player);
		bool checkDraw();
		void update();
		void render();
		void drawGrid();
		void drawMarks();
		void updateTurnIndicator();
		void resetGame();
};