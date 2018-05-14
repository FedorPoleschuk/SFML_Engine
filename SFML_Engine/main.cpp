#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


float offsetX = 0, offsetY = 0;


const int H = 17;
const int W = 250;


String TileMap[H] = {
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
	"0                                     kk                       kk                        kk                       kk                                                                                                                                                                                                    0",
	"0                w                    kk             w         kk                        kk                       kk                                                                                                                                                                                                    0",
	"0                                     kk                       kk                        kk                       kk                                                                                                                                                                                  w                 0",
	"0                                     kk                       kk                                                 kk                                                                                                                                                                                                    0",
	"0                                     kk                       kk                                                 kk					w                                                                                                                                                                                0",
	"0                                     kk                       kk          w                           w          kk                                                       w                                                                                                                                            0",
	"0                                                              kk                        kk                       kk                                                                                                                                                                                                    0",
	"0                                                              kk                        kk                       kk                                                                                                                                                                                                    0",
	"0                                                                                        kk                       kk                                                                                                                                                                                                    0",
	"0                                                                                        kk                       kk                                                                                                                                                                                                    0",
	"0     w                               kk                                                 kk                                                                                                                                                                                    w                                        0",
	"0                                     kk                                                 kk           w                                                                                                                                                                                                                 0",
	"0                                     kk                       kk                        kk                                                                                                                                                                                                                             0",
	"0   G G                  G            KK                       KK     G                  kk        G                                G                 GG                                   G                       G                                                                                                    0",
	"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
	
};




class PLAYER {

public:

	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(400, 720, 400, 180);

		dx = dy = 0.1;
		currentFrame = 0;
	}


	void update(float time)
	{

		rect.left += dx * time;
		Collision(0);


		if (!onGround) dy = dy + 0.0012 * time;
		rect.top += dy * time;
		onGround = false;
		Collision(1);


		currentFrame += time * 0.005;
		if (currentFrame > 3) currentFrame -= 3;


		if (dx > 0) sprite.setTextureRect(IntRect(0, 0, 400, 180));
		if (dx<0) sprite.setTextureRect(IntRect(400, 0, -400, 180));


		sprite.setPosition(rect.left - offsetX, rect.top + offsetY);

		dx = 0;
	}


	void Collision(int num)
	{

		for (int i = rect.top / 64; i<(rect.top + rect.height) / 64; i++)
			for (int j = rect.left / 64; j<(rect.left + rect.width) / 64; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
				{
					if (dy>0 && num == 1)
					{
						rect.top = i * 64 - rect.height;  dy = 0;   onGround = true;
					}
					if (dy<0 && num == 1)
					{
						rect.top = i * 64 + 64;   dy = 0;
					}
					if (dx>0 && num == 0)
					{
						rect.left = j * 64 - rect.width;
						
					}
					if (dx<0 && num == 0)
					{
						rect.left = j * 64 + 64;
					}
				}

				if (TileMap[i][j] == 'c') {
					// TileMap[i][j]=' '; 
				}
			}

	}

};




int main()
{

	RenderWindow window(VideoMode(1800, 1000), "Pink Helicopter!", sf::Style::Fullscreen);
	sf::Music music;
	if (!music.openFromFile("sound.wav"))
		return -1; // error
	music.play();
	
	Texture tileSet;
	tileSet.loadFromFile("Mario_Tileset.png");


	PLAYER Nikita(tileSet);
	

	Sprite tile(tileSet);


	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 700;  // здесь регулируем скорость игры

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))    Nikita.dx = -0.1;
		if (Keyboard::isKeyPressed(Keyboard::Right))    Nikita.dx = 0.1;
		//Mario.dx = 0.1;

		if (Keyboard::isKeyPressed(Keyboard::Up))	 Nikita.dy = -0.27; Nikita.onGround = false; 


		
		Nikita.update(time);
		


		


		if (Nikita.rect.left>200) offsetX = Nikita.rect.left - 200;           //смещение




		window.clear(Color(128, 128, 128));

		for (int i = 0; i<H; i++)
			for (int j = 0; j<W; j++)
			{
				if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(572 - 16 * 12, 448, 64, 64));

				if (TileMap[i][j] == 'k')  tile.setTextureRect(IntRect(572, 448, 64, 64));

				if (TileMap[i][j] == 'c')  tile.setTextureRect(IntRect(572 - 64, 448, 64, 64));

				if (TileMap[i][j] == 't')  tile.setTextureRect(IntRect(0, 188, 128, 380 - 188));

				if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(0, 256 * 9 - 80, 12 * 16, 16 * 8 + 80));

				if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(580, 888, 888 - 570, 1020 - 888));

				if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(0, 424, 296, 308 - 424));

				if (TileMap[i][j] == 'w')  tile.setTextureRect(IntRect(396, 892, 560 - 396, 1020 - 892));

				if (TileMap[i][j] == 'r')  tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

				tile.setPosition(j * 64 - offsetX, i * 64 - offsetY);
				window.draw(tile);
			}



		window.draw(Nikita.sprite);
		

		window.display();
	}

	return 0;
}



