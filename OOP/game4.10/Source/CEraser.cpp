#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
	int map1_init[25][27] = {
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3},
		{3,9,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,2,2,2,1,1,8,8,1,3},
		{3,1,1,10,1,1,3,1,1,3,1,1,1,1,1,3,1,7,7,1,1,7,8,8,1,3},
		{3,1,2,7,7,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,3},
		{3,1,2,2,2,7,3,3,4,3,3,3,4,3,3,3,3,3,3,3,3,3,1,3,3,3},
		{3,1,7,2,2,2,4,1,1,3,3,3,1,1,1,1,3,3,3,3,3,3,1,3,3,3},
		{3,1,1,1,7,7,3,1,1,1,1,1,1,1,3,1,1,1,1,3,3,3,1,3,3,3},
		{3,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3},
		{3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3},
		{3,1,1,1,1,1,1,3,6,6,6,6,6,3,3,3,1,1,1,3,3,3,1,1,3,3},
		{3,1,1,1,7,7,8,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3},
		{3,1,1,1,7,7,8,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3},
		{3,1,1,1,1,8,8,3,6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1,3,3},
		{3,1,1,1,1,1,1,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3},
		{3,1,1,1,1,1,1,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3},
		{3,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,1,3,3},
		{3,3,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,1,3,3,3,3,3,1,3,3},
		{3,3,3,1,1,4,1,1,8,8,8,8,8,1,3,1,1,1,3,3,3,3,3,1,3,3},
		{3,3,3,3,3,3,1,1,8,8,1,8,8,1,3,1,1,1,3,3,3,3,3,1,3,3},
		{3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,4,3,3,3,3,3,3,3,1,3,3},
		{3,3,3,3,3,1,1,1,1,3,1,1,1,7,1,1,1,1,1,1,3,3,3,1,3,3},
		{3,3,3,3,3,1,1,1,1,4,1,1,7,2,7,1,1,1,1,1,4,1,1,1,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
	///樓層1  0空 1地板 2水地板 3正牆 4門 5水牆 6木地板 7小草 8大草 9上樓 10下樓 11開門
=======

>>>>>>> chun
	CEraser::CEraser()
	{
		Initialize();
	}

<<<<<<< HEAD
=======
	int CEraser::Character() {
		return character;
	}

>>>>>>> chun
	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	void CEraser::Initialize()
	{
<<<<<<< HEAD
		const int X_POS = 245;
		const int Y_POS = 95;
=======
		const int X_POS = 280;
		const int Y_POS = 400;
		character = 0;
>>>>>>> chun
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
<<<<<<< HEAD
		animation.AddBitmap(IDB_archer_right, RGB(255, 255, 255));
	}
	int actor_x = 1;
	int actor_y = 1;
	void CEraser::OnMove()
	{
		
		const int STEP_SIZE = 45;
		animation.OnMove();
		if (isMovingLeft)
			if (map1_init[actor_y][actor_x -1] != 3 && actor_x != 1) {
				x -= STEP_SIZE;
				actor_x -= 1;
			}
			else {
				printf("wall");
			}
		if (isMovingRight)
			if (map1_init[actor_y ][actor_x +1] != 3 && actor_x != 23) {
				x += STEP_SIZE;
				actor_x += 1;
			}
			else {
				printf("wall");
			}
		if (isMovingUp)
			if (map1_init[actor_y-1][actor_x ] != 3 && actor_y != 1) {
				y -= STEP_SIZE;
				actor_y -= 1;
			}
			else {
				printf("wall");
			}
		if (isMovingDown)
			if (map1_init[actor_y +1][actor_x] != 3 && actor_y != 25) {
				y += STEP_SIZE;
				actor_y += 1;
			}
			else {
				printf("wall");
			}
		printf("actor_x=%d\n", actor_x);
		printf("actor_y=%d\n", actor_y);
		printf("x=%d\n", x);
		printf("y=%d\n\n", y);
		printf("location=%d\n\n", map1_init[actor_y][actor_x]);

=======
		animation.AddBitmap(warrior, RGB(255, 255, 255));
		/*if (character == 1) {
			animation.AddBitmap(warrior, RGB(255, 255, 255));
		}
		else if (character == 2) {
			animation.AddBitmap(mage, RGB(255, 255, 255));
		}
		else if (character == 3) {
			animation.AddBitmap(assassin, RGB(255, 255, 255));
		}
		else if (character == 4) {
			animation.AddBitmap(hunter, RGB(255, 255, 255));
		}*/
		
	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 10;
		animation.OnMove();
		if (isMovingLeft)
			x -= STEP_SIZE;
		if (isMovingRight)
			x += STEP_SIZE;
		if (isMovingUp)
			y -= STEP_SIZE;
		if (isMovingDown)
			y += STEP_SIZE;
>>>>>>> chun
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}