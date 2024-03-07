#pragma once

class IScoreListener
{
public:
	virtual ~IScoreListener() {};

	virtual void OnUpdateCheeseScore(int score) = 0;
	virtual void OnUpdateBestCheeseScore(int score) = 0;


protected:
	IScoreListener() {};
};