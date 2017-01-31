#ifndef KEVIN_SOLVER_HPP
#define KEVIN_SOLVER_HPP
#include "MazeSolver.hpp"

class KevinSolver:public MazeSolver
{
public:
	KevinSolver();
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	vector<Direction> KevinGenerator::check_around(int x, int y, Maze& maze);
	void find_path(int x, int y, Maze& maze);
	void move(int& x, int& y, Direction dir);
};

#endif //KEVIN_SOLVER_HPP