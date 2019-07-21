#include "pch.h"
#include "../GameLogic/game_object.h"
#include "../GameLogic/game.h"
#include "../GameLogic/game_logic.h"

TEST(GridLogicTest, FootprintActualSizeX) {

	GameObject cube(CubeType::Cube);
	EXPECT_EQ(1, cube.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "cube succ" << std::endl;

	GameObject line(CubeType::Line);
	EXPECT_EQ(0, line.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "line succ" << std::endl;

	GameObject l(CubeType::L);
	EXPECT_EQ(1, l.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "l succ" << std::endl;

	GameObject reverseL(CubeType::ReverseL);
	EXPECT_EQ(1, reverseL.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "reverseL succ" << std::endl;

	GameObject s(CubeType::S);
	EXPECT_EQ(2, s.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "s succ" << std::endl;

	GameObject reverseS(CubeType::ReverseS);
	EXPECT_EQ(2, reverseS.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "reverseS succ" << std::endl;

	GameObject t(CubeType::T);
	EXPECT_EQ(2, t.getFootprintBoundaryX(lrDirection::dRight));
	std::cerr << "t succ" << std::endl;

}

TEST(GridLogicTest, FootprintActualSizeY) {

	GameObject cube(CubeType::Cube);
	EXPECT_EQ(1, cube.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "cube succ" << std::endl;

	GameObject line(CubeType::Line);
	EXPECT_EQ(3, line.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "line succ" << std::endl;

	GameObject l(CubeType::L);
	EXPECT_EQ(2, l.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "l succ" << std::endl;

	GameObject reverseL(CubeType::ReverseL);
	EXPECT_EQ(2, reverseL.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "reverseL succ" << std::endl;

	GameObject s(CubeType::S);
	EXPECT_EQ(1, s.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "s succ" << std::endl;

	GameObject reverseS(CubeType::ReverseS);
	EXPECT_EQ(1, reverseS.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "reverseS succ" << std::endl;

	GameObject t(CubeType::T);
	EXPECT_EQ(1, t.getFootprintBoundaryY(tbDirection::dBottom));
	std::cerr << "t succ" << std::endl;
}

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
	std::cerr << "line at Y: " << line.Y() << " can go down" << std::endl;
	line.MoveD();
	EXPECT_EQ(false, gameLogic.canCubeGoDown_(line));
	std::cerr << "line at Y: " << line.Y() << " can't go down" << std::endl;

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
	for (int i = 0; i < 5; i++) {
		cube.MoveR();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoRight_(cube));
	std::cerr << "cube at X: " << cube.X() << " can go right" << std::endl;
	cube.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(cube));
	std::cerr << "cube at X: " << cube.X() << " can't go right" << std::endl;

	//line
	GameObject line(CubeType::Line);
	for (int i = 0; i < 6; i++) {
		line.MoveR();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoRight_(line));
	std::cerr << "line at X: " << line.X() << " can go right" << std::endl;
	line.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(line));
	std::cerr << "line at X: " << line.X() << " can't go right" << std::endl;

	//l
	GameObject l(CubeType::L);
	for (int i = 0; i < 5; i++) {
		l.MoveR();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoRight_(l));
	std::cerr << "l at X: " << l.X() << " can go right" << std::endl;
	l.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(l));
	std::cerr << "l at X: " << l.X() << " can't go right" << std::endl;

	//reverseL
	GameObject reverseL(CubeType::ReverseL);
	for (int i = 0; i < 5; i++) {
		reverseL.MoveR();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoRight_(reverseL));
	std::cerr << "reverseL at X: " << reverseL.X() << " can go right" << std::endl;
	reverseL.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(reverseL));
	std::cerr << "reverseL at X: " << reverseL.X() << " can't go right" << std::endl;

	//s
	GameObject s(CubeType::S);
	for (int i = 0; i < 4; i++) {
		s.MoveR();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoRight_(s));
	std::cerr << "s at X: " << s.X() << " can go right" << std::endl;
	s.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(s));
	std::cerr << "s at X: " << s.X() << " can't go right" << std::endl;

	//reverseS
	GameObject reverseS(CubeType::ReverseS);
	for (int i = 0; i < 4; i++) {
		reverseS.MoveR();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoRight_(reverseS));
	std::cerr << "reverseS at X: " << reverseS.X() << " can go right" << std::endl;
	reverseS.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(reverseS));
	std::cerr << "reverseS at X: " << reverseS.X() << " can't go right" << std::endl;

	//t
	GameObject t(CubeType::T);
	for (int i = 0; i < 4; i++) {
		t.MoveR();
	}
	EXPECT_EQ(true, gameLogic.canCubeGoRight_(t));
	std::cerr << "t at X: " << t.X() << " can go right" << std::endl;
	t.MoveR();
	EXPECT_EQ(false, gameLogic.canCubeGoRight_(t));
	std::cerr << "t at X: " << t.X() << " can't go right" << std::endl;
}

TEST(GridLogicTest, CanCubeGoLeft) {
	//cube
	GameLogic gameLogic = *new GameLogic(Game::gridHeight, Game::gridWidth);
	GameObject cube(CubeType::Cube);
		
	EXPECT_EQ(false, gameLogic.canCubeGoLeft_(cube));
	std::cerr << "cube at X: " << cube.X() << " can't go left" << std::endl;
}