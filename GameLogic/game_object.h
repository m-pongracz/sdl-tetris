#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <utility>;
#include <vector>;

enum lrDirection { dLeft, dRight };
enum tbDirection { dTop, dBottom };
enum CubeType { Cube, Line, L, ReverseL, S, ReverseS, T };

class GameObject
{

public:
	GameObject();
	static const int fprintRows = 4;
	static const int fprintCols = 4;
	static const int fprintSize = fprintRows * fprintCols;
	GameObject(CubeType type);
	auto Type() const& -> const CubeType& { return type_; };
	auto Type() & -> const CubeType& { return type_; };
	//auto Type() && -> const CubeType&& { return std::move(type_); };
	auto X() const& -> const int& { return x_; };
	auto X() & -> const int& { return x_; };
	auto Y() const& -> const int& { return y_; };
	auto Y() & -> const int& { return y_; };
	auto Rotation() const& -> const int& { return rotation_; };
	auto Rotation() & -> const int& { return rotation_; };
	auto Footprint() const& -> const std::vector<std::vector<bool>>& { return footprint_; };
	auto Footprint() & -> const std::vector<std::vector<bool>>& { return footprint_; };
	void RotateCW();
	void RotateCCW();
	void MoveL();
	void MoveR();
	void MoveD();
	int index(int x, int y);
	int getFootprintBoundaryX(lrDirection dir);
	int getFootprintBoundaryY(tbDirection dir);
	void setX(int x);
	void setY(int y);
private:
	std::vector<std::vector<bool>> footprint_;
	CubeType type_;
	int x_;
	int y_;
	int rotation_;
	void makeFootprint();
	void rotateFootprint();
};

#endif