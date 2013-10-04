#pragma once

#include "ofMain.h"

class ofxSimpleMask
{
    public:
        ofxSimpleMask();
        virtual ~ofxSimpleMask();

        void setup( string shaderPath , ofRectangle _area ) ;
		void setup( ofShader * shader , ofRectangle _area ) ; 
        
			//Masking
        ofImage mask ;
        ofRectangle maskArea ;
        ofRectangle originalMaskArea ;
		ofShader * maskShader;

        void setMask( string maskPath , bool bSetBounds = false ) ;
        void setMask( ofImage newMask , bool bSetFounds = false ) ;

		void drawMask (  ofTexture contentTex , ofTexture maskTex , float xOffset , float yOffset ,
						float contentAlpha  , float width = 0.f , float height = 0.f ) ;
        void drawScrollingMask( ofTexture contextText , ofTexture maskTex , float scrolling , float contentAlpha ) ;    
        
		static ofxSimpleMask* Instance()
         {
             static ofxSimpleMask inst ;
             return &inst ;
         }
    
        string getDefaultShaderPath( )
        {
            string shaderDirectory = ofToDataPath( "shaders/" ) ;
            return shaderDirectory ;
        }

		string getShaderPathToAddons( )
        {
            string shaderDirectory = ofToDataPath( "../../../../../addons/ofxSimpleMask/shaders/" ) ;
            return shaderDirectory ;
        }


		bool bUseShaderRef ; 

    protected:
    private:
};
