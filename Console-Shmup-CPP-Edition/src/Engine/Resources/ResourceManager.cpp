#include "ResourceManager.h"
#include "../Rendering/AnimationFrame.h"
#include "../IO/FilePath.h"
#include "../IO/FileHelpers.h"

const std::string ResourceManager::SPRITE_PATH = "res/Sprites/";
const std::locale ResourceManager::LOCALE = std::locale("en_US.UTF-8");

ResourceManager::ResourceManager() : _sprites(), _animations() {
	loadSprites();
	loadAnimations();
}

ResourceManager::~ResourceManager() { }

bool ResourceManager::tryGetSprite(const std::string name, Sprite** spriteOut) {

	auto iter = _sprites.find(name);
	if (iter == _sprites.end()) 
	{ 
		*spriteOut = nullptr;
		return false; 
	}

	*spriteOut = _sprites[name];
	return true;
}

bool ResourceManager::tryGetAnimation(const std::string name, Animation** animOut) {
	auto iter = _animations.find(name);
	if (iter == _animations.end())
	{
		*animOut = nullptr;
		return false;
	}

	*animOut = _animations[name];
	return false;
}

void ResourceManager::loadSprites() {
	std::vector<FilePath*> filePaths;
	if (FileHelpers::getAllFilesByExtension(SPRITE_PATH, filePaths, ".sprt")) {

		for (size_t i = 0; i < filePaths.size(); i++)
		{
			const auto file = filePaths[i];
			const std::string name = std::string(file->name.begin(), file->name.end());

			Sprite* sprt(nullptr);
			if (tryLoadSprite(file->fullPath, &sprt, LOCALE) == 0) {

				_sprites.insert(std::pair<std::string, Sprite*>(file->name, sprt));
			}

			delete file;
		}
	}
	filePaths.clear();
}

void ResourceManager::loadAnimations() {
	std::vector<FilePath*> filePaths;
	if (FileHelpers::getAllFilesByExtension(SPRITE_PATH, filePaths, ".anim")) {

		for (size_t i = 0; i < filePaths.size(); i++)
		{
			const auto file = filePaths[i];
			const std::string name = std::string(file->name.begin(), file->name.end());

			std::wifstream stream;

			stream.imbue(LOCALE);
			stream.open(file->fullPath);
			if (!stream)
			{
				const auto out = std::string("Could not open file: '" + file->fullPath + "'\n");
				OutputDebugStringA(out.c_str());
				continue;
			}

			int frameCount(0);
			float frameRate(0);
			stream >> frameCount;
			stream >> frameRate;

			frameRate = frameRate == 0 ? 1.0f : 1.0f / frameRate;
			std::wstring temp;

			std::getline(stream, temp);

			AnimationFrame* frames = new AnimationFrame[frameCount];
			for (size_t i = 0; i < frameCount; i++)
			{
				Sprite* sprt(nullptr);
				if (tryLoadAnimFrame(stream, &sprt) == 0) {
					_sprites.insert(std::pair<std::string, Sprite*>(file->name + " F #" + std::to_string(i), sprt));
				}
				frames[i] = AnimationFrame(sprt, frameRate);
			}
			stream.close();

			_animations.insert(std::pair<std::string, Animation*>(file->name, new Animation(frames, frameCount, true)));

			delete[] frames;
			delete file;
		}
	}
	filePaths.clear();
}

int ResourceManager::tryLoadSprite(const std::string path, Sprite** sprite, const std::locale locale) {

	std::wifstream stream;

	stream.imbue(locale);
	stream.open(path);

	if(!stream) 
	{ 
		const auto out = std::string("Could not open file: '" + path + "'\n");
		OutputDebugStringA(out.c_str());

		stream.close();
		sprite = nullptr;
		return 2;
	}

	int w(0);
	int h(0);

	float pivotX(0);
	float pivotY(0);
	int flip(0);

	stream >> w;
	stream >> h;

	stream >> pivotX;
	stream >> pivotY;

	stream >> flip;

	const int total(w * h);
	auto _pixels = std::make_unique<char[]>(total);
	int ii = 0;

	int x = 0;
	int y = 0;
	while (!stream.eof()) {

		std::wstring line;
		std::getline(stream, line);

		if (line.empty()) { continue; }

		for (size_t i = 0; i < line.length(); i++)
		{
			if (ii >= total) { break; }
			const wchar_t cW = line.at(i);
			const char c = convertToANSI(cW);

			_pixels[y * w + x] = replacementChars(c);
			x++;
			if (x >= w) {
				y++;
				x = 0;
			}
			ii++;
		}
	}
	stream.close();
	*sprite = new Sprite(_pixels.get(), Vector2Int(w, h), Vector2(pivotX, pivotY), flip);
	return 0;
}

int ResourceManager::tryLoadAnimFrame(std::wifstream& stream, Sprite** sprite) {

	int w(0);
	int h(0);

	float pivotX(0);
	float pivotY(0);
	int flip(0);

	std::wstring line(L"");
	std::getline(stream, line);

	if (line.empty()) { return 1; }

	std::wstring tmp(L"");

	std::unique_ptr<char[]> pixels = nullptr;

	int cur = 0;
	bool breakOut = false;
	for (size_t i = 0; i < line.length(); i++)
	{
		wchar_t c = line[i];
		switch (c) {

		default:
			tmp += c;
			break;

		case L',':
			switch (cur)
			{
			case 0:
				w = _wtoi(tmp.c_str());
				break;
			case 1:
				h = _wtoi(tmp.c_str());
				pixels = std::make_unique<char[]>(w * h);
				break;

			case 2:
				pivotX = _wtof(tmp.c_str());
				break;
			case 3:
				pivotY = _wtof(tmp.c_str());
				break;
			case 4:
				flip = _wtoi(tmp.c_str());
				break;
			}

			tmp.clear();
			cur++;
			break;

		case '[':
			if (pixels == nullptr) { return 1; }
			
			std::wstring temp(L"");
			temp = line.substr(i + 1, w * h);

			int ii = 0;
			int offset = ((h - 1) * w);
			for (size_t j = 0; j < temp.length(); j++)
			{
				pixels[offset + ii] = replacementChars(convertToANSI(temp[j]));
				
				ii++;
				if (ii >= w) {
					ii = 0;
					offset -= w;
				}
			}
			breakOut = true;
			break;
		}
		if (breakOut) { break; }
	}

	if (pixels == nullptr) { return 1; }

	*sprite = new Sprite(pixels.get(), Vector2Int(w, h), Vector2(pivotX, pivotY), flip);
	return 0;
}


char ResourceManager::replacementChars(const char input) {
	switch (input) {
	default: return input;
	case '^': return ' ';
	case '½': return '\0';
	}
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