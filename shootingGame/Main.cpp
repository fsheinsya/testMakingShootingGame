# include <Siv3D.hpp> // Siv3D v0.6.16

class Player
{
public:
	Player() : playerPos(300.0, 600.0) {};
	void update()
	{
		//操作
		if (KeyW.pressed()) playerPos.y -= 5.0;
		if (KeyS.pressed()) playerPos.y += 5.0;
		if (KeyA.pressed()) playerPos.x -= 5.0;
		if (KeyD.pressed()) playerPos.x += 5.0;

		//画面外に出ないようにする
		playerPos.x = Clamp(playerPos.x, 50.0, 550.0);
		playerPos.y = Clamp(playerPos.y, 100.0, 700.0);
	}

	void draw()
	{
		pleyerDraw
			.rotated(-45_deg)
			.drawAt(playerPos);
	}
private:
	Vec2 playerPos;

	Texture pleyerDraw{ U"🚀"_emoji };
};

void Main()
{
	Window::Resize(600, 800);

	Player player;

	while (System::Update())
	{
		player.update();

		player.draw();

		//Git te3t//
	}
}
