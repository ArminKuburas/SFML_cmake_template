#include "TicTacToe.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	TicTacToe game;
	try
	{
		game.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
