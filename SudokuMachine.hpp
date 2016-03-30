#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class SudokuMachine
{
	public:
		void giveQuestion();
		void readIn();
		int solve();
		
		void printSudokuBoard();

	private:
		int sudokuBoard[9][9];//讀題跟解題所用的板子

		int justPicked[81];//紀錄在第幾次遞迴，嘗試過哪個數字
		int recursiveTimes;//紀錄第幾次遞迴
		bool justFailed;//如果上一次失敗了，跳出遞迴重作的話

		const int rawBoard[9][9]={{8,0,0,0,0,0,0,0,0},
                	   		  {0,0,3,6,0,0,0,0,0},
                        		  {0,7,0,0,9,0,2,0,0},
                      			  {0,5,0,0,0,7,0,0,0},
                      			  {0,0,0,0,4,5,7,0,0},
                        		  {0,0,0,1,0,0,0,3,0},
                        		  {0,0,1,0,0,0,0,6,8},
                        		  {0,0,8,5,0,0,0,1,0},
                        		  {0,9,0,0,0,0,4,0,0}};
		//給giveQuestion出題的樣板
		int swapBoard[9][9];
		//把rawBoard做變換之後，要暫存的板子

};


