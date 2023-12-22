#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

enum Status
{
	Name,
	Hp,
	Atk,
	Def,
	Heal,
};

class Enemy;
class Hero;

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Attack(Hero* hero);              // 1 ダメージの修正
	int GetStatus(int status);            // 2 関数名の変更   // 3 return case:Name の修正
	void SetHp(int changeInHp);           // 2 関数名の変更

private:
	int NameShow();                       // 3 case:Nameで呼ばれる関数の追加

private:
	const char* name;
	int hp;
	int atk;
	int def;
};

class Hero
{
public:
	Hero();
	~Hero();
	void Attack(Enemy* enemy);           // 1 ダメージの修正
	void Heal();
	int GetStatus(int status);           // 2 関数名の変更 // 3 return case:Name の修正
	void SetHp(int changeInHp);          // 2 関数名の変更
	int InputKey();


private:
	void InputName();
	int ShowName();                      // 3 case:Nameで呼ばれる関数の追加


private:
	char* name;
	int hp;
	int atk;
	int def;


};



//敵の定義
Enemy::Enemy()
{
	name = "enemy";
	hp = 10;
	atk = 5;
	def = 2;
}

void Enemy::Attack(Hero* hero)
{
	int damage = hero->GetStatus(Def) - atk;        //1 ダメージ変数の追加

	if (damage > 0)                                 //1 修正
	{
		damage = 0;                                 //1 damageがマイナスの値でなければ0を入れる
	}

	cout << name << "の攻撃" << endl;
	hero->GetStatus(Name);
	cout << "に " << abs(damage) << " のダメージ" << endl;
	
	hero->SetHp(damage);
}

int Enemy::GetStatus(int status)
{
	switch (status)
	{
	case Hp:
		return hp;
		break;

	case Atk:
		return atk;
		break;

	case Def:
		return def;
		break;

	case Name:
		NameShow();                     //3 関数の追加
		break;

	default:
		break;
	}
}

void Enemy::SetHp(int changeInHp)
{
	hp += changeInHp;
}

int Enemy::NameShow()                   //3 GetStatusで呼ぶ関数の追加
{
	cout << name;
	return 0;
}

Enemy::~Enemy()
{
	
};



//プレイヤーの定義
Hero::Hero()
{
	InputName();

	cout << "HPを設定してください > " << flush;
	cin >> hp;

	atk = 5;
	def = 2;
};

void Hero::Attack(Enemy* enemy)
{
	int damage = enemy->GetStatus(Def) - atk;          //1 ダメージ変数の追加

	if (damage > 0)                                    //1 修正
	{
		damage = 0;                                    //1 damageがマイナスの値でなければ0を入れる
	}

	cout << name << "の攻撃" << endl;
	enemy->GetStatus(Name);
	cout << "に " << abs(damage) << " のダメージ" << endl;

	enemy->SetHp(damage); 
}


void Hero::Heal()
{
	int heal = 4;

	cout << "HPが "<< heal << " 回復した" << endl;
	hp += heal;
}

int Hero::GetStatus(int status)
{
	switch (status)
	{
	case Hp:
		return hp;
		break;

	case Atk:
		return atk;
		break;

	case Def:
		return def;
		break;

	case Name:
		ShowName();                   //3 関数の追加
		break;

	default:
		break;
	}
}

void Hero::SetHp(const int changeInHp)
{
	hp += changeInHp;
}

int Hero::ShowName()                                 //3 GetStatusで呼ぶ関数の追加
{
	cout << name;
	return 0;
}

void Hero::InputName()
{
	const int MAX_NAME = 30;
	char inputName[MAX_NAME + 1];
	
	cout << "名前を入力してください > " << flush;
	cin >> inputName;

	int size = strlen(inputName);                //4 strlenの使用に変更
	name = new char[size + 1];

	strcpy(name, inputName);                     //4 strcpyの使用に変更

	cout << "あなたの名前は " << name << " です。" << endl;
}

int Hero::InputKey()
{
	int inputKey;

	cout << "どうする？" << endl
		<< "攻撃 > 2のキー, 回復 > 4のキー" << endl;
	cin >> inputKey;

	return inputKey;
}

Hero::~Hero()
{
	delete[] name;      //5 解放はnewでとった値を解放するだけでポインタをdeleteするわけではないから先に開放を行う。
	*name = NULL;       //5 修正
};


void Battle(Hero* hero)
{
	Enemy enemy;

	int heroNowHp = hero->GetStatus(Hp);
	int enemyNowHp = enemy.GetStatus(Hp);

	while (true)
	{
		cout << endl;
		hero->GetStatus(Name);
		cout << " HP " << heroNowHp << endl;
		enemy.GetStatus(Name);
		cout << " HP " << enemyNowHp << endl;

		int action = hero->InputKey();

		if (action == Atk)
		{
			hero->Attack(&enemy);
			enemyNowHp = enemy.GetStatus(Hp);
		}
		else if (action == Heal)
		{
			hero->Heal();
		}

		if (enemyNowHp <= 0)
		{
			cout << "敵を倒した！" << endl;
			break;
		}

		enemy.Attack(hero);
		heroNowHp = hero->GetStatus(Hp);

		if (heroNowHp <= 0)
		{
			cout << "あなたは負けてしまった..." << endl;
			break;
		}
	}
}

int main()
{
	Hero hero;

	Battle(&hero);

}