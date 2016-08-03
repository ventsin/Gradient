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
		unsigned char ch[4][3];
	
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ch[i][j] = (unsigned char)rand() % 255;
			}
			vex[i].color = sf::Color(ch[i][0], ch[i][1], ch[i][2]);
		}
		txt->caption('[' + std::to_string((int)ch[0][0]) + "; " + std::to_string((int)ch[0][1]) + "; " + std::to_string((int)ch[0][2]) + ";]"
			+ '[' + std::to_string((int)ch[1][0]) + "; " + std::to_string((int)ch[1][1]) + "; " + std::to_string((int)ch[1][2]) + ";]"
			+ '[' + std::to_string((int)ch[2][0]) + "; " + std::to_string((int)ch[2][1]) + "; " + std::to_string((int)ch[2][2]) + ";]"
			+ '[' + std::to_string((int)ch[3][0]) + "; " + std::to_string((int)ch[3][1]) + "; " + std::to_string((int)ch[3][2]) + ";]");
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

		nana::textbox color_report;
		color_report.create(fm, nana::rectangle{ 10, 40, 280, 20 });
		color_report.multi_lines(false).editable(false);
		
		nana::button btn1(fm, nana::rectangle{ 25, 70, 100, 25 });
		btn1.caption("Generate");
		btn1.events().click([&](){
			generateRandomColors(&color_report);});

		nana::button btn2(fm, nana::rectangle{ 178, 70, 100, 25 });
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
				unsigned char ch[4][3];
				ch[0][0] = (unsigned char)red1.value(); ch[0][1] = (unsigned char)gre1.value(); ch[0][2] = (unsigned char)blu1.value();
				ch[1][0] = (unsigned char)red2.value(); ch[1][1] = (unsigned char)gre2.value(); ch[1][2] = (unsigned char)blu2.value();
				ch[2][0] = (unsigned char)red3.value(); ch[2][1] = (unsigned char)gre3.value(); ch[2][2] = (unsigned char)blu3.value();
				ch[3][0] = (unsigned char)red3.value(); ch[3][1] = (unsigned char)gre3.value(); ch[3][2] = (unsigned char)blu3.value();

				vex[0].color = sf::Color(ch[0][0], ch[0][1], ch[0][2]);
				vex[1].color = sf::Color(ch[1][0], ch[1][1], ch[1][2]);
				vex[2].color = sf::Color(ch[2][0], ch[2][1], ch[2][2]);
				vex[3].color = sf::Color(ch[3][0], ch[3][1], ch[3][2]);

				color_report.caption('[' + std::to_string((int)ch[0][0]) + "; " + std::to_string((int)ch[0][1]) + "; " + std::to_string((int)ch[0][2]) + ";]"
					+ '[' + std::to_string((int)ch[1][0]) + "; " + std::to_string((int)ch[1][1]) + "; " + std::to_string((int)ch[1][2]) + ";]"
					+ '[' + std::to_string((int)ch[2][0]) + "; " + std::to_string((int)ch[2][1]) + "; " + std::to_string((int)ch[2][2]) + ";]"
					+ '[' + std::to_string((int)ch[3][0]) + "; " + std::to_string((int)ch[3][1]) + "; " + std::to_string((int)ch[3][2]) + ";]");
			}
	});

		nana::button btn3(fm, nana::rectangle{ 25, 105, 100, 25 });
		btn3.caption("Preview");
		btn3.events().click([&]() {
			if (!window.isOpen())
				window.create(sf::VideoMode(width, height), "Preview");
			else
				window.close(); });

		nana::button btn4(fm, nana::rectangle{ 178, 105, 100, 25 });
		btn4.caption("Save N");
		btn4.events().click([&]()
		{
			nana::inputbox::integer n_files("", 10, 1, 1000, 1);
			
			nana::inputbox inbox(fm, "Please fill in the <bold>number of files</> to save.", "Save N");

			if (inbox.show(n_files))
			{
				for (size_t n = 0; n < n_files.value(); n++)
				{
					generateRandomColors(&color_report);
					
					std::string str = txt.caption();
					size_t it = str.rfind('.');
					if (it != std::string::npos)
						str = "grad/" + str.substr(0, it) + std::to_string(n) + str.substr(it);
					else
						str = "grad/" + str + std::to_string(n);

					save(str);
				}
			}
		});

		nana::button btn5(fm, nana::rectangle{ 25, 140, 100, 25 });
		btn5.caption("Save");
		btn5.events().click([&]() {
			save(txt.caption()); });

		nana::button btn6(fm, nana::rectangle{ 178, 140, 100, 25 });
		btn6.caption("Save");
		btn6.events().click([&]() {
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