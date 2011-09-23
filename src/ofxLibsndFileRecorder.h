#include "ofUtils.h"
#include "sndfile.hh"


class ofxLibsndFileRecorder{
	public :
	
	ofxLibsndFileRecorder();
	void setup(string fileName, int sampleRate=44100, int numChannels=1);
	void addSamples(float* &input, int numSamples);
	
	
	
	/*****FORMAT EXAMPLES:  
	 SF_FORMAT_AIFF | SF_FORMAT_PCM_16;
	 SF_FORMAT_RAW | SF_FORMAT_PCM_16;
	 SF_FORMAT_AU | SF_FORMAT_FLOAT;
	 (see sndfile.h for more information)*/
	void setFormat(int format);
	
	
	void finalize();
	void close();
		
	private:
		SndfileHandle	*outFile;
		bool			initialized;
		string			fileName;
		int				sampleRate;
		int				numChannels;		
		int				audioFormat;
		string			suffix;
		float			*recordingBuffer;
		int				recordingSize;
	
};
