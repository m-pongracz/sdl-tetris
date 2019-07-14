#include "game_object.h"
#include <iostream>
GameObject::GameObject()
{
}

GameObject::GameObject(CubeType type)
{
	footprint_.resize(fprintRows, std::vector<bool>(fprintCols, false));

	type_ = type;
	x_ = 0;
	y_ = 0;
	rotation_ = 0;

	makeFootprint();
}
void GameObject::RotateCW() {
	++rotation_;
	if (rotation_ == 4) rotation_ = 0;
	rotateFootprint();
}

void GameObject::RotateCCW() {
	--rotation_;
	if (rotation_ == 0) rotation_ = 4;
	rotateFootprint();
}
void GameObject::MoveL() {
	--x_;
}
void GameObject::MoveR() {
	++x_;
}
void GameObject::MoveD() {
	++y_;
}

void GameObject::makeFootprint() {
	switch (type_) {
	case Cube:
		footprint_[0][0] = true;
		footprint_[0][1] = true;
		footprint_[1][0] = true;
		footprint_[1][1] = true;
		break;
	case L:
		footprint_[0][0] = true;
		footprint_[1][0] = true;
		footprint_[2][0] = true;
		footprint_[2][1] = true;
		break;
	case ReverseL:
		footprint_[0][1] = true;
		footprint_[1][1] = true;
		footprint_[2][1] = true;
		footprint_[2][0] = true;
		break;
	case S:
		footprint_[0][1] = true;
		footprint_[0][2] = true;
		footprint_[1][0] = true;
		footprint_[1][1] = true;
		break;
	case ReverseS:
		footprint_[0][0] = true;
		footprint_[0][1] = true;
		footprint_[1][1] = true;
		footprint_[1][2] = true;
		break;
	case T:
		footprint_[0][1] = true;
		footprint_[1][0] = true;
		footprint_[1][1] = true;
		footprint_[1][2] = true;
		break;
	case Line:
		footprint_[0][0] = true;
		footprint_[1][0] = true;
		footprint_[2][0] = true;
		footprint_[3][0] = true;
		break;

	}

}

void GameObject::rotateFootprint() {
	
	std::vector<std::vector<bool>> tempArr;
	tempArr.resize(fprintRows, std::vector<bool>(fprintCols, false));

	for (int x = 0; x < fprintRows; x++) {
		for (int y = 0; y < fprintCols; y++) {
			tempArr[x][y] = footprint_[x][y];
		}
	}

	for (int x = 0; x < fprintRows; x++) {
		for (int y = 0; y < fprintCols; y++) {
			footprint_[x][y] = tempArr[y][x];
		}
	}
}

int GameObject::index(int x, int y) {
	return x + (fprintRows * y);
}

int GameObject::getFootprintBoundaryX() {
	int firstTruePosX = -1;

	for (int x = GameObject::fprintCols - 1; x >= 0 && firstTruePosX == -1; --x) {
		for (int y = GameObject::fprintRows - 1; y >= 0 && firstTruePosX == -1; --y) {
			if (footprint_[y][x] == true) {
				firstTruePosX = x;
			}
		}
	}

	return firstTruePosX;
}

int GameObject::getFootprintBoundaryY() {
	int firstTruePosY = -1;

	for (int y = GameObject::fprintCols - 1; y >= 0 && firstTruePosY == -1; --y) {
		for (int x = GameObject::fprintRows - 1; x >= 0 && firstTruePosY == -1; --x) {
			if (footprint_[y][x] == true) {
				firstTruePosY = y;
			}
		}
	}

	return firstTruePosY;
}

void GameObject::setX(int x) {
	x_ = x;
}

void GameObject::setY(int y) {
	y_ = y;
}
