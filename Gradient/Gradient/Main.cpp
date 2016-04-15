#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/timer.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>

class app
{
public:
	void render()
	{
		if (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					return;
				}
				else if (event.type == sf::Event::Resized)
				{
					vex[0].position = sf::Vector2f(0.f, 0.f);
					vex[1].position = sf::Vector2f((float)event.size.width, 0.f);
					vex[2].position = sf::Vector2f((float)event.size.width, (float)event.size.height);
					vex[3].position = sf::Vector2f(0.f, (float)event.size.height);
				}
			}
			
			if (demo)
				generateDemoColors();

			window.clear();
			window.draw(vex);
			window.display();
		}
	}

	void save(std::string name)
	{
		size_t found = name.rfind('.');
		if (found != std::string::npos)
		{
			std::string extension = name.substr(found);

			if (extension != ".jpg" && extension != ".png" &&
				extension != ".tga" && extension != ".psd" &&
				extension != ".bmp" && extension != ".dds")
				name += ".png";
		}
		else
			name += ".png";

		sf::RenderTexture tex;
		tex.create(res.x, res.y);

		tex.clear();
		tex.draw(vex);
		tex.display();

		tex.getTexture().copyToImage().saveToFile(name);
	}

	void generateDemoColors()
	{
		for (int i = 0; i < 4; i++)
		{
			vex[i].color.r += rand() % 100 - vex[i].color.r;
			vex[i].color.g += rand() % 100 - vex[i].color.g;
			vex[i].color.b += rand() % 100 - vex[i].color.b;
		}
	}

	void generateRandomColors()
	{
		for (int i = 0; i < 4; i++)
		{
			unsigned char ch[3];
			for (int j = 0; j < 3; j++)
			{
				ch[j] = (unsigned char)rand() % 255;
			}
			vex[i].color = sf::Color(ch[0], ch[1], ch[2]);
		}
	}

	void go(float width, float height)
	{
		res = sf::Vector2f(width, height);
		vex.setPrimitiveType(sf::Quads);
		vex.resize(4);

		vex[0].position = sf::Vector2f(0.f, 0.f);
		vex[1].position = sf::Vector2f(width, 0.f);
		vex[2].position = sf::Vector2f(width, height);
		vex[3].position = sf::Vector2f(0.f, height);

		window.create(sf::VideoMode(width, height), "Preview");
		nana::form fm;
		fm.size(nana::size(300, 185));

		nana::textbox txt(fm, nana::rectangle{ 10, 10, 280, 20 });
		txt.tip_string("File name...");
		txt.multi_lines(false);

		nana::button btn1(fm, nana::rectangle{ 25, 40, 100, 25 });
		btn1.caption("Generate");
		btn1.events().click([this](){
			generateRandomColors();});

		nana::button btn2(fm, nana::rectangle{ 25, 75, 100, 25 });
		btn2.caption("Demo");
		btn2.events().click([&]() {
			if (demo)
			{
				demo = false;
				btn1.enabled(true);
			}
			else
			{
				demo = true;
				btn1.enabled(false);
			}});

		nana::button btn3(fm, nana::rectangle{ 25, 110, 100, 25 });
		btn3.caption("Preview");
		btn3.events().click([&]() {
			if (!window.isOpen())
				window.create(sf::VideoMode(width, height), "Preview");
			else
				window.close(); });

		nana::button btn4(fm, nana::rectangle{ 25, 145, 100, 25 });
		btn4.caption("Save");
		btn4.events().click([&]() {
			save(txt.caption()); });


		nana::timer timer;

		timer.interval(50);
		timer.elapse(std::bind(&app::render, this));
		timer.start();

		fm.show();
		nana::exec();
	}

	sf::RenderWindow window;
	sf::VertexArray vex;
	sf::Vector2f res;
	bool demo = false;
};

int CALLBACK WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	app app;
	app.go(500.f, 500.f);
	return 0;
}