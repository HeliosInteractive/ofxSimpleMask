#include "ofxSimpleMask.h"

ofxSimpleMask::ofxSimpleMask()
{
    //ctor
}

ofxSimpleMask::~ofxSimpleMask()
{
    //dtor
}

 void ofxSimpleMask::setup( string shaderPath , ofRectangle _area )
 {
     maskShader.load( shaderPath ) ; //"shaders/composite" ) ;
     maskArea = _area ;
     originalMaskArea = _area ;
 }

void ofxSimpleMask::setMask( string maskPath , bool bSetBounds )
{
    mask.loadImage( maskPath ) ;
    if ( bSetBounds == true )
    {
        maskArea.width = mask.getWidth() ;
        maskArea.height = mask.getHeight() ;
    }
}
void ofxSimpleMask::setMask( ofImage newMask , bool bSetBounds )
{
    mask = newMask ;
    if ( bSetBounds == true )
    {
        maskArea.width = mask.getWidth() ;
        maskArea.height = mask.getHeight() ;
    }
}

void ofxSimpleMask::drawMask ( ofTexture contentTex , ofTexture maskTex , float xOffset , float yOffset , float contentAlpha )
{
    //BEGIN MASK
    ofEnableAlphaBlending( ) ;

		glActiveTexture(GL_TEXTURE0_ARB);
		contentTex.bind();

		glActiveTexture(GL_TEXTURE1_ARB);
		maskTex.bind();

            //prevents weird texture wrapping , otherwise the last or first pixel is repeated to infinity
            contentTex.setTextureWrap( GL_CLAMP_TO_BORDER_ARB , GL_CLAMP_TO_BORDER_ARB ) ;
            //contentTex.setTextureWrap( GL_CLAMP , GL_CLAMP ) ;


            maskShader.begin();

                maskShader.setUniformTexture("Tex0", contentTex , 0);
                maskShader.setUniformTexture("Tex1", maskTex , 1);
                maskShader.setUniform1f( "alpha" , contentAlpha ) ;
                glBegin(GL_QUADS);
                ofFill() ;

                glMultiTexCoord2d(GL_TEXTURE0_ARB, xOffset , yOffset );
                glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0 );
                glVertex2f( maskArea.x ,  maskArea.y );


                glMultiTexCoord2d(GL_TEXTURE0_ARB, xOffset + contentTex.getWidth(), yOffset );
                glMultiTexCoord2d(GL_TEXTURE1_ARB, maskTex.getWidth(), 0 );
                glVertex2f(  maskArea.x + maskArea.width , maskArea.y );


                glMultiTexCoord2d(GL_TEXTURE0_ARB, xOffset + contentTex.getWidth() , contentTex.getHeight() + yOffset );
                glMultiTexCoord2d(GL_TEXTURE1_ARB, maskTex.getWidth() , maskTex.getHeight() );
                glVertex2f(  maskArea.x + maskArea.width  , maskArea.height + maskArea.y );

                glMultiTexCoord2d(GL_TEXTURE0_ARB, xOffset , contentTex.getHeight() + yOffset );
                glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, maskTex.getHeight()  );
                glVertex2f(  maskArea.x , maskArea.height + maskArea.y ) ;

                glEnd();

            maskShader.end() ;
		//deactive and clean up
		glActiveTexture(GL_TEXTURE1_ARB);
		maskTex.unbind();

		glActiveTexture(GL_TEXTURE0_ARB);
		contentTex.unbind();

		//maskArea = originalMaskArea ;
}

void ofxSimpleMask::drawScrollingMask( ofTexture content , ofTexture mask , float scrolling , float contentAlpha )
{
    
    content.setTextureWrap( GL_CLAMP_TO_BORDER_ARB , GL_CLAMP_TO_BORDER_ARB ) ;
    
    glActiveTexture(GL_TEXTURE0_ARB);
    content.bind() ;
    
    glActiveTexture(GL_TEXTURE1_ARB);
    mask.bind() ;

    //ofTranslate ( 0 , offset.y + 100 , 0 ) ;
    
    //draw a quad the size of the frame
    glBegin(GL_QUADS);
    ofFill() ;
    ofSetColor ( 255 , 255 , 255 , 255 ) ;
    
    int fadeMaskOffset = 0 ;
    
    //move the mask around with the mouse by modifying the texture coordinates
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, scrolling );
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, 0);
    glVertex2f( 0 , fadeMaskOffset  );
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, content.getWidth(), scrolling );
    glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth(), 0 );
    glVertex2f(  maskArea.width , fadeMaskOffset );
    
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, content.getWidth() , mask.getHeight() + scrolling );
    glMultiTexCoord2d(GL_TEXTURE1_ARB, mask.getWidth() , mask.getHeight() );
    glVertex2f(  maskArea.width  ,  maskArea.height + fadeMaskOffset );
    
    glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, mask.getHeight() + scrolling );
    glMultiTexCoord2d(GL_TEXTURE1_ARB, 0, mask.getHeight()  );
    glVertex2f( 0 , maskArea.height + fadeMaskOffset ) ;
    
    glEnd();
    
    //deactive and clean up
    glActiveTexture(GL_TEXTURE1_ARB);
    mask.unbind() ; 
    
    glActiveTexture(GL_TEXTURE0_ARB);
    content.unbind() ;
}
