#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/timer.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>

class GradientApp
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
				name += ".jpg";
		}
		else
			name += ".jpg";

		sf::RenderTexture tex;
		tex.create(res.x, res.y);

		tex.clear();
		tex.draw(vex);
		tex.display();

		tex.getTexture().copyToImage().saveToFile(name);
	}

	void generateRandomColors(nana::textbox* txt)
	{
		for (int i = 0; i < 4; i++)
		{
			unsigned char ch[3];
			for (int j = 0; j < 3; j++)
			{
				ch[j] = (unsigned char)rand() % 255;
			}
			vex[i].color = sf::Color(ch[0], ch[1], ch[2]);
			txt[i].caption(std::to_string((int)ch[0]) + "; " + std::to_string((int)ch[1]) + "; " + std::to_string((int)ch[2]) + "; ");
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
		fm.caption("Gradient Generator");
		fm.size(nana::size(300, 185));

		nana::textbox txt(fm, nana::rectangle{ 10, 10, 280, 20 });
		txt.tip_string("File name...");
		txt.multi_lines(false);

		nana::textbox color_reports[4];
		color_reports[0].create(fm, nana::rectangle{ 140, 42, 150, 20 });
		color_reports[1].create(fm, nana::rectangle{ 140, 78, 150, 20 });
		color_reports[2].create(fm, nana::rectangle{ 140, 112, 150, 20 });
		color_reports[3].create(fm, nana::rectangle{ 140, 148, 150, 20 });
		color_reports[0].multi_lines(false).editable(false);
		color_reports[1].multi_lines(false).editable(false);
		color_reports[2].multi_lines(false).editable(false);
		color_reports[3].multi_lines(false).editable(false);

		nana::button btn1(fm, nana::rectangle{ 25, 40, 100, 25 });
		btn1.caption("Generate");
		btn1.events().click([&](){
			generateRandomColors(color_reports);});

		nana::button btn2(fm, nana::rectangle{ 25, 75, 100, 25 });
		btn2.caption("Manual");
		btn2.events().click([&]() {
			nana::inputbox::integer red1("Red 1", 100, 1, 255, 1);
			nana::inputbox::integer red2("Red 2", 100, 1, 255, 1);
			nana::inputbox::integer red3("Red 3", 100, 1, 255, 1);
			nana::inputbox::integer red4("Red 4", 100, 1, 255, 1);
			nana::inputbox::integer gre1("Green 1", 100, 1, 255, 1);
			nana::inputbox::integer gre2("Green 2", 100, 1, 255, 1);
			nana::inputbox::integer gre3("Green 3", 100, 1, 255, 1);
			nana::inputbox::integer gre4("Green 4", 100, 1, 255, 1);
			nana::inputbox::integer blu1("Blue 1", 100, 1, 255, 1);
			nana::inputbox::integer blu2("Blue 2", 100, 1, 255, 1);
			nana::inputbox::integer blu3("Blue 3", 100, 1, 255, 1);
			nana::inputbox::integer blu4("Blue 4", 100, 1, 255, 1);

			nana::inputbox inbox(fm, "Please fill in the <bold>color array</>.", "Color array");

			if (inbox.show(red1, red2, red3, red4, gre1, gre2, gre3, gre4, blu1, blu2, blu3, blu4))
			{
				unsigned char ch[12];
				ch[0] = (unsigned char)red1.value(); ch[1] = (unsigned char)gre1.value(); ch[2] = (unsigned char)blu1.value();
				ch[3] = (unsigned char)red2.value(); ch[4] = (unsigned char)gre2.value(); ch[5] = (unsigned char)blu2.value();
				ch[6] = (unsigned char)red3.value(); ch[7] = (unsigned char)gre3.value(); ch[8] = (unsigned char)blu3.value();
				ch[9] = (unsigned char)red3.value(); ch[10] = (unsigned char)gre3.value(); ch[11] = (unsigned char)blu3.value();

				vex[0].color = sf::Color(ch[0], ch[1], ch[2]);
				vex[1].color = sf::Color(ch[3], ch[4], ch[5]);
				vex[2].color = sf::Color(ch[6], ch[7], ch[8]);
				vex[3].color = sf::Color(ch[9], ch[10], ch[11]);

				color_reports[0].caption(std::to_string((int)ch[0]) + "; " + std::to_string((int)ch[1]) + "; " + std::to_string((int)ch[2]) + "; ");
				color_reports[1].caption(std::to_string((int)ch[3]) + "; " + std::to_string((int)ch[4]) + "; " + std::to_string((int)ch[5]) + "; ");
				color_reports[2].caption(std::to_string((int)ch[6]) + "; " + std::to_string((int)ch[7]) + "; " + std::to_string((int)ch[8]) + "; ");
				color_reports[3].caption(std::to_string((int)ch[9]) + "; " + std::to_string((int)ch[10]) + "; " + std::to_string((int)ch[11]) + "; ");
			}
	});

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
		timer.elapse(std::bind(&GradientApp::render, this));
		timer.start();

		fm.show();
		nana::exec();
	}

	sf::RenderWindow window;
	sf::VertexArray vex;
	sf::Vector2f res;
};

int CALLBACK WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow)
{
	GradientApp app;
	app.go(500.f, 500.f);
	return 0;
}