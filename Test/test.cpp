#include "pch.h"
#include "../GameLogic/game_object.h"
#include "../GameLogic/game.h"
#include "../GameLogic/game_logic.h"
#include <sstream>;

//FOOTPRINT REGION
TEST(FootprintSizeTest, XFromRight) {

	GameObject cube(CubeType::Cube);
	EXPECT_EQ(1, cube.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "cube from right success" << std::endl;

	GameObject line(CubeType::Line);
	EXPECT_EQ(1, line.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "line from right success" << std::endl;

	GameObject l(CubeType::L);
	EXPECT_EQ(1, l.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "l from right success" << std::endl;

	GameObject reverseL(CubeType::ReverseL);
	EXPECT_EQ(2, reverseL.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "reverseL from right success" << std::endl;

	GameObject s(CubeType::S);
	EXPECT_EQ(2, s.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "s from right success" << std::endl;

	GameObject reverseS(CubeType::ReverseS);
	EXPECT_EQ(2, reverseS.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "reverseS from right success" << std::endl;

	GameObject t(CubeType::T);
	EXPECT_EQ(2, t.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "t from right success" << std::endl;
}

TEST(FootprintSizeTest, XFromLeft) {

	GameObject cube(CubeType::Cube);
	EXPECT_EQ(0, cube.getFootprintBoundaryX(lrDirection::dLeft));
	std::cerr << "cube from left success" << std::endl;

	GameObject line(CubeType::Line);
	EXPECT_EQ(1, line.getFootprintBoundaryX(lrDirection::dLeft));
	std::cerr << "line from left success" << std::endl;

	GameObject l(CubeType::L);
	EXPECT_EQ(0, l.getFootprintBoundaryX(lrDirection::dLeft));
	std::cerr << "l from left success" << std::endl;

	GameObject reverseL(CubeType::ReverseL);
	EXPECT_EQ(1, reverseL.getFootprintBoundaryX(lrDirection::dLeft));
	std::cerr << "reverseL from left success" << std::endl;

	GameObject s(CubeType::S);
	EXPECT_EQ(0, s.getFootprintBoundaryX(lrDirection::dLeft));
	std::cerr << "s from left success" << std::endl;

	GameObject reverseS(CubeType::ReverseS);
	EXPECT_EQ(0, reverseS.getFootprintBoundaryX(lrDirection::dLeft));
	std::cerr << "reverseS from left success" << std::endl;

	GameObject t(CubeType::T);
	EXPECT_EQ(0, t.getFootprintBoundaryX(lrDirection::dLeft));
	std::cerr << "t from left success" << std::endl;

}

TEST(FootprintSizeTest, YFromBottom) {

	GameObject cube(CubeType::Cube);
	EXPECT_EQ(1, cube.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "cube success" << std::endl;

	GameObject line(CubeType::Line);
	EXPECT_EQ(3, line.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "line success" << std::endl;

	GameObject l(CubeType::L);
	EXPECT_EQ(2, l.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "l success" << std::endl;

	GameObject reverseL(CubeType::ReverseL);
	EXPECT_EQ(2, reverseL.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "reverseL success" << std::endl;

	GameObject s(CubeType::S);
	EXPECT_EQ(1, s.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "s success" << std::endl;

	GameObject reverseS(CubeType::ReverseS);
	EXPECT_EQ(1, reverseS.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "reverseS success" << std::endl;

	GameObject t(CubeType::T);
	EXPECT_EQ(1, t.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "t success" << std::endl;
}

TEST(FootprintSizeTest, YFromTop) {

	GameObject cube(CubeType::Cube);
	EXPECT_EQ(0, cube.getFootprintBoundaryY(tbDirection::dTop));
	std::cerr << "cube success" << std::endl;

	GameObject line(CubeType::Line);
	EXPECT_EQ(0, line.getFootprintBoundaryY(tbDirection::dTop));
	std::cerr << "line success" << std::endl;

	GameObject l(CubeType::L);
	EXPECT_EQ(0, l.getFootprintBoundaryY(tbDirection::dTop));
	std::cerr << "l success" << std::endl;

	GameObject reverseL(CubeType::ReverseL);
	EXPECT_EQ(0, reverseL.getFootprintBoundaryY(tbDirection::dTop));
	std::cerr << "reverseL success" << std::endl;

	GameObject s(CubeType::S);
	EXPECT_EQ(0, s.getFootprintBoundaryY(tbDirection::dTop));
	std::cerr << "s success" << std::endl;

	GameObject reverseS(CubeType::ReverseS);
	EXPECT_EQ(0, reverseS.getFootprintBoundaryY(tbDirection::dTop));
	std::cerr << "reverseS success" << std::endl;

	GameObject t(CubeType::T);
	EXPECT_EQ(0, t.getFootprintBoundaryY(tbDirection::dTop));
	std::cerr << "t success" << std::endl;
}
//FOOTPRINT REGION END

//GRIDLOGIC REGION
TEST(GridLogicTest, CanCubeGoDown) {
	//cube
	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
	GameObject cube(CubeType::Cube);
	for (int i = 0; i < 11; i++) {
		cube.MoveD();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoDown_(cube));
	std::cerr << "cube at Y: " << cube.Y() << " can go down" << std::endl;
	cube.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(cube));
	std::cerr << "cube at Y: " << cube.Y() << " can't go down" << std::endl;

	//line
	GameObject line(CubeType::Line);
	for (int i = 0; i < 9; i++) {
		line.MoveD();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoDown_(line));
	std::cerr << "line at X: " << line.X() << "Y: " << line.Y() << "rotation: " << line.Rotation() << " can go down" << std::endl;
	line.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(line));
	std::cerr << "line at X: " << line.X() << "Y: " << line.Y() << "rotation: " << line.Rotation() << " can't go down" << std::endl;

	//l
	GameObject l(CubeType::L);
	for (int i = 0; i < 10; i++) {
		l.MoveD();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoDown_(l));
	std::cerr << "l at Y: " << l.Y() << " can go down" << std::endl;
	l.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(l));
	std::cerr << "l at Y: " << l.Y() << " can't go down" << std::endl;

	//reverseL
	GameObject reverseL(CubeType::ReverseL);
	for (int i = 0; i < 10; i++) {
		reverseL.MoveD();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoDown_(reverseL));
	std::cerr << "reverseL at Y: " << reverseL.Y() << " can go down" << std::endl;
	reverseL.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(reverseL));
	std::cerr << "reverseL at Y: " << reverseL.Y() << " can't go down" << std::endl;

	//s
	GameObject s(CubeType::S);
	for (int i = 0; i < 11; i++) {
		s.MoveD();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoDown_(s));
	std::cerr << "s at Y: " << s.Y() << " can go down" << std::endl;
	s.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(s));
	std::cerr << "s at Y: " << s.Y() << " can't go down" << std::endl;

	//reverseS
	GameObject reverseS(CubeType::ReverseS);
	for (int i = 0; i < 11; i++) {
		reverseS.MoveD();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoDown_(reverseS));
	std::cerr << "reverseS at Y: " << reverseS.Y() << " can go down" << std::endl;
	reverseS.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(reverseS));
	std::cerr << "reverseS at Y: " << reverseS.Y() << " can't go down" << std::endl;

	//t
	GameObject t(CubeType::T);
	for (int i = 0; i < 11; i++) {
		t.MoveD();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoDown_(t));
	std::cerr << "t at Y: " << t.Y() << " can go down" << std::endl;
	t.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(t));
	std::cerr << "t at Y: " << t.Y() << " can't go down" << std::endl;
}

TEST(GridLogicTest, CanCubeGoRight) {
	//cube
	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
	GameObject cube(CubeType::Cube);
	cube.setX(5);

	EXPECT_EQ(true, gameLogic.canCubeGoRight_(cube));
	std::cerr << "cube at X: " << cube.X() << " can go right" << std::endl;
	cube.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(cube));
	std::cerr << "cube at X: " << cube.X() << " can't go right" << std::endl;

	//line
	GameObject line(CubeType::Line);
	line.setX(5);

	EXPECT_EQ(true, gameLogic.canCubeGoRight_(line));
	std::cerr << "line at X: " << line.X() << "Y: " << line.Y() << "rotation: " << line.Rotation() << " can go right" << std::endl;
	line.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(line));
	std::cerr << "line at X: " << line.X() << "Y: " << line.Y() << "rotation: " << line.Rotation() << " can't go right" << std::endl;

	//l
	GameObject l(CubeType::L);
	l.setX(5);

	EXPECT_EQ(true, gameLogic.canCubeGoRight_(l));
	std::cerr << "l at X: " << l.X() << " can go right" << std::endl;
	l.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(l));
	std::cerr << "l at X: " << l.X() << " can't go right" << std::endl;

	//reverseL
	GameObject reverseL(CubeType::ReverseL);
	reverseL.setX(4);

	EXPECT_EQ(true, gameLogic.canCubeGoRight_(reverseL));
	std::cerr << "reverseL at X: " << reverseL.X() << " can go right" << std::endl;
	reverseL.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(reverseL));
	std::cerr << "reverseL at X: " << reverseL.X() << " can't go right" << std::endl;

	//s
	GameObject s(CubeType::S);
	s.setX(4);

	EXPECT_EQ(true, gameLogic.canCubeGoRight_(s));
	std::cerr << "s at X: " << s.X() << " can go right" << std::endl;
	s.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(s));
	std::cerr << "s at X: " << s.X() << " can't go right" << std::endl;

	//reverseS
	GameObject reverseS(CubeType::ReverseS);
	reverseS.setX(4);

	EXPECT_EQ(true, gameLogic.canCubeGoRight_(reverseS));
	std::cerr << "reverseS at X: " << reverseS.X() << " can go right" << std::endl;
	reverseS.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(reverseS));
	std::cerr << "reverseS at X: " << reverseS.X() << " can't go right" << std::endl;

	//t
	GameObject t(CubeType::T);
	t.setX(4);

	EXPECT_EQ(true, gameLogic.canCubeGoRight_(t));
	std::cerr << "t at X: " << t.X() << " can go right" << std::endl;
	t.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(t));
	std::cerr << "t at X: " << t.X() << " can't go right" << std::endl;
}

