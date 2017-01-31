#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
#include <vector>
#include <random>
#ifndef KEVINGENERATOR_HPP
#define KEVINGENERATOR_HP
using namespace std;



class KevinGenerator: public MazeGenerator
{
public:
	KevinGenerator();
	void generateMaze(Maze& maze);
	void fill_vector(Maze& maze);
	void create_path(int x, int y, Maze& maze);
	vector<Direction> check_around(int x, int y, Maze& maze);
	void move_direction(int& x, int & y, Direction dir);
	bool in_bounds(int x, int y, Maze& maze);

private:
	vector<vector<bool>> mazething;


};
#endif //KEVINGENERATOR_HPP