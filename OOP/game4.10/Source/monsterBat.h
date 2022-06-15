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
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int  Character();				//���o¾�~���ܼ�
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetCharacter(int monster);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetMoving(bool flag);		// �]�w�O�_���b����
		void showdata();
		void death();
		int deathshow = 0;
		void superdeath();
		int stopeverything=0;
	protected:
		CEraser eraser;
		monster monster_cpp;
		CAnimation animation;		// ���l���ʵe
		showHp Shp;
		int x, y;					// ���l���W���y��
		int character;				//¾�~���ܼ�
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isMoving;
	};
}

#endif