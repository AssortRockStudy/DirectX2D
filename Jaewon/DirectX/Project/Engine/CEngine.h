#pragma once

class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);
public:
	void init();

};
