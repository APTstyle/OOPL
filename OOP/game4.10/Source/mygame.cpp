/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
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
	
	int random_map = 1; //���ե�
	int test = 0;

	int check_backpack = 0;
	int pack_space[19];
	int pack_now = 1;
	int attack = 0;
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////


CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{

}



void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	

	logo.LoadBitmap(mainpage);
	startb.LoadBitmap(startbutton);
	startb.SetTopLeft(600, 850);
	
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
		//random_map = (rand()%2)+1; ���a���H���X�{
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
		
		
    }						///�Ӽh1  0�� 1�a�O 2���a�O 3���� 4�� 5���� 6��a�O 7�p�� 8�j�� 9�W�� 10�U�� 11�}��	//12�L�Ť� 13�`��� 14�`����

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
       for(int i=0;i<27;i++)	//�e��27
            for (int j = 0; j < 27; j++) //����25
		/*for (int i = actor_x - 5; i < actor_x + 5; i++)	//�e��27
			for (int j = actor_y - 5; j < actor_y + 5; j++) //����25*/
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
		/*���~�s��:
			12�L�Ť� 13�`��� 14�`����


		*/
		////////////////////////////////////////


		/*for (int i = 0; i < random_num; i++) {
			bballs[i].OnShow();
		}*/
    }
	void CGameMap::OnKeyDown(UINT nChar) {
		const int KEY_SPACE = 0x20;
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y
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
		//GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(point.x>startb.Left() && point.y>startb.Top() && (point.y < startb.Top()+startb.Height()) && (point.x < startb.Left()+startb.Width()))
		GotoGameState(GAME_MAIN_UI);		// ������GAME_STATE_RUN
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
	// �K�Wlogo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	startb.ShowBitmap();
	//
	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	/*pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");*/
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
	for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	//CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI*/
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	//
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// ���ʭI���Ϫ��y��
	gamemap.OnMove();
	//
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(80 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	//
	// ���ʲy
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
	// �������l
	//
	monster_cpp.OnMove();
	eraser.OnMove();
	monster_bat_cpp.OnMove();
	//
	// �P�_���l�O�_�I��y
	//
	for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-10);
			//
			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//
	// ���ʼu�����y
	//
	bballs.OnMove();
}

void CGameStateRun::OnInit()  							// �C������Ȥιϧγ]�w
{
	
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
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
		ball[i].LoadBitmap();								// ���J��i�Ӳy���ϧ�

	
	
	background.LoadBitmap(mainpage);					// ���J�I�����ϧ�
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	
	//help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	//corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	//corner.ShowBitmap(background);							// �Ncorner�K��background
	bballs.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int test = 1;
	const int KEY_SPACE = 0x20;
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_Z  = 0x5a; // keyboard���b�Y
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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y

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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(true);
	

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
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

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(true);
	
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	int uix = 700, uiy = 990;
	if (random_map == 1) {
		eraser.SetXY(920 + 45, 540 +45);//�����l��m
	}
	if (random_map == 2) {
		eraser.SetXY(920 + 45, 540 + 45);//�����l��m
	}
	if (random_map == 3) {
		eraser.SetXY(920 + 45, 540 + 45);//�����l��m
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
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	//
	//background.ShowBitmap();			// �K�W�I����
	gamemap.OnShow();
	//help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();
	//for (int i=0; i < NUMBALLS; i++)
	//	ball[i].OnShow();				// �K�W��i���y
	//bballs.OnShow();	// �K�W�u�����y
	eraser.OnShow();					// �K�W���l
	monster_cpp.OnShow();
	monster_bat_cpp.OnShow();

	backpack.ShowBitmap();
	stop.ShowBitmap();
	detect.ShowBitmap();
	qitem1.ShowBitmap();
	qitem2.ShowBitmap();
	qitem3.ShowBitmap();
	qitem4.ShowBitmap();
	///////////////////////////////////�}�ҭI�]/////////////////////////
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
	///////////////////////////////////�}�ҭI�]/////////////////////////



	//
	//  �K�W���W�Υk�U��������
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