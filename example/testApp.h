#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxLibsndFileRecorder.h"
#define NUM_CHANNELS 1
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 1024


/*
THIS EXAMPLE SHOW HOW TO RECORD A WAV USING LIBSNDFILE LIBRARY.
IN THIS CASE WE'RE RECORDING AUDIO INPUT FROM MICROPHONE

TESTED ON WINDOWS FOR NOW
TODO: TEST ON MAC AND UPDATE XCODE PROJECT
*/

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		void keyPressed  (int key);
		void audioReceived(float * input, int bufferSize, int nChannels);
		bool recording;
		ofxLibsndFileRecorder audioRecorder;
};	

#endif
