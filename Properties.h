#pragma once
enum class PROPERTY
{
	NONE = 0,
	AUTO, RED, BLUE, ORANGE, YELLOW, LIME, GREEN, CYAN, PURPLE, PINK, ROSY, GREY, BLACK, SILVER, WHITE,
	BROWN, BEST, SAD, WONDER, PET, BROKEN, CHILL, BACK, FALL_DOWN, FALL_RIGHT, FALL_UP, FALL_LEFT,
	NUDGE_DOWN, NUDGE_RIGHT, NUDGE_UP, NUDGE_LEFT, TURN_CLOCKWISE, TURN_CCLOCKWISE, PHANTOM,
	REVERSE, POWER1, POWER2, POWER3, SAFE, STILL, LOCKED_DOWN, LOCKED_RIGHT, LOCKED_UP, LOCKED_LEFT,
	YOU_2, REVERT, PROPERTY_3D, BOOM, HOLD,
	STOP, YOU, WIN, DEFEAT, PUSH, HOT, MELT, SINK, SHUT, OPEN,
	WEAK, FLOAT, MOVE, SHIFT, FALL, TELE, PULL, SWAP, UP, RIGHT, LEFT, DOWN,
	WORD, MORE, SLEEP, HIDE, BONUS, END, DONE, SELECT
};

static const TCHAR* PROPERTYToString(PROPERTY p) 
{
	if (PROPERTY::NONE == p) return L"NONE";
	if (PROPERTY::YOU == p) return L"YOU";
	if (PROPERTY::MELT == p) return L"MELT";
	if (PROPERTY::FLOAT == p) return L"FLOAT";
	if (PROPERTY::PUSH == p) return L"PUSH";
	if (PROPERTY::STOP == p) return L"STOP";
	if (PROPERTY::WIN == p) return L"WIN";
	if (PROPERTY::HOT == p) return L"HOT";
	if (PROPERTY::END == p) return L"END";
	if (PROPERTY::DONE == p) return L"DONE";
	if (PROPERTY::DEFEAT == p) return L"DEFEAT";
	if (PROPERTY::SHUT == p) return L"SHUT";
	if (PROPERTY::OPEN == p) return L"OPEN";
	if (PROPERTY::SINK == p) return L"SINK";
}

static PROPERTY StringToProperty(const std::wstring& str)
{
	if (str == L"NONE") return PROPERTY::NONE;
	if (str == L"YOU") return PROPERTY::YOU;
	if (str == L"MELT") return PROPERTY::MELT;
	if (str == L"FLOAT") return PROPERTY::FLOAT;
	if (str == L"STOP") return PROPERTY::STOP;
	if (str == L"WIN") return PROPERTY::WIN;
	if (str == L"HOT") return PROPERTY::HOT;
	if (str == L"END") return PROPERTY::END;
	if (str == L"DONE") return PROPERTY::DONE;
	if (str == L"DEFEAT") return PROPERTY::DEFEAT;
	if (str == L"SHUT") return PROPERTY::SHUT;
	if (str == L"PUSH") return PROPERTY::PUSH;
	if (str == L"OPEN") return PROPERTY::OPEN;
	if (str == L"SINK") return PROPERTY::SINK;
}