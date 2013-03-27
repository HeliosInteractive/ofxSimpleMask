#ifndef EASYMASK_H
#define EASYMASK_H

#include "ofMain.h"

class ofxSimpleMask
{
    public:
        ofxSimpleMask();
        virtual ~ofxSimpleMask();

        void setup( string shaderPath , ofRectangle _area ) ;

        //Masking
        ofImage mask ;
        ofRectangle maskArea ;
        ofRectangle originalMaskArea ;
		ofShader maskShader;

        void setMask( string maskPath , bool bSetBounds = false ) ;
        void setMask( ofImage newMask , bool bSetFounds = false ) ;

		void drawMask (  ofTexture contentTex , ofTexture maskTex , float xOffset , float yOffset , float contentAlpha ) ;
        void drawScrollingMask( ofTexture contextText , ofTexture maskTex , float scrolling , float contentAlpha ) ;    
         static ofxSimpleMask* Instance()
         {
             static ofxSimpleMask inst ;
             return &inst ;
         }
    
        string getDefaultShaderPath( )
        {
            string shaderDirectory = ofToDataPath( "../../../../../addons/ofxSimpleMask/shaders/" ) ;
            return shaderDirectory ;
        }

    protected:
    private:
};

#endif // EASYMASK_H
