# include <Siv3D.hpp> // Siv3D v0.6.16

class Player
{
public:
	Player() : playerPos(300.0, 600.0) {};
	void update()
	{
		//操作
		if (KeyW.pressed()) playerPos.y -= 10.0;
		if (KeyS.pressed()) playerPos.y += 10.0;
		if (KeyA.pressed()) playerPos.x -= 10.0;
		if (KeyD.pressed()) playerPos.x += 10.0;

		//画面外に出ないようにする
		playerPos.x = Clamp(playerPos.x, 50.0, 550.0);
		playerPos.y = Clamp(playerPos.y, 100.0, 700.0);
	}

	//ブレイヤーの描画
	void draw()
	{
		pleyerDraw
			.rotated(-45_deg)
			.drawAt(playerPos);
	}

	//プレイヤーの位置を取得
	Vec2 getPos() const
	{
		return playerPos;
	}

private:
	Vec2 playerPos;

	Texture pleyerDraw{ U"🚀"_emoji };
};

class Bullet
{
public:
	Bullet(Vec2 startPos) : bulletPos(startPos) {};

	//弾の更新
	void update()
	{
		bulletPos.y -= 10.0;
	}

	//弾の描画
	void draw() const
	{
		bulletDraw
		.drawAt(bulletPos);
	}

	//画面外に排出された弾の削除
	bool isOffScreen() const
	{
		return bulletPos.y < 0.0;
	}

private:
		Texture bulletDraw{ U"⭐"_emoji };

		Vec2 bulletPos;
};

struct Enemy
{
public:
	Enemy() : enemyPos(300.0,0.0) {};
	void update()
	{
		enemyPos.y += 5.0;
	}
	void draw() const
	{
		enemyDraw
		.drawAt(enemyPos);
	}
private:
	Vec2 enemyPos;

	Texture enemyDraw{ U"😁"_emoji };
};

void Main()
{
	Window::Resize(600, 800);

	Player player;
	Array<Bullet> bullets;

	Enemy enemy;

	while (System::Update())
	{
		player.update();

		if(KeySpace.down())
		{
			bullets << Bullet(player.getPos());
		}

		for(auto& bullet : bullets)
		{
			bullet.update();
		}

		bullets.remove_if([](const Bullet& b) { return b.isOffScreen(); });

		player.draw();
		for(const auto& bullet : bullets)
		{
			bullet.draw();
		}

		//敵の生成
		enemy.update();
		enemy.draw();
	}
}
