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

	int CEraser::map_x = 920;
	int CEraser::map_y = 540;

	CEraser::CEraser()
	{
		Initialize();
		showdata();

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
		const int X_POS = 920;
		const int Y_POS = 540;
		character = 0;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		animation_test.LoadBitmap(herohp1, RGB(255, 255, 255));
		//animation.AddBitmap(warrior, RGB(255, 255, 255));
		if (character == 1) {
			animation.AddBitmap(warrior, RGB(255, 255, 255));
			animation_hp_background.AddBitmap(ui_item1, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_warrior_hp, RGB(255, 255, 255));
		}
		else if (character == 2) {
			animation.AddBitmap(mage, RGB(255, 255, 255));
			animation_hp_background.AddBitmap(ui_item1, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_mage_hp, RGB(255, 255, 255));
		}
		else if (character == 3) {
			animation.AddBitmap(assassin, RGB(255, 255, 255));
			animation_hp_background.AddBitmap(ui_item1, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_assassin_hp, RGB(255, 255, 255));
		}
		else if (character == 4) {
			animation.AddBitmap(hunter, RGB(255, 255, 255));
			animation_hp_background.AddBitmap(ui_item1, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_hunter_hp, RGB(255, 255, 255));
		}
		else {
			animation.AddBitmap(mage, RGB(255, 255, 255));
			animation_hp_background.AddBitmap(ui_item1, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_mage_hp, RGB(255, 255, 255));
		}
	}
	int CEraser::actor_x = 1;
	int CEraser::actor_y = 1;
	int CEraser::hero_HP = 20;
	int show = 1;
	void CEraser::OnMove()
	{

		const int STEP_SIZE = 0;
		animation.OnMove();
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
		animation_hp_background.SetTopLeft(0, 0);
		animation_hp_background.OnShow();
		animation_icon.SetTopLeft(18, 12);
		animation_icon.OnShow();
		for (int i = 0; i < CEraser::hero_HP*4; i++) {
			animation_test.SetTopLeft(87+i*2, 0);
			animation_test.ShowBitmap();
		}
	}

	int CEraser::attacked(int ATK) {//攻擊者的攻擊力 回傳被攻擊後的血量
		CEraser::hero_HP -= ATK;
		printf("Hero is attacked\n");
		return CEraser::hero_HP - ATK;
	}

	void CEraser::showdetail() {
		printf("\nHero:\n");
		printf("HP:%d\n", CEraser::hero_HP);
		//printf("ATK:%d\n", hero_ATK);
		printf("Location:%d,%d\n", actor_x, actor_y);
		printf("X,Y:%d,%d\n", x, y);
	}

	void CEraser::showdata() {
		printf("\nHero:\n");
		printf("HP:%d\n", CEraser::hero_HP);
		//printf("ATK:%d\n", hero_ATK);
		printf("Location:%d,%d\n", actor_x, actor_y);
		printf("X,Y:%d,%d\n", x, y);
	}
}