/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "monster.h"
#include "monsterBat.h"




namespace game_framework {
	int main_actor = 0;

	const int MAX_RAND_NUM = 3;
	
	int random_map = 1; //測試用
	int test = 0;

	int check_backpack = 0;
	int pack_space[19];
	int pack_now = 1;
	int attack = 0;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////


CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{

}



void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	

	logo.LoadBitmap(mainpage);
	startb.LoadBitmap(startbutton);
	startb.SetTopLeft(600, 850);
	
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}
CGameMainMenu::CGameMainMenu(CGame *g)
	: CGameState(g)
{
}
void CGameMainMenu::OnBeginState()
{
	
}
void CGameMainMenu::OnInit()
{
	c1.LoadBitmap(warrior_icon,RGB(255,255,255));
	c2.LoadBitmap(mage_icon, RGB(255, 255, 255));
	c3.LoadBitmap(assassian_icon, RGB(255, 255, 255));
	c4.LoadBitmap(hunter_icon, RGB(255, 255, 255));
}

void CGameStateInit::OnBeginState()
{

}



void CGameMainMenu::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);
}

void CGameMainMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (point.x > c1.Left() && point.y > c1.Top() && (point.y < c1.Top() + c1.Height()) && (point.x < c1.Left() + c1.Width())){
		main_actor = 1;
		GotoGameState(GAME_STATE_RUN);
	}
	if (point.x > c2.Left() && point.y > c2.Top() && (point.y < c2.Top() + c2.Height()) && (point.x < c2.Left() + c2.Width())) {
		main_actor = 2;
		GotoGameState(GAME_STATE_RUN);
	}
	if (point.x > c3.Left() && point.y > c3.Top() && (point.y < c3.Top() + c3.Height()) && (point.x < c3.Left() + c3.Width())){
		main_actor = 3;
		GotoGameState(GAME_STATE_RUN);
	}
	if (point.x > c4.Left() && point.y > c4.Top() && (point.y < c4.Top() + c4.Height()) && (point.x < c4.Left() + c4.Width())){
		main_actor = 4;
		GotoGameState(GAME_STATE_RUN);
	}
}
	CGameMap::CGameMap()
        :X(920), Y(540), MW(45), MH(45)
    {

		int map1_init[24][26] = {
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
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 26; j++) {
				map[i][j] = map1_init[i][j];
			}
		}
		//srand((unsigned)time(NULL));
		//random_map = (rand()%2)+1; 讓地圖隨機出現
	changemap(random_map);

	monster_cpp.getmap(random_map, map);
	monster_bat_cpp.getmap(random_map, map);
	random_num = 0;
	bballs = NULL;
    }

	int CGameMap::ismoving = 1;

    void CGameMap::LoadBitmap()
    {
		
		mf.LoadBitmap(map_floor);
		opd.LoadBitmap(open_door);
		wh.LoadBitmap(water_hole);
		fw.LoadBitmap(front_wall);
		md.LoadBitmap(map_door);
		wf.LoadBitmap(wood_floor);
		sg.LoadBitmap(small_grass);
		lg.LoadBitmap(big_grass);
		stair_d.LoadBitmap(stair_up);
		stair_u.LoadBitmap(stair_down);
		water_floor.LoadBitmap(level1_water);
		lb_p.LoadBitmap(light_blue,RGB(255,255,255));
		dg_p.LoadBitmap(dark_green,RGB(255, 255, 255));
		dr_p.LoadBitmap(dark_red,RGB(255, 255, 255));
		
		
    }						///樓層1  0空 1地板 2水地板 3正牆 4門 5水牆 6木地板 7小草 8大草 9上樓 10下樓 11開門	//12淺藍水 13深綠水 14深紅水

	void CGameMap::SetXY(int x, int y) {
		X = x;
		Y = y;
		CEraser::map_x = x;
		CEraser::map_y = y;
	}

	void CGameMap::changemap(int m) {
		if (m == 1) {

			actor_x = 1;
			actor_y = 1;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map1_init[i][j];
			SetXY(920,540);
		}
		else if (m == 2) {
			actor_x = 6;
			actor_y = 5;

			for (int i = 0; i < 27; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map2_init[i][j];
			SetXY(695, 360);
		}
		else if (m == 3) {
			actor_x = 16;
			actor_y = 5;

			for (int i = 0; i < 27; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map3_init[i][j];
			SetXY(245, 360);
		}
		else if (m == 4) {
			actor_x = 3;
			actor_y = 13;

			for (int i = 0; i < 27; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map4_init[i][j];
			SetXY(825, 0);
		}
		else if (m == 5) {
			actor_x = 16;
			actor_y = 21;

			for (int i = 0; i < 27; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map5_init[i][j];
			SetXY(245, -350);
		}
		else if (m == 6) {
			actor_x = 11;
			actor_y = 2;

			for (int i = 0; i < 27; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map6_init[i][j];
			SetXY(475, 490);
		}
		else if (m == 7) {
			actor_x = 3;
			actor_y = 2;

			for (int i = 0; i < 27; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map7_init[i][j];
			SetXY(835, 485);
		}
	}

    void CGameMap::OnShow()
    {

		//test = (rand()%2)+1;
		//printf("test:%d", test);
       for(int i=0;i<27;i++)	//寬度27
            for (int j = 0; j < 27; j++) //高度25
		/*for (int i = actor_x - 5; i < actor_x + 5; i++)	//寬度27
			for (int j = actor_y - 5; j < actor_y + 5; j++) //高度25*/
            {
				if(random_map==1){
					if (j < 0) j = 0;
					if (j > 24)break;
					if (i < 0)i = 0;
					if (i > 26)break;
				}
				if (random_map == 2) {
					if (j < 0) j = 0;
					if (j > 24)break;
					if (i < 0)i = 0;
					if (i > 26)break;
				}
				if (random_map == 3) {
					if (j < 0) j = 0;
					if (j > 24)break;
					if (i < 0)i = 0;
					if (i > 26)break;
				}
                switch (map[j][i]) 
                {
                case 0:
					break;
                case 1:
                    mf.SetTopLeft(X + (MW*i), Y + (MH*j));
                    mf.ShowBitmap();
                    break;
                case 2:
					water_floor.SetTopLeft(X + (MW*i), Y + (MH*j));
					water_floor.ShowBitmap();
                    
                    break;
				case 3:
					fw.SetTopLeft(X + (MW*i), Y + (MH*j));
					fw.ShowBitmap();
					break;
				case 4:
					md.SetTopLeft(X + (MW*i), Y + (MH*j));
					md.ShowBitmap();
					break;
				case 5:
					wh.SetTopLeft(X + (MW*i), Y + (MH*j));
					wh.ShowBitmap();
					break;
				case 6:
					wf.SetTopLeft(X + (MW*i), Y + (MH*j));
					wf.ShowBitmap();
					break;
				case 7:
					sg.SetTopLeft(X + (MW*i), Y + (MH*j));
					sg.ShowBitmap();
					break;
				case 8:
					lg.SetTopLeft(X + (MW*i), Y + (MH*j));
					lg.ShowBitmap();
					break;
				case 9:
					stair_d.SetTopLeft(X + (MW*i), Y + (MH*j));
					stair_d.ShowBitmap();
					break;
				case 10:
					stair_u.SetTopLeft(X + (MW*i), Y + (MH*j));
					stair_u.ShowBitmap();
					break;
				case 11:
					opd.SetTopLeft(X + (MW*i), Y + (MH*j));
					opd.ShowBitmap();
					break;
				case 12:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					lb_p.SetTopLeft(X + (MW*i), Y + (MH*j));
					lb_p.ShowBitmap();
					break;
				case 13:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					dg_p.SetTopLeft(X + (MW*i), Y + (MH*j));
					dg_p.ShowBitmap();
					break;
				case 14:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					dr_p.SetTopLeft(X + (MW*i), Y + (MH*j));
					dr_p.ShowBitmap();
					break;
                default:
                    ASSERT(0);
                }
            }
		if (map[actor_y][actor_x] == 4) {
			map[actor_y][actor_x] = 11;
		}
		else if (map[actor_y][actor_x] == 8) {
			map[actor_y][actor_x] = 7;
		}
		else if (map[actor_y][actor_x] == 14) {
			map[actor_y][actor_x] = 1;
			pack_space[pack_now] = 14;
			pack_now++;
		}
		else if (map[actor_y][actor_x] == 13) {
			map[actor_y][actor_x] = 1;
			pack_space[pack_now] = 13;
			pack_now++;
		}
		else if (map[actor_y][actor_x] == 12) {
			map[actor_y][actor_x] = 1;
			pack_space[pack_now] = 12;
			pack_now++;
		}
		///////////////////////////////////////////
		/*物品編號:
			12淺藍水 13深綠水 14深紅水


		*/
		////////////////////////////////////////


		/*for (int i = 0; i < random_num; i++) {
			bballs[i].OnShow();
		}*/
    }
	void CGameMap::OnKeyDown(UINT nChar) {
		const int KEY_SPACE = 0x20;
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const int step = 45;
		int next_step = 0;
		if (nChar == KEY_LEFT) {
			if (map[actor_y][actor_x - 1] != 3 && map[actor_y][actor_x - 1] != 5) {
				SetXY(X + step, Y);
				actor_x -= 1;
				CGameMap::ismoving = 1;
				printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
			}
			else {
				printf("wall:%d,%d\n", actor_y, actor_x - 1);
				CGameMap::ismoving = 0;
			}
		}
		if (nChar == KEY_RIGHT) {
			if (map[actor_y][actor_x + 1] != 3 && map[actor_y][actor_x + 1] != 5) {
				SetXY(X - step, Y);
				actor_x += 1;
				CGameMap::ismoving = 1;
				printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
			}
			else {
				printf("wall:%d,%d\n", actor_y, actor_x + 1);
				CGameMap::ismoving = 0;
			}
		}
		if (nChar == KEY_UP) {
			if (map[actor_y - 1][actor_x] != 3 && map[actor_y - 1][actor_x] != 5) {
				SetXY(X, Y + step);
				actor_y -= 1;
				CGameMap::ismoving = 1;
				printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
			}
			else {
				printf("wall:%d,%d\n", actor_y - 1, actor_x);
				CGameMap::ismoving = 0;
			}
		}
		if (nChar == KEY_DOWN) {
			if (map[actor_y + 1][actor_x] != 3 && map[actor_y + 1][actor_x] != 5) {
				SetXY(X, Y - step);
				actor_y += 1;
				CGameMap::ismoving = 1;
				printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
			}
			else {
				printf("wall:%d,%d\n", actor_y + 1, actor_x);
				CGameMap::ismoving = 0;
			}
		}
		//printf("actor_x_y=%d,%d\n", actor_x, actor_y);
		//printf("actor_location=%d,%d\n", X,Y);
		CEraser::actor_x = actor_x;
		CEraser::actor_y = actor_y;
	}
	void CGameMap::OnMove() {
		for (int i = 0; i < random_num; i++) {
			bballs[i].OnMove();
		}

	}
	void CGameMap::InititalizeBouncingBall(int ini_index, int row, int col)
	{
		const int VELOCITY = 10;
		const int BALL_PIC_HEIGHT = 15;
		int floor = Y + (row + 1)*MH - BALL_PIC_HEIGHT;

		bballs[ini_index].LoadBitmap();
		bballs[ini_index].SetFloor(floor);
		bballs[ini_index].Setvelocity(VELOCITY + col);
		bballs[ini_index].SetXY(X + col * MW + MW / 2, floor);
	}
	void CGameMap::RandomBouncingBall() {
		//const int MAX_RAND_NUM = 10;
		//random_num = (rand() % MAX_RAND_NUM) + 1;
		

		delete[] bballs;
		bballs = new CBouncingBall[random_num];
		int ini_index = 0;
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 5; col++) {
				if (map[row][col] != 0 && ini_index < random_num) {
					InititalizeBouncingBall(ini_index, row, col);
					ini_index++;
				}
			}
		}
	}

	CGameMap::~CGameMap() {
		delete[] bballs;
	}
////////////////////////////////////////////////////////////////
	void CBouncingBall::SetXY(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void CBouncingBall::SetFloor(int floor)
	{
		this->floor = floor;
	}
	void CBouncingBall::Setvelocity(int velocoty)
	{
		this->velocity = velocity;
		this->initial_velocity = velocity;
	}




void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	//if (nChar == KEY_SPACE)
		//GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(point.x>startb.Left() && point.y>startb.Top() && (point.y < startb.Top()+startb.Height()) && (point.x < startb.Left()+startb.Width()))
		GotoGameState(GAME_MAIN_UI);		// 切換至GAME_STATE_RUN
}
//void CGameMainMenu::OnInit() {

//}

void CGameMainMenu::OnShow() {
	int menu_x = 700, menu_y = 250;
	c1.SetTopLeft(menu_x, menu_y);
	c1.ShowBitmap();
	c2.SetTopLeft(menu_x+350, menu_y);
	c2.ShowBitmap();
	c3.SetTopLeft(menu_x, menu_y+400);
	c3.ShowBitmap();
	c4.SetTopLeft(menu_x+350, menu_y+400);
	c4.ShowBitmap();
	
}


void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	startb.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	/*pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");*/
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(28) 
{
	

	ball = new CBall [NUMBALLS];
	picX = picY = 0;
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnBeginState()
{
	eraser.SetCharacter(main_actor);
	eraser.LoadBitmap();
	monster_cpp.SetCharacter(main_actor);
	monster_cpp.LoadBitmap();
	monster_bat_cpp.SetCharacter(main_actor);
	monster_bat_cpp.LoadBitmap();
	/*const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 0;
	const int ANIMATION_SPEED = 15;
	for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI*/
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	gamemap.OnMove();
	//
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(80 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// 移動球
	//practice.SetTopLeft(10, 10);
	if (picX <= SIZE_Y) {
		picX += 5;
		picY += 5;
	}
	else {
		picX = picY = 0;
	}
	//practice3.SetTopLeft(picX, picY);

	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();
	//
	// 移動擦子
	//
	monster_cpp.OnMove();
	eraser.OnMove();
	monster_bat_cpp.OnMove();
	//
	// 判斷擦子是否碰到球
	//
	for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-10);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//
	// 移動彈跳的球
	//
	bballs.OnMove();
}

void CGameStateRun::OnInit()  							// 遊戲的初值及圖形設定
{
	
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	backpack.LoadBitmap(ui_backpack,RGB(0,0,0));
	stop.LoadBitmap(ui_stop, RGB(0, 0, 0));
	detect.LoadBitmap(ui_detect, RGB(0, 0, 0));
	qitem1.LoadBitmap(ui_item1, RGB(0, 0, 0));
	qitem2.LoadBitmap(ui_item1, RGB(0, 0, 0));
	qitem3.LoadBitmap(ui_item1, RGB(0, 0, 0));
	qitem4.LoadBitmap(ui_item1, RGB(0, 0, 0));
	backpackUI.LoadBitmapA(backpack_ui, RGB(255, 255, 255));

	lb_p.LoadBitmap(light_blue1, RGB(255, 255, 255));
	dg_p.LoadBitmap(dark_green1, RGB(255, 255, 255));
	dr_p.LoadBitmap(dark_red1, RGB(255, 255, 255));

	herohp.LoadBitmap(hp1, RGB(255, 255, 255));

	finishbackground.LoadBitmap(finish, RGB(255, 255, 120));
	finishbackground2.LoadBitmap(blackbackground, RGB(2, 1, 2));
	gameoverBG.LoadBitmap(gameover, RGB(255, 255, 255));
	//border.LoadBitmap("Bitmaps/practice2.bmp", RGB(255, 255, 255));
	//practice.LoadBitmap(IDB_BALL);
	//practice3.LoadBitmap("Bitmaps/hi.bmp");
	gamemap.LoadBitmap();
	
	//
	int i;
	for (i = 0; i < NUMBALLS; i++)	
		ball[i].LoadBitmap();								// 載入第i個球的圖形

	
	
	background.LoadBitmap(mainpage);					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	
	//help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	//corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	//corner.ShowBitmap(background);							// 將corner貼到background
	bballs.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int test = 1;
	const int KEY_SPACE = 0x20;
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_Z  = 0x5a; // keyboard左箭頭
	if (nChar == KEY_Z ) {
		bool_finish = 1;
		printf("finsih%d\n", bool_finish);
	}
	if (nChar == KEY_SPACE) {
		test = 2;
		gamemap.changemap(test);
		monster_cpp.getmap(test, gamemap.map);
		monster_bat_cpp.getmap(test, gamemap.map);
	}
	if (nChar == KEY_LEFT) {
		eraser.SetMovingLeft(true);
		gamemap.OnKeyDown(nChar);
		monster_cpp.SetMovingLeft(true);
		monster_bat_cpp.SetMovingLeft(true);
	}
	if (nChar == KEY_RIGHT) {
		eraser.SetMovingRight(true);
		gamemap.OnKeyDown(nChar);
		monster_cpp.SetMovingRight(true);
		monster_bat_cpp.SetMovingRight(true);
	}
	if (nChar == KEY_UP){
		eraser.SetMovingUp(true);
		gamemap.OnKeyDown(nChar);
		monster_cpp.SetMovingUp(true);
		monster_bat_cpp.SetMovingUp(true);
	}
	if (nChar == KEY_DOWN){
		eraser.SetMovingDown(true);
		gamemap.OnKeyDown(nChar);
		monster_cpp.SetMovingDown(true);
		monster_bat_cpp.SetMovingDown(true);
		printf("keydown\n");
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭

	if (nChar == KEY_LEFT){
		eraser.SetMovingLeft(false);
		monster_cpp.SetMovingLeft(false);
		monster_bat_cpp.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {
		eraser.SetMovingRight(false);
		monster_cpp.SetMovingRight(false);
		monster_bat_cpp.SetMovingRight(false);
	}
	if (nChar == KEY_UP) {
		eraser.SetMovingUp(false);
		monster_cpp.SetMovingUp(false);
		monster_bat_cpp.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN) {
		eraser.SetMovingDown(false);
		monster_cpp.SetMovingDown(false);
		monster_bat_cpp.SetMovingDown(false);
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingLeft(true);
	

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingLeft(false);
	//if ((point.x < backpack.Left() + backpack.Width()) && point.x > backpack.Left() && point.y > backpack.Top() && (point.y > backpack.Top() + backpack.Height())) {
	if(point.x>backpack.Left()&&(point.x<backpack.Left()+backpack.Width())&& point.y > backpack.Top() && (point.y < backpack.Top() + backpack.Height())){
	check_backpack = 1;
	}
	else if(point.x < backpackUI.Left() || (point.x > backpackUI.Left() + backpackUI.Width()) || point.y < backpackUI.Top() || (point.y > backpackUI.Top() + backpackUI.Height())) {
	check_backpack = 0;
	}
	/*printf("GetXY:%d,%d\n", monster_cpp.GetX1(), monster_cpp.GetY1());
	printf("GetXY:%d,%d\n", monster_cpp.GetX2(), monster_cpp.GetY2());
	printf("GetXY:%d,%d\n", monster_bat_cpp.GetX1(), monster_bat_cpp.GetY1());
	printf("GetXY:%d,%d\n", monster_bat_cpp.GetX2(), monster_bat_cpp.GetY2());*/
	if (point.x > monster_cpp.GetX1() && point.x < monster_cpp.GetX2() && point.y > monster_cpp.GetY1() && point.y < monster_cpp.GetY2()) {
		if (monster_cpp.attacked_judge(monster::mon_x, monster::mon_y, CEraser::actor_x, CEraser::actor_y) == 1) {
			monster_cpp.attacked(eraser.hero_ATK);
			eraser.showdata();
			monster_cpp.showdata();
			monster_bat_cpp.SetMoving(true);
			monster_bat_cpp.SetMoving(false);
		}
	}
	if (point.x > monster_bat_cpp.GetX1() && point.x < monster_bat_cpp.GetX2() && point.y > monster_bat_cpp.GetY1() && point.y < monster_bat_cpp.GetY2()) {
		if (monster_cpp.attacked_judge(monster_bat_cpp.mon_x, monster_bat_cpp.mon_y, CEraser::actor_x, CEraser::actor_y) == 1) {
			monster_bat_cpp.attacked(eraser.hero_ATK);
			eraser.showdata();
			monster_cpp.SetMoving(true);
			monster_cpp.SetMoving(false);
			monster_bat_cpp.showdata();
		}
	}
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingRight(true);
	
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	int uix = 700, uiy = 990;
	if (random_map == 1) {
		eraser.SetXY(920 + 45, 540 +45);//角色初始位置
	}
	if (random_map == 2) {
		eraser.SetXY(920 + 45, 540 + 45);//角色初始位置
	}
	if (random_map == 3) {
		eraser.SetXY(920 + 45, 540 + 45);//角色初始位置
	}

	
	stop.SetTopLeft(uix, uiy);
	backpack.SetTopLeft(stop.Left()+550, uiy);
	detect.SetTopLeft(stop.Left()+90, uiy);
	qitem1.SetTopLeft(stop.Left() + 193, uiy);
	qitem2.SetTopLeft(stop.Left() + 276, uiy);
	qitem3.SetTopLeft(stop.Left() + 359, uiy);
	qitem4.SetTopLeft(stop.Left() + 442, uiy);
	backpackUI.SetTopLeft(700, 0);
	
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	//background.ShowBitmap();			// 貼上背景圖
	gamemap.OnShow();
	//help.ShowBitmap();					// 貼上說明圖
	hits_left.ShowBitmap();
	//for (int i=0; i < NUMBALLS; i++)
	//	ball[i].OnShow();				// 貼上第i號球
	//bballs.OnShow();	// 貼上彈跳的球
	eraser.OnShow();					// 貼上擦子
	monster_cpp.OnShow();
	monster_bat_cpp.OnShow();

	backpack.ShowBitmap();
	stop.ShowBitmap();
	detect.ShowBitmap();
	qitem1.ShowBitmap();
	qitem2.ShowBitmap();
	qitem3.ShowBitmap();
	qitem4.ShowBitmap();
	///////////////////////////////////開啟背包/////////////////////////
	int packx = 0, packy = 0;
	if (check_backpack == 1) {
		backpackUI.ShowBitmap();



		for (int i = 1; i < 20; i++) {
			if (i < 5) {
				packx = 760, packy = 230;
			}
			switch (pack_space[i])
			{
			case 12:
				lb_p.SetTopLeft(packx + (i % 5) * 130, packy);
				lb_p.ShowBitmap();
				break;
			case 13:
				dg_p.SetTopLeft(packx + (i % 5) * 130, packy);
				dg_p.ShowBitmap();
				break;
			case 14:
				dr_p.SetTopLeft(packx + (i%5) * 130, packy);
				dr_p.ShowBitmap();
				break;
			default:
				break;
			}
		}
	}
	///////////////////////////////////開啟背包/////////////////////////



	//
	//  貼上左上及右下角落的圖
	//
	
	//corner.SetTopLeft(0,0);
	//corner.ShowBitmap();
	//corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	//corner.ShowBitmap();
	//practice3.ShowBitmap();
	//practice.ShowBitmap();
	//border.ShowBitmap();
	//c_practice4.OnShow();
	if (eraser.hero_HP <= 0) {
		finishbackground2.SetTopLeft(0, 0);
		finishbackground2.ShowBitmap();
		gameoverBG.SetTopLeft(eraser.GetX1() -230, eraser.GetY1()-110);
		gameoverBG.ShowBitmap();

	}
	if (bool_finish == 1) {
		finishbackground.SetTopLeft(700, 0);
		finishbackground2.SetTopLeft(0, 0);
		finishbackground2.ShowBitmap();
		finishbackground.ShowBitmap();
	}
}

}