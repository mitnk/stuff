#ifndef COIL_H_INCLUDED
#define COIL_H_INCLUDED

#include <vector>
#include <string>
#include <map>
#include <stack>
#include <fstream>

using namespace std;

const int OFF_SETS[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const string OFF_NAMES = "LDRU";
const int SPECIAL_DIR = 77;

struct BranchPoint
{
    int x;
    int y;
    int direction;
    string path;
    int nFilled;
    vector< vector<int> > bd;

    BranchPoint(int nx, int ny, int ndir, string spath, int nfill, vector< vector<int> > vbd)
    {
        x = nx;
        y = ny;
        direction = ndir;
        path = spath;
        nFilled = nfill;
        bd = vbd;
    }

    BranchPoint()
    {
    }
};

class Coil
{
public:
    Coil(int, int, string);
    void ShowInfo();
    void FindPath(const int x, const int y, string& solution);

protected:
    bool GoodSquare(const int x, const int y);

    bool HaveTwoDirect(const int x, const int y, int & direction, bool& flag);

	void GetGoodDirection(const int x, const int y);
    void PrintBoard();

	bool CheckOneArea();
    bool HaveMoreSingleDirectionNode();
    int CountDirect(const int x, const int y);
    bool HaveTwoSameDirect(const int x, const int y);
	bool HaveMoreZero();

	bool GoodSquareCheck(const int x, const int y);

	void FloodFill(const int x, const int y);

private:
    const int X;
    const int Y;

    int m_nTotalStep;
    int m_nStartDir; // the start direction of each time.

    int m_nStartX;
    int m_nStartY;

    vector< vector<int> > m_vBoard;
    vector< vector<int> > m_vBd;
	vector< vector<int> > m_vCheck;

    stack< BranchPoint > m_stackPath;
    string m_formerPath;
};

#endif // COIL_H_INCLUDED
