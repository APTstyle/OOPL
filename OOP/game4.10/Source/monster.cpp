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

	int monster::mon_x = 23;
	int monster::mon_y = 21;
	const int STEP_SIZE = -45;
	const int STEP = -1; //因為地圖座標會移動 所以為-1 因不知名原本 座標很奇怪
	int next_step, next_x, next_y;
	monster::monster()
	{
		printf("%d,%d",mon_x,mon_y);
		Initialize();
		SetXY(200 + 45 * monster::mon_x, 50 + 45 * monster::mon_y);
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
		int x = main_y, y = main_x;
		if (map_calculate[x][y + 1] == -2 || map_calculate[x + 1][y + 1] == -2 || map_calculate[x - 1][y + 1] == -2 || map_calculate[x][y] == -2 || map_calculate[x + 1][y] == -2 || map_calculate[x - 1][y] == -2 || map_calculate[x][y - 1] == -2 || map_calculate[x + 1][y - 1] == -2 || map_calculate[x - 1][y - 1] == -2) {
			return main_x * 100 + main_y;
		}
		if (map_calculate[x][y + 1] == 0) {
			map_calculate[x][y + 1] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y + 1;
			count_step_now += 1;
		}
		if (map_calculate[x - 1][y] == 0) {
			map_calculate[x - 1][y] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y - 100;
			count_step_now += 1;
		}
		if (map_calculate[x][y - 1] == 0) {
			map_calculate[x][y - 1] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y - 1;
			count_step_now += 1;
		}
		if (map_calculate[x + 1][y] == 0) {
			map_calculate[x + 1][y] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y + 100;
			count_step_now += 1;
		}
		if (map_calculate[x + 1][y + 1] == 0) {
			map_calculate[x + 1][y + 1] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y + 101;
			count_step_now += 1;
		}
		if (map_calculate[x + 1][y - 1] == 0) {
			map_calculate[x + 1][y - 1] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y + 99;
			count_step_now += 1;
		}
		if (map_calculate[x - 1][y - 1] == 0) {
			map_calculate[x - 1][y - 1] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y - 101;
			count_step_now += 1;
		}
		if (map_calculate[x - 1][y + 1] == 0) {
			map_calculate[x - 1][y + 1] = x * 100 + y;
			step_record_now[count_step_now] = x * 100 + y - 99;
			count_step_now += 1;
		}
		while (search) {//廣度優先搜尋法 BFS
			count_step_next = 0;
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < count_step_now; i++) {
					x = step_record_now[i] / 100;
					y = step_record_now[i] % 100;
					if (map_calculate[x][y + 1] == -2 || map_calculate[x][y - 1] == -2 || map_calculate[x + 1][y] == -2 || map_calculate[x - 1][y] == -2 || map_calculate[x + 1][y - 1] == -2 || map_calculate[x - 1][y + 1] == -2 || map_calculate[x + 1][y + 1] == -2 || map_calculate[x - 1][y - 1] == -2) {
						search = 0;
						i = 100;
						j = 3;
						map_calculate[end_y][end_x] = x * 100 + y;
						continue;
					}
					if (map_calculate[x][y + 1] == 0) {
						map_calculate[x][y + 1] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y + 1;
						count_step_next += 1;
						continue;
					}
					if (map_calculate[x - 1][y] == 0) {
						map_calculate[x - 1][y] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y - 100;
						count_step_next += 1;
						continue;
					}
					if (map_calculate[x][y - 1] == 0) {
						map_calculate[x][y - 1] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y - 1;
						count_step_next += 1;
						continue;
					}
					if (map_calculate[x + 1][y] == 0) {
						map_calculate[x + 1][y] = x * 100 + y;
						step_record_next[count_step_next] = x * 100 + y + 100;
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
						if (map_calculate[x + 1][y + 1] == 0) {
							map_calculate[x + 1][y + 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y + 101;
							count_step_next += 1;
							continue;
						}
						if (map_calculate[x + 1][y - 1] == 0) {
							map_calculate[x + 1][y - 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y + 99;
							count_step_next += 1;
							continue;
						}
						if (map_calculate[x - 1][y - 1] == 0) {
							map_calculate[x - 1][y - 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y - 101;
							count_step_next += 1;
							continue;
						}
						if (map_calculate[x - 1][y + 1] == 0) {
							map_calculate[x - 1][y + 1] = x * 100 + y;
							step_record_next[count_step_next] = x * 100 + y - 99;
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
		while (first_step)
		{
			x = ram / 100;
			y = ram % 100;
			if (map_calculate[x][y] != main_x * 100 + main_y) {
				check_step[check++] = y * 100 + x;//!!!!!!!!!!!!因為技術失誤 因此前面的XY顛倒了 在此將其相反過來
				ram = map_calculate[x][y];
				continue;
			}
			else {
				first_step = 0;
				next_step = ram;
			}
		}
		if (check == 0) {
			return 100 * y + x;
		}
		return check_step[--check];
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
		const int X_POS = 200;//245 = 200 + 1*45
		const int Y_POS = 50;// 95 = 50  + 1*45
		character = 0;
		mon_x = 23;
		mon_y = 21;
	}

	void monster::LoadBitmap()
	{
		//animation.AddBitmap(warrior, RGB(255, 255, 255));
		animation.AddBitmap(boss, RGB(255, 255, 255));
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
				CGameMap::ismoving = 0;
			}
			printf("---------------------------\n");
			printf("checkdata:%d,%d,%d,%d\n", monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = monster::mon_x;
			next_y = monster::mon_y;
			printf("next_XY:%d,%d\n", next_x, next_y);
			next_step = automove(map_monster, monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = next_step / 100;
			next_y = next_step % 100;
			x += (next_x - monster::mon_x) * 45;
			y += (next_y - monster::mon_y) * 45;
			monster::mon_x = next_x;
			monster::mon_y = next_y;
			printf("automove:%d\n", next_step);
			printf("automove_XY:%d,%d\n", next_x, next_y);
			printf("charactor_XY:%d,%d\n", CEraser::actor_x, CEraser::actor_y);
			printf("mon_loca_XY:%d,%d\n", x, y);
			printf("automove_mon_XY:%d,%d\n", monster::mon_x, monster::mon_y);

		}
	}

	void monster::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				x -= STEP_SIZE;
				CGameMap::ismoving = 0;
			}
			printf("---------------------------\n");
			printf("checkdata:%d,%d,%d,%d\n", monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = monster::mon_x;
			next_y = monster::mon_y;
			printf("next_XY:%d,%d", next_x, next_y);
			next_step = automove(map_monster, monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = next_step / 100;
			next_y = next_step % 100;
			x += (next_x - monster::mon_x) * 45;
			y += (next_y - monster::mon_y) * 45;
			monster::mon_x = next_x;
			monster::mon_y = next_y;

			printf("automove:%d\n", next_step);
			printf("automove_XY:%d,%d\n", next_x, next_y);
			printf("charactor_XY:%d,%d\n", CEraser::actor_x, CEraser::actor_y);
			printf("mon_loca_XY:%d,%d\n", x, y);
			printf("automove_mon_XY:%d,%d\n", mon_x, mon_y);
		}
	}

	void monster::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				x += STEP_SIZE;
				CGameMap::ismoving = 0;
			}
			printf("---------------------------\n");
			printf("checkdata:%d,%d,%d,%d\n", monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = monster::mon_x;
			next_y = monster::mon_y;
			printf("next_XY:%d,%d", next_x, next_y);
			next_step = automove(map_monster, monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = next_step / 100;
			next_y = next_step % 100;
			x += (next_x - monster::mon_x) * 45;
			y += (next_y - monster::mon_y) * 45;
			monster::mon_x = next_x;
			monster::mon_y = next_y;

			printf("automove:%d\n", next_step);
			printf("automove_XY:%d,%d\n", next_x, next_y);
			printf("charactor_XY:%d,%d\n", CEraser::actor_x, CEraser::actor_y);
			printf("mon_loca_XY:%d,%d\n", x, y);
			printf("automove_mon_XY:%d,%d\n", mon_x, mon_y);
		}
	}

	void monster::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				y -= STEP_SIZE;
				CGameMap::ismoving = 0;
			}
			printf("---------------------------\n");
			printf("checkdata:%d,%d,%d,%d\n", monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = monster::mon_x;
			next_y = monster::mon_y;
			printf("next_XY:%d,%d", next_x, next_y);
			next_step = automove(map_monster, monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y);
			next_x = next_step / 100;
			next_y = next_step % 100;
			x += (next_x - monster::mon_x) * 45;
			y += (next_y - monster::mon_y) * 45;
			monster::mon_x = next_x;
			monster::mon_y = next_y;

			printf("automove:%d\n", next_step);
			printf("automove_XY:%d,%d\n", next_x, next_y);
			printf("charactor_XY:%d,%d\n", CEraser::actor_x, CEraser::actor_y);
			printf("mon_loca_XY:%d,%d\n", x, y);
			printf("automove_mon_XY:%d,%d\n", mon_x, mon_y);
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
}