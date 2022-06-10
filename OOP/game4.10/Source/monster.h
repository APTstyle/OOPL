#ifndef MONSTER_H
#define MONSTER_H
#include "CEraser.h"
namespace game_framework {
	class monster
	{
	public:
		monster();
		int map_monster[27][27];
		int mon_HP = 20;
		int mon_ATK = 1;
		int map_num = 1;
		static int mon_x;
		static int mon_y;
		int next_step, next_x, next_y;
		int main_x, main_y;
		int map_x, map_y;
		void get_bat(int n, int x, int y);
		static int mon_bat_x;
		static int mon_bat_y;
		int mon2_x = 0;
		int mon2_y = 0;
		int test = 0;
		int deathshow=0;
		int mon_loc_judge(int mon_x, int mon_y);
		int whichway(int mon_way_x, int mon_way_y, int next_way_x, int next_way_y, int main_x, int main_y);
		void showdetail();
		void showdata();
		int attacked(int ATK);
		void attack_judge(int x1, int y1, int x2, int y2);
		int attacked_judge(int x1, int y1, int x2, int y2);
		void findroad();
		int getmap(int random_map, int map[][27]);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		int  Character();				//取得職業的變數
		int automove(int automove_map[][27], int main_x, int main_y, int end_x, int end_y);
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
		void SetMoving(bool flag);	// 設定是否正在移動
		void superdeath(); 
		void death();
		int stopeverything = 0;
	protected:
		CEraser eraser;
		CAnimation animation;		// 擦子的動畫
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