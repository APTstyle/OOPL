#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "showHp.h"

namespace game_framework {
	void showHp::ShowHP(){

		x = 0;
		y = 0;
		Initialize();
		showdata();
		data = 0;
		maxHP = 1;
		load = false;
	}


	int showHp::GetX1()
	{
		return x;
	}

	int showHp::GetY1()
	{
		return y;
	}

	int showHp::GetX2()
	{
		return x + animation.Width();
	}

	int showHp::GetY2()
	{
		return y + animation.Height();
	}

	void showHp::Initialize()	{
		SetXY(0, 0);
	}

	void showHp::LoadBitmap(int n,int m){
		if (load == true) {
			data = n;
			maxHP = m;
			return;
		}
		data = n;
		maxHP = m;
		animation_test.LoadBitmap(hp1, RGB(255, 255, 255));
		load = true;
	}


	void showHp::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void showHp::OnShow()
	{
		/*animation.SetTopLeft(x, y-20);
		animation.OnShow();*/
		for (int i = 0; i <  data*30 / maxHP; i++) {
			animation_test.SetTopLeft(x+i+7, y-20);
			animation_test.ShowBitmap();
		}
	}

	void showHp::showdata() {
		/*printf("HP:\n");
		printf("X,Y:%d,%d\n", x, y);*/
	}
}