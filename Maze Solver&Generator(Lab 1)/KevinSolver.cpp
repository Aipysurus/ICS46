#include <random>
#include "KevinGenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
#include "Maze.hpp"
#include "MazeSolution"
#include <vector>
#include "KevinSolver.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, KevinSolver, "KEVIN SOLVER(REQUIRED)");
KevinSolver::KevinSolver()
{
}

void KevinSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
//find_path(0,0,maze,mazeSolution);
}

vector<Direction> KevinGenerator::check_around(int x, int y, Maze& maze)
{//check coordiate flags if marked then do not add to vector of direction
	vector<Direction> moves;
	if (x - 1 >= 0)// check left
	{
        if (!(mazeSolution.wallExists(x,y,Direction::left)))/*change to check if wall does not exist*/
            moves.push_back(Direction::left);
	}
	if (x + 1 < maze.getWidth())//check right
	{
        if (!(mazeSolution.wallExists(x,y,Direction::right)))
			moves.push_back(Direction::right);
	}
	if (y - 1 >= 0)// check up
	{
		if (!(mazeSolution.wallExists(x,y,Direction::up)))
			moves.push_back(Direction::up);
	}
	if (y + 1 < maze.getHeight())//check down
	{
		if (!(mazeSolution.wallExists(x,y,Direction::down)))
			moves.push_back(Direction::down);
	}
	return moves;
}

void KevinSolver::find_path(int x, int y, const Maze& maze, MazeSolution& mazeSolution)
{
    vector<Direction> possible = check_around(x,y,maze);//possible moves from current position
    while (possible.size() > 0) // while cell has possible moves
    {                                   //add final condition if current position extends into bottom right corner
		Direction move = possible[0];//grab a direction
		int newx = x;
		int newy = y;
		move_direction(newx,newy,move);
		if(!(mazething[newx][newy]))//change this condition to unhit 
		{
			if(maze.wallExists(x,y,move)) // change to if it doesnt exist
			{
				maze.removeWall(x,y,move); //extend into that cell and set flag as moved
				create_path(newx,newy,maze); //call function again
			}

		}
		possible = check_around(x,y,maze);
    }
    //set those coodinate flags as unusable
    //if no possible moves begin backtrack
}

void KevinSolver::move(int& x, int& y, Direction dir)
{
	if (dir == Direction::up)
		y -= 1;
	else if(dir == Direction::down)
		y += 1;
	else if(dir == Direction::right)
		x += 1;
	else //Direction::left
		x -= 1;
}