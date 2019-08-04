#include "game_object.h"
#include <iostream>
GameObject::GameObject()
{
}

GameObject::GameObject(CubeType type)
{
	//footprint_.resize(fprintRows, std::vector<bool>(fprintCols, false));

	type_ = type;
	x_ = 0;
	y_ = 0;
	rotation_ = 0;

	makeFootprint();
}
void GameObject::RotateCW() {
	if (rotation_ == 0) rotation_ = 3;
	else --rotation_;
	//rotateFootprint();
}

void GameObject::RotateCCW() {
	if (rotation_ == 3) rotation_ = 0;
	else ++rotation_;
	rotateFootprintCCW();
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

		footprint_.resize(2, std::vector<bool>(2, false));

		footprint_[0][0] = true;
		footprint_[0][1] = true;
		footprint_[1][0] = true;
		footprint_[1][1] = true;
		break;
	case L:

		footprint_.resize(3, std::vector<bool>(3, false));

		footprint_[0][0] = true;
		footprint_[1][0] = true;
		footprint_[2][0] = true;
		footprint_[2][1] = true;
		break;
	case ReverseL:

		footprint_.resize(3, std::vector<bool>(3, false));

		footprint_[0][2] = true;
		footprint_[1][2] = true;
		footprint_[2][2] = true;
		footprint_[2][1] = true;
		break;
	case S:
		footprint_.resize(2, std::vector<bool>(3, false));
		footprint_[0][1] = true;
		footprint_[0][2] = true;
		footprint_[1][0] = true;
		footprint_[1][1] = true;
		break;
	case ReverseS:

		footprint_.resize(2, std::vector<bool>(3, false));
		footprint_[0][0] = true;
		footprint_[0][1] = true;
		footprint_[1][1] = true;
		footprint_[1][2] = true;
		break;
	case T:

		footprint_.resize(3, std::vector<bool>(3, false));
		footprint_[0][1] = true;
		footprint_[1][0] = true;
		footprint_[1][1] = true;
		footprint_[1][2] = true;
		break;
	case Line:
		footprint_.resize(4, std::vector<bool>(3, false));

		footprint_[0][1] = true;
		footprint_[1][1] = true;
		footprint_[2][1] = true;
		footprint_[3][1] = true;
		break;

	}

}

void GameObject::rotateFootprintCCW() {

	std::vector<std::vector<bool>> tempArr;
	tempArr.resize(footprint_[0].size(), std::vector<bool>(footprint_.size(), false));

	for (int x = 0; x < footprint_.size(); x++) {
		for (int y = 0; y < footprint_[0].size(); y++) {
			if (footprint_[x][y] == true) {
				/*if (rotation_ % 2 == 0) {
					tempArr[y][x] = footprint_[x][y];
				}
				else {
					tempArr[(fprintRows - 1) - y - 1][(fprintCols - 1) - x - 1] = footprint_[x][y];
				}*/
				tempArr[y][(tempArr[0].size() - 1) - x] = footprint_[x][y];
			}
		}
	}

	//for (int x = 0; x < fprintRows; x++) {
	//	for (int y = 0; y < fprintCols; y++) {
	//		footprint_[x][y] = tempArr[x][y];
	//	}
	//}

	footprint_ = tempArr;
}

int GameObject::index(int x, int y) {
	return x + (footprint_.size() * y);
}

int GameObject::getFootprintBoundaryX(lrDirection dir) {
	int firstTruePosX = -1;
	if (dir == lrDirection::dRight) {

		for (int y = footprint_.size() - 1; y >= 0; --y) {
			int tempRes = 0;
			bool trueFound = false;
			for (int x = footprint_[0].size() - 1; x >= 0 && !trueFound; --x) {
				if (footprint_[y][x] == true) {
					tempRes = x;
					trueFound = true;
				}
			}
			if (tempRes > firstTruePosX) {
				firstTruePosX = tempRes;
			}
		}

	}
	else if (dir == lrDirection::dLeft) {
		firstTruePosX = footprint_[0].size();
		for (int y = 0; y <= footprint_.size() - 1; ++y) {
			int tempRes = footprint_[0].size();
			bool trueFound = false;
			for (int x = 0; x <= footprint_[0].size() - 1 && !trueFound; ++x) {
				if (footprint_[y][x] == true) {
					tempRes = x;
					trueFound = true;
				}
			}
			if (tempRes < firstTruePosX) {
				firstTruePosX = tempRes;
			}
		}

	}

	return firstTruePosX;

}

int GameObject::getFootprintBoundaryY(tbDirection dir) {

	if (dir == tbDirection::dBottom) {
		int firstTruePosY = -1;
		bool trueFound = false;
		for (int y = footprint_.size() - 1; y >= 0 && !trueFound; --y) {
			int tempRes = -1;

			for (int x = footprint_[0].size() - 1; x >= 0 && !trueFound; --x) {
				if (footprint_[y][x] == true) {
					tempRes = y;
					trueFound = true;
				}
			}
			if (tempRes > firstTruePosY) {
				firstTruePosY = tempRes;
			}
		}
		return firstTruePosY;
	}
	if (dir == tbDirection::dTop) {
		int firstTruePosY = footprint_.size();
		bool trueFound = false;
		for (int y = 0; y <= footprint_.size() - 1 && !trueFound; ++y) {
			int tempRes = footprint_.size();
			for (int x = 0; x <= footprint_[0].size() - 1 && !trueFound; ++x) {
				if (footprint_[y][x] == true) {
					tempRes = y;
					trueFound = true;
				}
			}
			if (tempRes < firstTruePosY) {
				firstTruePosY = tempRes;
			}
		}
		return firstTruePosY;
	}
}

void GameObject::setX(int x) {
	x_ = x;
}

void GameObject::setY(int y) {
	y_ = y;
}
