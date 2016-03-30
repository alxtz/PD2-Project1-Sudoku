#include <iostream>
#include <fstream>
#include <cstdlib>
#include "SudokuMachine.hpp"

using namespace std;

int main()
{
	SudokuMachine machine1;
	
	cout<<"開始輸出rawBoard"<<endl;
	machine1.giveQuestion();	
	cout<<"========="<<endl;	

	
	machine1.readIn();
	cout<<"結束讀檔"<<endl;
	machine1.solve();
	cout<<"結束解題"<<endl;
	machine1.printSudokuBoard();
	cout<<"結束打印"<<endl;
	
	return 0;
}
