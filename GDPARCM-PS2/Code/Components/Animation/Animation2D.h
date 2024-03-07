#pragma once
#include <vector>
#include "Animation2DKeyFrames.h"

class Animation2D
{
public:
	Animation2D(const std::string& animationStateName, float animationDuration, bool isLooping, const Animation2DKeyFrames& startingFrame); 
	~Animation2D();

	std::string GetAnimationStateName();

	void AddKeyFrame(const Animation2DKeyFrames& newKeyFrame, int keyNum = -1);
	void AddKeyFrames(std::vector<Animation2DKeyFrames>& newKeyFramesList, int startingPos = -1);
	void DeleteKeyFrame(const Animation2DKeyFrames& keyFrame);
	void DeleteKeyFrame(int keyNum);
	void UpdateKeyFrame(const Animation2DKeyFrames& newKeyFrame, int keyNum);
	Animation2DKeyFrames GetKeyFrame(int keyNum);

	void UpdateAnimation(float dt);
	sf::Sprite* GetCurrentSpriteAnimation();
	bool IsAtTheEndOfFrame();
	void ResetAnimation();


private:
	std::string animationStateName;
	float animationDuration;
	bool isLooping;
	std::vector<Animation2DKeyFrames> keyFramesList;

	int currentKeyFrameIndex;
	float elapsedTime;
	bool atTheEndOfFrame;
};

