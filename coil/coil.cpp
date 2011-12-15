#include "coil.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>

using namespace std;

Coil::Coil(int x, int y, string board) : X(x), Y(y)
{
    m_nTotalStep = 0;
    for (int i = 0; i < x; i++)
    {
        vector<int> v;
        for (int j = 0; j < y; j++)
        {
            if (board[j * X + i] == '.')
            {
                v.push_back(0);
                m_nTotalStep ++;
            }
            else
            {
                v.push_back(1);
            }
        }
        m_vBoard.push_back(v);
    }

	m_vBd = m_vBoard;
    PrintBoard();
    for (int j = 0; j < Y; j++)
    {
        for (int i = 0; i < X; i++)
        {
            if (m_vBd[i][j] == 0 && CountDirect(i, j) == 1)
                cout << "(" << i << ", " << j << ")" << endl;
        }
    }
}

void Coil::PrintBoard()
{
    for (int j = 0; j < Y; j++)
    {
        for (int i = 0; i < X; i++)
        {
            cout << m_vBd[i][j] << " ";
        }
        cout << endl;
    }
}

void Coil::FindPath(const int cx, const int cy, string& solution)
{
    m_vBd = m_vBoard; // Reset board

	if (!GoodSquare(cx, cy))
	{
		return;
	}
    //cout << "Begin " << cx << ", " << cy << endl;

	for (int i = 0; i < 4; ++i)
	{
        if (!GoodSquare(cx + OFF_SETS[i][0], cy + OFF_SETS[i][1]))
        {
            continue;
        }
        m_stackPath.push(BranchPoint(cx, cy, i, "", 1, m_vBoard));
	}

	int max_fill = 1;
	BranchPoint bp;
    while (true)
    {
		string path  = "";
        int x = cx;
        int y = cy;
        int nFilled = 1;
        int direction;
        int offx, offy;

        if (m_stackPath.empty())
        {
            //cout << " No solution . " << endl;
            return;
        }
        else
        {
            bp = m_stackPath.top();
            m_stackPath.pop();
            x = bp.x;
            y = bp.y;
            direction = bp.direction;
            path = bp.path;
            nFilled = bp.nFilled;
            m_vBd = bp.bd;
        }

        while (true)
        {
            usleep(1000);
            offx = OFF_SETS[direction][0];
            offy = OFF_SETS[direction][1];

            if (!GoodSquare(x + offx, y + offy))
            {
                break;
            }

            path += OFF_NAMES[direction];
            m_vBd[x][y] = 2;

            // Move toward for one direction, until hit a wall
            // One step per loop
            while (true)
            {
                if (!GoodSquare(x + offx, y + offy))
                    break;

                x += offx; y += offy;
                nFilled += 1;
                m_vBd[x][y] = 2;

                if (nFilled > max_fill)
                {
                    max_fill = nFilled;
                }

                if (nFilled == m_nTotalStep)
                {
                    // Solution Found!
                    solution = path;
                    return; 
                }
            }

            if(HaveMoreSingleDirectionNode())
            {
                //cout << "HaveMoreSingleDirectionNode ..." << endl;
                break;
            }

            if(!CheckOneArea())
            {
                //cout << "Have Two Areas." << endl;
                break;
            }

            bool bTwoDirection = HaveTwoDirect(x, y, direction);
            if (bTwoDirection)
            {
                m_stackPath.push(BranchPoint(x, y, (direction + 2) % 4, path, nFilled, m_vBd));
            }
        }
    }
}

int Coil::CountDirect(const int x, const int y)
{
    int count = 0;
    if (GoodSquare(x, y + 1))
        count ++;
    if (GoodSquare(x, y - 1))
        count ++;
    if (GoodSquare(x - 1, y))
        count ++;
    if (GoodSquare(x + 1, y))
        count ++;
	return count;
}

bool Coil::HaveTwoDirect(const int x, const int y, int & direction)
{
    int count = 0;
    // left or right
    if (direction % 2 == 0)
    {
        // the lower point
        if (GoodSquare(x, y + 1))
        {
            count ++;
            direction = 1; // Down
        }

        // the upper point
        if (GoodSquare(x, y - 1))
        {
            count ++;
            direction = 3; // up
        }
    }
    else // up or down
    {
        if (GoodSquare(x - 1, y))
        {
            count ++;
            direction = 0; // left
        }

        if (GoodSquare(x + 1, y))
        {
            count ++;
            direction = 2; // right
        }
    }

	return count == 2;
}

bool Coil::GoodSquare(const int x, const int y)
{
    if (x < 0 || y < 0 || x >= X || y >= Y)
    {
        return false;
    }

    return m_vBd[x][y] == 0;
}

bool Coil::GoodSquareCheck(const int x, const int y)
{
    if (x < 0 || y < 0 || x >= X || y >= Y)
    {
        return false;
    }
    return m_vCheck[x][y] == 0;
}

void Coil::FloodFill(const int x, const int y)
{
	if (m_vCheck[x][y] != 0)
	{
		return;
	}

    // make sure 7 is special.
	if (m_vCheck[x][y] == 7)
	{
		return;
	}


    m_vCheck[x][y] = 7;

    int nx = x - 1;
    if (GoodSquareCheck(nx, y))
	{
		FloodFill(nx, y);
	}

    nx = x + 1;
    if (GoodSquareCheck(nx, y))
	{
		FloodFill(nx, y);
	}

    int ny = y + 1;
	if (GoodSquareCheck(x, ny))
	{
		FloodFill(x, ny);
	}

    ny = y - 1;
	if (GoodSquareCheck(x, ny))
	{
		FloodFill(x, ny);
	}
}

bool Coil::HaveMoreZero()
{
	for (int j = 0; j < Y; j++)
    {
        for (int i = 0; i < X; i++)
        {
            if (m_vCheck[i][j] == 0)
			{
				return true;
			}
        }
    }

	return false;
}

bool Coil::HaveMoreSingleDirectionNode()
{
    int count = 0;
	for (int j = 0; j < Y; j++)
    {
        for (int i = 0; i < X; i++)
        {
            if (m_vBd[i][j] == 0)
			{
				if (CountDirect(i, j) == 1)
                {
                    if (++count > 2)
                        return true;
                }
			}
        }
    }
    return false;
}

bool Coil::CheckOneArea()
{
	m_vCheck = m_vBd;

	for (int j = 0; j < Y; j++)
    {
        for (int i = 0; i < X; i++)
        {
            if (m_vBd[i][j] == 0)
			{
				FloodFill(i, j);
				return !HaveMoreZero();
			}
        }
    }

	return true;
}
