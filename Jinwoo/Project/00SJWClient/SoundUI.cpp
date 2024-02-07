#include "pch.h"
#include "SoundUI.h"

SoundUI::SoundUI()
	: AssetUI("Sound", "##Sound", ASSET_TYPE::SOUND)
{
}

SoundUI::~SoundUI()
{
}

void SoundUI::render_update()
{
	AssetUI::render_update();
}
