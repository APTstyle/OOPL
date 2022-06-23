#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "monster.h"
#include "mygame.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// monster: Eraser class
	/////////////////////////////////////////////////////////////////////////////
	const int STEP_SIZE = 45;
	const int STEP = -1; //因為地圖座標會移動 所以為-1 因不知名原本 座標很奇怪

	int monster::mon_bat_x = 0;
	int monster::mon_bat_y = 0;
	monster::monster()
	{
		//CAudio::Instance()->Load(SND_ghost, "sounds\\snd_ghost.mp3");
		main_x = 0;
		main_y = 0;
		Initialize();
		SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
		showdata();
		/*for (int i = 0; i < 27; i++) {
			for (int j = 0; j < 27; j++) {
					map_monster[i][j] = 0;
			}
		}*/
	}
	int monster::automove(int automove_map[][27], int main_x, int main_y, int end_x, int end_y) {
		int map_calculate[25][27];//計算用的地圖
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 27; j++) {
				if (automove_map[i][j] == 3 || automove_map[i][j] == 5) {
					map_calculate[i][j] = -1;//0520
				}
				else {
					map_calculate[i][j] = 0;
				}
			}
		}
		if (main_x == 0 && main_y == 0) {
			return 0;
		}
		map_calculate[main_y][main_x] = main_x * 100 + main_y;//起點為起點座標
		map_calculate[end_y][end_x] = -2;//終點為-2
		int check_step[100];
		int count_step_now = 0;//記錄這一圈有幾個
		int count_step_next = 0;//紀錄新的一圈有幾個新位置
		int search = 1;
		int step_record_now[100];//紀錄這一圈的位置
		int step_record_next[100];//紀錄新的一圈的位置
		int attack = 0;
		for (int i = 0; i < 100; i++) {
			step_record_now[i] = 0;
			step_record_next[i] = 0;
			check_step[i] = 0;
		}
		int x = main_x, y = main_y;
		if (map_calculate[main_y][main_x + 1] == -2 || map_calculate[main_y + 1][main_x + 1] == -2 || map_calculate[main_y - 1][main_x + 1] == -2 || map_calculate[main_y][main_x] == -2 || map_calculate[main_y + 1][main_x] == -2 || map_calculate[main_y - 1][main_x] == -2 || map_calculate[main_y][main_x - 1] == -2 || map_calculate[main_y + 1][main_x - 1] == -2 || map_calculate[main_y - 1][main_x - 1] == -2) {
			return main_x * 100 + main_y;
		}
		if (map_calculate[main_y][main_x + 1] == 0) {
			map_calculate[main_y][main_x + 1] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y + 100;
			count_step_now += 1;
		}
		if (map_calculate[main_y - 1][main_x] == 0) {
			map_calculate[main_y - 1][main_x] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y - 1;
			count_step_now += 1;
		}
		if (map_calculate[main_y][main_x - 1] == 0) {
			map_calculate[main_y][main_x - 1] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y - 100;
			count_step_now += 1;
		}
		if (map_calculate[main_y + 1][main_x] == 0) {
			map_calculate[main_y + 1][main_x] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y + 1;
			count_step_now += 1;
		}
		if (map_calculate[main_y + 1][main_x + 1] == 0) {
			map_calculate[main_y + 1][main_x + 1] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y + 101;
			count_step_now += 1;
		}
		if (map_calculate[main_y + 1][main_x - 1] == 0) {
			map_calculate[main_y + 1][main_x - 1] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y - 99;
			count_step_now += 1;
		}
		if (map_calculate[main_y - 1][main_x - 1] == 0) {
			map_calculate[main_y - 1][main_x - 1] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y - 101;
			count_step_now += 1;
		}
		if (map_calculate[main_y - 1][main_x + 1] == 0) {
			map_calculate[main_y - 1][main_x + 1] = main_x * 100 + main_y;
			step_record_now[count_step_now] = main_x * 100 + main_y + 99;
			count_step_now += 1;
		}
		while (search) {//廣度優先搜尋法 BFS
			count_step_next = 0;
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < count_step_now; i++) {
					x = step_record_now[i] / 100;
					y = step_record_now[i] % 100;
					if (map_calculate[y][x + 1] == -2 || map_calculate[y][x - 1] == -2 || map_calculate[y + 1][x] == -2 || map_calculate[y - 1][x] == -2 || map_calculate[y + 1][x - 1] == -2 || map_calculate[y - 1][x + 1] == -2 || map_calculate[y + 1][x + 1] == -2 || map_calculate[y - 1][x - 1] == -2) {
						search = 0;
						i = 100;
						j = 3;
						map_calculate[end_y][end_x] = x * 100 + y;
						continue;
					}
					if (map_calculate[y][x + 1] == 0) {
						map_calculate[y][x + 1] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y + 100;
						count_step_next += 1;
						continue;
					}
					if (map_calculate[y - 1][x] == 0) {
						map_calculate[y - 1][x] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y - 1;
						count_step_next += 1;
						continue;
					}
					if (map_calculate[y][x - 1] == 0) {
						map_calculate[y][x - 1] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y - 100;
						count_step_next += 1;
						continue;
					}
					if (map_calculate[y + 1][x] == 0) {
						map_calculate[y + 1][x] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y + 1;
						count_step_next += 1;
						continue;
					}
				}
			}
			if (search == 1) {
				for (int j = 0; j < 2; j++) {
					for (int i = 0; i < count_step_now; i++) {
						x = step_record_now[i] / 100;
						y = step_record_now[i] % 100;
						if (map_calculate[y + 1][x + 1] == 0) {
							map_calculate[y + 1][x + 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y + 101;
							count_step_next += 1;
							continue;
						}
						if (map_calculate[y + 1][x - 1] == 0) {
							map_calculate[y + 1][x - 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y - 99;
							count_step_next += 1;
							continue;
						}
						if (map_calculate[y - 1][x - 1] == 0) {
							map_calculate[y - 1][x - 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y - 101;
							count_step_next += 1;
							continue;
						}
						if (map_calculate[y - 1][x + 1] == 0) {
							map_calculate[y - 1][x + 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y + 99;
							count_step_next += 1;
							continue;
						}
					}
				}
			}
			count_step_now = count_step_next;
			for (int i = 0; i < 100; i++) {
				step_record_now[i] = step_record_next[i];
				step_record_next[i] = 0;
			}
		}
		//最短路線尋找
		//方法一 計算出每格的路徑 求最小值 P:很難計算
		//方法二 在每一格存入上一個的位置 找到終點後直接回推 P:很難去往下尋找下一格 S:用一個陣列去存每一輪的新位置
		int first_step = 1;
		int ram = map_calculate[end_y][end_x];
		int next_step = 0;
		int check = 0;
		while (first_step) {
			x = ram / 100;
			y = ram % 100;
			if (map_calculate[y][x] != main_x * 100 + main_y) {
				//printf("%d ", x * 100 + y);
				check_step[check++] = x * 100 + y;//!!!!!!!!!!!!因為技術失誤 因此前面的XY顛倒了 在此將其相反過來
				ram = map_calculate[y][x];
				continue;
			}
			else {
				first_step = 0;
				check_step[check++] = x * 100 + y;
				next_step = ram;
			}
		}
		if (check == 0) {
			return 100 * x + y;
		}
		return check_step[--check];
	}

	void monster::findroad() {
		if (stopeverything == 1) {
			return;
		}
		//next_x = mon_x;
		//next_y = mon_y;
		next_step = automove(map_monster, mon_x, mon_y, CEraser::actor_x, CEraser::actor_y);
		//next_step = 100 * next_x + next_y;
		next_x = next_step / 100;
		next_y = next_step % 100;
	}

	int monster::mon_loc_judge(int x, int y) {
		if (monster::mon_bat_x == x && monster::mon_bat_y == y) {
			return 1;
		}
		return 0;
	}

	void monster::attack_judge(int x1, int y1, int x2, int y2) {
		if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
			printf("boss atk");
			eraser.attacked(mon_ATK);
		}
	}

	int monster::attacked_judge(int x1, int y1, int x2, int y2) {
		if (abs(x1 - x2) < 2 && abs(y1 - y2) < 2) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int monster::whichway(int mon_way_x, int mon_way_y, int next_way_x, int next_way_y, int main_x, int main_y) {//在與其他物件重疊時 應該走到哪一格代替
		if (next_way_x == mon_way_x + 1 && next_way_y == mon_way_y) {//往右
			if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_y > mon_way_y) {
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y - 1][next_way_x] != 3 && map_monster[next_way_y - 1][next_way_x] != 5 && main_y < mon_way_y) {
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x - 1 && next_way_y == mon_way_y) {//往左
			if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_y > mon_way_y) {
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y - 1][next_way_x] != 3 && map_monster[next_way_y - 1][next_way_x] != 5 && main_y < mon_way_y) {
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x && next_way_y == mon_way_y + 1) {//往下
			if (map_monster[next_way_y][next_way_x + 1] != 3 && map_monster[next_way_y][next_way_x + 1] != 5 && main_x > mon_way_x) {
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y][next_way_x - 1] != 3 && map_monster[next_way_y][next_way_x - 1] != 5 && main_x < mon_way_x) {
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_y -= 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x && next_way_y == mon_way_y - 1) {//往上
			if (map_monster[next_way_y][next_way_x + 1] != 3 && map_monster[next_way_y][next_way_x + 1] != 5 && main_x > mon_way_x) {
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y][next_way_x - 1] != 3 && map_monster[next_way_y][next_way_x - 1] != 5 && main_x < mon_way_x) {
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

	void monster::get_bat(int n, int x121, int y121) {//n是怪物的種類 xy是座標
		//printf("show1:%d,%d\n", mon_bat_x, mon_bat_y);
		if (n == 1) {
			monster::mon_bat_x = x121;
			monster::mon_bat_y = y121;
		}
		if (n == 2) {
			monster::mon2_x = x121;
			monster::mon2_y = y121;
		}
		//printf("show2:%d,%d\n", mon_bat_x, mon_bat_y);
	}

	int monster::getroad() {
		eraser.showdetail();
		if (deathshow == 1) {
			mon_x = 0;
			mon_y = 0;
			next_step = 0;
			SetXY(-100, -100);
			return 0;
/*
		if (mon_loc_judge(next_x, next_y) == 1) {
			next_step = whichway(mon_x, mon_y, next_x, next_y, CEraser::actor_x, CEraser::actor_y);
chun*/
		}
		/*if (mon_loc_judge(next_x, next_y) == 1) {
			next_step = whichway(mon_x, mon_y, next_x, next_y, CEraser::actor_x, CEraser::actor_y);
		}*/
		next_x = next_step / 100;
		next_y = next_step % 100;
		SetXY(CEraser::map_x + 45 * next_x, CEraser::map_y + 45 * next_y);
		mon_x = next_x;
		mon_y = next_y;
		LoadBitmap();
		showdata();
		return 0;
	}

	void monster::showdata() {
		printf("\nboss:\n");
		printf("HP:%d\n", mon_HP);
		printf("ATK:%d\n", mon_ATK);
		printf("Location:%d,%d\n", mon_x, mon_y);
		printf("X,Y:%d,%d\n", x, y);
		//printf("test:%d\n", test);
		//printf("show:%d,%d\n", monster::mon_bat_x, monster::mon_bat_y);
		printf("map:%d,%d\n", CEraser::map_x, CEraser::map_y);
		printf("mon1:%d,%d\n", mon_x, mon_y);
	}

	int monster::getmap(int random_map, int map[][27])
	{
		map_num = random_map;
		for (int i = 0; i < 25; i++)
			for (int j = 0; j < 27; j++)
				map_monster[i][j] = map[i][j];
		if (map_num == 7) {//24*24
			mon_HP = 50;
			mon_ATK = 1;
			mon_x = 1;
			mon_y = 9;
			next_step = 109;
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			stopeverything = 0;
		}
		else {
			mon_x = 0;
			mon_y = 0;
			SetXY(-100,-100);
		}
		LoadBitmap();
		//printf("monster_map:%d\n", map_num);
		return random_map;
	}

	int monster::Character() {
		return character;
	}

	int monster::GetX1()
	{
		return x;
	}

	int monster::GetY1()
	{
		return y;
	}

	int monster::GetX2()
	{
		return x + animation.Width();
	}

	int monster::GetY2()
	{
		return y + animation.Height();
	}

	void monster::Initialize()
	{
		const int X_POS = 920;//245 = 200 + 1*45
		const int Y_POS = 540;// 95 = 50  + 1*45
		character = 0;
	}

	void monster::LoadBitmap()
	{
		if (mon_HP == 50) {
			animation.cleanBitmap();
			animation.AddBitmap(boss, RGB(255, 255, 255));
			animation.AddBitmap(boss2, RGB(255, 255, 255));
			//Shp.LoadBitmap(mon_HP,mon_MAXHP);
			Shp.SetXY(GetX1(), GetY2());
		}
		if (mon_HP != 50 && mon_HP > 0) {
			animation.cleanBitmap();
			animation.AddBitmap(boss3, RGB(255, 255, 255));
			animation.AddBitmap(boss4, RGB(255, 255, 255));
			Shp.LoadBitmap(mon_HP, mon_MAXHP);
			Shp.SetXY(GetX1(), GetY2());
			printf("bitmap:%d", animation.GetCurrentBitmapNumber());
		}
		if (mon_HP < 1 && deathshow == 1) {
			printf("boss dead");
			animation.cleanBitmap();
			animation.SetDelayCount(5);
			animation.AddBitmap(boss5, RGB(255, 255, 255));
			animation.AddBitmap(boss6, RGB(255, 255, 255));
			animation.AddBitmap(boss7, RGB(255, 255, 255));
			animation.AddBitmap(boss8, RGB(255, 255, 255));
			animation.AddBitmap(death_mon, RGB(255, 255, 255));
			Shp.LoadBitmap(0, mon_MAXHP);
			Shp.SetXY(GetX1(), GetY2());
			deathshow = 0;
		}
	}

	void monster::OnMove()
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

	void monster::SetCharacter(int actor)
	{
		character = actor;
	}

	void monster::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		if (flag&& stopeverything == 0) {
			findroad();
		}
	}

	void monster::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag&& stopeverything == 0) {
			findroad();
		}
	}

	void monster::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag&& stopeverything == 0) {
			findroad();
		}
	}

	void monster::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag&& stopeverything == 0) {
			findroad();
		}
	}

	void monster::SetMoving(bool flag)
	{
		isMoving = flag;
		if (flag) {
			findroad();
			attack_judge(mon_x, mon_y, next_x, next_y);
			getroad();
		}
	}

	void monster::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void monster::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
		Shp.OnShow();
		if (animation.GetCurrentBitmapNumber() == 4) {
			animation.cleanBitmap();
			animation.AddBitmap(death_mon, RGB(255, 255, 255));
			x = eraser.GetX1() + 45;
			y = eraser.GetY1() + 45;
		}
	}

	int monster::attacked(int ATK) {//攻擊者的攻擊力 回傳被攻擊後的血量
		mon_HP -= ATK;
		printf("boss is attacked\n");
		LoadBitmap();
		if (mon_HP < 1) {
			//CAudio::Instance()->Play(SND_ghost,false);
			death();
		}
		return mon_HP - ATK;
	}

	void monster::death() {
		deathshow = 1;
		mon_x = CEraser::actor_x;
		mon_y = CEraser::actor_y;
		mon_ATK = 0;
		LoadBitmap();
	}

	void monster::superdeath() {
		animation.cleanBitmap();
		animation.AddBitmap(death_mon, RGB(255, 255, 255));
		mon_x = CEraser::actor_x;
		mon_y = CEraser::actor_y;
		mon_ATK = 0;
		mon_HP = 0;
		x = eraser.GetX1() + 45;
		y = eraser.GetY1() + 45;
		stopeverything = 1;
	}

	void monster::setdata(int m, int set_x, int set_y) {
		mon_HP = 20;
		mon_ATK = 0;
		mon_x = set_x;
		mon_y = set_y;
		switch (m)
		{
		case 1:
			SetXY(CEraser::map_x + 45 * mon_x, CEraser::map_y + 45 * mon_y);
			break;
		case 2:
			SetXY(695 + 45 * mon_x, 360 + 45 * mon_y);
			break;
		case 3:
			SetXY(245 + 45 * mon_x, 360 + 45 * mon_y);
			break;
		case 4:
			SetXY(825 + 45 * mon_x, 0 + 45 * mon_y);
			break;
		case 5:
			SetXY(245 + 45 * mon_x, -350 + 45 * mon_y);
			break;
		case 6:
			SetXY(475 + 45 * mon_x, 490 + 45 * mon_y);
			break;
		default:
			break;
		}

	};
}