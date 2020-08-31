#include "CarsManagment.h"

int CarsManagment::_numOfCars = 0;
CarsManagment::CarsManagment(Cell** &matrix, int rows,int cols)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bool isFirstCellHorizontal = (matrix[i][j].getHorizontalSt() != nullptr) && (matrix[i][j].getHorizontalCellNumber() == 0);
			bool cellhasCarHorizontal = matrix[i][j].getHorizontalCar() != nullptr;
			bool isFirstCellVertical = (matrix[i][j].getVerticalSt() != nullptr) && (matrix[i][j].getVerticalCellNumber() == 0);
			bool cellhasCarVertical = matrix[i][j].getVerticalCar() != nullptr;
			bool isJunction = matrix[i][j].getIsJunction();

			if (isFirstCellHorizontal && !cellhasCarHorizontal && !isJunction){
				int x = matrix[i][j].getHorizontalSt()->getX();
				int y = matrix[i][j].getHorizontalSt()->getY();
				int location = matrix[i][j].getHorizontalCellNumber();

				matrix[i][j].setHorizontalCar( new Car(x,y, location));

			}
			else if (isFirstCellVertical && !cellhasCarVertical && !isJunction) {
				int x = matrix[i][j].getVerticalSt()->getX();
				int y = matrix[i][j].getVerticalSt()->getY();
				int location = matrix[i][j].getVerticalCellNumber();
				matrix[i][j].setVerticalCar( new Car(x,y, location));
			}
		}
	}
}
