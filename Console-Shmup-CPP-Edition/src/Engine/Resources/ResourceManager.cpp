#include "ResourceManager.h"
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
			stream >> frameCount;

			AnimationFrame* frames = new AnimationFrame[frameCount];
			for (size_t i = 0; i < frameCount; i++)
			{
				Sprite* sprt(nullptr);
				if (tryLoadAnimFrame(stream, &sprt) == 0) {
					_sprites.insert(std::pair<std::string, Sprite*>(file->name + " F #" + std::to_string(i), sprt));
				}
				frames[i] = AnimationFrame(sprt, 1.0f / 30.0f);
			}

			_animations.insert(std::pair<std::string, Animation*>(file->name, new Animation(frames, frameCount)));

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
	auto _pixels = std::make_unique<char[]>(total);
	int ii = 0;

	while (!stream.eof()) {

		std::wstring line;
		std::getline(stream, line);

		if (line.empty()) { continue; }

		for (size_t i = 0; i < line.length(); i++)
		{
			if (ii >= total) { break; }
			const wchar_t cW = line.at(i);
			const char c = convertToANSI(cW);

			_pixels[ii++] = replacementChars(c);
		}
	}
	stream.close();
	*sprite = new Sprite(_pixels.get(), Vector2Int(w, h), Vector2(pivotX, pivotY));
	return 0;
}

int ResourceManager::tryLoadAnimFrame(std::wifstream& stream, Sprite** sprite) {

	int w(0);
	int h(0);

	float pivotX(0);
	float pivotY(0);
	int rendOffset(0);

	std::wstring line(L"");
	std::getline(stream, line);

	if (line.empty()) { return 1; }

	std::wstring tmp(L"");

	std::unique_ptr<char[]> pixels = nullptr;

	int cur = 0;
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
			}

			tmp.clear();
			cur++;
			break;

		case '[':
			if (pixels == nullptr) { return 1; }
			signed int last = line.find_last_of(L']');

			if (last < 0) { return 1; }

			std::string test(std::to_string(last) + " // " + std::to_string(line.length()));
			OutputDebugStringA(test.c_str());

			int ii = 0;
			for (size_t j = i + 1; j < last; j++)
			{
				pixels[ii++] = replacementChars(convertToANSI(line[j]));
			}

			i = last + 1;
			break;
		}
	}

	if (pixels == nullptr) { return 1; }

	*sprite = new Sprite(pixels.get(), Vector2Int(w, h), Vector2(pivotX, pivotY));
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