#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

enum Status
{
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
	void Attack(Hero* hero);              // ダメージの修正
	int GetStatus(int status);            // 関数名の変更
	void SetHp(int changeInHp);           // 関数名の変更
	int ShowName();                       // publicに変更

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
	void Attack(Enemy* enemy);           // ダメージの修正
	void Heal();
	int GetStatus(int status);           // 関数名の変更
	void SetHp(int changeInHp);          // 関数名の変更
	int InputKey();
	int ShowName();                      // publicに変更


private:
	void InputName();
	


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
	int damage = hero->GetStatus(Def) - atk;        // ダメージ変数の追加

	if (damage > 0)                                 // 修正
	{
		damage = 0;                                 // damageがマイナスの値でなければ0を入れる
	}

	cout << name << "の攻撃" << endl;
	hero->ShowName();	                        // ShowNameに修正
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
		                                   // caseNameの削除
	default:
		break;
	}
}

void Enemy::SetHp(int changeInHp)
{
	hp += changeInHp;
}

int Enemy::ShowName()
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
	InputName();
	InputName();

	cout << "HPを設定してください > " << flush;
	cin >> hp;

	atk = 5;
	def = 2;
};

void Hero::Attack(Enemy* enemy)
{
	int damage = enemy->GetStatus(Def) - atk;          // ダメージ変数の追加

	if (damage > 0)                                    // 修正
	{
		damage = 0;                                    // damageがマイナスの値でなければ0を入れる
	}

	cout << name << "の攻撃" << endl;
	enemy->ShowName();                                 // ShowNameに修正
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
		                                    // caseNameの削除
	default:
		break;
	}
}

void Hero::SetHp(const int changeInHp)
{
	hp += changeInHp;
}

int Hero::ShowName()
{
	cout << name;
	return 0;
}

void Hero::InputName()
{
	if (name != NULL)                             // new二重防止コードの追加
	{
		delete[] name;
		name = NULL;
	}

	const int MAX_NAME = 30;
	char inputName[MAX_NAME + 1];
	
	cout << "名前を入力してください > " << flush;
	cin >> inputName;

	int size = strlen(inputName);                // strlenの使用に変更
	name = new char[size + 1];

	strcpy(name, inputName);                     // strcpyの使用に変更

	cout << "あなたの名前は " << name << " です。" << endl;
}

int Hero::InputKey()
{
	int inputKey;

	cout << "どうする？" << endl
		<< "攻撃 > 1のキー, 回復 > 3のキー" << endl;
	cin >> inputKey;

	return inputKey;
}

Hero::~Hero()
{
	if (name != NULL)
	{
		delete[] name;      // 解放はnewでとった値を解放するだけでポインタをdeleteするわけではないから先に開放を行う。
		name = NULL;        // 修正
	}
};


void Battle(Hero* hero)
{
	Enemy enemy;

	int heroNowHp = hero->GetStatus(Hp);
	int enemyNowHp = enemy.GetStatus(Hp);

	while (true)
	{
		cout << endl;
		hero->ShowName();     // ShowNameに修正
		cout << " HP " << heroNowHp << endl;
		enemy.ShowName();     // ShowNameに修正
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