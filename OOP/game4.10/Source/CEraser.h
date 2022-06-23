#ifndef CERASER_H
#define CERASER_H
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CEraser
	{
	public:
		CEraser();
		static int hero_def;
		static int hero_HP;
		static int hero_max_hp;
		static int hero_ATK;
		static int hero_hungry;
		void showdetail();
		void showdata();
		int attacked(int ATK);
		static int map_x, map_y;
		void reset(int m);
		void changeskin(int c);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		int  Character();				//取得職業的變數
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void equiparmor(int item);		//穿上裝備
		void equipweapon(int item);
		void equipring(int item);
		int checkarmor();		//穿上裝備
		int checkweapon();
		int checkring();
		void SetCharacter(int actor);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		static int actor_x, actor_y;	// 擦子左上角座標
		int changedef(int n);
		int changeatk(int n);
		int changemaxhp(int n);
		void heal();
		void addhp(int n);
		void stave();
		bool direction;
		void setdata(int n);
	protected:
		CAnimation animation;		// 擦子的動畫
		CAnimation animation2;		// 擦子的動畫
		CAnimation animation_hp_background;		// 擦子的動畫
		CAnimation animation_icon;		// 擦子的動畫
		CMovingBitmap animation_test;
		int x, y;					// 擦子左上角座標
		int character;				//職業的變數
		int hero_armor, hero_weapon,hero_ring; //裝備
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動

	};
}
#endif