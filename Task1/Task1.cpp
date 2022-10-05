/*
Name:Abdul Rehman
Roll Number: BCSF20A020
*/
#include <iostream>
#include <stack>
#include <fstream>
#include <string>
using namespace std;
struct Position
{
	int row;
	int col;
	bool operator !=(const Position& rhs)
	{
		if (row != rhs.row || col != rhs.col)
		{
			return true;
		}
		return false;
	}
};
bool isValid(int x, int y, int size)
{
	if (x >= 0 && x < size&&y >= 0 && y < size)
	{
		return true;
	}
	return false;
}

bool isBlocked(char** m, int x, int y, int size)
{
	if (!isValid(x, y, size) || m[x][y] == '1' || m[x][y] == 'd')
	{
		return true;
	}
	return false;
}

bool findPath(char** maze, int size, Position src, Position des, fstream& out)
{
	if (!isValid(src.row, src.col, size) || !isValid(des.row, des.col, size))
	{
		exit(0);
	}
	Position current = src;
	stack<Position> path;
	path.push(current);
	if (maze[src.row][src.col] == '1' || maze[des.row][des.col] == '1')
	{
		return false;
	}
	else if (!(isValid(des.row + 1, des.col, size) && maze[des.row + 1][des.col] == '0') && !(isValid(des.row, des.col + 1, size) && maze[des.row][des.col + 1] == '0') && !(isValid(des.row - 1, des.col, size) && maze[des.row - 1][des.col] == '0') && !(isValid(des.row, des.col - 1, size) && maze[des.row][des.col - 1] == '0'))
	{
		return false;
	}
	else if (!(isValid(src.row + 1, src.col, size) && maze[src.row + 1][src.col] == '0') && !(isValid(src.row, src.col + 1, size) && maze[src.row][src.col + 1] == '0') && !(isValid(src.row - 1, src.col, size) && maze[src.row - 1][src.col] == '0') && !(isValid(src.row, src.col - 1, size) && maze[src.row][src.col - 1] == '0'))
	{
		return false;
	}
	while (current != des)
	{
		if (isBlocked(maze, current.row + 1, current.col, size) && isBlocked(maze, current.row, current.col + 1, size) && isBlocked(maze, current.row, current.col - 1, size) && isBlocked(maze, current.row - 1, current.col, size))
		{
			return false;
		}
		else if (isValid(current.row + 1, current.col, size) && maze[current.row + 1][current.col] == '0')
		{
			maze[current.row][current.col] = '*';
			current.row = current.row + 1;
			path.push(current);
		}
		else if (isValid(current.row, current.col + 1, size) && maze[current.row][current.col + 1] == '0')
		{
			maze[current.row][current.col] = '*';
			current.col = current.col + 1;
			path.push(current);
		}
		else if (isValid(current.row, current.col - 1, size) && maze[current.row][current.col - 1] == '0')
		{
			maze[current.row][current.col] = '*';
			current.col = current.col - 1;
			path.push(current);
		}
		else if (isValid(current.row - 1, current.col, size) && maze[current.row - 1][current.col] == '0')
		{
			maze[current.row][current.col] = '*';
			current.row = current.row - 1;
			path.push(current);
		}
		else
		{
			path.pop();
			maze[current.row][current.col] = 'd';
			current.row = path.top().row;
			current.col = path.top().col;
		}
	}
	maze[current.row][current.col] = '*';
	stack<Position> path2;
	while (!path.empty())
	{
		path2.push(path.top());
		path.pop();
	}
	out << size << endl;
	out << src.row << " " << src.col << endl;
	out << des.row << " " << des.col << endl;
	while (!path2.empty())
	{
		out << "(" << path2.top().row << "," << path2.top().col << ") ";
		path2.pop();
	}
	out << endl << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (maze[i][j] == 'd')
				maze[i][j] = '0';
			out << maze[i][j] << " ";
		}
		out << endl;
	}
	return true;
}
int main()
{
	fstream f1("in.txt", ios::in);
	if (!f1.is_open())
	{
		cout << "Input File could not be opened successfully\n";
		exit(0);
	}
	int size;
	f1 >> size;
	Position start, end;
	int x_ind, y_ind;
	f1 >> x_ind;
	f1 >> y_ind;
	start.row = x_ind;
	start.col = y_ind;
	f1 >> x_ind;
	f1 >> y_ind;
	end.row = x_ind;
	end.col = y_ind;
	char inp;
	char** matrix = new char*[size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new char[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			f1 >> inp;
			matrix[i][j] = inp;
		}
	}
	f1.close();
	f1.open("out.txt", ios::out);
	if (!f1.is_open())
	{
		cout << "Output File could not be created successfully\n";
		exit(0);
	}
	if (findPath(matrix, size, start, end, f1))
	{
		cout << "The path has been displayed in the output file..." << endl;
	}
	else
	{
		cout << "No path found!" << endl;
	}
	return 0;
}