TEST(GridLogicTest, CanCubeGoLeft) {

	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
	//cube	
	GameObject cube(CubeType::Cube);

	EXPECT_EQ(false, gameLogic.canCubeGoLeft_(cube));
	std::cerr << "cube at X: " << cube.X() << " can't go left" << std::endl;

	//reverseL
	GameObject reverseL(CubeType::ReverseL);

	EXPECT_EQ(true, gameLogic.canCubeGoLeft_(reverseL));
	std::cerr << "reverseL at X: " << reverseL.X() << " can go left" << std::endl;
	reverseL.MoveL();
	EXPECT_EQ(false, gameLogic.canCubeGoLeft_(reverseL));
	std::cerr << "reverseL at X: " << reverseL.X() << " can't go left" << std::endl;


	//line
	GameObject line(CubeType::Line);

	EXPECT_EQ(true, gameLogic.canCubeGoLeft_(line));
	std::cerr << "line at X: " << line.X() << "Y: " << line.Y() << "rotation: " << line.Rotation() << " can go left" << std::endl;
	line.MoveL();
	EXPECT_EQ(false, gameLogic.canCubeGoLeft_(line));
	std::cerr << "line at X: " << line.X() << "Y: " << line.Y() << "rotation: " << line.Rotation() << " can't go left" << std::endl;



}

