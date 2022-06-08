#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "monster.h"
#include "CEraser.h"
#include "mygame.h"

namespace game_framework {
	int map_monster[25][27] = {
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
	// monster: Eraser class
	/////////////////////////////////////////////////////////////////////////////
	const int STEP_SIZE = -45;
	const int STEP = -1; //因為地圖座標會移動 所以為-1 因不知名原本 座標很奇怪
	int next_step, next_x, next_y;
	int map_x = 965, map_y = 585;//對於當前地圖左上角的X座標與Y座標
	monster::monster()
	{
		map_x = 920 - CEraser::actor_x * 45;
		map_y = 540 - CEraser::actor_y * 45;
		mon_x = 23;
		mon_y = 21;
		printf("map:%d,%d", map_x, map_y);
		printf("mon1:%d,%d\n",mon_x,mon_y);
		Initialize();
		SetXY(920 + 45 * mon_x, 540 + 45 * mon_y);
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
		while (first_step){
			x = ram / 100;
			y = ram % 100;
			if (map_calculate[y][x] != main_x * 100 + main_y) {
				printf("%d ", x * 100 + y);
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

	void monster :: findroad() {
		next_x = mon_x;
		next_y = mon_y;
		next_step = automove(map_monster, mon_x, mon_y, CEraser::actor_x, CEraser::actor_y);
		next_x = next_step / 100;
		next_y = next_step % 100;
	}

	int monster::attacked(int ATK) {//攻擊者的攻擊力 回傳被攻擊後的血量
		return mon_HP - ATK;
	}

	void monster::attack_judge(int x1,int y1,int x2,int y2) {
		printf("judge:%d,%d,%d,%d\n", x1, y1, x2, y2);
		if (x1 == x2 && y1 == y2) {
			eraser.attacked(mon_ATK);
		}
	}

	int monster::Character() {
		return character;
	}

	void monster::showdetail() {
		eraser.showdetail();
		x += (next_x - mon_x) * 45;
		y += (next_y - mon_y) * 45;
		mon_x = next_x;
		mon_y = next_y;
		//printf("\nmonster1:\n");
		//printf("HP:%d\n", mon_HP);
		//printf("ATK:%d\n", mon_ATK);
		//printf("Location:%d,%d\n", mon_x,mon_y);
		//printf("X,Y:%d,%d\n\n", x, y);
	}

	int monster::getmap(int random_map, int map[][27])
	{
		map_num = random_map;
		for (int i = 0; i < 25; i++)
			for (int j = 0; j < 27; j++)
				map_monster[i][j] = map[i][j];
		if (map_num == 2) {
			mon_x = 18;
			mon_y = 17;
			CEraser::actor_x = 6;
			CEraser::actor_y = 5;
			SetXY(695 + 45 * mon_x, 360 + 45 * mon_y);
		}
		if (map_num == 3) {
			mon_x = 8;
			mon_y = 17;
			CEraser::actor_x = 16;
			CEraser::actor_y = 5;
			SetXY(245 + 45 * mon_x, 360 + 45 * mon_y);
		}
		//printf("monster_map:%d\n", map_num);
		return random_map;
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
		//animation.AddBitmap(warrior, RGB(255, 255, 255));
		animation.AddBitmap(boss, RGB(255, 255, 255));
		animation.AddBitmap(boss2, RGB(255, 255, 255));
		if (mon_HP != 20) {
			animation.AddBitmap(boss3, RGB(255, 255, 255));
			animation.AddBitmap(boss4, RGB(255, 255, 255));
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
		if (flag) {
			if (CGameMap::ismoving == 1) {
				y += STEP_SIZE;
				map_y += STEP_SIZE;
				CGameMap::ismoving = 0;
			}
			findroad();
			attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				x -= STEP_SIZE;
				map_x -= STEP_SIZE;
				CGameMap::ismoving = 0;
			}
			findroad();
			attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				x += STEP_SIZE;
				map_x += STEP_SIZE;
				CGameMap::ismoving = 0;
			}
			findroad();
			attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				y -= STEP_SIZE;
				map_y -= STEP_SIZE;
				CGameMap::ismoving = 0;
			}
			findroad();
			attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
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
	}
//----------------------------bat class--------------------
	monster_bat::monster_bat()		{
		mon_x = 24;
		mon_y = 1;
		printf("%d,%d\n", mon_x, mon_y);
		Initialize();
		SetXY(map_x + 45 * mon_x +45, map_y + 45 * mon_y+45);
	}

	int monster_bat::Character() {
		return character;
	}

	void monster_bat::showdetail() {
		mon_x = next_x;
		mon_y = next_y;
		x = map_x + 45 * mon_x +45;
		y = map_y + 45 * mon_y + 45;
		printf("\nmonster2:\n");
		printf("HP:%d\n", mon_HP);
		printf("ATK:%d\n", mon_ATK);
		printf("Location:%d,%d\n", mon_x, mon_y);
		printf("X,Y:%d,%d\n\n", x, y);
		printf("\nmap:%d,%d\n", map_x, map_y);
	}
	void monster_bat::findroad() {
		next_x = mon_x;
		next_y = mon_y;
		next_step = monster_cpp.automove(map_monster, mon_x, mon_y, CEraser::actor_x, CEraser::actor_y);
		next_x = next_step / 100;
		next_y = next_step % 100;
	}

	int monster_bat::getmap(int random_map, int map[][27])
	{
		map_num = random_map;
		if (map_num == 2) {
			mon_x = 18;//24-actor_x
			mon_y = -3;//2-actor_y
			CEraser::actor_x = 6;
			CEraser::actor_y = 5;
			SetXY(695 + 45 * mon_x, 360 + 45 *mon_y);
		}
		if (map_num == 3) {
			mon_x = 8;
			mon_y = -3;
			CEraser::actor_x = 16;
			CEraser::actor_y = 5;
			SetXY(245 + 45 * mon_x, 360 + 45 * mon_y);
		}
		//printf("monster_map:%d\n", map_num);
		return random_map;
	}

	int monster_bat::GetX1()
	{
		return x;
	}

	int monster_bat::GetY1()
	{
		return y;
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
			findroad();
			monster_cpp.attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();

		}
	}

	void monster_bat::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) {
			findroad();
			monster_cpp.attack_judge(mon_x,  mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster_bat::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) {
			findroad();
			monster_cpp.attack_judge(mon_x, mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster_bat::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag) {
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