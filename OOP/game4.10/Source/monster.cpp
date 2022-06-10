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
	const int STEP_SIZE = -45;
	const int STEP = -1; //�]���a�Ϯy�з|���� �ҥH��-1 �]�����W�쥻 �y�Ыܩ_��

	int monster::mon_bat_x = 0;
	int monster::mon_bat_y = 0;
	int monster::mon_x = 23;
	int monster::mon_y = 21;
	monster::monster()
	{
		map_x = 920 - CEraser::actor_x * 45;
		map_y = 540 - CEraser::actor_y * 45;
		main_x = 0;
		main_y = 0;
		printf("map:%d,%d", map_x, map_y);
		printf("mon1:%d,%d\n", monster::mon_x, monster::mon_y);
		Initialize();
		SetXY(920 + 45 * monster::mon_x, 540 + 45 * monster::mon_y);
	}
	int monster::automove(int automove_map[][27], int main_x, int main_y, int end_x, int end_y,int mon1,int mon2) {
		int map_calculate[25][27];//�p��Ϊ��a��
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
		//map_calculate[mon1 % 100][mon1 / 100] = -1;
		//map_calculate[mon2 % 100][mon2 / 100] = -1;
		map_calculate[main_y][main_x] = main_x * 100 + main_y;//�_�I���_�I�y��
		map_calculate[end_y][end_x] = -2;//���I��-2
		int check_step[100];
		int count_step_now = 0;//�O���o�@�馳�X��
		int count_step_next = 0;//�����s���@�馳�X�ӷs��m
		int search = 1;
		int step_record_now[100];//�����o�@�骺��m
		int step_record_next[100];//�����s���@�骺��m
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
		while (search) {//�s���u���j�M�k BFS
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
		//�̵u���u�M��
		//��k�@ �p��X�C�檺���| �D�̤p�� P:�����p��
		//��k�G �b�C�@��s�J�W�@�Ӫ���m �����I�᪽���^�� P:�����h���U�M��U�@�� S:�Τ@�Ӱ}�C�h�s�C�@�����s��m
		int first_step = 1;
		int ram = map_calculate[end_y][end_x];
		int next_step = 0;
		int check = 0;
		while (first_step) {
			x = ram / 100;
			y = ram % 100;
			if (map_calculate[y][x] != main_x * 100 + main_y) {
				printf("%d ", x * 100 + y);
				check_step[check++] = x * 100 + y;//!!!!!!!!!!!!�]���޳N���~ �]���e����XY�A�ˤF �b���N��ۤϹL��
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
		next_x = monster::mon_x;
		next_y = monster::mon_y;
		next_step = automove(map_monster, monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y, monster::mon_bat_x * 100 + monster::mon_bat_y, monster::mon2_x * 100 + monster::mon2_x);
		next_x = next_step / 100;
		next_y = next_step % 100;
	}

	int monster::attacked(int ATK) {//�����̪������O �^�ǳQ�����᪺��q
		return mon_HP - ATK;
	}

	void monster::attack_judge(int x1, int y1, int x2, int y2) {
		printf("judge:%d,%d,%d,%d\n", x1, y1, x2, y2);
		if (x1 == x2 && y1 == y2) {
			eraser.attacked(mon_ATK);
		}
	}

	int monster::mon_loc_judge(int x, int y) {
		if (monster::mon_bat_x == x && monster::mon_bat_y == y) {
			return 1;
		}
		return 0;
	};

	int monster::whichway(int mon_way_x, int mon_way_y, int next_way_x, int next_way_y,int main_x,int main_y) {//�b�P��L�����|�� ���Ө�����@��N��
		if (next_way_x == mon_way_x + 1 && next_way_y == mon_way_y) {//���k
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
		if (next_way_x == mon_way_x - 1 && next_way_y == mon_way_y) {//����
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
		if (next_way_x == mon_way_x && next_way_y == mon_way_y + 1) {//���U
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
		if (next_way_x == mon_way_x && next_way_y == mon_way_y - 1) {//���W
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
		if (next_way_x == mon_way_x + 1 && next_way_y == mon_way_y - 1) {//���k�W
			if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_x > mon_way_x+1) {
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y][next_way_x - 1] != 3 && map_monster[next_way_y][next_way_x - 1] != 5 && main_y > mon_way_y - 1) {
				next_way_x -= 1;
				return next_way_x * 100 + next_way_y;
			}
			else {
				next_way_x -= 1;
				next_way_y += 1;
				return next_way_x * 100 + next_way_y;
			}
		}
		if (next_way_x == mon_way_x - 1 && next_way_y == mon_way_y + 1) {//�����U
			if (map_monster[next_way_y - 1][next_way_x] != 3 && map_monster[next_way_y - 1][next_way_x] != 5 && main_x > mon_way_x - 1) {
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
		if (next_way_x == mon_way_x + 1 && next_way_y == mon_way_y + 1) {//���k�U
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
		if (next_way_x == mon_way_x - 1 && next_way_y == mon_way_y - 1) {//�����W
			if (map_monster[next_way_y][next_way_x + 1] != 3 && map_monster[next_way_y][next_way_x + 1] != 5 && main_y > mon_way_y - 1) {
				next_way_x += 1;
				return next_way_x * 100 + next_way_y;
			}
			else if (map_monster[next_way_y + 1][next_way_x] != 3 && map_monster[next_way_y + 1][next_way_x] != 5 && main_x > mon_way_x - 1) {
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

	int monster::Character() {
		return character;
	}

	void monster::get_bat(int n,int x121,int y121) {//n�O�Ǫ������� xy�O�y��
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

	void monster::showdetail() {
		eraser.showdetail();
		if (mon_loc_judge(next_x, next_y) == 1) {
			next_step = whichway(monster::mon_x, monster::mon_y, next_x, next_y,CEraser::actor_x,CEraser::actor_y);
		}
		next_x = next_step / 100;
		next_y = next_step % 100;
		x += (next_x - monster::mon_x) * 45;
		y += (next_y - monster::mon_y) * 45;
		monster::mon_x = next_x;
		monster::mon_y = next_y;
		//printf("\nmonster1:\n");
		//printf("HP:%d\n", mon_HP);
		//printf("ATK:%d\n", mon_ATK);
		//printf("Location:%d,%d\n", mon_x,mon_y);
		//printf("X,Y:%d,%d\n\n", x, y);
		printf("test:%d\n", test);
		printf("show:%d,%d\n", monster::mon_bat_x, monster::mon_bat_y);
	}

	int monster::getmap(int random_map, int map[][27])
	{
		map_num = random_map;
		for (int i = 0; i < 25; i++)
			for (int j = 0; j < 27; j++)
				map_monster[i][j] = map[i][j];
		if (map_num == 2) {
			monster::mon_x = 18;
			monster::mon_y = 17;
			map_x = 740;
			map_y = 405;
			CEraser::actor_x = 6;
			CEraser::actor_y = 5;
			SetXY(695 + 45 * monster::mon_x, 360 + 45 * monster::mon_y);
		}
		if (map_num == 3) {
			monster::mon_x = 8;
			monster::mon_y = 17;
			CEraser::actor_x = 16;
			CEraser::actor_y = 5;
			SetXY(245 + 45 * monster::mon_x, 360 + 45 * monster::mon_y);
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
			}
			findroad();
			attack_judge(monster::mon_x, monster::mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				x -= STEP_SIZE;
			}
			findroad();
			attack_judge(monster::mon_x, monster::mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				x += STEP_SIZE;
			}
			findroad();
			attack_judge(monster::mon_x, monster::mon_y, next_x, next_y);
			showdetail();
		}
	}

	void monster::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag) {
			if (CGameMap::ismoving == 1) {
				y -= STEP_SIZE;
			}
			findroad();
			attack_judge(monster::mon_x, monster::mon_y, next_x, next_y);
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
}