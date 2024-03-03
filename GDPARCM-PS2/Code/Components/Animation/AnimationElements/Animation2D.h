#pragma once
#include <vector>
#include "Animation2DKeyFrames.h"

class Animation2D
{
public:
	Animation2D(const std::string& animationStateName, float animationDuration, bool isLooping, const Animation2DKeyFrames& startingFrame); 
	~Animation2D();

	std::string GetAnimationStateName();

	void AddKeyFrame(const Animation2DKeyFrames& keyFrame, int keyNum = -1);
	void DeleteKeyFrame(const Animation2DKeyFrames& keyFrame);
	void DeleteKeyFrame(int keyNum);
	void UpdateKeyFrame(const Animation2DKeyFrames& newKeyFrame, int keyNum);
	Animation2DKeyFrames GetKeyFrame(int keyNum);


private:
	std::string animationStateName;
	float animationDuration;
	bool isLooping;
	std::vector<Animation2DKeyFrames> keyFramesList;
};

