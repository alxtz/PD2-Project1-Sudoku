#include"SudokuMachine.hpp"

/*
	giveQustion();預定功能，用rawBoard[9][9]做一些變換，
	然後輸出一份數獨題目到Question.txt
*/
void SudokuMachine::giveQuestion()
{
	//之後才會有打亂rawBoard存入swapBoard暫存的功能
	//所以目前swapBoard就是rawBoard
	
	for(int i=0; i<=8; i++)
	{
		for(int j=0; j<=8; j++)
		{
			swapBoard[i][j]=rawBoard[i][j];
		}
	}

	int num;

	ofstream writeFile("Question.txt",ios::out);
	if(!writeFile)
	{
		cerr<<"Failed to create Question.txt"<<endl;
		exit(1);
	}
	
	for(int i=0; i<=8; i++)
	{
		for(int j=0; j<=8; j++)
		{
			writeFile<<swapBoard[i][j];
		}
		writeFile<<"\n";
	}
	writeFile.close();	
}

void SudokuMachine::readIn()
{
        char ch;
        fstream sudokuFile;
        sudokuFile.open("Question.txt",ios::in);

        if(!sudokuFile)
        {
                cout<<"Fail to read in file Question.txt"<<endl;
                exit(1);
        }

        for(int i=0; i<=8; i++)
        {
                for(int j=0; j<=8; j++)
                {
                        sudokuFile>>ch;
                        sudokuBoard[i][j]=ch-'0';
                        cout<<sudokuBoard[i][j];
                }
                cout<<endl;
        }
	recursiveTimes=0;//因為接下來就要解題了，所以先把遞迴次數初始化成0
}

int SudokuMachine::solve()
{
	//cout<<"================================"<<endl;

	if(recursiveTimes==60)
	{
		exit(0);
	}
	
	justFailed=false;

	//cout<<"第"<<recursiveTimes<<"次遞迴"<<endl;
	//printSudokuBoard();

	bool candidate[10];//候選數的陣列，1~9代表1~9，0我們不使用
	
	//cout<<"初始化candidate陣列"<<endl;

	for(int i=1; i<=9; i++)
	{
		candidate[i]=false;
	}		

	for(int i=0; i<=8; i++)//代表row
	{
		for(int j=0; j<=8; j++)//代表column
		{
			if(sudokuBoard[i][j]==0)
			{

				//cout<<"找到一個待填空格("<<i<<"'"<<j<<")"<<endl;

				//如果找到一個空格，就開始確認候選數
				for(int k=0; k<=8; k++)//在同一row上做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        if(sudokuBoard[i][k]!=0)
                                        {
                                                candidate[sudokuBoard[i][k]]=true;
                                        }
                                }
				
				for(int k=0; k<=8; k++)//在同一column上做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        if(sudokuBoard[k][j]!=0)
                                        {
                                                candidate[sudokuBoard[k][j]]=true;
                                        }
                                }

				for(int k=(i-i%3); k<=((i-i%3)+2); k++)//在所在的cell上面做搜尋，如果找到某數字，candidate上就寫true
                                {
                                        for(int l=(j-j%3); l<=((j-j%3)+2); l++)
                                        {
                                                if(sudokuBoard[k][l]!=0)
                                                {
                                                        candidate[sudokuBoard[k][l]]=true;
                                                }
                                        }
                                }

				//cout<<"輸出candidate陣列檢查";
				
				/*
				for(int k=1; k<=9; k++)
				{
					cout<<candidate[k];	
				}
				cout<<endl;
				*/		
				
                                LastRecursiveFailed:
				
				if(justFailed==true)
				{

					//cout<<"剛剛失敗了"<<endl;

					candidate[justPicked[recursiveTimes]]=true;
				}
				
				
				int countCandidate;
				countCandidate=0;
				for(int k=1; k<=9; k++)
				{
					if(candidate[k]==true)
					{
						countCandidate++;
					}
				}
				if(countCandidate==9)//如果9個數字全都存在了，代表該題可能無解或是之前填錯
				{

					//cout<<"發現矛盾"<<endl;

					sudokuBoard[i][j]=0;
					return -1;
				}
				
				
				//cout<<"現在開始找一個測試數填入"<<endl;

				for(int k=1; k<=9; k++)
				{

					//cout<<"進入迴圈第"<<k<<"次"<<endl;

					if(candidate[k]!=true)//如果某號候選數，還沒出現的話
					{
						sudokuBoard[i][j]=k;//我們就試著把該格填上其中一個候選數
						
						//cout<<"試著在"<<i<<","<<j<<"填入"<<k<<endl;

						justPicked[recursiveTimes]=k;//我們在第幾次遞迴，測試了某個數字
						justFailed=false;
						if(i==8&&j==8)
						{
							return 1;
						}
					}else
					{
						continue;
					}


					/*
					我們填完一個測試數之後，就在執行下一次
					如果下一次return 1的話，代表出現矛盾，這邊我們就要把剛剛挑的數字( justPicked[recursiveTimes] )
					在candidate[]裡面變成true，不讓我們填他，並再次執行當次的遞迴
					*/
					recursiveTimes++;
					int result;
					result=solve();

					//cout<<"solve執行完畢"<<endl;
					//cout<<"result目前為"<<result<<endl;

					if(result==-1)
					{

						//cout<<"接到矛盾消息，該重新執行當次迴圈"<<endl;

						recursiveTimes--;
						justFailed=true;

						//cout<<"更新justFailed為true"<<endl;

						goto LastRecursiveFailed;	
					}
					else if(result==1)
					{
						return 1;
					}					
				}
			}	
		}
	}
}



void SudokuMachine::printSudokuBoard()
{
        for(int i=0; i<=8; i++)
        {
                for(int j=0; j<=8; j++)
                {
                        cout<<sudokuBoard[i][j];
                }
                cout<<endl;
        }

}
























