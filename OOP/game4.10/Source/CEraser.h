#ifndef CERASER_H
#define CERASER_H
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
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
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int  Character();				//���o¾�~���ܼ�
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void equiparmor(int item);		//��W�˳�
		void equipweapon(int item);
		void equipring(int item);
		int checkarmor();		//��W�˳�
		int checkweapon();
		int checkring();
		void SetCharacter(int actor);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		static int actor_x, actor_y;	// ���l���W���y��
		int changedef(int n);
		int changeatk(int n);
		int changemaxhp(int n);
		void heal();
		void addhp(int n);
		void stave();
		bool direction;
		void setdata(int n);
	protected:
		CAnimation animation;		// ���l���ʵe
		CAnimation animation2;		// ���l���ʵe
		CAnimation animation_hp_background;		// ���l���ʵe
		CAnimation animation_icon;		// ���l���ʵe
		CMovingBitmap animation_test;
		int x, y;					// ���l���W���y��
		int character;				//¾�~���ܼ�
		int hero_armor, hero_weapon,hero_ring; //�˳�
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����

	};
}
#endif