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
	int test = 1;

	int check_backpack = 0;
	int pack_space[19] = { 0 };
	
	int pack_now = 1;
	int attack = 0;
	int bool_finish = 0;
	int bool_gameover = 0;
	int save[27][27] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	int test1[3] = { 0,0,0 }; // 偵測之前的怪物座標
	int	test2[3] = { 0,0,0 }; // 偵測之後的怪物座標
	void backpackadd(int item) { //增加背包物品
		for (int i = 0; i < 19; i++) {
			if (pack_space[i] == 0) {
				pack_space[i] = item;
				break;
			}
		}
	}
	void backpackdel (int item) { //刪除背包物品
		for (int i = 18; i >= 0; i--) {
			if (pack_space[i] == item) {
				pack_space[i] = 0;
				break;
			}
		}
	}

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
	//CAudio::Instance()->Play(START_MUSIC, true); //開頭音樂
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

	CEraser::hero_HP = 20;
	CAudio::Instance()->Load(START_MUSIC, "sounds\\theme.mp3");
	CAudio::Instance()->Play(START_MUSIC, true); //開頭音樂
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
		
    /*for (int i = 0; i < 24; i++)
        for (int j = 0; j < 26; j++)
            map[i][j] = map1_init[i][j];*/
		//srand((unsigned)time(NULL));
		//random_map = (rand()%2)+1; 讓地圖隨機出現
	changemap(random_map);

	monster_cpp.getmap(random_map, map);
	monster_bat_cpp.getmap(random_map, map);
	monster_bat_cpp2.getmap(random_map, map);
	monster_bat_cpp3.getmap(random_map, map);
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
		tr1s.LoadBitmap(treasure, RGB(255, 255, 255));
		gr1s.LoadBitmap(grave, RGB(255, 255, 255));


		lb_p.LoadBitmap(light_blue,RGB(255,255,255));
		dg_p.LoadBitmap(dark_green,RGB(255, 255, 255));
		dr_p.LoadBitmap(dark_red,RGB(255, 255, 255));
		pa1s.LoadBitmap(paper1s, RGB(255, 255, 255));
		pa2s.LoadBitmap(paper2s, RGB(255, 255, 255));
		pa3s.LoadBitmap(paper3s, RGB(255, 255, 255));
		sw1s.LoadBitmap(sword1s, RGB(255, 255, 255));
		sw2s.LoadBitmap(sword2s, RGB(255, 255, 255));
		sw3s.LoadBitmap(sword3s, RGB(255, 255, 255));
		st1s.LoadBitmap(stick1s, RGB(255, 255, 255));
		st2s.LoadBitmap(stick2s, RGB(255, 255, 255));
		st3s.LoadBitmap(stick3s, RGB(255, 255, 255));
		cl1s.LoadBitmap(cloth1s, RGB(0, 0,0 ));
		cl2s.LoadBitmap(cloth2s, RGB(255, 255, 255));
		cl3s.LoadBitmap(cloth3s, RGB(255, 255, 255));
		ri1s.LoadBitmap(ring1s, RGB(255, 255, 255));
		ri2s.LoadBitmap(ring2s, RGB(255, 255, 255));
		ri3s.LoadBitmap(ring3s, RGB(255, 255, 255));
		fo1s.LoadBitmap(food1b, RGB(255, 255, 255));
		fo2s.LoadBitmap(food2b, RGB(255, 255, 255));
		ar1s.LoadBitmap(arrow1s, RGB(255, 255, 255));
		ar2s.LoadBitmap(arrow2s, RGB(255, 255, 255));
		ke1s.LoadBitmap(key, RGB(255, 255, 255));



		
		
    }						///樓層1  0空 1地板 2水地板 3正牆 4門 5水牆 6木地板 7小草 8大草 9上樓 10下樓 11開門	//12淺藍水 13深綠水 14深紅水

	void CGameMap::SetXY(int x, int y) {
		X = x;
		Y = y;
		CEraser::map_x = x;
		CEraser::map_y = y;
	}

	void CGameMap::changemap(int m) { //換地圖
		if (m == 1) {

			CEraser::actor_x = 1;
			CEraser::actor_y = 1;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map1_init[i][j];
			SetXY(920,540);
		}
		else if (m == 2) {
			CEraser::actor_x = 6;
			CEraser::actor_y = 5;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map2_init[i][j];
			SetXY(695, 360);
		}
		else if (m == 3) {
			CEraser::actor_x = 16;
			CEraser::actor_y = 5;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map3_init[i][j];
			SetXY(245, 360);
		}
		else if (m == 4) {
			CEraser::actor_x = 3;
			CEraser::actor_y = 13;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map4_init[i][j];
			SetXY(825, 0);
		}
		else if (m == 5) {
			CEraser::actor_x = 16;
			CEraser::actor_y = 21;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map5_init[i][j];
			SetXY(245, -350);
		}
		else if (m == 6) {
			CEraser::actor_x = 11;
			CEraser::actor_y = 2;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map6_init[i][j];
			SetXY(475, 490);
		}
		else if (m == 7) {
			CEraser::actor_x = 3;
			CEraser::actor_y = 2;

			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 27; j++)
					map[i][j] = map7_init[i][j];
			SetXY(835, 485);
		}
	}

    void CGameMap::OnShow()
    {

		//test = (rand()%2)+1;
		//printf("test:%d", test);
		/*for (int i = CEraser::actor_x - 5; i < CEraser::actor_x + 5; i++)	//寬度27
			for (int j = CEraser::actor_y - 5; j < CEraser::actor_y + 5; j++) //高度25*/
       //for(int i=0;i<27;i++)	//寬度27
        //    for (int j = 0; j < 27; j++) //高度25
		for (int i = CEraser::actor_x - 5; i < CEraser::actor_x + 5; i++)	//寬度27
			for (int j = CEraser::actor_y - 5; j < CEraser::actor_y + 5; j++) //高度25
            {
				if(random_map==1){
					if (j < 0) j = 0;
					if (j > 23)break;
					if (i < 0)i = 0;
					if (i > 25)break;
				}
				/*if (random_map == 2) {
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
				}*/
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
				case 15:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					sw1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					sw1s.ShowBitmap();
					break;
				case 16:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					sw2s.SetTopLeft(X + (MW*i), Y + (MH*j));
					sw2s.ShowBitmap();
					break;
				case 17:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					sw3s.SetTopLeft(X + (MW*i), Y + (MH*j));
					sw3s.ShowBitmap();
					break;
				case 18:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					st1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					st1s.ShowBitmap();
					break;
				case 19:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					st2s.SetTopLeft(X + (MW*i), Y + (MH*j));
					st2s.ShowBitmap();
					break;
				case 20:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					st3s.SetTopLeft(X + (MW*i), Y + (MH*j));
					st3s.ShowBitmap();
					break;
				case 21:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					pa1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					pa1s.ShowBitmap();
					break;
				case 22:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					pa2s.SetTopLeft(X + (MW*i), Y + (MH*j));
					pa2s.ShowBitmap();
					break;
				case 23:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					pa3s.SetTopLeft(X + (MW*i), Y + (MH*j));
					pa3s.ShowBitmap();
					break;
				case 24:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					ri1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					ri1s.ShowBitmap();
					break;
				case 25:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					ri2s.SetTopLeft(X + (MW*i), Y + (MH*j));
					ri2s.ShowBitmap();
					break;
				case 26:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					ri3s.SetTopLeft(X + (MW*i), Y + (MH*j));
					ri3s.ShowBitmap();
					break;
				case 27:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					cl1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					cl1s.ShowBitmap();
					break;
				case 28:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					cl2s.SetTopLeft(X + (MW*i), Y + (MH*j));
					cl2s.ShowBitmap();
					break;
				case 29:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					cl3s.SetTopLeft(X + (MW*i), Y + (MH*j));
					cl3s.ShowBitmap();
					break;
				case 30:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					fo1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					fo1s.ShowBitmap();
					break;
				case 31:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					fo2s.SetTopLeft(X + (MW*i), Y + (MH*j));
					fo2s.ShowBitmap();
					break;
				case 32:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					ke1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					ke1s.ShowBitmap();
					break;
				case 33:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					tr1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					tr1s.ShowBitmap();
					break;
				case 34:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					gr1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					gr1s.ShowBitmap();
					break;
				case 35:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					ar1s.SetTopLeft(X + (MW*i), Y + (MH*j));
					ar1s.ShowBitmap();
					break;
				case 36:
					mf.SetTopLeft(X + (MW*i), Y + (MH*j));
					mf.ShowBitmap();
					ar2s.SetTopLeft(X + (MW*i), Y + (MH*j));
					ar2s.ShowBitmap();
					break;
                default:
                    ASSERT(0);
                }
            }
		if (map[CEraser::actor_y][CEraser::actor_x] == 4) {
			map[CEraser::actor_y][CEraser::actor_x] = 11;
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 8) {
			map[CEraser::actor_y][CEraser::actor_x] = 7;
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 10) {
			srand((unsigned)time(NULL));
			random_map = (rand()%7)+1; //讓地圖隨機出現
			changemap(random_map);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 14) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(14);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 13) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(13);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 12) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(12);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 15) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(15);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 16) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(16);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 17) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(17);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 18) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(18);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 19) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(19);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 20) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(20);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 21) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(21);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 22) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(22);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 23) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(23);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 24) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(24);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 25) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(25);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 26) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(26);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 27) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(27);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 28) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(28);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 29) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(29);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 30) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(30);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 31) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(31);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 32) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(32);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 33) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 34) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 35) {
			map[CEraser::actor_y][CEraser::actor_x] = 1;
			backpackadd(35);
		}
		else if (map[CEraser::actor_y][CEraser::actor_x] == 36) {
		map[CEraser::actor_y][CEraser::actor_x] = 1;
		backpackadd(36);
		}

		///////////////////////////////////////////
		/*物品編號:
			12淺藍水 13深綠水 14深紅水
			15劍1 16劍2 17劍3
			18杖1 19杖2 20杖3
			21紙1 22紙2 23紙3
			24戒1 25戒2 26戒3
			27服1 28服2 29服3
			30食1 31食2
			32鑰匙 33寶箱 34墳墓
			35箭1 36箭2


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
		}
		if (nChar == KEY_RIGHT) {
			
		}
		if (nChar == KEY_UP) {
		}
		if (nChar == KEY_DOWN) {
		}
		//printf("CEraser::actor_x_y=%d,%d\n", CEraser::actor_x, CEraser::actor_y);
		//printf("actor_location=%d,%d\n", X,Y);
		//CEraser::actor_x = CEraser::actor_x;
		//CEraser::actor_y = CEraser::actor_y;
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
}

void CGameStateOver::OnBeginState()
{
	gamemap.changemap(1);
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x > gameoverbutton.Left() && point.y > gameoverbutton.Top() && (point.y < gameoverbutton.Top() + gameoverbutton.Height()) && (point.x < gameoverbutton.Left() + gameoverbutton.Width())) {
		bool_gameover = 0;
		GotoGameState(GAME_STATE_INIT);
	}
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
	finishbackground.LoadBitmap(finish, RGB(255, 255, 120));
	finishbackground2.LoadBitmap(blackbackground, RGB(2, 1, 2));
	gameoverBG.LoadBitmap(gameover, RGB(255, 255, 255));
	gameoverbutton.LoadBitmap(gameoverBN, RGB(0, 0, 0));
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	if (bool_gameover == 1) {
		finishbackground2.SetTopLeft(0, 0);
		finishbackground2.ShowBitmap();
		gameoverBG.SetTopLeft(eraser.GetX1() - 230, eraser.GetY1() - 110);
		gameoverBG.ShowBitmap();
		gameoverbutton.SetTopLeft(eraser.GetX1() - 300, eraser.GetY1());
		gameoverbutton.ShowBitmap();
	}
	if (bool_finish == 1) {
		finishbackground.SetTopLeft(700, 0);
		finishbackground2.SetTopLeft(0, 0);
		finishbackground2.ShowBitmap();
		finishbackground.ShowBitmap();
	}			// 放掉 Back Plain 的 CDC
	
}

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
	gamemap.SetXY(920, 540);
	eraser.SetCharacter(main_actor);
	CEraser::actor_x = 1;
	CEraser::actor_y = 1;
	CEraser::map_x = 920;
	CEraser::map_y = 540;
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			save[i][j] = 0;
		}
	}
	monster_cpp.SetCharacter(main_actor);
	monster_cpp.setdata(test, 5, 5);
	monster_cpp.SetXY(CEraser::map_x + 45 * monster_cpp.mon_x, CEraser::map_y + 45 * monster_cpp.mon_y);
	
	bat_setup(5, 7);
	bat_setup2(3,17);
	bat_setup3(23,21);

	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			printf("%d ", save[i][j]);
		}
		printf("\n");
	}
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
	CAudio::Instance()->Play(GAMING_MUSIC, true);
}

void CGameStateRun::bat_setup(int x,int y) {
	monster_bat_cpp.SetCharacter(main_actor);
	monster_bat_cpp.setdata(test, x, y); // mapnum x y
	monster_bat_cpp.SetXY(CEraser::map_x + 45 * monster_bat_cpp.mon_x, CEraser::map_y + 45 * monster_bat_cpp.mon_y);
	save[y][x] = 1;
	test1[0] = 100 * x + y;
}
void CGameStateRun::bat_setup2(int x, int y) {
	monster_bat_cpp2.SetCharacter(main_actor);
	monster_bat_cpp2.setdata(test, x, y); // mapnum x y
	monster_bat_cpp2.SetXY(CEraser::map_x + 45 * monster_bat_cpp2.mon_x, CEraser::map_y + 45 * monster_bat_cpp2.mon_y);
	save[y][x] = 1;
	test1[1] = 100 * x + y;
}
void CGameStateRun::bat_setup3(int x, int y) {
	monster_bat_cpp3.SetCharacter(main_actor);
	monster_bat_cpp3.setdata(test, x, y); // mapnum x y
	monster_bat_cpp3.SetXY(CEraser::map_x + 45 * monster_bat_cpp3.mon_x, CEraser::map_y + 45 * monster_bat_cpp3.mon_y);
	save[y][x] = 1;
	test1[2] = 100 * x + y;
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

	monster_cpp.OnMove();
	eraser.OnMove();
	monster_bat_cpp.OnMove();
	monster_bat_cpp2.OnMove();
	monster_bat_cpp3.OnMove();
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
	eraser.LoadBitmap();
	monster_cpp.LoadBitmap();
	monster_bat_cpp.LoadBitmap();
	monster_bat_cpp2.LoadBitmap();
	monster_bat_cpp3.LoadBitmap();
	backpack.LoadBitmap(ui_backpack,RGB(0,0,0));
	stop.LoadBitmap(ui_stop, RGB(0, 0, 0));
	detect.LoadBitmap(ui_detect, RGB(0, 0, 0));
	qitem1.LoadBitmap(ui_item1, RGB(0, 0, 0));
	qitem2.LoadBitmap(ui_item1, RGB(0, 0, 0));
	qitem3.LoadBitmap(ui_item1, RGB(0, 0, 0));
	qitem4.LoadBitmap(ui_item1, RGB(0, 0, 0));
	backpackUI.LoadBitmapA(backpack_ui, RGB(255, 255, 255));

	///////////背包的物品///////////////////////////////////////////////////////////////////
	lb_p.LoadBitmap(light_blue1, RGB(255, 255, 255));
	dg_p.LoadBitmap(dark_green1, RGB(255, 255, 255));
	dr_p.LoadBitmap(dark_red1, RGB(255, 255, 255));
	herohp.LoadBitmap(hp1, RGB(255, 255, 255));
	//border.LoadBitmap("Bitmaps/practice2.bmp", RGB(255, 255, 255));
	//practice.LoadBitmap(IDB_BALL);
	//practice3.LoadBitmap("Bitmaps/hi.bmp");

	pa1s_p.LoadBitmap(paper1b, RGB(255, 255, 255));
	pa2s_p.LoadBitmap(paper2b, RGB(255, 255, 255));
	pa3s_p.LoadBitmap(paper3b, RGB(255, 255, 255));
	sw1s_p.LoadBitmap(sword1b, RGB(255, 255, 255));
	sw2s_p.LoadBitmap(sword2b, RGB(255, 255, 255));
	sw3s_p.LoadBitmap(sword3b, RGB(255, 255, 255));
	st1s_p.LoadBitmap(stick1b, RGB(255, 255, 255));
	st2s_p.LoadBitmap(stick2b, RGB(255, 255, 255));
	st3s_p.LoadBitmap(stick3b, RGB(255, 255, 255));
	cl1s_p.LoadBitmap(cloth1b, RGB(0,0, 0));
	cl2s_p.LoadBitmap(cloth2b, RGB(255, 255, 255));
	cl3s_p.LoadBitmap(cloth3b, RGB(255, 255, 255));
	ri1s_p.LoadBitmap(ring1b, RGB(255, 255, 255));
	ri2s_p.LoadBitmap(ring2b, RGB(255, 255, 255));
	ri3s_p.LoadBitmap(ring3b, RGB(255, 255, 255));
	fo1s_p.LoadBitmap(food1s, RGB(255, 255, 255));
	fo2s_p.LoadBitmap(food2s, RGB(255, 255, 255));
	ar1s_p.LoadBitmap(arrow1b, RGB(255, 255, 255));
	ar2s_p.LoadBitmap(arrow2b, RGB(255, 255, 255));
	ke1s_p.LoadBitmap(key1, RGB(255, 255, 255));

	



	/////////背包的物品/////////////////////////////////////////////////////////////////////

	border.LoadBitmap("Bitmaps/practice2.bmp", RGB(255, 255, 255));
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
	
	//help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	//corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	//corner.ShowBitmap(background);							// 將corner貼到background
	bballs.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	
	CAudio::Instance()->Load(GAMING_MUSIC, "sounds\\game.mp3");
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const int KEY_SPACE = 0x20;
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_Z = 0x5a; // keyboard左箭頭
	const int step = 45;
	if (nChar == KEY_Z) {
		bool_finish = 1;
		printf("finsih%d\n", bool_finish);
	}
	if (nChar == KEY_SPACE) {
		test = 2;
		gamemap.changemap(test);
		monster_cpp.getmap(test, gamemap.map);
		monster_bat_cpp.getmap(test, gamemap.map);
		monster_bat_cpp2.getmap(test, gamemap.map);
		monster_bat_cpp3.getmap(test, gamemap.map);
	}
	if (nChar == KEY_LEFT) {
		if (gamemap.map[CEraser::actor_y][CEraser::actor_x - 1] != 3 && gamemap.map[CEraser::actor_y][CEraser::actor_x - 1] != 5) {
			gamemap.SetXY(gamemap.X + step, gamemap.Y);
			CGameMap::ismoving = 1;
			eraser.SetMovingLeft(true);
			printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
		}
		else {
			printf("wall:%d,%d\n", CEraser::actor_y, CEraser::actor_x - 1);
			CGameMap::ismoving = 0;
		}
		gamemap.OnKeyDown(nChar);
		monster_cpp.SetMovingLeft(true);

		monster_bat_cpp.SetMovingLeft(true);
		test2[0] = monster_bat_cpp.getroad(save);
		if (test1[0] == test2[0]) {
			monster_bat_cpp.attack_judge(test1[0] / 100, test1[0] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[0] % 100][test1[0] / 100] = 0;
		save[test2[0] % 100][test2[0] / 100] = 1;
		test1[0] = test2[0];

		monster_bat_cpp2.SetMovingLeft(true);
		test2[1] = monster_bat_cpp2.getroad(save);
		if (test1[1] == test2[1]) {
			monster_bat_cpp2.attack_judge(test1[1] / 100, test1[1] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[1] % 100][test1[1] / 100] = 0;
		save[test2[1] % 100][test2[1] / 100] = 1;
		test1[1] = test2[1];

		monster_bat_cpp3.SetMovingLeft(true);
		test2[2] = monster_bat_cpp3.getroad(save);
		if (test1[2] == test2[2]) {
			monster_bat_cpp3.attack_judge(test1[2] / 100, test1[2] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[2] % 100][test1[2] / 100] = 0;
		save[test2[2] % 100][test2[2] / 100] = 1;
		test1[2] = test2[2];
	}
	if (nChar == KEY_RIGHT) {
		if (gamemap.map[CEraser::actor_y][CEraser::actor_x + 1] != 3 && gamemap.map[CEraser::actor_y][CEraser::actor_x + 1] != 5) {
			gamemap.SetXY(gamemap.X - step, gamemap.Y);
			CGameMap::ismoving = 1;
			printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
			eraser.SetMovingRight(true);
		}
		else {
			printf("wall:%d,%d\n", CEraser::actor_y, CEraser::actor_x + 1);
			CGameMap::ismoving = 0;
		}
		gamemap.OnKeyDown(nChar);
		monster_cpp.SetMovingRight(true);

		monster_bat_cpp.SetMovingRight(true);
		test2[0] = monster_bat_cpp.getroad(save);
		if (test1[0] == test2[0]) {
			monster_bat_cpp.attack_judge(test1[0] / 100, test1[0] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[0] % 100][test1[0] / 100] = 0;
		save[test2[0] % 100][test2[0] / 100] = 1;
		test1[0] = test2[0];

		monster_bat_cpp2.SetMovingRight(true);
		test2[1] = monster_bat_cpp2.getroad(save);
		if (test1[1] == test2[1]) {
			monster_bat_cpp2.attack_judge(test1[1] / 100, test1[1] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[1] % 100][test1[1] / 100] = 0;
		save[test2[1] % 100][test2[1] / 100] = 1;
		test1[1] = test2[1];

		monster_bat_cpp3.SetMovingRight(true);
		test2[2] = monster_bat_cpp3.getroad(save);
		if (test1[2] == test2[2]) {
			monster_bat_cpp3.attack_judge(test1[2] / 100, test1[2] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[2] % 100][test1[2] / 100] = 0;
		save[test2[2] % 100][test2[2] / 100] = 1;
		test1[2] = test2[2];
	}
	if (nChar == KEY_UP) {
		if (gamemap.map[CEraser::actor_y - 1][CEraser::actor_x] != 3 && gamemap.map[CEraser::actor_y - 1][CEraser::actor_x] != 5) {
			gamemap.SetXY(gamemap.X, gamemap.Y + step);
			CGameMap::ismoving = 1;
			eraser.SetMovingUp(true);
			printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
		}
		else {
			printf("wall:%d,%d\n", CEraser::actor_y - 1, CEraser::actor_x);
			CGameMap::ismoving = 0;
		}
		gamemap.OnKeyDown(nChar);
		monster_cpp.SetMovingUp(true);

		monster_bat_cpp.SetMovingUp(true);
		test2[0] = monster_bat_cpp.getroad(save);
		if (test1[0] == test2[0]) {
			monster_bat_cpp.attack_judge(test1[0] / 100, test1[0] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[0] % 100][test1[0] / 100] = 0;
		save[test2[0] % 100][test2[0] / 100] = 1;
		test1[0] = test2[0];

		monster_bat_cpp2.SetMovingUp(true);
		test2[1] = monster_bat_cpp2.getroad(save);
		if (test1[1] == test2[1]) {
			monster_bat_cpp2.attack_judge(test1[1] / 100, test1[1] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[1] % 100][test1[1] / 100] = 0;
		save[test2[1] % 100][test2[1] / 100] = 1;
		test1[1] = test2[1];

		monster_bat_cpp3.SetMovingUp(true);
		test2[2] = monster_bat_cpp3.getroad(save);
		if (test1[2] == test2[2]) {
			monster_bat_cpp3.attack_judge(test1[2] / 100, test1[2] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[2] % 100][test1[2] / 100] = 0;
		save[test2[2] % 100][test2[2] / 100] = 1;
		test1[2] = test2[2];
	}
	if (nChar == KEY_DOWN) {
		if (gamemap.map[CEraser::actor_y + 1][CEraser::actor_x] != 3 && gamemap.map[CEraser::actor_y + 1][CEraser::actor_x] != 5) {
			gamemap.SetXY(gamemap.X, gamemap.Y - step);
			CGameMap::ismoving = 1;
			eraser.SetMovingDown(true);
			printf("\nmapXY::%d,%d!!!!!!!!!!!\n", CEraser::map_x, CEraser::map_y);
		}
		else {
			printf("wall:%d,%d\n", CEraser::actor_y + 1, CEraser::actor_x);
			CGameMap::ismoving = 0;
		}
		gamemap.OnKeyDown(nChar);

		monster_cpp.SetMovingDown(true);

		monster_bat_cpp.SetMovingDown(true);
		test2[0] = monster_bat_cpp.getroad(save);
		if (test1[0] == test2[0]) {
			monster_bat_cpp.attack_judge(test1[0] / 100, test1[0] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[0] % 100][test1[0] / 100] = 0;
		save[test2[0] % 100][test2[0] / 100] = 1;
		test1[0] = test2[0];

		monster_bat_cpp2.SetMovingDown(true);
		test2[1] = monster_bat_cpp2.getroad(save);
		if (test1[1] == test2[1]) {
			monster_bat_cpp2.attack_judge(test1[1] / 100, test1[1] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[1] % 100][test1[1] / 100] = 0;
		save[test2[1] % 100][test2[1] / 100] = 1;
		test1[1] = test2[1];

		monster_bat_cpp3.SetMovingDown(true);
		test2[2] = monster_bat_cpp3.getroad(save);
		if (test1[2] == test2[2]) {
			monster_bat_cpp3.attack_judge(test1[2] / 100, test1[2] % 100, CEraser::actor_x, CEraser::actor_y);
		}
		save[test1[2] % 100][test1[2] / 100] = 0;
		save[test2[2] % 100][test2[2] / 100] = 1;
		test1[2] = test2[2];

	}

	printf("keydown\n");
	printf("\n");
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			printf("%d ", save[i][j]);
		}
		printf("\n");
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭

	if (nChar == KEY_LEFT) {
		eraser.SetMovingLeft(false);
		monster_cpp.SetMovingLeft(false);
		monster_bat_cpp.SetMovingLeft(false);
		monster_bat_cpp2.SetMovingLeft(false);
		monster_bat_cpp3.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {
		eraser.SetMovingRight(false);
		monster_cpp.SetMovingRight(false);
		monster_bat_cpp.SetMovingRight(false);
		monster_bat_cpp2.SetMovingRight(false);
		monster_bat_cpp3.SetMovingRight(false);
	}
	if (nChar == KEY_UP) {
		eraser.SetMovingUp(false);
		monster_cpp.SetMovingUp(false);
		monster_bat_cpp.SetMovingUp(false);
		monster_bat_cpp2.SetMovingUp(false);
		monster_bat_cpp3.SetMovingUp(false);
	}
	if (nChar == KEY_DOWN) {
		eraser.SetMovingDown(false);
		monster_cpp.SetMovingDown(false);
		monster_bat_cpp.SetMovingDown(false);
		monster_bat_cpp2.SetMovingDown(false);
		monster_bat_cpp3.SetMovingDown(false);
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingLeft(true);
	

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	printf("pointX:%d ,pointY:%d \n", point.x, point.y);
	//eraser.SetMovingLeft(false);
	//if ((point.x < backpack.Left() + backpack.Width()) && point.x > backpack.Left() && point.y > backpack.Top() && (point.y > backpack.Top() + backpack.Height())) {
	if(point.x>backpack.Left()&&(point.x<backpack.Left()+backpack.Width())&& point.y > backpack.Top() && (point.y < backpack.Top() + backpack.Height())){
	check_backpack = 1;
	}
	else if(point.x < backpackUI.Left() || (point.x > backpackUI.Left() + backpackUI.Width()) || point.y < backpackUI.Top() || (point.y > backpackUI.Top() + backpackUI.Height())) {
	check_backpack = 0;
	}
	if (point.x > monster_bat_cpp.GetX1() && point.x < monster_bat_cpp.GetX2() && point.y > monster_bat_cpp.GetY1() && point.y < monster_bat_cpp.GetY2()) {
		if (monster_cpp.attacked_judge(monster_bat_cpp.mon_x, monster_bat_cpp.mon_y, CEraser::actor_x, CEraser::actor_y) == 1) {
			monster_bat_cpp.attacked(eraser.hero_ATK);

			monster_bat_cpp2.SetMoving(true);
			monster_bat_cpp2.SetMoving(false);
			test2[1] = monster_bat_cpp2.getroad(save);
			if (test1[1] == test2[1]) {
				monster_bat_cpp2.attack_judge(test1[1] / 100, test1[1] % 100, CEraser::actor_x, CEraser::actor_y);
			}
			save[test1[1] % 100][test1[1] / 100] = 0;
			save[test2[1] % 100][test2[1] / 100] = 1;
			test1[1] = test2[1];

			monster_bat_cpp3.SetMoving(true);
			monster_bat_cpp3.SetMoving(false);
			test2[2] = monster_bat_cpp3.getroad(save);
			if (test1[2] == test2[2]) {
				monster_bat_cpp3.attack_judge(test1[2] / 100, test1[2] % 100, CEraser::actor_x, CEraser::actor_y);
			}
			save[test1[2] % 100][test1[2] / 100] = 0;
			save[test2[2] % 100][test2[2] / 100] = 1;
			test1[2] = test2[2];
		}
	}
	if (point.x > monster_bat_cpp2.GetX1() && point.x < monster_bat_cpp2.GetX2() && point.y > monster_bat_cpp2.GetY1() && point.y < monster_bat_cpp2.GetY2()) {
		if (monster_cpp.attacked_judge(monster_bat_cpp2.mon_x, monster_bat_cpp2.mon_y, CEraser::actor_x, CEraser::actor_y) == 1) {
			monster_bat_cpp2.attacked(eraser.hero_ATK);

			monster_bat_cpp.SetMoving(true);
			monster_bat_cpp.SetMoving(false);
			test2[0] = monster_bat_cpp.getroad(save);
			if (test1[0] == test2[0]) {
				monster_bat_cpp.attack_judge(test1[0] / 100, test1[0] % 100, CEraser::actor_x, CEraser::actor_y);
			}
			save[test1[0] % 100][test1[0] / 100] = 0;
			save[test2[0] % 100][test2[0] / 100] = 1;
			test1[0] = test2[0];

			monster_bat_cpp3.SetMoving(true);
			monster_bat_cpp3.SetMoving(false);
			test2[2] = monster_bat_cpp3.getroad(save);
			if (test1[2] == test2[2]) {
				monster_bat_cpp3.attack_judge(test1[2] / 100, test1[2] % 100, CEraser::actor_x, CEraser::actor_y);
			}
			save[test1[2] % 100][test1[2] / 100] = 0;
			save[test2[2] % 100][test2[2] / 100] = 1;
			test1[2] = test2[2];
		}
	}
	if (point.x > monster_bat_cpp3.GetX1() && point.x < monster_bat_cpp3.GetX2() && point.y > monster_bat_cpp3.GetY1() && point.y < monster_bat_cpp3.GetY2()) {
		if (monster_cpp.attacked_judge(monster_bat_cpp3.mon_x, monster_bat_cpp3.mon_y, CEraser::actor_x, CEraser::actor_y) == 1) {
			monster_bat_cpp3.attacked(eraser.hero_ATK);

			monster_bat_cpp.SetMoving(true);
			monster_bat_cpp.SetMoving(false);
			test2[0] = monster_bat_cpp.getroad(save);
			if (test1[0] == test2[0]) {
				monster_bat_cpp.attack_judge(test1[0] / 100, test1[0] % 100, CEraser::actor_x, CEraser::actor_y);
			}
			save[test1[0] % 100][test1[0] / 100] = 0;
			save[test2[0] % 100][test2[0] / 100] = 1;
			test1[0] = test2[0];

			monster_bat_cpp2.SetMoving(true);
			monster_bat_cpp2.SetMoving(false);
			test2[1] = monster_bat_cpp2.getroad(save);
			if (test1[1] == test2[1]) {
				monster_bat_cpp2.attack_judge(test1[1] / 100, test1[1] % 100, CEraser::actor_x, CEraser::actor_y);
			}
			save[test1[1] % 100][test1[1] / 100] = 0;
			save[test2[1] % 100][test2[1] / 100] = 1;
			test1[1] = test2[1];
		}
	}

	if (check_backpack == 1) {	/////////////////點擊背包
		//脫下武器
		if (point.x > 760 && point.y < 250 && point.x<880) {
			backpackadd(eraser.checkweapon());
			printf("脫下");
			eraser.equipweapon(0);
		}
		//脫下裝備
		if (point.x > 890 && point.y < 250 && point.x < 1010) {
			backpackadd(eraser.checkarmor());
			printf("脫下");
			eraser.equiparmor(0);
		}
		//脫下戒指
		if (point.x > 1150 && point.y < 250 && point.x < 1270) {//脫下
			backpackadd(eraser.checkring());
			printf("脫下");
			eraser.equipring(0);
		}



		if (point.x > lb_p.Left() && point.x < lb_p.Left() + lb_p.Width() && point.y >  lb_p.Top() && point.y < lb_p.Top() + lb_p.Height()) {
			backpackdel(12);   /////喝藍水效果
		}
		if (point.x > dg_p.Left() && point.x < dg_p.Left() + dg_p.Width() && point.y >  dg_p.Top() && point.y < dg_p.Top() + dg_p.Height()) {
			backpackdel(13);	/////喝綠水效果
		}
		if (point.x > dr_p.Left() && point.x < dr_p.Left()+dr_p.Width() && point.y >  dr_p.Top() && point.y < dr_p.Top()+dr_p.Height()) {
			backpackdel(14);	/////喝紅水效果
		}
		if (point.x > sw1s_p.Left() && point.x < sw1s_p.Left() + sw1s_p.Width() && point.y >  sw1s_p.Top() && point.y < sw1s_p.Top() + sw1s_p.Height()) {
			
				printf("穿上");
				backpackadd(eraser.checkweapon());
				eraser.equipweapon(15);  //穿上
				backpackdel(15);

		}
		if (point.x > sw2s_p.Left() && point.x < sw2s_p.Left() + sw2s_p.Width() && point.y >  sw2s_p.Top() && point.y < sw2s_p.Top() + sw2s_p.Height()) {
			
				backpackadd(eraser.checkweapon());
				eraser.equipweapon(16);  //脫下
				backpackdel(16);
			
		}
		if (point.x > sw3s_p.Left() && point.x < sw3s_p.Left() + sw3s_p.Width() && point.y >  sw3s_p.Top() && point.y < sw3s_p.Top() + sw3s_p.Height()) {
			
			backpackadd(eraser.checkweapon());
				eraser.equipweapon(17);
				
				backpackdel(17);
			
		}
		if (point.x > st1s_p.Left() && point.x < st1s_p.Left() + st1s_p.Width() && point.y >  st1s_p.Top() && point.y < st1s_p.Top() + st1s_p.Height()) {
			backpackadd(eraser.checkweapon());
				eraser.equipweapon(18);
				
				backpackdel(18);
			
		}
		if (point.x > st2s_p.Left() && point.x < st2s_p.Left() + st2s_p.Width() && point.y >  st2s_p.Top() && point.y < st2s_p.Top() + st2s_p.Height()) {
			
			backpackadd(eraser.checkweapon());
				eraser.equipweapon(19);
				
				backpackdel(19);
			
		}
		if (point.x > st3s_p.Left() && point.x < st3s_p.Left() + st3s_p.Width() && point.y >  st3s_p.Top() && point.y < st3s_p.Top() + st3s_p.Height()) {
			
			backpackadd(eraser.checkweapon());
				eraser.equipweapon(20);
				
				backpackdel(20);
			
		}
		if (point.x > pa1s_p.Left() && point.x < pa1s_p.Left() + pa1s_p.Width() && point.y >  pa1s_p.Top() && point.y < pa1s_p.Top() + pa1s_p.Height()) {
			backpackdel(21);
		}
		if (point.x > pa2s_p.Left() && point.x < pa2s_p.Left() + pa2s_p.Width() && point.y >  pa2s_p.Top() && point.y < pa2s_p.Top() + pa2s_p.Height()) {
			backpackdel(22);
		}
		if (point.x > pa3s_p.Left() && point.x < pa3s_p.Left() + pa3s_p.Width() && point.y >  pa3s_p.Top() && point.y < pa3s_p.Top() + pa3s_p.Height()) {
			backpackdel(23);
		}
		if (point.x > ri1s_p.Left() && point.x < ri1s_p.Left() + ri1s_p.Width() && point.y >  ri1s_p.Top() && point.y < ri1s_p.Top() + ri1s_p.Height()) {
			
			backpackadd(eraser.checkring());
				eraser.equipring(24);
				
				backpackdel(24);
			
		}
		if (point.x > ri2s_p.Left() && point.x < ri2s_p.Left() + ri2s_p.Width() && point.y >  ri2s_p.Top() && point.y < ri2s_p.Top() + ri2s_p.Height()) {
			
			backpackadd(eraser.checkring());
				eraser.equipring(25);
				backpackdel(25);
			
		}
		if (point.x > ri3s_p.Left() && point.x < ri3s_p.Left() + ri3s_p.Width() && point.y >  ri3s_p.Top() && point.y < ri3s_p.Top() + ri3s_p.Height()) {
			
			backpackadd(eraser.checkring());
				eraser.equipring(26);
				backpackdel(26);
			
		}
		if (point.x > cl1s_p.Left() && point.x < cl1s_p.Left() + cl1s_p.Width() && point.y >  cl1s_p.Top() && point.y < cl1s_p.Top() + cl1s_p.Height()) {
			
			backpackadd(eraser.checkarmor());
				eraser.equiparmor(27);
				backpackdel(27);
			
			
		}
		if (point.x > cl2s_p.Left() && point.x < cl2s_p.Left() + cl2s_p.Width() && point.y >  cl2s_p.Top() && point.y < cl2s_p.Top() + cl2s_p.Height()) {
			
			backpackadd(eraser.checkarmor());
				eraser.equiparmor(28);
				backpackdel(28);
			
		}
		if (point.x > cl3s_p.Left() && point.x < cl3s_p.Left() + cl3s_p.Width() && point.y >  cl3s_p.Top() && point.y < cl3s_p.Top() + cl3s_p.Height()) {
			
			backpackadd(eraser.checkarmor());
				eraser.equiparmor(29);
				backpackdel(29);
			
		}
		if (point.x > fo1s_p.Left() && point.x < fo1s_p.Left() + fo1s_p.Width() && point.y >  fo1s_p.Top() && point.y < fo1s_p.Top() + fo1s_p.Height()) {
			backpackdel(30);  /////吃包子
		}
		if (point.x > fo2s_p.Left() && point.x < fo2s_p.Left() + fo2s_p.Width() && point.y >  fo2s_p.Top() && point.y < fo2s_p.Top() + fo2s_p.Height()) {
			backpackdel(31);  /////吃肉餅
		}
		if (point.x > ar1s_p.Left() && point.x < ar1s_p.Left() + ar1s_p.Width() && point.y >  ar1s_p.Top() && point.y < ar1s_p.Top() + ar1s_p.Height()) {
			backpackdel(35);
		}
		if (point.x > ar2s_p.Left() && point.x < ar2s_p.Left() + ar2s_p.Width() && point.y >  ar2s_p.Top() && point.y < ar2s_p.Top() + ar2s_p.Height()) {
			backpackdel(36);
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
	eraser.OnShow();		
	//monster_cpp.OnShow();
	monster_bat_cpp.OnShow();
	monster_bat_cpp2.OnShow();
	monster_bat_cpp3.OnShow();

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

		if (eraser.checkweapon() == 15) { ///裝備欄
			packx = 760, packy = 110;
			sw1s_p.SetTopLeft(packx, packy);
			sw1s_p.ShowBitmap();
		}
		else if (eraser.checkweapon() == 16) {
			packx = 760, packy = 110;
			sw2s_p.SetTopLeft(packx, packy);
			sw2s_p.ShowBitmap();
		}
		else if (eraser.checkweapon() == 17) {
			packx = 760, packy = 110;
			sw3s_p.SetTopLeft(packx, packy);
			sw3s_p.ShowBitmap();
		}
		else if (eraser.checkweapon() == 18) {
			packx = 760, packy = 110;
			st1s_p.SetTopLeft(packx, packy);
			st1s_p.ShowBitmap();
		}
		else if (eraser.checkweapon() == 19) {
			packx = 760, packy = 110;
			st2s_p.SetTopLeft(packx, packy);
			st2s_p.ShowBitmap();
		}
		else if (eraser.checkweapon() == 20) {
			packx = 760, packy = 110;
			st3s_p.SetTopLeft(packx, packy);
			st3s_p.ShowBitmap();
		}

		if (eraser.checkarmor() == 27) {
			packx = 890, packy = 110;
			cl1s_p.SetTopLeft(packx, packy);
			cl1s_p.ShowBitmap();
		}
		else if (eraser.checkarmor() == 28) {
			packx = 890, packy = 110;
			cl2s_p.SetTopLeft(packx, packy);
			cl2s_p.ShowBitmap();

		}
		else if (eraser.checkarmor() == 29) {
			packx = 890, packy = 110;
			cl3s_p.SetTopLeft(packx, packy);
			cl3s_p.ShowBitmap();
		}

		if (eraser.checkring() ==24 ) {
			packx = 1150, packy = 110;
			ri1s_p.SetTopLeft(packx, packy);
			ri1s_p.ShowBitmap();
		}
		else if (eraser.checkring() == 25) {
			packx = 1150, packy = 110;
			ri2s_p.SetTopLeft(packx, packy);
			ri2s_p.ShowBitmap();

		}
		else if (eraser.checkring() == 26) {
			packx = 1150, packy = 110;
			ri3s_p.SetTopLeft(packx, packy);
			ri3s_p.ShowBitmap();
		}



		for (int i = 0; i < 20; i++) {
			if (i <= 3) {
				packx = 760, packy = 230;
			}
			if (i > 3 && i <= 7) {
				packx = 760, packy = 360;
			}
			if (i > 7 && i <= 11) {
				packx = 760, packy = 480;
			}
			if (i > 11 && i <= 15) {
				packx = 760, packy = 620;
			}
			if (i > 15 && i <= 19) {
				packx = 760, packy = 740;
			}
			switch (pack_space[i])
			{
			case 12:
				lb_p.SetTopLeft(packx + (i % 4) * 130, packy);
				lb_p.ShowBitmap();
				break;
			case 13:
				dg_p.SetTopLeft(packx + (i % 4) * 130, packy);
				dg_p.ShowBitmap();
				break;
			case 14:
				dr_p.SetTopLeft(packx + (i%4) * 130, packy);
				dr_p.ShowBitmap();
				break;
			case 15:
				sw1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				sw1s_p.ShowBitmap();
				break;
			case 16:
				sw2s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				sw2s_p.ShowBitmap();
				break;
			case 17:
				sw3s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				sw3s_p.ShowBitmap();
				break;
			case 18:
				st1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				st1s_p.ShowBitmap();
				break;
			case 19:
				st2s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				st2s_p.ShowBitmap();
				break;
			case 20:
				st3s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				st3s_p.ShowBitmap();
				break;
			case 21:
				pa1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				pa1s_p.ShowBitmap();
				break;
			case 22:
				pa2s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				pa2s_p.ShowBitmap();
				break;
			case 23:
				pa3s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				pa3s_p.ShowBitmap();
				break;
			case 24:
				ri1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				ri1s_p.ShowBitmap();
				break;
			case 25:
				ri2s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				ri2s_p.ShowBitmap();
				break;
			case 26:
				ri3s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				ri3s_p.ShowBitmap();
				break;
			case 27:
				cl1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				cl1s_p.ShowBitmap();
				break;
			case 28:
				cl2s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				cl2s_p.ShowBitmap();
				break;
			case 29:
				cl3s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				cl3s_p.ShowBitmap();
				break;
			case 30:
				fo1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				fo1s_p.ShowBitmap();
				break;
			case 31:
				fo2s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				fo2s_p.ShowBitmap();
				break;
			case 32:
				ke1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				ke1s_p.ShowBitmap();
				break;
			case 35:
				ar1s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				ar1s_p.ShowBitmap();
				break;
			case 36:
				ar2s_p.SetTopLeft(packx + (i % 4) * 130, packy);
				ar2s_p.ShowBitmap();
				break;

			default:
				break;
			}
		}
	}
	///////////////////////////////////////////
		/*物品編號:
			12淺藍水 13深綠水 14深紅水
			15劍1 16劍2 17劍3
			18杖1 19杖2 20杖3
			21紙1 22紙2 23紙3
			24戒1 25戒2 26戒3
			27服1 28服2 29服3
			30食1 31食2
			32鑰匙 33寶箱 34墳墓
			35箭1 36箭2


		*/
		////////////////////////////////////////
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
		bool_gameover = 1;
		GotoGameState(GAME_STATE_OVER);
	}
	if (bool_finish == 1) {
		GotoGameState(GAME_STATE_OVER);
	}
}

}