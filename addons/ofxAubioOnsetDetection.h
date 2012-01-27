/*
 *  ofxAubioOnsetDetection.h
 *  ofxOnsetDetection
 *
 *  Created by Andrew Robertson on 24/11/2011.
 *  Copyright 2011 Centre for Digital Music, QMUL. All rights reserved.
 *
 */


#ifndef OFX_AUBDIO_ONSET_DETECTION_H_
#define OFX_AUBIO_ONSET_DETECTION_H_

#define NUM_DETECTION_SAMPLES 64000
#define TEXT_HEIGHT 16

#include "ofMain.h"
#include "AubioOnsetDetector.h"
#include "ChromaOnset.h"
#include "ofxWindowRegion.h"

//#include "OnsetDetectionFunction.h"

//this builds on aubioOsetDetector class
//but that doesn't store any values
//for drawing, perhpas we need to


struct DrawOnsetParameters{
	float width;//= screenWidth / (float) amplitudeNumber;	
	float maximumValue;// = onsetDetector->maximumDetectionValue;
	float minimumValue;// = 0;//minimumDetectionFunction ;
	float difference;// = maximumValue - minimumValue;
	float scale_factor;// = screenHeight/ difference;
};

class ofxAubioOnsetDetection{
public:
	ofxAubioOnsetDetection();
	~ofxAubioOnsetDetection();
	AubioOnsetDetector	*onsetDetector;
	//OnsetDetectionFunction *qmOnsetDetector;
	
	void reset();
	
	double dfSample;
	
	void processFrame(double* frame, const int& n);
	void processFrame(float* frame, const int& n);
	
	void printOnsetList();//print the vector of chromaOnset times - onsets with timing and chroma info
	
	//switch between different onset methods
	void aubioOnsetDetect_energy();
	void aubioOnsetDetect_complex();
	void aubioOnsetDetect_kl();
	void aubioOnsetDetect_hfc();
	void aubioOnsetDetect_specdiff();
	void aubioOnsetDetect_phase();//this is pretty bad I think
	void aubioOnsetDetect_mkl();

	void drawOnsetDetection();
	void drawOnsetDetectionScrolling();//float of how far thru file - e.g 0.6 60% through
	void drawOnsetDetection(int startIndex, int endIndex);
	void drawOnsetDetection(int startIndex, int endIndex, const ofxWindowRegion& screenRegion);//overloaded
	int onsetIndex, frameCountIndex;
	
	
	float			onsetFunction[NUM_DETECTION_SAMPLES];
	bool			aubioOnsetRecorded[NUM_DETECTION_SAMPLES];
	
	float			rawOnsetFunction[NUM_DETECTION_SAMPLES];		
	bool			highSlopeOnsetRecorded[NUM_DETECTION_SAMPLES];//true/false for onset

	float			medianOnsetFunction[NUM_DETECTION_SAMPLES];		
	bool			medianOnsetRecorded[NUM_DETECTION_SAMPLES];//true/false for onset
	
	float			highSlopeOnsetFunction[NUM_DETECTION_SAMPLES];
	
	float			aubioLongTermAverage[NUM_DETECTION_SAMPLES];
	
	float			maximumDetectionFunction;
	float			minimumDetectionFunction;		
	
	float			maxValue;
	
	int				amplitudeNumber;
	bool			onsetFound;
	
	typedef std::vector<double> DoubleVector;
	DoubleVector highSlopeOnsetsFrames;
	DoubleVector highSlopeOnsetsMillis;
	double framesToMillis(const double& frameCount);
	double playPosition, playPositionFrames;
	
	typedef std::vector<ChromaOnset> ChromaOnsetVector;
	ChromaOnsetVector chromaOnsets;
	
	void checkChromaAndPitch(float* tmpFrame, const int& n);
	
	void drawChromaOnsetData(const int& startIndex, const int& endIndex);
	void drawChromaOnsetData(const int& startIndex, const int& endIndex, const ofxWindowRegion& screenRegion);
	
	DrawOnsetParameters drawParams;
	void setDrawParams();
	void setDrawParams(const ofxWindowRegion& screenRegion);
	
	AubioPitch pitchDetector;
	float	maximumAubioPitch;
	
	//basic screen stuff
	float screenWidth;//= ofGetWidth();
	float screenHeight;// = ofGetHeight();
	void windowResized(const int& w, const int& h);
	
	ofxWindowRegion window;
	ofxWindowRegion fullScreen;
};


#endif