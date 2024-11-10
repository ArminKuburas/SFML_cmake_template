/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TicTacToe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:25:08 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/10 16:33:01 by akuburas         ###   ########.fr       */
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
enum class GameMode { None, PlayerVsPlayer, PlayerVsBeginnerAI, PlayerVsAdvancedAI };

class TicTacToe
{
	public:
		TicTacToe();
		void run();
	private:
		sf::RenderWindow window;
		std::vector<std::vector<Player>> grid;
		Player currentPlayer;
		GameMode gameMode;
		sf::Font font;
		sf::Text text;
		sf::Text turnIndicator;
		sf::Text resultText;
		sf::Text rematchPrompt;
		sf::Text WinDrawText;
		sf::Text startPrompt;
		sf::Text PlayerVsPlayerPrompt;
		sf::Text PlayerVsBeginnerAIPrompt;
		sf::Text PlayerVsAdvancedAIPrompt;
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
		void showStartScreen();
		void handleStartScreenClick(int x, int y);
		void makeBotMove();
		int minimax(std::vector<std::vector<Player>> grid, bool isMaximizing);
		bool handleRematchPrompt();
		void handleWin();
		void handleDraw();
};