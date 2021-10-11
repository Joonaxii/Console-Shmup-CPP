#include "ResourceManager.h"
#include "FilePath.h"
#include "FileHelpers.h"

const std::string ResourceManager::SPRITE_PATH = "res/Sprites/";

ResourceManager::ResourceManager() : _renderers() {

    std::vector<FilePath*> filePaths;

	if (FileHelpers::getAllFilesByExtension(SPRITE_PATH, filePaths, ".sprt")) {

		for (size_t i = 0; i < filePaths.size(); i++)
		{
			const auto file = filePaths[i];
			const std::string name = std::string(file->name.begin(), file->name.end());

			Sprite* sprt(nullptr);
			if (tryLoadSprite(file->fullPath, sprt)) {

				_renderers.insert(std::pair<std::string, Sprite*>(file->name, sprt));
				const auto out = std::string("Added Sprite: '" + file->name + "'\n");
				OutputDebugStringA(out.c_str());

			}

			delete file;
		}
	}

	filePaths.clear();
}

ResourceManager::~ResourceManager() { }


int ResourceManager::tryLoadSprite(const std::string path, Sprite* sprite) {

	std::wifstream stream;
	std::ofstream streamO;

	stream.imbue(std::locale("en_US.utf8"));
	stream.open(path);

	if(!stream) 
	{ 
		const auto out = std::string("Could not open file: '" + path + "'\n");
		OutputDebugStringA(out.c_str());

		sprite = nullptr;
		return 2;
	}

	int w(0);
	int h(0);

	float pivotX(0);
	float pivotY(0);
	int rendOffset(0);

	stream >> w;
	stream >> h;

	stream >> pivotX;
	stream >> pivotY;

	stream >> rendOffset;

	const int total(w * h);
	char* pixels = new char[total]  {0};
	int ii = 0;

	while (!stream.eof()) {

		std::wstring line;
		std::getline(stream, line);

		if (line.empty()) { continue; }

		for (size_t i = 0; i < line.length(); i++)
		{
			const wchar_t cW = line.at(i);
			const char c = convertToANSI(cW);

			pixels[ii++] = *&c;
		}
	}
	stream.close();
	sprite = new Sprite(pixels, Vector2Int(w, h), Vector2(pivotX, pivotY));
}

char ResourceManager::convertToANSI(const wchar_t input) {

	if (input < 256) { return (char)input; }

	switch (input)
	{
	default:
		return '½';

	case L'─':
	case L'┬':
	case L'┴':
	case L'╤':
	case L'╧':
	case L'╦':
	case L'╩':
	case L'┭':
	case L'┵':
	case L'┯':
	case L'┷':
	case L'═':
	case L'━':
	case L'┅':
		return '-';

	case L'│':
	case L'┼':
	case L'├':
	case L'┤':
	case L'╡':
	case L'╞':
	case L'╪':
	case L'┿':
	case L'╟':
	case L'╠':
	case L'╣':
	case L'╬':
		return '|';

	case L'╲':
	case L'╮':
	case L'╰':
	case L'└':
	case L'┐':
	case L'╚':
	case L'╗':
	case L'╘':
	case L'╕':
	case L'┗':
	case L'┑':
		return '\\';

	case L'╱':
	case L'╭':
	case L'╯':
	case L'┘':
	case L'┌':
	case L'╝':
	case L'╔':
	case L'╒':
	case L'╛':
	case L'┏':
	case L'┙':
		return '/';
	}
}