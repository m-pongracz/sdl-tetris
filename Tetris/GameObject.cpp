#include "game_object.h"

GameObject::GameObject()
{
}

GameObject::GameObject(CubeType type)
{
	for (int x = 0; x < sizeof footprint_; ++x) {
		footprint_[x] = false;
	}
	type_ = type;
	x_ = 4;
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
	if (x_ > 0) --x_;
}
void GameObject::MoveR() {
	if (x_ < 8) ++x_;
}
void GameObject::MoveD() {
	if (y_ < 12) ++y_;
}

void GameObject::makeFootprint() {
	switch (type_) {
	case Cube:
		footprint_[index(0, 0)] = true;
		footprint_[index(1, 0)] = true;
		footprint_[index(1, 0)] = true;
		footprint_[index(1, 1)] = true;
		break;
	case L:
		footprint_[index(0, 0)] = true;
		footprint_[index(0, 1)] = true;
		footprint_[index(0, 2)] = true;
		footprint_[index(1, 2)] = true;
		break;
	case ReverseL:
		footprint_[index(0, 1)] = true;
		footprint_[index(1, 1)] = true;
		footprint_[index(2, 1)] = true;
		footprint_[index(3, 1)] = true;
		footprint_[index(3, 0)] = true;
		break;
	case S:
		footprint_[index(0, 1)] = true;
		footprint_[index(0, 2)] = true;
		footprint_[index(1, 0)] = true;
		footprint_[index(1, 1)] = true;
		break;
	case ReverseS:
		footprint_[index(0, 0)] = true;
		footprint_[index(0, 1)] = true;
		footprint_[index(1, 1)] = true;
		footprint_[index(1, 2)] = true;
		break;
	case T:
		footprint_[index(0, 1)] = true;
		footprint_[index(1, 0)] = true;
		footprint_[index(1, 1)] = true;
		footprint_[index(1, 2)] = true;
		break;
	}
}

void GameObject::rotateFootprint() {
	const int size = sizeof footprint_;

	int tempArr[size];

	/*for (int x = 0; x < lenX; x++) {
		for (int y = 0; lenY; y++) {
			tempArr[x][y] = footprint_[x][y];
		}
	}

	for (int x = 0; x < lenX; x++) {
		for (int y = 0; lenY; y++) {
			footprint_[x][y] = tempArr[y][x];
		}
	}*/

	for (int x = 0; x < size; x++) {
		tempArr[x] = footprint_[x];
	}

	for (int x = 0; x < fprintRows; x++) {
		for (int y = 0; y < fprintCols; y++) {
			footprint_[index(x, y)] = tempArr[index(y, x)];
		}
	}
}

int GameObject::index(int x, int y) {
	return x + (fprintRows * y);
}

//const bool* GameObject::Footprint() const {
//	return footprint_;
//}