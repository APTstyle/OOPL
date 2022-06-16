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

	void showHp::LoadBitmap(int n){
		switch (n)
		{
		case 10:
			animation.cleanBitmap();
			animation.AddBitmap(hp10, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 9:
			animation.cleanBitmap();
			animation.AddBitmap(hp9, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 8:
			animation.cleanBitmap();
			animation.AddBitmap(hp8, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 7:
			animation.cleanBitmap();
			animation.AddBitmap(hp7, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 6:
			animation.cleanBitmap();
			animation.AddBitmap(hp6, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 5:
			animation.cleanBitmap();
			animation.AddBitmap(hp5, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 4:
			animation.cleanBitmap();
			animation.AddBitmap(hp4, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 3:
			animation.cleanBitmap();
			animation.AddBitmap(hp3, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 2:
			animation.cleanBitmap();
			animation.AddBitmap(hp2, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		case 1:
			animation.cleanBitmap();
			animation.AddBitmap(hp1, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		default:
			animation.cleanBitmap();
			animation.AddBitmap(death_mon, RGB(255, 255, 255));
			printf("SHOWHP:%d\n", n);
			break;
		}
	}


	void showHp::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void showHp::OnShow()
	{
		animation.SetTopLeft(x, y-20);
		animation.OnShow();
	}

	void showHp::showdata() {
		printf("HP:\n");
		printf("X,Y:%d,%d\n", x, y);
	}
}