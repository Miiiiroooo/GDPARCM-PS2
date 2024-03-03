#include "Animation2D.h"
#include <iostream>
#include <algorithm>

Animation2D::Animation2D(const std::string& animationStateName, float animationDuration, bool isLooping, const Animation2DKeyFrames& startingFrame) : 
	animationStateName(animationStateName), animationDuration(animationDuration), isLooping(isLooping)
{
	keyFramesList.push_back(startingFrame);
}

Animation2D::~Animation2D()
{

}

std::string Animation2D::GetAnimationStateName()
{
	return animationStateName;
}

void Animation2D::AddKeyFrame(const Animation2DKeyFrames& keyFrame, int keyNum)
{
	if (keyFrame.sprite == NULL)
	{
		std::cout << "key frame is not properly set! cant add to the " << animationStateName << " animation! \n";
		return;
	}

	if ((keyNum < 0 && keyNum != -1) || keyNum > keyFramesList.size())
	{
		std::cout << "invalid key frame position to be set on the " << animationStateName << " animation!\n";
		return;
	}

	if (keyNum == -1 || keyNum == keyFramesList.size())
	{
		keyFramesList.push_back(keyFrame);
	}
	else
	{
		keyFramesList.insert(keyFramesList.begin() + keyNum, keyFrame);
	}
}

void Animation2D::DeleteKeyFrame(const Animation2DKeyFrames& keyFrame)
{
	//keyFramesList.erase(std::remove(keyFramesList.begin(), keyFramesList.end(), keyFrame), keyFramesList.end());

	auto keyFramePos = std::find(keyFramesList.begin(), keyFramesList.end(), keyFrame); 
	if (keyFramePos != keyFramesList.end()) 
	{
		keyFramesList.erase(keyFramePos);
	}
}

void Animation2D::DeleteKeyFrame(int keyNum)
{
	if (keyNum >= keyFramesList.size() || keyNum < 0)
	{
		std::cout << "invalid key frame position to be deleted on the " << animationStateName << " animation!\n";
		return;
	}

	keyFramesList.erase(keyFramesList.begin() + keyNum);
}

void Animation2D::UpdateKeyFrame(const Animation2DKeyFrames& newKeyFrame, int keyNum)
{
	if (keyNum >= keyFramesList.size() || keyNum < 0) 
	{
		std::cout << "invalid key frame position to be updated on the " << animationStateName << " animation!\n";
		return;
	}

	keyFramesList[keyNum] = newKeyFrame;
}

Animation2DKeyFrames Animation2D::GetKeyFrame(int keyNum)
{
	if (keyNum >= keyFramesList.size() || keyNum < 0) 
	{
		std::cout << "invalid key frame position to be retrieved from the " << animationStateName << " animation!\n";
		return Animation2DKeyFrames();
	}

	return keyFramesList[keyNum]; 
}
