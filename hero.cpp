#include <iostream>
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
	void Attack(Hero* hero);
	int EnemyGetStatus(int status);
	void EnemySetHp(int changeInHp);

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
	void Attack(Enemy* enemy);
	void Heal();
	int HeroGetStatus(int status);
	void HeroSetHp(int changeInHp);
	int InputKey();


private:
	void InputName(int &nameSize);
	int CharArrayCheckSize(const char* array);

private:
	char* name;
	int hp;
	int atk;
	int def;
	int nameSize;


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
	cout << name << "の攻撃" << endl;
	hero->HeroGetStatus(Name);
	cout << "に " << abs(hero->HeroGetStatus(Def) - atk) << " のダメージ" << endl;

	hero->HeroSetHp(hero->HeroGetStatus(Def) - atk);
}

int Enemy::EnemyGetStatus(int status)
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
		cout << name;
		break;

	default:
		break;
	}
}

void Enemy::EnemySetHp(int changeInHp)
{
	hp += changeInHp;
}

Enemy::~Enemy()
{
	
};



//プレイヤーの定義
Hero::Hero()
{
	InputName(nameSize);

	cout << "HPを設定してください > " << flush;
	cin >> hp;

	atk = 5;
	def = 2;
};

void Hero::Attack(Enemy* enemy)
{
	cout << name << "の攻撃" << endl;
	enemy->EnemyGetStatus(Name);
	cout << "に " << abs(enemy->EnemyGetStatus(Def) - atk) << " のダメージ" << endl;

	enemy->EnemySetHp(enemy->EnemyGetStatus(Def) - atk);
}

int Hero::CharArrayCheckSize(const char* array)
{
	int size = 1; //1の初期化は終端子記号（\0）の分

	for (int i = 0; array[i] != '\0'; ++i)
	{
		size++;
	}
	return size;
}

void Hero::Heal()
{
	int heal = 4;

	cout << "HPが "<< heal << " 回復した" << endl;
	hp += heal;
}

int Hero::HeroGetStatus(int status)
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
		cout << name;
		break;

	default:
		break;
	}
}

void Hero::HeroSetHp(const int changeInHp)
{
	hp += changeInHp;
}

void Hero::InputName(int &nameSize)
{
	const int MAX_NAME = 30;
	char inputName[MAX_NAME + 1];

	cout << "名前を入力してください > " << flush;
	cin >> inputName;

	nameSize = CharArrayCheckSize(inputName);
	name = new char[nameSize];

	
	for (int i = 0; i < nameSize; ++i)
	{
		name[i] = inputName[i];
	}
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
	for (int i = 0; i < nameSize; ++i)
	{
		name[i] = NULL;
	}

	delete[] name;
};


void Battle(Hero* hero)
{
	Enemy enemy;

	int heroNowHp = hero->HeroGetStatus(Hp);
	int enemyNowHp = enemy.EnemyGetStatus(Hp);

	while (true)
	{
		cout << endl;
		hero->HeroGetStatus(Name);
		cout << " HP " << heroNowHp << endl;
		enemy.EnemyGetStatus(Name);
		cout << " HP " << enemyNowHp << endl;

		int action = hero->InputKey();

		if (action == Atk)
		{
			hero->Attack(&enemy);
			enemyNowHp = enemy.EnemyGetStatus(Hp);
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
		heroNowHp = hero->HeroGetStatus(Hp);

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