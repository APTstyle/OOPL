#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "mygame.h"
#include "monsterBat.h"
#include "monster.h"

namespace game_framework {
	
	/////////////////////////////////////////////////////////////////////////////
	// monster: Eraser class
	/////////////////////////////////////////////////////////////////////////////
	const int STEP_SIZE = -45;
	const int STEP = -1; //因為地圖座標會移動 所以為-1 因不知名原本 座標很奇怪
	monster_bat::monster_bat() {
		map_x = 965 - CEraser::actor_x * 45;
		map_y = 585 - CEraser::actor_y * 45;
		mon_x = 24;
		mon_y = 1;
		printf("%d,%d\n", mon_x, mon_y);
		Initialize();
		SetXY(map_x + 45 * mon_x +45, map_y + 45 * mon_y +45);
	}

	int monster_bat::Character() {
		return character;
	}

	int monster_bat::mon_loc_judge(int x, int y) {
		if (monster::mon_x == x && monster::mon_y == y) {
			return 1;
		}
		return 0;
	};

	void monster_bat::showdetail() {
		if (mon_loc_judge(next_x, next_y) == 1) {
			next_step = monster_cpp.whichway(mon_x, mon_y, next_x, next_y, CEraser::actor_x, CEraser::actor_y);
		}
		next_x = next_step / 100;
		next_y = next_step % 100;
		mon_x = next_x;
		mon_y = next_y;
		x = map_x + 45 * mon_x;
		y = map_y + 45 * mon_y;
		monster_cpp.get_bat(1,mon_x, mon_y);
		printf("\nmonster2:\n");
		//printf("HP:%d\n", mon_HP);
		//printf("ATK:%d\n", mon_ATK);
		printf("Location:%d,%d\n", mon_x, mon_y);
		//printf("X,Y:%d,%d\n\n", x, y);
		//printf("\nmap:%d,%d\n", map_x, map_y);
	}
	void monster_bat::findroad() {
		next_x = mon_x;
		next_y = mon_y;
		printf("monster_cpp.mon:%d,%d\n", monster::mon_x, monster::mon_y);
		next_step = monster_cpp.automove(map_monster, mon_x, mon_y, CEraser::actor_x, CEraser::actor_y, monster::mon_x * 100 + monster::mon_y, 0);
		next_x = next_step / 100;
		next_y = next_step % 100;
	}

	int monster_bat::getmap(int random_map, int map[][27])
	{
		map_num = random_map; 
		for (int i = 0; i < 25; i++)
			for (int j = 0; j < 27; j++)
				map_monster[i][j] = map[i][j];
		if (map_num == 2) {//24*24
			map_x = 650;
			map_y = 315;
			mon_x = 22;//24-actor_x
			mon_y = 1;//2-actor_y
			CEraser::actor_x = 6;
			CEraser::actor_y = 5;
			monster_cpp.get_bat(1,mon_x, mon_y);
			SetXY(map_x + 45 * mon_x + 45, map_y + 45 * mon_y + 45);
		}
		if (map_num == 3) {//24*24
			map_x = 200;
			map_y = 315;
			mon_x = 22;
			mon_y = 1;
			CEraser::actor_x = 16;
			CEraser::actor_y = 5;
			monster_cpp.get_bat(1,mon_x, mon_y);
			SetXY(map_x + 45 * mon_x + 45, map_y + 45 * mon_y + 45);
		}
		//printf("monster_map:%d\n", map_num);
		return random_map;
	}

	int monster_bat::GetX1()
	{
		return this->x;
	}

	int monster_bat::GetY1()
	{
		return this->y;
	}

	int monster_bat::GetX2()
	{
		return x + animation.Width();
	}

	int monster_bat::GetY2()
	{
		return y + animation.Height();
	}

	void monster_bat::Initialize()
	{
		const int X_POS = 920;//245 = 200 + 1*45
		const int Y_POS = 540;// 95 = 50  + 1*45
		character = 0;
	}

	void monster_bat::LoadBitmap()
	{
		//animation.AddBitmap(warrior, RGB(255, 255, 255));
		animation.AddBitmap(bat, RGB(255, 255, 255));
		animation.AddBitmap(bat2, RGB(255, 255, 255));
		if (mon_HP != 20) {
			animation.AddBitmap(bat3, RGB(255, 255, 255));
			animation.AddBitmap(bat4, RGB(255, 255, 255));
		}
	}
	void monster_bat::OnMove()
	{

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
	void monster_bat::SetCharacter(int actor)
	{
		character = actor;
	}

	void monster_bat::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				map_y += STEP_SIZE;
			}
			findroad();
			monster_cpp.attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();

		}
	}

	void monster_bat::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				map_x -= STEP_SIZE;
			}
			findroad();
			monster_cpp.attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster_bat::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				map_x += STEP_SIZE;
			}
			findroad();
			monster_cpp.attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster_bat::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag) {
			if(CGameMap::ismoving == 1) {
				map_y -= STEP_SIZE;
			}
			findroad();
			monster_cpp.attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster_bat::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void monster_bat::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
};