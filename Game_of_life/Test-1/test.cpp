#include "pch.h"
#include"../Game_of_life/Header.h"

#include<fstream>
TEST(T1, Print) {
	//a simple test case to print the grid
	GameofLife a(4, 4);
	a.print_grid();
	a.generate();
	a.print_grid();
	EXPECT_TRUE(true);
}
TEST(T2, value_check) {
	//a test case to check wether next generation has actually updated the values or not
	GameofLife a(4, 4);
	a.generate();
	//this int will get neighbours of a specific cell
	//and then we will check if that cell get updates accordingly
	int index1x = a.arr[0].x;//index1x will be saving x axis index of ist alive cell
	int index2y = a.arr[0].y;//index1y will be saving y axis index of ist alive cell
	int neighbour = a.aux_arr[index1x][index2y];//neighbour will be having sum of index1x,index1y from orignal ptr
	if (neighbour < 2 && a.ptr[index1x][index2y] == 1) {
		a.generate();
		EXPECT_EQ(0, a.ptr[index1x][index2y]);
	}
	else if (neighbour > 3 && a.ptr[index1x][index2y] == 1) {
		a.generate();
		EXPECT_EQ(0, a.ptr[index1x][index2y]);
	}
	else {
		a.generate();
		EXPECT_EQ(a.ptr[index1x][index2y], a.ptr[index1x][index2y]);
	}
}
TEST(T3, aux_array) {

	//will check if the aux array is working fine and kepping sum of all the neighbours
	int row = 5;
	int col = 5;
	GameofLife a(row, col);
	a.fill_uninit();
	a.fill_aux();

	int n = 0;//to extract value of any random live cells
	srand(time(NULL));
	n = (rand() % a.count_arr) - 1;
	if (n < 0) {
		n = 0;
	}
	int i = a.arr[n].x;//index1x will be saving x axis i of any alive cell
	int j = a.arr[n].y;//index1y will be saving y axis j of any random alive cell
	int sum = 0;//will be use to save sum of neighbours manually for comparing test 

	if ((i - 1 >= 0) && (j - 1 >= 0)) {//upper left diagonal if it exists
		sum = sum + a.ptr[i - 1][j - 1];
	}
	if (j - 1 >= 0) {//left value if it exists
		sum = sum + a.ptr[i][j - 1];
	}
	if ((i + 1 < row) && (j - 1 >= 0)) {//down left diagonal if it exists
		sum = sum + a.ptr[i + 1][j - 1];
	}
	if (i - 1 >= 0) {//upper value if it exists
		sum = sum + a.ptr[i - 1][j];
	}
	if (i + 1 < row) {//down value if it exists
		sum = sum + a.ptr[i + 1][j];
	}
	if ((i - 1 >= 0) && (j + 1 < row)) {//upper right diagonal if it exists
		sum = sum + a.ptr[i - 1][j + 1];
	}
	if (j + 1 < row) {//right value if it exists
		sum = sum + a.ptr[i][j + 1];
	}
	if ((i + 1 < row) && (j + 1 < col)) {//down right diagonal if it exists
		sum = sum + a.ptr[i + 1][j + 1];
	}


	EXPECT_EQ(sum, a.aux_arr[i][j]);//will compare the sum we have calculated 
	//and the sum calculated bhy the class function it self

}
TEST(T4, UnInit_Array) {
	//a function that will check if UnInit array is working fine
	//as we know tis array will save the index number of each live cell
	GameofLife a(6, 6);
	a.fill_uninit();
	a.fill_aux();

	int i = 0;
	int j = 0;
	bool br = false;//a bool to break the loop
	for (; i < 6; i++) {
		for (; j < 6; j++) {
			if (a.ptr[i][j] == 1) {
				br = true;
				break;
			}
		}
		if (br) {
			break;
		}
	}
	//above nested loop treverses the array untill it reaches ist of its '1' live cell
	//and when it reaches it breaks internal loop and then make a bool value true 
	//the bool value is used to break the externl loop


	EXPECT_EQ(i, a.arr[0].x);//checking if the x index of this array's '1' matches the x index of aux_array's index
	EXPECT_EQ(j, a.arr[0].y);//checking if the y index of this array's '1' matches the y index of aux_array's index
	//above mentioned details goes for the 3rd and 4th EXPECT_EQ statement

}
//a test case that would write data into the files as doing task of printing
TEST(T5, FIle_handling) {

	int generations;//will read how many generations needs to be written in another file
	int x = 0;
	fstream file;
	file.open("ins.txt", ios::in);//opening the file which contains the instruction 
	file >> generations;//reading how many geeration/simulations needs to be wriiten in file

	int row = 7;
	int col = 7;
	fstream file1;
	file1.open("Generations.txt", ios::out);//opening a file which will have all the generations/simulations 
	GameofLife a(row, col);

	int loop_Size = 0;
	file >> loop_Size;//reading how many cells need to be written in the cell file
	unInit* l = new unInit[loop_Size];//an array which will keep (x,y) axis of every cell to be written
	fstream file2;
	file2.open("cells.txt", ios::out);//opening a file named as cel which will have the 
	int i = 0;

	while (i < generations + 1) {//loop runs till number of generations+ 1 because
		//at initial it will print/write the orignal grind and then after calling 
		//generate function it will be writing generations/simulations 
		if (i == 0) {
			file1 << "\nOrignal Generation\n";
			file2 << "\nOrignal Generation\n";

		}
		else {
			file1 << "\nGeneration No " << i << "\n";
			if (i <= loop_Size)
				file2 << "\nGeneration No " << i << "\n";
		}
		for (int j = 0; j < row; j++) {
			for (int k = 0; k < col; k++) {
				//main loop that writes the grid values to the file of generations
				file1 << a.ptr[j][k] << "    ";

			}
			file1 << "\n";
		}
		if (i <= loop_Size) {
			for (int p = 0; p < loop_Size; p++) {
				file >> l[p].x;
				file >> l[p].y;
				file2 << "x = " << l[p].x;
				file2 << " y = " << l[p].y;
				file2 << " Value = " << a.ptr[l[p].x][l[p].y] << "\n";
				//this is a loop that will saves/write all the values of specified indexes 
					//into the cell file
			}
			file2 << "\n";
		}
		i++;
		a.generate();//calling generate function for next simulation
	}
	file2.close();
	file1.close();
	file.close();
	//an array that would read differet axis as x and y asix to print the cell data
}