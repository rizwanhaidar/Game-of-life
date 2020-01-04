#pragma once
#include<iostream>
#include<cstdlib>
#include<time.h>

using namespace std;
//A class whose array will be declared later which would keep track of live cells 
class unInit
{
public:
	int x = 0;//to keep track of x co-ordinate
	int y = 0;//to keep track of y co-ordinate
	//default constructor
	unInit() {
		x = 0;
		y = 0;
	}
	//default constructor with arguments
	unInit(int x_, int y_) {
		x = x_;
		y = y_;
	}
	//set values
	void set(int x_, int y_) {
		x = x_;
		y = y_;
	}
	//print values
	void show() {
		cout << x << "    " << y << "    ";

	}

};
//A class for the implementation of Game Of Life
class GameofLife {

public:
	int** ptr;//a 2-d pointer for sake of a grid
	int row = 0, col = 0;//number of rows and number of columns of the grid
	int** aux_arr;//will keep the track of sum of neighbours of each cell(index)
	unInit* arr;//will keep track of living cells on the grid
	int count_arr = 0;//a counter to keep track how many living cells exist or to which point next 
	// living cell would be added


	//default constructor
	GameofLife(int row_, int col_) {
		row = row_;
		col = col_;
		//memory allocation to 2 d array's size
		arr = new unInit[row * col];
		ptr = new int* [row];
		aux_arr = new int* [row];
		for (int i = 0; i < row; i++) {
			ptr[i] = new int[col];
			aux_arr[i] = new int[col];
		}

		int randNum = 0;
		srand(time(NULL));
		//populating array with random values.
		for (int i = 0; i < row; i++) {

			for (int j = 0; j < col; j++) {

				randNum = rand() % 2;
				ptr[i][j] = randNum;

			}
		}

	}

	//will print the grid after it is called by the user
	void print_grid() {
		cout << "\n\n";
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << ptr[i][j] << "     ";
			}
			cout << "\n";
		}
	}

	//filling the unint array with the x and y co=ordinates of live cells
	void fill_uninit() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (ptr[i][j] == 1) {//checking if a cell is live put its co-ordinates in one d array
					arr[count_arr].set(i, j);
					count_arr++;//and incrrease the current size of the array which keeps the track of tis thing
				}
			}
		}
	}


	//to print th coordinates of uninit array
	void print_uninit() {
		for (int i = 0; i < count_arr; i++) {
			arr[i].show();
			if (i % 5 == 0 && i != 0) {
				cout << "\n";
			}
			else {
				cout << "    ";
			}

		}
	}

	//fill the aux-array
	void fill_aux() {
		//ist initialize aux array with 0
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				aux_arr[i][j] = 0;
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {

				if ((i - 1 >= 0) && (j - 1 >= 0)) {//upper left diagonal if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i - 1][j - 1];
				}
				if (j - 1 >= 0) {//left value if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i][j - 1];
				}
				if ((i + 1 < row) && (j - 1 >= 0)) {//down left diagonal if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i + 1][j - 1];
				}
				if (i - 1 >= 0) {//upper value if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i - 1][j];
				}
				if (i + 1 < row) {//down value if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i + 1][j];
				}
				if ((i - 1 >= 0) && (j + 1 < row)) {//upper right diagonal if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i - 1][j + 1];
				}
				if (j + 1 < row) {//right value if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i][j + 1];
				}
				if ((i + 1 < row) && (j + 1 < col)) {//down right diagonal if it exists
					aux_arr[i][j] = aux_arr[i][j] + ptr[i + 1][j + 1];
				}
			}
		}
	}
	//will print the values of aux_arr
	void show_aux_array() {
		cout << "\n";
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << aux_arr[i][j] << "   ";
			}
			cout << "\n";
		}
	}

	//will generate the new simulation 
	//will check condition on every cell and update its value
	void generate() {

		fill_uninit();
		fill_aux();
		count_arr = 0;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if ((ptr[i][j] == 1) && (aux_arr[i][j] < 2)) ptr[i][j] = 0;           // death by Loneliness
				else if ((ptr[i][j] == 1) && (aux_arr[i][j] > 3)) ptr[i][j] = 0;           // death by Overpopulation
				else if ((ptr[i][j] == 0) && (aux_arr[i][j] == 3)) ptr[i][j] = 1;           //Birth as per requirements 
				else                                            ptr[i][j] = ptr[i][j];  // Status will remain the smae
			}
		}

	}
	//a distructor that will delete the memory allocated to the pointers
	virtual ~GameofLife()
	{
		for (int i = 0; i < row; i++)
		{
			delete[] ptr[i];//main grid
			delete[] aux_arr[i];//array to kep the track of sum
		}

		delete[] ptr;
		delete[]arr;
		delete[] aux_arr;


	}

};