#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
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
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::Character() {
		return character;
	}

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
		const int X_POS = 750+45;
		const int Y_POS = 750+45;
>>>>>>> chun
		character = 0;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		//animation.AddBitmap(warrior, RGB(255, 255, 255));
		if (character == 1) {
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
		}
		else {
			animation.AddBitmap(mage, RGB(255, 255, 255));
		}
	}
<<<<<<< HEAD
	int CEraser::actor_x = 1;
	int CEraser::actor_y = 1;
=======
	int actor_x = 1;
	int actor_y = 1;
>>>>>>> chun
	void CEraser::OnMove()
	{

		const int STEP_SIZE = 0;
		animation.OnMove();
<<<<<<< HEAD
		if (isMovingLeft) {
		}
		if (isMovingRight) {
		}
		if (isMovingUp) {
		}
		if (isMovingDown) {
		}

	}
	void CEraser::SetCharacter(int actor)
	{
		character = actor;
	}
=======
		if (isMovingLeft)
			if (map1_init[actor_y][actor_x - 1] != 3 && actor_x != 1) {
				x -= STEP_SIZE;
				actor_x -= 1;
			}
			else {
				printf("wall");
			}
		if (isMovingRight)
			if (map1_init[actor_y][actor_x + 1] != 3 && actor_x != 24) {
				x += STEP_SIZE;
				actor_x += 1;
			}
			else {
				printf("wall");
			}
		if (isMovingUp)
			if (map1_init[actor_y - 1][actor_x] != 3 && actor_y != 1) {
				y -= STEP_SIZE;
				actor_y -= 1;
			}
			else {
				printf("wall");
			}
		if (isMovingDown)
			if (map1_init[actor_y + 1][actor_x] != 3 && actor_y != 25) {
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

	}
	void CEraser::SetCharacter(int actor)
	{
		character = actor;
	}
>>>>>>> chun
	

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
<<<<<<< HEAD

=======
	//////////////////////////////////////////////////////
	Monster::Monster()
	{
		Initialize();
	}

	int Monster::Character() {
		return character;
	}

	int Monster::GetX1()
	{
		return x;
	}

	int Monster::GetY1()
	{
		return y;
	}

	int Monster::GetX2()
	{
		return x + animation.Width();
	}

	int Monster::GetY2()
	{
		return y + animation.Height();
	}

	void Monster::Initialize()
	{
		const int X_POS = 750 + 45;
		const int Y_POS = 750 + 45;
		character = 0;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Monster::LoadBitmap()
	{
		animation.AddBitmap(wolf1,RGB(255,255,255));
	}

	void Monster::OnMove()
	{

		const int STEP_SIZE = 0;
		animation.OnMove();
		if (isMovingLeft)
			if (map1_init[actor_y][actor_x - 1] != 3 && actor_x != 1) {
				x -= STEP_SIZE;
				actor_x -= 1;
			}
			else {
				printf("wall");
			}
		if (isMovingRight)
			if (map1_init[actor_y][actor_x + 1] != 3 && actor_x != 24) {
				x += STEP_SIZE;
				actor_x += 1;
			}
			else {
				printf("wall");
			}
		if (isMovingUp)
			if (map1_init[actor_y - 1][actor_x] != 3 && actor_y != 1) {
				y -= STEP_SIZE;
				actor_y -= 1;
			}
			else {
				printf("wall");
			}
		if (isMovingDown)
			if (map1_init[actor_y + 1][actor_x] != 3 && actor_y != 25) {
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

	}
	void Monster::SetCharacter(int actor)
	{
		character = actor;
	}


	void Monster::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Monster::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Monster::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Monster::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Monster::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Monster::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
>>>>>>> chun
}