std::string cubeStatus_(GameObject cube, bool state) {
	std::ostringstream oss;
	oss << std::endl << "cube at \nX: \n" << cube.X() << "\n Y: \n" << cube.Y() << "\n rotation: \n" << cube.Rotation();
	if (state) oss << +"\n can be rotated \n\n";
	else oss << "\n can't be rotated \n\n";
	return oss.str();
}

void cubeCWRotationTestHorizontal(GameObject cube, int fprintEmptyXLeft, int fprintEmptyXRight, int fprintEmptyYTop, int fprintEmptyYBottom) {
	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);

	for (int i = 0; i < 4; ++i) {

		int rotatedEmptyXLeft;
		int rotatedEmptyXRight;
		int rotatedEmptyYTop;
		int rotatedEmptyYBottom;

		switch (i) {
		case 0:
			rotatedEmptyXLeft = fprintEmptyXLeft;
			rotatedEmptyXRight = fprintEmptyXRight;
			rotatedEmptyYTop = fprintEmptyYTop;
			rotatedEmptyYBottom = fprintEmptyYBottom;
			break;
		case 1:
			rotatedEmptyXLeft = fprintEmptyYTop;
			rotatedEmptyXRight = fprintEmptyYBottom;
			rotatedEmptyYTop = fprintEmptyXRight;
			rotatedEmptyYBottom = fprintEmptyXLeft;
			break;
		case 2:
			rotatedEmptyXLeft = fprintEmptyXRight;
			rotatedEmptyXRight = fprintEmptyXLeft;
			rotatedEmptyYTop = fprintEmptyYBottom;
			rotatedEmptyYBottom = fprintEmptyYTop;
			break;
		case 3:
			rotatedEmptyXLeft = fprintEmptyYBottom;
			rotatedEmptyXRight = fprintEmptyYTop;
			rotatedEmptyYTop = fprintEmptyXLeft;
			rotatedEmptyYBottom = fprintEmptyXRight;
			break;
		}

		for (int j = 0; j <= Game::gridWidth - (cube.Footprint()[0].size() - rotatedEmptyXRight); ++j) {
			int actualX;
			bool beyondHalf = !((j + 1) <= Game::gridWidth / 2);
			int xWithEmpty;
			int expectedOverflow;
			bool expected;

			if (beyondHalf) {
				actualX = j;
				xWithEmpty = Game::gridWidth - rotatedEmptyXRight;
				expectedOverflow = (cube.Footprint().size() - cube.Footprint()[0].size()) - rotatedEmptyYBottom;
				int xWithOverflow = actualX + expectedOverflow;

				expected = xWithOverflow <= xWithEmpty;
			}
			else {
				actualX = j - rotatedEmptyXLeft;
				xWithEmpty = 0 - rotatedEmptyXLeft;
				expectedOverflow = (cube.Footprint().size() - cube.Footprint()[0].size()) - rotatedEmptyYTop;
				int xWithOverflow = actualX - expectedOverflow;

				expected = xWithOverflow >= xWithEmpty;
			}

			cube.setX(actualX);
			EXPECT_EQ(expected, gameLogic.canCubeBeRotatedCW(cube));
			std::cerr << cubeStatus_(cube, expected);
		}

		cube.RotateCW();
	}

}
//
//TEST(GridLogicTest, CanCubeBeRotated) {
//
//	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
//
//	GameObject cube(CubeType::Cube);
//
//	cubeCWRotationTestHorizontal(cube, 0, 0, 0, 0);
//}
//
//TEST(GridLogicTest, CanTBeRotated) {
//
//	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
//
//	GameObject t(CubeType::T);
//
//	cubeCWRotationTestHorizontal(t, 0, 0, 0, 1);
//}
//
//TEST(GridLogicTest, CanLineBeRotated) {
//
//	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
//
//	GameObject line(CubeType::Line);
//
//	cubeCWRotationTestHorizontal(line, 1, 1, 0, 0);
//
//	line.setX(0);
//	line.RotateCW();
//	line.setY(-1);
//	EXPECT_EQ(false, gameLogic.canCubeBeRotatedCW(line));
//	std::cerr << cubeStatus_(line, false);
//	line.RotateCCW();
//
//	line.RotateCW();
//	line.setY(0);
//	EXPECT_EQ(true, gameLogic.canCubeBeRotatedCW(line));
//	std::cerr << cubeStatus_(line, true);
//	line.RotateCCW();
//
//	line.RotateCW();
//	line.setY(Game::gridHeight - 2);
//	EXPECT_EQ(false, gameLogic.canCubeBeRotatedCW(line));
//	std::cerr << cubeStatus_(line, false);
//	line.RotateCCW();
//
//	line.RotateCW();
//	line.setY(Game::gridHeight - 3);
//	EXPECT_EQ(false, gameLogic.canCubeBeRotatedCW(line));
//	std::cerr << cubeStatus_(line, false);
//	line.RotateCCW();
//
//	line.RotateCW();
//	line.setY(Game::gridHeight - 4);
//	EXPECT_EQ(true, gameLogic.canCubeBeRotatedCW(line));
//	std::cerr << cubeStatus_(line, true);
//	line.RotateCCW();
//}

