#pragma once


class CEngine
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);


public:
	int init();
	void progress();
};

