#pragma once

#include <ofMain.h>

class ColorCycler {
public:
	enum RepeatType { Loop, PingPong };

	ofColor getColor() {
		if (ofGetFrameNum() != mLastFrameNum) {
			// Recalculate color
			float t = ofGetElapsedTimef() / mDuration;
			if (mRepeat == Loop) {
				t = fmod(t, 1.0);
			} else if (mRepeat == PingPong) {
				if (static_cast<int>(t) % 2 == 0) t = fmod(t, 1.0);
				else t = 1.0 - fmod(t, 1.0);
			}
			float hue = ofLerp(mStartHue, mEndHue, t);
			mColor = ofColor_<float>::fromHsb(hue, mSaturation, mBrightness);
			mLastFrameNum = ofGetFrameNum();
		}

		return mColor;
	}

	float mStartHue = 0.0;
	float mEndHue = 1.0;
	float mSaturation = 1.0, mBrightness = 1.0;
	float mDuration = 3.0;
	RepeatType mRepeat = Loop;

private:
	float mHue = -1;
	uint64_t mLastFrameNum = -1;
	ofColor mColor;

};
