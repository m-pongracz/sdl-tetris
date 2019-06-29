#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <utility>;

enum CubeType { Cube, Line, L, ReverseL, S, ReverseS, T };

class GameObject
{

public:
	GameObject();
	static const int fprintRows = 4;
	static const int fprintCols = 4;
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
	bool footprint_[fprintRows*fprintCols];
	//const bool* Footprint() const;
	void RotateCW();
	void RotateCCW();
	void MoveL();
	void MoveR();
	void MoveD();
	static int index(int x, int y);
private:
	CubeType type_;
	int x_;
	int y_;
	int rotation_;
	void makeFootprint();
	void rotateFootprint();	
};

#endif