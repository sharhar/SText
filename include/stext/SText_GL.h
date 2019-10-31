//
//  SText_GL.h
//  SText
//
//  Created by Shahar Sandhaus on 9/25/19.
//

#ifndef SText_GL_h
#define SText_GL_h

typedef struct SFontGL {
	unsigned int* GLTexIDs;
	SFont* font;
} SFontGL;

typedef void* (*stPfnGetProcAdressGL)(char* name);

void stInitGL(stPfnGetProcAdressGL gl_func);
SFontGL* stCreateFontGL(SFont* font);
void stRenderTextGL(SFontGL* fontGL, const char* text, float posx, float posy);

#endif /* SText_GL_h */
