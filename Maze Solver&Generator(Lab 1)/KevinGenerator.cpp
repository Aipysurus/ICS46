#include <random>
#include "KevinGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
#include "Maze.hpp"
#include <vector>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, KevinGenerator, "KEVIN GENERATOR(REQUIRED)");

using namespace std;

KevinGenerator::KevinGenerator()
{
}
void KevinGenerator::generateMaze(Maze& maze)
{
	maze.addAllWalls();
	//recursive function goes here
	fill_vector(maze);
	create_path(0,0, maze);

}
void KevinGenerator::fill_vector(Maze& maze)
{
	mazething.resize(maze.getWidth());
	for (int i = 0; i < maze.getWidth(); ++i)
		mazething[i].resize(maze.getHeight());
	int x,y;
	for(x = 0; x < maze.getWidth(); ++x)
		mazething[x][0] = false;
	for (y = 0; y < maze.getHeight(); ++y)
		mazething[0][y] = false;
	for (x = 1; x < maze.getWidth(); ++x)
		for (y = 1; y < maze.getHeight(); ++y)
			mazething[x][y] = false;

}
void KevinGenerator::create_path(int x, int y, Maze& maze)
{
    mazething[x][y] = true;
    vector<Direction> possible = check_around(x,y,maze);
    while (possible.size() > 0)
    {
		random_shuffle(possible.begin(),possible.end());
		Direction move = possible[0];
		int newx = x;
		int newy = y;
		move_direction(newx,newy,move);
		if(!(mazething[newx][newy]))
		{
			if(maze.wallExists(x,y,move))
			{
				maze.removeWall(x,y,move);
				create_path(newx,newy,maze);
			}

		}
		possible = check_around(x,y,maze);
    }
}



vector<Direction> KevinGenerator::check_around(int x, int y, Maze& maze)
{
	vector<Direction> moves;
	if (x - 1 >= 0)// check left
	{
		if (!(mazething[x - 1][y]))
			moves.push_back(Direction::left);
	}
	if (x + 1 < maze.getWidth())//check right
	{
		if (!(mazething[x+1][y]))
			moves.push_back(Direction::right);
	}
	if (y - 1 >= 0)// check up
	{
		if (!(mazething[x][y - 1]))
			moves.push_back(Direction::up);
	}
	if (y + 1 < maze.getHeight())//check down
	{
		if (!(mazething[x][y + 1]))
			moves.push_back(Direction::down);
	}
	return moves;
}

bool KevinGenerator::in_bounds(int x, int y, Maze& maze)
{
	if (x - 1 >= 0 || x + 1 < maze.getWidth())
		return true;
	if (y - 1 >= 0 || x + 1 < maze.getHeight())
		return true;
	else 
		return false;
}
void KevinGenerator::move_direction(int& x, int& y, Direction dir)
{
	if (dir == Direction::up)
		y -= 1;
	else if(dir == Direction::down)
		y += 1;
	else if(dir == Direction::right)
		x += 1;
	else 
		x -= 1;
}


