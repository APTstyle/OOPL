#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"
#include "mygame.h"

namespace game_framework {
	int CEraser::map_x = 920;
	int CEraser::map_y = 540;

	CEraser::CEraser()
	{
		Initialize();
		showdata();
		//CAudio::Instance()->Load(SND_hit, "sounds\\snd_hit.mp3");

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
		CEraser::hero_max_hp = 20;
		CEraser::hero_def = 10;
		direction = true;
		moving = false;
		movingcount = 0;
		attacking = false;
	}
	void CEraser::changeskin(int c) {
		animation_walk.SetDelayCount(2);
		animation_walk_l.SetDelayCount(2);
		animation.cleanBitmap();
		animation2.cleanBitmap();
		animation_walk.cleanBitmap();
		animation_walk_l.cleanBitmap();
		animation_atk.cleanBitmap();
		animation_atk_l.cleanBitmap();
		animation_icon.cleanBitmap();
		animation_hp_background.AddBitmap(hero_status, RGB(255, 255, 255));
		if (character == 1) {
			animation.AddBitmap(warrior, RGB(255, 255, 255));
			animation2.AddBitmap(warrior_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_warrior_hp, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk1, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk2, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk3, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk4, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk5, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk6, RGB(255, 255, 255));
			animation_atk.AddBitmap(warrior_attack1, RGB(255, 255, 255));
			animation_atk.AddBitmap(warrior_attack2, RGB(255, 255, 255));
			animation_atk.AddBitmap(warrior_attack3, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk1_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk2_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk3_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk4_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk5_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk6_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(warrior_attack1_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(warrior_attack2_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(warrior_attack3_l, RGB(255, 255, 255));
		}
		else if (character == 2) {
			animation.AddBitmap(mage, RGB(255, 255, 255));
			animation2.AddBitmap(mage_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_mage_hp, RGB(255, 255, 255));
			animation_walk.AddBitmap(mage_walk1, RGB(255, 255, 255));
			animation_walk.AddBitmap(mage_walk2, RGB(255, 255, 255));
			animation_walk.AddBitmap(mage_walk3, RGB(255, 255, 255));
			animation_walk.AddBitmap(mage_walk4, RGB(255, 255, 255));
			animation_walk.AddBitmap(mage_walk5, RGB(255, 255, 255));
			animation_walk.AddBitmap(mage_walk6, RGB(255, 255, 255));
			animation_atk.AddBitmap(mage_attack1, RGB(255, 255, 255));
			animation_atk.AddBitmap(mage_attack2, RGB(255, 255, 255));
			animation_atk.AddBitmap(mage_attack3, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(mage_walk1_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(mage_walk2_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(mage_walk3_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(mage_walk4_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(mage_walk5_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(mage_walk6_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(mage_attack1_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(mage_attack2_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(mage_attack3_l, RGB(255, 255, 255));
		}
		else if (character == 3) {
			animation.AddBitmap(assassin, RGB(255, 255, 255));
			animation2.AddBitmap(rogue_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_assassin_hp, RGB(255, 255, 255));
			animation_walk.AddBitmap(rogue_walk1, RGB(255, 255, 255));
			animation_walk.AddBitmap(rogue_walk2, RGB(255, 255, 255));
			animation_walk.AddBitmap(rogue_walk3, RGB(255, 255, 255));
			animation_walk.AddBitmap(rogue_walk4, RGB(255, 255, 255));
			animation_walk.AddBitmap(rogue_walk5, RGB(255, 255, 255));
			animation_walk.AddBitmap(rogue_walk6, RGB(255, 255, 255));
			animation_atk.AddBitmap(rogue_attack1, RGB(255, 255, 255));
			animation_atk.AddBitmap(rogue_attack2, RGB(255, 255, 255));
			animation_atk.AddBitmap(rogue_attack3, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(rogue_walk1_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(rogue_walk2_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(rogue_walk3_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(rogue_walk4_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(rogue_walk5_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(rogue_walk6_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(rogue_attack1_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(rogue_attack2_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(rogue_attack3_l, RGB(255, 255, 255));
		}
		else if (character == 4) {
			animation.AddBitmap(hunter, RGB(255, 255, 255));
			animation2.AddBitmap(ranger_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_hunter_hp, RGB(255, 255, 255));
			animation_walk.AddBitmap(ranger_walk1, RGB(255, 255, 255));
			animation_walk.AddBitmap(ranger_walk2, RGB(255, 255, 255));
			animation_walk.AddBitmap(ranger_walk3, RGB(255, 255, 255));
			animation_walk.AddBitmap(ranger_walk4, RGB(255, 255, 255));
			animation_walk.AddBitmap(ranger_walk5, RGB(255, 255, 255));
			animation_walk.AddBitmap(ranger_walk6, RGB(255, 255, 255));
			animation_atk.AddBitmap(ranger_attack1, RGB(255, 255, 255));
			animation_atk.AddBitmap(ranger_attack2, RGB(255, 255, 255));
			animation_atk.AddBitmap(ranger_attack3, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(ranger_walk1_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(ranger_walk2_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(ranger_walk3_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(ranger_walk4_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(ranger_walk5_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(ranger_walk6_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(ranger_attack1_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(ranger_attack2_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(ranger_attack3_l, RGB(255, 255, 255));
		}
		setdata(c);
	}

	void CEraser::LoadBitmap()
	{
		animation.cleanBitmap();
		animation2.cleanBitmap();
		animation_walk.cleanBitmap();
		animation_walk_l.cleanBitmap();
		animation_atk.cleanBitmap();
		animation_atk_l.cleanBitmap();
		animation_test.LoadBitmap(herohp1, RGB(255, 255, 255));
		animation_hp_background.AddBitmap(hero_status, RGB(255, 255, 255));
		//animation.AddBitmap(warrior, RGB(255, 255, 255));
		if (character == 1) {
			animation.AddBitmap(warrior, RGB(255, 255, 255));
			animation2.AddBitmap(warrior_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_warrior_hp, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk1, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk2, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk3, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk4, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk5, RGB(255, 255, 255));
			animation_walk.AddBitmap(warrior_walk6, RGB(255, 255, 255));
			animation_atk.AddBitmap(warrior_attack1, RGB(255, 255, 255));
			animation_atk.AddBitmap(warrior_attack2, RGB(255, 255, 255));
			animation_atk.AddBitmap(warrior_attack3, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk1_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk2_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk3_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk4_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk5_l, RGB(255, 255, 255));
			animation_walk_l.AddBitmap(warrior_walk6_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(warrior_attack1_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(warrior_attack2_l, RGB(255, 255, 255));
			animation_atk_l.AddBitmap(warrior_attack3_l, RGB(255, 255, 255));
		}
		else if (character == 2) {
			animation.AddBitmap(mage, RGB(255, 255, 255));
			animation2.AddBitmap(mage_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_mage_hp, RGB(255, 255, 255));
		}
		else if (character == 3) {
			animation.AddBitmap(assassin, RGB(255, 255, 255));
			animation2.AddBitmap(rogue_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_assassin_hp, RGB(255, 255, 255));
		}
		else if (character == 4) {
			animation.AddBitmap(hunter, RGB(255, 255, 255));
			animation2.AddBitmap(ranger_l, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_hunter_hp, RGB(255, 255, 255));
		}
		/*else {
			animation.AddBitmap(mage, RGB(255, 255, 255));
			animation_hp_background.AddBitmap(ui_item1, RGB(255, 255, 255));
			animation_icon.AddBitmap(charactor_mage_hp, RGB(255, 255, 255));
		}*/
	}
	int CEraser::actor_x = 1;
	int CEraser::actor_y = 1;
	int CEraser::hero_HP = 20;
	int CEraser::hero_ATK = 4;
	int CEraser::hero_def = 10;
	int CEraser::hero_max_hp = 20;
	int CEraser::hero_hungry = 200;
	int show = 1;
	void CEraser::OnMove()
	{

		const int STEP_SIZE = 0;
		animation.OnMove();
		animation2.OnMove();
		animation_walk.OnMove();
		animation_walk_l.OnMove();
		animation_atk.OnMove();
		animation_atk_l.OnMove();
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

	void CEraser::equiparmor(int item) {
		
			hero_armor = item;
		
		
	}
	void CEraser::equipweapon(int item) {
		
			hero_weapon = item;
		
	}
	void CEraser::equipring(int item) {
		
		
			hero_ring = item;
		
	}
	int CEraser::checkarmor() {
		return hero_armor;
	}
	int CEraser::checkweapon() {
		return hero_weapon;
	}
	int CEraser::checkring() {
		return hero_ring;
	}
	void CEraser::showwalk(int n) {
		animation_walk_l.SetTopLeft(x, y);
		animation_walk_l.OnShow(); 
		if (animation_walk.GetCurrentBitmapNumber() >0) {
			return;
		}
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		if (flag) {
			CEraser::actor_y += 1;
			moving = true;
		}
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) {
			CEraser::actor_x -= 1;
			direction = false;
			moving = true;
		}
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) {
			CEraser::actor_x += 1;
			direction = true;
			moving = true;
		}
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if (flag) {
			CEraser::actor_y -= 1;
			moving = true;
		}
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	int CEraser::OnShow()
	{
		if (attacking == true) {
			if (direction == true) {
				animation_atk.SetTopLeft(x, y);
				animation_atk.OnShow();
			}
			else {
				animation_atk_l.SetTopLeft(x, y);
				animation_atk_l.OnShow();
			}
			printf("\n%d\n", animation_walk.GetCurrentBitmapNumber());
			if (animation_atk_l.GetCurrentBitmapNumber() == 2 || animation_atk.GetCurrentBitmapNumber() == 2) {
				attacking = false;
			}
		}
		else {
			if (moving == false) {
				if (direction == true) {
					animation.SetTopLeft(x, y);
					animation.OnShow();
				}
				if (direction == false) {
					animation2.SetTopLeft(x, y);
					animation2.OnShow();
				}
			}
			else {
				if (direction == true) {
					animation_walk.SetTopLeft(x, y);
					animation_walk.OnShow();
				}
				else if (direction == false) {
					animation_walk_l.SetTopLeft(x, y);
					animation_walk_l.OnShow();
				}
				printf("\n%d\n", animation_walk.GetCurrentBitmapNumber());
				if (animation_walk.GetCurrentBitmapNumber() == 5 || animation_walk_l.GetCurrentBitmapNumber() == 5) {
					moving = false;
				}
			}
		}
		animation_hp_background.SetTopLeft(0, 0);
		animation_hp_background.OnShow();
		animation_icon.SetTopLeft(30, 30);
		animation_icon.OnShow();
		for (int i = 0; i < CEraser::hero_HP*200 /CEraser::hero_max_hp; i++) {
			animation_test.SetTopLeft(132+i, 7);
			animation_test.ShowBitmap();
		}
		return 0;
	}

	int CEraser::attacked(int ATK) {//攻擊者的攻擊力 回傳被攻擊後的血量

		printf("atked CEraser::hero_def:%d\n", CEraser::hero_def);
		if (ATK == 0) {
			return CEraser::hero_HP;
		}
		if ((CEraser::hero_def * 2 - ATK * 3) > 0) {
			return CEraser::hero_HP;
		}
		CEraser::hero_HP -=ATK*3;
		CEraser::hero_HP += CEraser::hero_def * 2;
		printf("Hero is attacked\n");
		return CEraser::hero_HP;
	}

	void CEraser::showdetail() {
		printf("\nHero:\n");
		printf("HP:%d\n", CEraser::hero_HP);
		//printf("ATK:%d\n", CEraser::hero_ATK);
		printf("Location:%d,%d\n", actor_x, actor_y);
		printf("X,Y:%d,%d\n", x, y);
	}

	void CEraser::showdata() {
		/*printf("\nHero:\n");
		printf("HP:%d\n", CEraser::hero_HP);
		//printf("ATK:%d\n", CEraser::hero_ATK);
		printf("Location:%d,%d\n", CEraser::actor_x, CEraser::actor_y);
		printf("X,Y:%d,%d\n", x, y);*/
	}

	void CEraser::reset(int m) {
		hero_HP = 5;
		CEraser::hero_ATK = 4;
		if (m == 1) {
			CEraser::actor_x = 1;
			CEraser::actor_y = 1;
			SetXY(920,540);
		}
		else if (m == 2) {
			CEraser::actor_x = 6;
			CEraser::actor_y = 5;
			SetXY(695, 360);
		}
		else if (m == 3) {
			CEraser::actor_x = 16;
			CEraser::actor_y = 5;
			SetXY(245, 360);
		}
		else if (m == 4) {
			CEraser::actor_x = 3;
			CEraser::actor_y = 13;
			SetXY(825, 0);
		}
		else if (m == 5) {
			CEraser::actor_x = 16;
			CEraser::actor_y = 21;
			SetXY(245, -350);
		}
		else if (m == 6) {
			CEraser::actor_x = 11;
			CEraser::actor_y = 2;
			SetXY(475, 490);
		}
		else if (m == 7) {
			CEraser::actor_x = 3;
			CEraser::actor_y = 2;
			SetXY(835, 485);
		}
		showdata();
	}

	int CEraser::changedef(int n) {
		CEraser::hero_def += n;
		return CEraser::hero_def;
	}
	int CEraser::changeatk(int n) {
		CEraser::hero_ATK += n;
		return CEraser::hero_ATK;
	}
	int CEraser::changemaxhp(int n) {
		CEraser::hero_max_hp += n;
		return CEraser::hero_max_hp;
	}
	void CEraser::heal() {
		CEraser::hero_HP = CEraser::hero_max_hp;
	}
	void CEraser::addhp(int n) {
		if (CEraser::hero_HP + n > CEraser::hero_max_hp) {
			CEraser::hero_HP = CEraser::hero_max_hp;
		}
		else {
			CEraser::hero_HP += n;
		}
		
	}

	void CEraser::stave() {
		if (CEraser::hero_hungry == 0) {
			CEraser::hero_HP -= 1;
		}
		else {
			CEraser::hero_hungry -= 1;
		}
		printf("CEraser::hero_hungry:%d", CEraser::hero_hungry);
	}

	void CEraser::setdata(int n) {
		switch (n)
		{
		case 1:
			changemaxhp(20);
			heal();
			break;
		case 2:
			changedef(2);
			break;
		case 3:
			changeatk(2);
			break;
		case 4:
			changedef(1);
			changeatk(1);
			changemaxhp(10);
			heal();
			break;
		default:
			break;
		}
	}
}