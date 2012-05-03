#include "ofxLibsndFileRecorder.h"

ofxLibsndFileRecorder::ofxLibsndFileRecorder(){
	initialized=false;
	recordingBuffer=NULL;
}


void ofxLibsndFileRecorder::setup(string fileName, int sampleRate_, int numChannels_){
	
	sampleRate=sampleRate_;
	numChannels = numChannels_;
	recordingSize=0;
	audioFormat=SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	
	//cout << "SND PATH: "<<ofToDataPath(fileName,true)<<"\n";
	outFile=new SndfileHandle(ofToDataPath(fileName,true),SFM_RDWR, audioFormat, numChannels, sampleRate);
	if(!outFile){
		cout<<"SndFileHandl outfile creation error\n";
		initialized=false;
	}
	else{
		recordingBuffer=(float*)realloc(recordingBuffer, sizeof(float));
		initialized=true;	
	}
}
void  ofxLibsndFileRecorder::close(){
	if(recordingBuffer!=NULL)
		free(recordingBuffer);
	recordingBuffer=NULL;
	initialized=false;
	recordingSize=0;
}

void  ofxLibsndFileRecorder::setFormat(int format){
	/*****EXAMPLES:  (see sndfile.h for more information)
		SF_FORMAT_AIFF | SF_FORMAT_PCM_16;
		SF_FORMAT_RAW | SF_FORMAT_PCM_16;
		SF_FORMAT_AU | SF_FORMAT_FLOAT;
	*/
	audioFormat=format;
}

void ofxLibsndFileRecorder::addSamples(float* &input, int numSamples){
	if(initialized){
		recordingSize+=numSamples*numChannels;
		recordingBuffer=(float*)realloc(recordingBuffer, recordingSize*sizeof(float));
		//cout << recordingSize <<" "<<numSamples <<" "<<numChannels << ""<< recordingSize*sizeof(float)<<"\n";
		memcpy(&recordingBuffer[recordingSize-numSamples*numChannels], input, numSamples*numChannels*sizeof(float)); 	
	}
}

void ofxLibsndFileRecorder::finalize(){
	if(initialized){
		int res=outFile->write(recordingBuffer, recordingSize);
		sf_close(outFile->takeOwnership());
		initialized=false;
		recordingSize=0;
		delete outFile;
	}
}