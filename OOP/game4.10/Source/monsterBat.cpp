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
	
	const int STEP_SIZE = 45;
	const int STEP = -1; //因為地圖座標會移動 所以為-1 因不知名原本 座標很奇怪
	monster_bat::monster_bat() {
		printf("%d,%d\n", mon_x, mon_y);
		Initialize();
		//SetXY(map_x + 45 * mon_x, map_y + 45 * mon_y);
	}

	void monster_bat::Initialize()
	{
		const int X_POS = 920;//245 = 200 + 1*45
		const int Y_POS = 540;// 95 = 50  + 1*45
		character = 0;
	}

	int monster_bat::Character() {
		return character;
	}

	int monster_bat::mon_loc_judge(int x, int y) {
		if (monster_cpp.mon_x == x && monster_cpp.mon_y == y) {
			LoadBitmap();
			return 1;
		}
		return 0;
	};

	int monster_bat::whichway(int mon_way_x, int mon_way_y, int next_way_x, int next_way_y, int main_x, int main_y) {//在與其他物件重疊時 應該走到哪一格代替
		if (next_way_x == mon_way_x + 1 && next_way_y == mon_way_y) {//往右
			if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_y >= mon_way_y) {//右上
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y - 1][next_way_x] != 3 && map_monster[next_way_y - 1][next_way_x] != 5 && main_y <= mon_way_y) {//右下
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x - 1 && next_way_y == mon_way_y) {//往左
			if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_y >= mon_way_y) {//左上
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y - 1][next_way_x] != 3 && map_monster[next_way_y - 1][next_way_x] != 5 && main_y <= mon_way_y) {//左下
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x && next_way_y == mon_way_y + 1) {//往下
			if (map_monster[next_way_y][next_way_x + 1] != 3 && map_monster[next_way_y][next_way_x + 1] != 5 && main_x >= mon_way_x) {//右下
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y][next_way_x - 1] != 3 && map_monster[next_way_y][next_way_x - 1] != 5 && main_x <= mon_way_x) {//左下
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x && next_way_y == mon_way_y - 1) {//往上
			if (map_monster[next_way_y][next_way_x + 1] != 3 && map_monster[next_way_y][next_way_x + 1] != 5 && main_x >= mon_way_x) {//右上
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y][next_way_x - 1] != 3 && map_monster[next_way_y][next_way_x - 1] != 5 && main_x <= mon_way_x) {//左上
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x + 1 && next_way_y == mon_way_y - 1) {//往右上
			if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_x > mon_way_x + 1) {
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y][next_way_x - 1] != 3 && map_monster[next_way_y][next_way_x - 1] != 5 && main_y < mon_way_y - 1) {
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x -= 1;
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x - 1 && next_way_y == mon_way_y + 1) {//往左下
			if (map_monster[next_way_y - 1][next_way_x] != 3 && map_monster[next_way_y - 1][next_way_x] != 5 && main_x < mon_way_x - 1) {
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y][next_way_x + 1] != 3 && map_monster[next_way_y][next_way_x + 1] != 5 && main_y > mon_way_y + 1) {
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x += 1;
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x + 1 && next_way_y == mon_way_y + 1) {//往右下
			if (map_monster[next_way_y][next_way_x - 1] != 3 && map_monster[next_way_y][next_way_x - 1] != 5 && main_y > mon_way_y + 1) {
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y - 1][next_way_x] != 3 && map_monster[next_way_y - 1][next_way_x] != 5 && main_x > mon_way_x + 1) {
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x -= 1;
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x - 1 && next_way_y == mon_way_y - 1) {//往左上
			if (map_monster[next_way_y][next_way_x + 1] != 3 && map_monster[next_way_y][next_way_x + 1] != 5 && main_y < mon_way_y - 1) {//往上
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_x < mon_way_x - 1) {//往左
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x += 1;
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		else {
			return next_way_x * 100 + next_way_y;
		}
	}

	int monster_bat::attack_judge(int x1, int y1, int x2, int y2) {
		//printf("judge:%d,%d,%d,%d\n", x1, y1, x2, y2);
		if (abs(x1 - x2) <= 1 && abs(y1-y2) <= 1) {
			eraser.attacked(mon_ATK);
			return 1;
		}
		return 0;
	}

	int monster_bat::getroad(int map[][27]) {
		for (int i = 0; i < 27; i++)
			for (int j = 0; j < 27; j++)
				rummap_bat[i][j] = map[i][j];
		if (rummap_bat[next_y][next_x]==1) {
			next_step = whichway(mon_x, mon_y, next_x, next_y, CEraser::actor_x, CEraser::actor_y);
		}
		next_x = next_step / 100;
		next_y = next_step % 100;
		SetXY(CEraser::map_x + 45 * next_x, CEraser::map_y + 45 * next_y);
		mon_x = next_x;
		mon_y = next_y;
		monster_cpp.get_bat(1,mon_x, mon_y);
		LoadBitmap();
		return next_step;
	}

	void monster_bat::findroad() {
		//next_x = mon_x;
		//next_y = mon_y;
		//printf("monster_cpp.mon:%d,%d\n", monster_cpp.mon_x, monster_cpp.mon_y);
		next_step = monster_cpp.automove(map_monster, mon_x, mon_y, CEraser::actor_x, CEraser::actor_y);
		next_x = next_step / 100;
		next_y = next_step % 100;
	}

	int monster_bat::getmap(int random_map, int map[][27])
	{
		map_num = random_map; 
		for (int i = 0; i < 27; i++)
			for (int j = 0; j < 27; j++)
				map_monster[i][j] = map[i][j];
		if (map_num == 1) {//24*24
			mon_x = 20;//24-actor_x
			mon_y = 1;//2-actor_y
			mon_HP = 20;
			mon_ATK = 1;
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			return random_map;
		}
		if (map_num == 2) {//24*24
			mon_x = 22;//24-actor_x
			mon_y = 1;//2-actor_y
			mon_HP = 20;
			monster_cpp.get_bat(1,mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
		}
		if (map_num == 3) {//24*24
			mon_x = 22;
			mon_y = 1;
			mon_HP = 20;
			monster_cpp.get_bat(1,mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
		}
		if (map_num == 4) {//24*24
			mon_x = 22;
			mon_y = 1;
			mon_HP = 20;
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
		}
		if (map_num == 5) {//24*24
			mon_x = 22;
			mon_y = 1;
			mon_HP = 20;
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
		}
		if (map_num == 6) {//24*24
			mon_x = 22;
			mon_y = 1;
			mon_HP = 20;
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
		}
		if (map_num == 7) {//24*24
			superdeath();
		}
		mon_HP = 20;
		mon_ATK = 1;
		LoadBitmap();
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

	void monster_bat::LoadBitmap()
	{
		//animation.AddBitmap(warrior, RGB(255, 255, 255));
		if (mon_HP == 20) {
			animation.cleanBitmap();
			animation.AddBitmap(bat, RGB(255, 255, 255));
			animation.AddBitmap(bat2, RGB(255, 255, 255));
			Shp.LoadBitmap(20);
			Shp.SetXY(GetX1(), GetY2());
		}
		if (mon_HP != 20 && mon_HP >0) {
			animation.cleanBitmap();
			animation.AddBitmap(bat3, RGB(255, 255, 255));
			animation.AddBitmap(bat4, RGB(255, 255, 255));
			Shp.LoadBitmap((mon_HP * 10) / mon_MAXHP);
			Shp.SetXY(GetX1(), GetY2());
			printf("bitmap:%d", animation.GetCurrentBitmapNumber());
		}
		if (mon_HP < 1 && deathshow == 1) {
			printf("bat dead");
			animation.cleanBitmap();
			animation.SetDelayCount(5);
			animation.AddBitmap(bat5, RGB(255, 255, 255));
			animation.AddBitmap(bat6, RGB(255, 255, 255));
			animation.AddBitmap(bat7, RGB(255, 255, 255));
			animation.AddBitmap(death_mon, RGB(255, 255, 255));
			Shp.LoadBitmap(0);
			Shp.SetXY(GetX1(), GetY2());
			deathshow = 0;
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

	int monster_bat::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		if (flag && stopeverything==0) {
			findroad();
			/*attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();*/
			return next_step;
		}
		return 0;
	}

	void monster_bat::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag && stopeverything == 0) {
			findroad();
			/*attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();*/
		}
	}

	void monster_bat::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag&& stopeverything == 0) {
			findroad();
			/*attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();*/
		}
	}

	void monster_bat::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag&& stopeverything == 0) {
			findroad();
			/*attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();*/
		}
	}

	void monster_bat::SetMoving(bool flag)
	{
		isMoving = flag;
		if (flag) {
			findroad();
			/*attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();*/
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
		Shp.OnShow();
		if (animation.GetCurrentBitmapNumber() == 3) {
			animation.cleanBitmap();
			animation.AddBitmap(death_mon, RGB(255, 255, 255));
			x = eraser.GetX1() + 45;
			y = eraser.GetY1() + 45;
		}
	}

	int monster_bat::attacked(int ATK) {//攻擊者的攻擊力 回傳被攻擊後的血量
		mon_HP -= ATK;
		printf("bat is attacked\n");
		LoadBitmap();
		if (mon_HP < 1) {
			monster_bat::death();
		}
		return mon_HP - ATK;
	}

	void monster_bat::death() {
		deathshow = 1;
		mon_x = CEraser::actor_x;
		mon_y = CEraser::actor_y;
		mon_ATK = 0;
		LoadBitmap();
	}

	void monster_bat::superdeath() {
		animation.cleanBitmap();
		animation.AddBitmap(death_mon, RGB(255, 255, 255));
		mon_x = CEraser::actor_x;
		mon_y = CEraser::actor_y;
		mon_ATK = 0;
		mon_HP = 0;
		SetXY(920, 450);
		stopeverything = 1;
	}

	void monster_bat::setdata(int m,int set_x,int set_y) {
		mon_HP = 20;
		mon_ATK = 1;
		mon_x = set_x;
		mon_y = set_y;
		/*
		switch (m)
		{
		case 1:
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			break;
		case 2:
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			break;
		case 3:
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			break;
		case 4:
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			break;
		case 5:
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			break;
		case 6:
			monster_cpp.get_bat(1, mon_x, mon_y);
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			break;
		case 7:
			superdeath();
			break;
		default:
			break;
		}*/
	}

	void monster_bat::showdata(int n) {
		printf("\nmonster%d:\n",n);
		printf("HP:%d\n", mon_HP);
		printf("ATK:%d\n", mon_ATK);
		printf("Location:%d,%d\n", mon_x, mon_y);
		printf("X,Y:%d,%d\n", x, y);
		printf("map:%d,%d\n", CEraser::map_x, CEraser::map_y);
	}

};