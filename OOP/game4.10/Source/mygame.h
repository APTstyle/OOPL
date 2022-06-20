/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

#include "CEraser.h"
#include "CBall.h"
#include "monster.h"
#include "monsterBat.h"
//#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT,				// 2
		START_MUSIC,			// 3
		GAMING_MUSIC,			//4
		SND_item,
		SND_death,
		SND_door,
		SND_drink,
		SND_eat,
		SND_ghost,
		SND_hit,
		SND_miss,
		SND_trap,
		SND_unlock

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		CEraser			eraser;
		monster			monster_cpp;
		monster_bat		monster_bat_cpp;
		monster_bat		monster_bat_cpp2;
		monster_bat		monster_bat_cpp3;
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap startb;
	};

	class CGameMainMenu : public CGameState {
	public:
		CGameMainMenu(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定				
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		//void GetActor();
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		//CEraser		eraser;		
		CMovingBitmap c1,c2,c3,c4;								//四個職業
		//int actor_number;
		
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	class CBouncingBall{
	public:
		CBouncingBall();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetFloor(int);
		void SetXY(int, int);
		void Setvelocity(int);
	private:
		int x, y;
		int floor;
		bool rising;
		int initial_velocity;
		int velocity;
		CAnimation animation;
	};
	////////////////////////////////////////////////////////////
	class CGameMap
	{
	public:
		CGameMap();
		monster			monster_cpp;
		monster_bat		monster_bat_cpp;
		monster_bat		monster_bat_cpp2;
		monster_bat		monster_bat_cpp3;
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void OnKeyDown(UINT);
		void RandomBouncingBall();
		void SetXY(int, int);
		void InititalizeBouncingBall(int, int, int);
		static int ismoving;
		int X, Y;
		void changemap(int);
		int map[25][27];
		int map1_init[25][27] = {//24*26
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3},
			{3,9,1,14,1,1,3,1,15,3,1,1,1,1,1,3,1,2,2,2,1,1,8,8,1,3},
			{3,1,1,26,1,1,3,1,1,3,1,1,1,1,1,3,27,7,7,1,1,7,8,8,1,3},
			{3,24,27,7,7,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,1,1,1,1,30,3},
			{3,1,2,2,2,7,3,3,4,3,3,3,4,3,3,3,3,3,3,3,3,3,1,3,3,3},
			{3,15,7,2,2,2,4,1,1,3,3,3,1,1,1,1,3,3,3,3,3,3,1,3,3,3},
			{3,15,15,1,7,7,3,1,1,1,1,1,1,1,3,1,31,1,1,3,3,3,1,3,3,3},
			{3,16,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3},
			{3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3},
			{3,1,1,1,1,1,1,3,1,1,1,1,14,3,3,3,1,1,1,3,3,3,1,1,3,3},
			{3,1,1,1,7,7,8,3,13,1,1,1,1,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,30,1,1,7,7,8,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,1,1,1,1,8,8,3,6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1,3,3},
			{3,1,1,1,1,1,31,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,1,1,1,1,1,1,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,3,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,1,3,3,3,3,3,1,3,3},
			{3,3,3,1,1,4,1,1,8,8,8,8,8,1,3,1,1,10,3,3,3,3,3,1,3,3},
			{3,3,3,3,3,3,1,1,8,8,1,8,8,1,3,1,1,1,3,3,3,3,3,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,4,3,3,3,3,3,3,3,1,3,3},
			{3,3,3,3,3,35,1,1,1,3,1,1,1,7,1,1,1,1,12,1,3,3,3,1,3,3},
			{3,3,3,3,3,1,1,1,1,4,1,1,7,2,7,1,1,1,1,1,4,1,1,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
		int map2_init[25][27] = {//24*24
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3},
			{3,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,31,3},
			{3,1,3,3,3,1,3,3,3,3,1,3,3,7,4,1,1,1,1,1,1,1,1,3},
			{3,1,3,3,3,4,3,3,3,3,4,3,3,3,3,1,1,16,1,1,1,1,1,3},
			{3,1,1,3,1,1,1,1,1,3,1,1,1,2,3,1,1,1,1,1,1,1,7,3},
			{3,3,1,3,1,1,9,1,12,3,1,1,1,2,3,1,1,1,7,3,3,3,3,3},
			{3,3,1,3,1,1,1,1,1,3,1,1,21,2,3,4,3,3,3,3,1,1,7,3},
			{3,3,1,3,1,1,1,1,1,4,1,1,1,2,3,1,3,3,1,4,1,1,27,3},
			{3,3,1,3,1,1,1,1,31,3,1,1,1,2,3,1,1,1,1,3,1,1,1,3},
			{3,2,1,3,1,1,1,1,1,3,1,1,1,2,3,3,3,1,3,3,7,7,7,3},
			{3,2,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,1,3,3,3,3,3,3},
			{3,1,3,5,5,3,3,3,1,1,1,7,3,3,5,5,3,1,1,1,3,5,5,3},
			{3,1,2,2,2,1,1,1,1,3,1,1,1,2,2,2,2,1,3,1,1,1,1,3},
			{3,1,3,3,3,3,1,3,3,3,7,3,3,3,3,3,2,3,3,3,3,3,1,3},
			{3,1,3,3,3,3,1,3,3,3,4,3,3,3,3,3,2,3,5,3,3,3,7,3},
			{3,7,3,3,3,1,1,3,14,1,1,1,3,3,3,3,2,2,2,1,1,1,7,3},
			{3,1,7,3,3,7,3,3,1,1,1,1,3,3,3,3,2,3,3,3,3,1,3,3},
			{3,3,4,3,3,4,3,3,3,3,4,3,3,3,3,3,3,3,3,3,3,4,3,3},
			{3,1,1,3,1,1,1,1,1,3,7,1,3,3,6,6,6,6,6,3,1,1,1,3},
			{3,1,1,3,1,1,1,10,1,3,3,1,3,3,6,6,6,6,6,3,1,1,1,3},
			{3,1,1,3,1,1,1,1,1,3,3,1,3,3,6,6,6,6,6,3,1,1,1,3},
			{3,1,29,3,1,26,1,1,1,3,3,1,3,3,6,6,6,6,6,3,1,1,13,3},
			{3,1,1,3,2,2,2,2,2,4,1,1,1,1,6,6,6,6,6,3,1,1,1,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
		int map3_init[25][27] = {//24*24
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3},
			{3,1,1,13,1,1,3,3,1,1,1,1,1,1,1,1,3,1,14,1,1,30,1,3},
			{3,1,1,1,1,1,3,3,1,3,3,3,3,1,3,1,4,1,1,1,1,1,1,3},
			{3,1,1,1,1,1,3,3,1,3,3,3,3,1,3,3,3,3,3,3,3,3,3,3},
			{3,1,30,1,1,1,4,1,1,3,3,3,3,1,4,1,1,1,1,1,1,1,1,3},
			{3,1,1,1,1,1,3,1,3,3,3,3,3,1,3,1,9,1,1,1,1,1,23,3},
			{3,3,3,3,3,3,3,1,1,3,3,3,3,1,3,1,1,1,1,1,1,1,1,3},
			{3,1,1,21,1,1,3,3,1,3,3,3,3,4,3,3,4,3,3,3,3,3,3,3},
			{3,1,1,1,1,1,3,3,1,3,3,7,1,1,4,1,1,1,1,1,1,1,1,3},
			{3,1,1,1,1,1,4,7,1,1,4,1,1,1,3,1,1,27,1,1,1,1,1,3},
			{3,3,3,4,3,3,3,3,1,3,3,1,1,1,3,1,1,1,1,1,1,1,1,3},
			{3,3,3,1,3,3,3,3,1,3,3,4,3,3,3,3,4,3,3,3,3,3,3,3},
			{3,3,1,1,3,3,3,3,1,3,3,1,3,3,3,3,1,3,34,1,1,1,1,3},
			{3,3,1,3,3,3,3,3,1,5,5,1,3,3,3,3,1,3,1,1,1,1,17,3},
			{3,3,1,3,3,3,3,3,1,2,2,2,2,2,2,2,2,3,3,3,4,3,3,3},
			{3,3,1,3,3,3,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,3},
			{3,3,1,1,1,1,1,1,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,3},
			{3,3,3,1,3,3,3,1,1,3,3,1,3,3,3,3,3,3,3,3,1,3,3,3},
			{3,3,3,1,3,3,3,4,3,3,3,1,3,3,3,3,3,3,3,3,1,3,3,3},
			{3,3,3,1,1,1,4,1,1,1,3,1,3,3,3,3,3,3,3,3,1,3,3,3},
			{3,3,3,3,3,3,3,1,1,1,4,1,1,1,1,1,1,1,1,1,1,3,3,3},
			{3,3,3,3,3,3,3,1,10,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
		int map4_init[25][27] = {
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3},
			{3,3,3,1,1,1,2,4,31,1,8,8,8,1,1,1,3,2,2,2,1,8,8,3},
			{3,3,3,1,3,3,3,3,1,1,8,8,8,1,3,1,4,1,1,1,1,8,8,3},
			{3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3},
			{3,3,1,3,3,3,3,1,8,3,3,3,3,1,4,1,8,8,8,1,3,3,3,3},
			{3,3,1,1,3,3,3,1,3,3,3,3,3,1,3,1,8,8,8,1,3,3,3,3},
			{3,3,3,4,3,3,3,1,1,3,3,3,3,1,3,1,1,15,1,1,3,3,3,3},
			{3,3,7,7,7,1,3,3,1,3,3,3,3,4,3,3,4,3,3,4,3,3,3,3},
			{3,1,7,8,8,7,3,3,1,3,3,7,1,1,3,1,1,10,3,1,3,3,3,3},
			{3,1,7,7,7,1,4,7,1,1,4,1,1,1,1,7,8,1,3,13,3,3,3,3},
			{3,3,3,4,3,3,3,3,1,3,3,1,1,1,3,1,7,1,3,1,1,1,1,3},
			{3,3,3,1,3,3,3,3,1,3,3,4,3,3,3,3,4,3,3,3,3,4,3,3},
			{3,1,1,1,1,1,3,3,1,3,3,1,3,3,3,3,1,3,1,1,1,1,1,3},
			{3,1,1,9,1,14,3,3,1,5,5,1,3,5,5,3,1,3,1,1,1,1,35,3},
			{3,1,1,7,7,1,3,3,1,2,2,2,2,2,2,2,2,3,3,3,4,3,3,3},
			{3,1,1,7,7,1,3,3,1,3,3,1,3,3,3,3,3,3,3,3,1,1,1,3},
			{3,3,3,1,1,1,1,1,1,3,3,1,3,3,3,3,3,3,3,3,1,1,1,3},
			{3,3,3,1,3,3,3,1,3,3,3,1,3,3,3,1,1,12,3,3,1,1,1,3},
			{3,3,3,1,3,3,3,4,3,3,3,1,3,3,3,1,1,1,3,3,1,1,1,3},
			{3,3,3,1,1,1,4,1,1,1,3,1,3,3,3,4,3,3,3,3,3,4,3,3},
			{3,3,3,3,3,3,3,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,3,3},
			{3,3,3,3,3,3,3,1,8,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,8,8,30,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
		int map5_init[25][27] = {
			{3,3,3,3,3,3,3,3,5,5,3,3,3,3,3,3,3,5,5,5,3,3,3,3},
			{3,3,3,3,3,1,1,2,2,2,2,1,1,1,3,1,1,1,1,1,1,1,1,3},
			{3,3,3,3,3,1,3,3,3,3,1,3,3,7,4,1,3,3,3,3,3,3,36,3},
			{3,3,3,3,3,4,3,3,3,3,4,3,3,3,3,1,3,3,3,3,3,3,1,3},
			{3,3,1,4,1,1,1,25,1,3,1,1,1,2,3,1,1,1,1,1,1,1,8,3},
			{3,3,1,3,1,1,1,1,1,4,1,1,1,2,3,4,3,3,3,3,3,3,3,3},
			{3,3,1,3,3,3,3,3,3,3,1,3,3,2,3,1,3,3,3,3,1,8,8,3},
			{3,3,1,3,3,3,3,3,3,3,30,5,5,2,3,1,3,3,3,3,1,1,10,3},
			{3,3,1,3,3,3,3,3,3,3,1,2,2,2,3,1,1,1,1,4,1,1,1,3},
			{3,2,1,3,3,3,3,3,3,3,1,1,1,2,3,3,3,1,3,3,8,8,8,3},
			{3,2,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,1,3,3,3,3,3,3},
			{3,1,3,5,5,3,3,3,1,1,1,7,3,3,5,5,3,1,1,1,3,5,5,3},
			{3,1,2,2,2,2,1,1,1,3,1,1,1,2,2,2,2,1,3,1,1,1,1,3},
			{3,3,3,3,3,3,3,3,3,3,7,3,3,3,3,3,2,3,3,3,3,3,1,3},
			{3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,2,3,5,3,3,3,7,3},
			{3,3,3,3,3,3,3,3,1,1,1,1,3,3,3,3,2,2,2,1,1,1,7,3},
			{3,3,3,3,3,3,3,3,1,1,1,1,3,3,3,3,3,3,3,3,3,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,3,4,3,3},
			{3,1,1,1,1,1,1,3,3,3,7,1,3,3,3,3,3,3,3,3,1,1,1,3},
			{3,1,1,1,15,1,1,3,3,3,3,1,3,3,3,3,3,3,3,3,1,1,31,3},
			{3,1,1,1,1,1,1,3,3,3,3,1,3,3,1,1,1,21,1,3,1,1,1,3},
			{3,1,28,1,1,1,1,3,3,3,3,1,3,3,1,1,9,1,1,3,12,1,1,3},
			{3,1,1,1,2,2,2,4,2,1,1,1,1,4,1,1,1,1,1,3,1,1,1,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
		int map6_init[25][27] = {
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,1,1,21,1,1,3,3,3,3,1,1,1,14,1,3,3,3,3,3,6,6,6,6,6,3},
			{3,1,1,1,1,1,3,3,3,3,1,9,1,1,1,3,3,3,3,3,6,6,13,6,6,3},
			{3,1,2,7,7,1,3,3,3,3,1,1,1,1,1,3,3,3,3,3,6,6,6,6,6,3},
			{3,1,2,2,2,7,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,1,3,3,3},
			{3,1,7,2,2,2,4,1,1,3,3,3,1,1,1,1,3,3,3,3,3,3,1,3,3,3},
			{3,1,1,1,7,7,3,1,1,1,1,1,1,1,3,1,1,1,1,3,3,3,1,3,3,3},
			{3,1,1,1,30,1,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3},
			{3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3},
			{3,1,1,1,3,3,3,3,8,8,8,8,8,3,3,3,1,1,1,3,3,3,1,1,3,3},
			{3,1,1,1,3,3,3,3,8,8,8,8,8,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,1,1,27,3,3,3,3,8,8,8,8,8,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,1,1,1,3,3,3,3,10,8,8,8,8,4,1,1,1,1,1,1,1,1,1,1,3,3},
			{3,1,1,1,3,3,3,3,8,8,8,8,8,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,1,1,1,3,3,3,3,8,8,8,8,8,3,3,3,1,3,3,3,3,3,1,1,3,3},
			{3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,1,3,3,3},
			{3,3,1,1,3,3,3,3,3,3,1,1,1,3,3,1,1,1,3,3,3,3,1,1,3,3},
			{3,3,3,1,1,1,1,1,1,4,1,1,1,3,3,1,24,1,3,3,3,3,3,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,1,1,1,3,3,1,1,1,3,3,3,3,1,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,4,3,3,3,3,3,3,1,3,3,3},
			{3,3,3,1,1,1,12,1,1,3,1,1,1,7,1,1,1,31,1,3,3,3,1,1,3,3},
			{3,3,3,1,17,1,1,1,1,4,1,1,7,2,7,1,1,1,1,4,1,3,3,1,3,3},
			{3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
		int map7_init[25][27] = {
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,1,1,1,1,1,3,3,3,3,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3},
			{3,1,1,9,1,1,4,1,1,2,2,2,1,1,1,3,3,3,3,3,3,3,3,3,3,3},
			{3,1,2,2,2,1,3,3,3,3,2,2,2,1,1,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,3},
			{3,1,1,1,3,3,3,3,2,2,2,2,2,3,3,3,1,1,1,3,3,3,3,3,3,3},
			{3,1,1,1,3,3,3,3,2,3,3,2,2,3,3,3,1,3,3,3,3,3,3,3,3,3},
			{3,1,10,1,3,3,3,3,2,3,3,1,1,3,3,3,1,3,3,3,3,3,3,3,3,3},
			{3,1,1,1,3,3,3,3,2,3,3,1,1,4,1,1,1,2,2,2,1,1,1,1,3,3},
			{3,1,1,1,3,3,3,3,2,3,3,1,1,3,3,3,1,2,2,2,1,1,1,1,3,3},
			{3,1,1,1,3,3,3,3,2,2,1,1,1,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,1,3,3},
			{3,3,1,1,3,3,3,3,3,3,1,1,1,3,3,2,2,1,3,3,3,3,3,2,3,3},
			{3,3,3,1,1,1,1,1,2,2,2,2,1,3,3,2,2,1,3,3,3,3,3,2,3,3},
			{3,3,3,3,3,3,3,3,3,3,2,2,1,3,3,1,1,1,3,3,3,3,3,2,3,3},
			{3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,1,3,3,3,3,3,3,3,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,1,2,2,7,1,1,1,1,2,3,3,3,3,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,1,1,7,2,7,1,1,1,2,4,1,1,1,1,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
			{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
		//int random_map;
		~CGameMap();

	protected:
		CMovingBitmap mf, wh,fw,opd,md,wf,sg,lg,stair_d, stair_u,water_floor;
		int actor_x=1, actor_y=1;
		int monster_x = 2, monster_y = 2;
		CMovingBitmap lb_p, dr_p, dg_p;

		CMovingBitmap pa1s, pa2s, pa3s;
		CMovingBitmap sw1s, sw2s, sw3s;
		CMovingBitmap st1s, st2s, st3s;
		CMovingBitmap cl1s, cl2s, cl3s;
		CMovingBitmap ri1s, ri2s, ri3s;
		CMovingBitmap fo1s, fo2s;
		CMovingBitmap tr1s,ke1s,ar1s,ar2s,gr1s;
		int MW, MH;
		CBouncingBall*bballs;
		int random_num;
	};

	///////////////////////////////////////////////////////
	class CGameStateRun : public CGameState {
	public:
		CEraser			eraser;	
		monster			monster_cpp;
		monster_bat		monster_bat_cpp;
		monster_bat		monster_bat_cpp2;
		monster_bat		monster_bat_cpp3;
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void bat_setup(int x, int y);
		void bat_setup2(int x, int y);
		void bat_setup3(int x, int y);
		void OnBeginState();							// 設定每次重玩所需的變數
		void monsetmap(int m);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void dealbackpack(int number);
		int open_infor;
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CGameMap		gamemap;
		const int		NUMBALLS;	// 球的總數
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		CBall			*ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖

		CMovingBitmap	backpack;
		CMovingBitmap	stop;
		CMovingBitmap	detect;
		CMovingBitmap	qitem1;
		CMovingBitmap	qitem2;
		CMovingBitmap	qitem3;
		CMovingBitmap	qitem4;
		CMovingBitmap	backpackUI;
		// infor ui
		CMovingBitmap	infor;
		CMovingBitmap	hero_infor;
		CMovingBitmap	a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
		CMovingBitmap	hp, atk, def, hero_word;
		CInteger		hp_n;
		CInteger		atk_n;
		CInteger		def_n;

		CMovingBitmap		hungry1, hungry2;
		///////////////////背包物品//////////////////////////
		CMovingBitmap	lb_p, dr_p, dg_p;

		CMovingBitmap pa1s_p, pa2s_p, pa3s_p;
		CMovingBitmap sw1s_p, sw2s_p, sw3s_p;
		CMovingBitmap st1s_p, st2s_p, st3s_p;
		CMovingBitmap cl1s_p, cl2s_p, cl3s_p;
		CMovingBitmap ri1s_p, ri2s_p, ri3s_p;
		CMovingBitmap fo1s_p, fo2s_p;
		CMovingBitmap ke1s_p, ar1s_p, ar2s_p;
		CMovingBitmap final_item;
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


		//////////////////////////////////////////////////////
		
		CMovingBitmap	herohp;

		//CInteger		hits_left;	// 剩下的撞擊數
		CBouncingBall   bballs;		// 反覆彈跳的球
		CMovingBitmap   practice;
		CMovingBitmap   border; //practice2
		CMovingBitmap	practice3;
		int picX, picY;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		CMovingBitmap	finishbackground2;
		CMovingBitmap	finishbackground;

		CMovingBitmap	gameoverBG;
		CMovingBitmap	gameoverbutton;
		CEraser			eraser;
		monster			monster_cpp;
		monster_bat		monster_bat_cpp;
		monster_bat		monster_bat_cpp2;
		monster_bat		monster_bat_cpp3;
		CGameMap		gamemap;
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};
}