#ifndef MONSTER_H
#define MONSTER_H
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class monster
	{
	public:
		monster();
		int monster_HP;
		int monster_ATK;
		int map_num = 1;
		int attack(int HP,int ATK);
		int getmap(int random_map,int map[][27]);
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int  Character();				//���o¾�~���ܼ�
		int automove(int automove_map[][27], int main_x, int main_y, int end_x, int end_y);
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
		static int mon_x;
		static int mon_y;
	protected:
		CAnimation animation;		// ���l���ʵe
		int x, y;					// ���l���W���y��
		int character;				//¾�~���ܼ�
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};

}
#endif