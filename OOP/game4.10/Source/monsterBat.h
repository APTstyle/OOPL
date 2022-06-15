#ifndef MONSTERBAT_H
#define MONSTERBAT_H
#include "CEraser.h"
#include "monster.h" 
#include "showHp.h"
namespace game_framework {
	class monster_bat
	{
	public:
		monster_bat();
		int map_monster[27][27]= {
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,3,3,3,3,3,3 },
		{ 3,9,1,13,14,12,3,1,1,3,1,1,1,1,1,3,1,2,2,2,1,1,8,8,1,3 },
		{ 3,1,1,10,1,1,3,1,1,3,1,1,1,1,1,3,1,7,7,1,1,7,8,8,1,3 },
		{ 3,1,2,7,7,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,3 },
		{ 3,1,2,2,2,7,3,3,4,3,3,3,4,3,3,3,3,3,3,3,3,3,1,3,3,3 },
		{ 3,1,7,2,2,2,4,1,1,3,3,3,1,1,1,1,3,3,3,3,3,3,1,3,3,3 },
		{ 3,1,1,1,7,7,3,1,1,1,1,1,1,1,3,1,1,1,1,3,3,3,1,3,3,3 },
		{ 3,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3 },
		{ 3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,1,3,3,3 },
		{ 3,1,1,1,1,1,1,3,6,6,6,6,6,3,3,3,1,1,1,3,3,3,1,1,3,3 },
		{ 3,1,1,1,7,7,8,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3 },
		{ 3,1,1,1,7,7,8,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3 },
		{ 3,1,1,1,1,8,8,3,6,6,6,6,6,1,1,1,1,1,1,1,1,1,1,1,3,3 },
		{ 3,1,1,1,1,1,1,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3 },
		{ 3,1,1,1,1,1,1,3,6,6,6,6,6,3,3,3,1,3,3,3,3,3,3,1,3,3 },
		{ 3,3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,1,3,3,3,3,3,3,1,3,3 },
		{ 3,3,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,1,3,3,3,3,3,1,3,3 },
		{ 3,3,3,1,1,4,1,1,8,8,8,8,8,1,3,1,1,1,3,3,3,3,3,1,3,3 },
		{ 3,3,3,3,3,3,1,1,8,8,1,8,8,1,3,1,1,1,3,3,3,3,3,1,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,4,3,3,3,3,4,3,3,3,3,3,3,3,1,3,3 },
		{ 3,3,3,3,3,1,1,1,1,3,1,1,1,7,1,1,1,1,1,1,3,3,3,1,3,3 },
		{ 3,3,3,3,3,1,1,1,1,4,1,1,7,2,7,1,1,1,1,1,4,1,1,1,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 }
		};
		int mon_MAXHP = 20;
		int mon_HP= 20;
		int mon_ATK = 0;
		int map_num = 1;
		int mon_x, mon_y;
		int next_step, next_x, next_y;
		int main_x, main_y;
		int map_x, map_y;
		void showdetail();
		void findroad();
		void attack_judge(int x1, int y1, int x2, int y2);
		int mon_loc_judge(int mon_x, int mon_y);
		int getmap(int random_map, int map[][27]);
		int whichway(int mon_way_x, int mon_way_y, int next_way_x, int next_way_y, int main_x, int main_y);
		int attacked(int ATK);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		int  Character();				//取得職業的變數
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetCharacter(int monster);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetMoving(bool flag);		// 設定是否正在移動
		void showdata();
		void death();
		int deathshow = 0;
		void superdeath();
		int stopeverything=0;
	protected:
		CEraser eraser;
		monster monster_cpp;
		CAnimation animation;		// 擦子的動畫
		showHp Shp;
		int x, y;					// 擦子左上角座標
		int character;				//職業的變數
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isMoving;
	};
}

#endif