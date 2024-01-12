#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

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
	Enemy(const Enemy& other);      //コピーコンストラクタ
	void operator=(const Enemy& other);     //代入演算子のオーバーロード
	void Attack(Hero* hero);
	int GetStatus(const int status) const;
	void SetHp(const int changeInHp);
	void ShowName() const;

private:
	void InputName();

private:
	char* name;
	int hp;
	int atk;
	int def;
};

class Hero
{
public:
	Hero();
	~Hero();
	Hero(const Hero& other);            // コピーコンストラクタ
	void operator=(const Hero& other);  // 代入演算子のオーバーロード
	void Attack(Enemy* enemy);
	void Heal();
	int GetStatus(const int status) const;
	void SetHp(const int changeInHp);
	int InputKey();
	void ShowName() const;


private:
	void InputName();
	


private:
	char* name;
	int hp;
	int atk;
	int def;


};


Enemy::Enemy()
{
	InputName();

	cout << "HPを設定してください > " << flush;
	cin >> hp;

	atk = 5;
	def = 2;
}

//コピーコンストラクタ
Enemy::Enemy(const Enemy& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	hp = other.hp;
	atk = other.atk;
	def = other.def;

	//copy(other.name, other.name + def, name);

	//cout << "コピーコンストラクタが呼ばれました。" << endl;
}

//代入演算子のオーバーロード
void Enemy::operator=(const Enemy& other)
{
	char* opName = new char[strlen(other.name) + 1];
	strcpy(opName, other.name);
	delete[] name;
	name = opName;

	hp = other.hp;
	atk = other.atk;
	def = other.def;
}

void Enemy::Attack(Hero* hero)
{
	int damage = hero->GetStatus(Def) - atk;

	if (damage > 0)
	{
		damage = 0;
	}

	cout << name << "の攻撃" << endl;
	hero->ShowName();
	cout << "に " << abs(damage) << " のダメージ" << endl;
	
	hero->SetHp(damage);
}

int Enemy::GetStatus(const int status) const
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

	default:
		break;
	}
}

void Enemy::SetHp(int changeInHp)
{
	hp += changeInHp;
}

void Enemy::InputName()
{
	if (name != NULL)
	{
		delete[] name;
		name = NULL;
	}

	const int MAX_NAME = 30;
	char inputName[MAX_NAME + 1];

	cout << "敵の名前を入力してください > " << flush;
	cin >> inputName;

	int size = strlen(inputName);
	name = new char[size + 1];

	strcpy(name, inputName);

	cout << "敵の名前は " << name << " です。" << endl;
}

void Enemy::ShowName() const
{
	cout << name;
}

Enemy::~Enemy()
{
	if (name != NULL)
	{
		delete[] name;
		name = NULL;
	}

	//cout << "デストラクタが呼ばれました。" << endl;
};



Hero::Hero()
{
	InputName();

	cout << "HPを設定してください > " << flush;
	cin >> hp;

	atk = 5;
	def = 2;
};

//コピーコンストラクタ
Hero::Hero(const Hero& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	hp = other.hp;
	atk = other.atk;
	def = other.def;

	//copy(other.name, other.name + def, name);

	//cout << "コピーコンストラクタが呼ばれました。" << endl;
}

//代入演算子のオーバーロード
void Hero::operator=(const Hero& other)
{
	char* opName = new char[strlen(other.name) + 1];
	strcpy(opName, other.name);
	delete[] name;
	name = opName;

	hp = other.hp;
	atk = other.atk;
	def = other.def;
}

void Hero::Attack(Enemy* enemy)
{
	int damage = enemy->GetStatus(Def) - atk;

	if (damage > 0)
	{
		damage = 0;
	}

	cout << name << "の攻撃" << endl;
	enemy->ShowName();
	cout << "に " << abs(damage) << " のダメージ" << endl;

	enemy->SetHp(damage); 
}

void Hero::Heal()
{
	int heal = 4;

	cout << "HPが "<< heal << " 回復した" << endl;
	hp += heal;
}

int Hero::GetStatus(const int status) const
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

	default:
		break;
	}
}

void Hero::SetHp(const int changeInHp)
{
	hp += changeInHp;
}

void Hero::ShowName() const
{
	cout << name;
}

void Hero::InputName()
{
	if (name != NULL)
	{
		delete[] name;
		name = NULL;
	}

	const int MAX_NAME = 30;
	char inputName[MAX_NAME + 1];
	
	cout << "あなたの名前を入力してください > " << flush;
	cin >> inputName;

	int size = strlen(inputName);
	name = new char[size + 1];

	strcpy(name, inputName);

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
		delete[] name;
		name = NULL;
	}

	//cout << "デストラクタが呼ばれました。" << endl;

};


void Battle(Hero* hero)
{
	Enemy enemy;

	int heroNowHp = hero->GetStatus(Hp);
	int enemyNowHp = enemy.GetStatus(Hp);

	while (true)
	{
		cout << endl;
		hero->ShowName();
		cout << " HP " << heroNowHp << endl;
		enemy.ShowName();
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

void showStatus(Hero hero, Enemy enemy);

int main()
{
	Hero hero;
	Hero otherHero;
	Enemy enemy;
	Enemy otherEnemy;

	//Battle(&hero);

	showStatus(hero, enemy); // 代入前
	hero = otherHero;
	enemy = otherEnemy;
	showStatus(hero, enemy); // 代入後
}

void showStatus(const Hero const hero, const Enemy const enemy)
{
	cout << "あなたのパラメータ" << endl;
	hero.ShowName();
	printf(" HP:%d ATK:%d DEF:%d\n", hero.GetStatus(Hp), hero.GetStatus(Atk), hero.GetStatus(Def));

	cout << "敵のパラメータ" << endl;
	enemy.ShowName();
	printf(" HP:%d ATK:%d DEF:%d\n", enemy.GetStatus(Hp), enemy.GetStatus(Atk), enemy.GetStatus(Def));
}