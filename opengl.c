#include "opengl.h"
#include <stdio.h>
#include <string.h>

#ifdef __linux__
extern Display *dpy;
#endif

#ifdef WIN32
GLboolean WGL_ARB_create_context_Flag=0;
HGLRC (*wglCreateContextAttribsARB)(HDC hDC, HGLRC hShareContext, const int *attribList)=NULL;

GLboolean WGL_ARB_create_context_profile_Flag=0;

GLboolean WGL_ARB_create_context_robustness_Flag=0;

GLboolean WGL_ARB_extensions_string_Flag=0;
const char *(*wglGetExtensionsStringARB)(HDC hdc)=NULL;

GLboolean WGL_ARB_framebuffer_sRGB_Flag=0;

GLboolean WGL_ARB_make_current_read_Flag=0;

GLboolean WGL_ARB_multisample_Flag=0;

BOOL (*wglMakeContextCurrentARB)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc)=NULL;
HDC (*wglGetCurrentReadDCARB)(void)=NULL;

GLboolean WGL_ARB_pixel_format_Flag=0;
BOOL (*wglGetPixelFormatAttribivARB)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues)=NULL;
BOOL (*wglGetPixelFormatAttribfvARB)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues)=NULL;
BOOL (*wglChoosePixelFormatARB)(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats)=NULL;
#else
GLXContext (*glXCreateContextAttribsARB)(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list)=NULL;

GLboolean GLX_ARB_create_context_Flag=0;

GLboolean GLX_ARB_create_context_profile_Flag=0;

GLboolean GLX_ARB_create_context_robustness_Flag=0;

GLboolean GLX_ARB_framebuffer_sRGB_Flag=0;

GLboolean GLX_ARB_multisample_Flag=0;
#endif

#ifdef WIN32 // Windows only has up to OpenGL 1.1, Linux is 2.1
GLvoid (*glDrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices)=NULL;
GLvoid (*glTexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)=NULL;
GLvoid (*glTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)=NULL;
GLvoid (*glCopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)=NULL;
GLvoid (*glActiveTexture)(GLenum texture)=NULL;
GLvoid (*glSampleCoverage)(GLfloat value, GLboolean invert)=NULL;
GLvoid (*glCompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data)=NULL;
GLvoid (*glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)=NULL;
GLvoid (*glCompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data)=NULL;
GLvoid (*glCompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)=NULL;
GLvoid (*glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)=NULL;
GLvoid (*glCompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data)=NULL;
GLvoid (*glGetCompressedTexImage)(GLenum target, GLint level, GLvoid *img)=NULL;
GLvoid (*glBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)=NULL;
GLvoid (*glMultiDrawArrays)(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount)=NULL;
GLvoid (*glMultiDrawElements)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount)=NULL;
GLvoid (*glPointParameterf)(GLenum pname, GLfloat param)=NULL;
GLvoid (*glPointParameterfv)(GLenum pname, const GLfloat *params)=NULL;
GLvoid (*glPointParameteri)(GLenum pname, GLint param)=NULL;
GLvoid (*glPointParameteriv)(GLenum pname, const GLint *params)=NULL;
GLvoid (*glBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)=NULL;
GLvoid (*glBlendEquation)(GLenum mode)=NULL;
#endif
GLvoid (*glGenQueries)(GLsizei n, GLuint *ids)=NULL;
GLvoid (*glDeleteQueries)(GLsizei n, const GLuint *ids)=NULL;
GLboolean (*glIsQuery)(GLuint id)=NULL;
GLvoid (*glBeginQuery)(GLenum target, GLuint id)=NULL;
GLvoid (*glEndQuery)(GLenum target)=NULL;
GLvoid (*glGetQueryiv)(GLenum target, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetQueryObjectiv)(GLuint id, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint *params)=NULL;
GLvoid (*glBindBuffer)(GLenum target, GLuint buffer)=NULL;
GLvoid (*glDeleteBuffers)(GLsizei n, const GLuint *buffers)=NULL;
GLvoid (*glGenBuffers)(GLsizei n, GLuint *buffers)=NULL;
GLboolean (*glIsBuffer)(GLuint buffer)=NULL;
GLvoid (*glBufferData)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)=NULL;
GLvoid (*glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)=NULL;
GLvoid (*glGetBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid *data)=NULL;
GLvoid *(*glMapBuffer)(GLenum target, GLenum access)=NULL;
GLboolean (*glUnmapBuffer)(GLenum target)=NULL;
GLvoid (*glGetBufferParameteriv)(GLenum target, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetBufferPointerv)(GLenum target, GLenum pname, GLvoid **params)=NULL;
GLvoid (*glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha)=NULL;
GLvoid (*glDrawBuffers)(GLsizei n, const GLenum *bufs)=NULL;
GLvoid (*glStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)=NULL;
GLvoid (*glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask)=NULL;
GLvoid (*glStencilMaskSeparate)(GLenum face, GLuint mask)=NULL;
GLvoid (*glAttachShader)(GLuint program, GLuint shader)=NULL;
GLvoid (*glBindAttribLocation)(GLuint program, GLuint index, const GLchar *name)=NULL;
GLvoid (*glCompileShader)(GLuint shader)=NULL;
GLuint (*glCreateProgram)(GLvoid);
GLuint (*glCreateShader)(GLenum type)=NULL;
GLvoid (*glDeleteProgram)(GLuint program)=NULL;
GLvoid (*glDeleteShader)(GLuint shader)=NULL;
GLvoid (*glDetachShader)(GLuint program, GLuint shader)=NULL;
GLvoid (*glDisableVertexAttribArray)(GLuint index)=NULL;
GLvoid (*glEnableVertexAttribArray)(GLuint index)=NULL;
GLvoid (*glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)=NULL;
GLvoid (*glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)=NULL;
GLvoid (*glGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders)=NULL;
GLint (*glGetAttribLocation)(GLuint program, const GLchar *name)=NULL;
GLvoid (*glGetProgramiv)(GLuint program, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)=NULL;
GLvoid (*glGetShaderiv)(GLuint shader, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)=NULL;
GLvoid (*glGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)=NULL;
GLint (*glGetUniformLocation)(GLuint program, const GLchar *name)=NULL;
GLvoid (*glGetUniformfv)(GLuint program, GLint location, GLfloat *params)=NULL;
GLvoid (*glGetUniformiv)(GLuint program, GLint location, GLint *params)=NULL;
GLvoid (*glGetVertexAttribdv)(GLuint index, GLenum pname, GLdouble *params)=NULL;
GLvoid (*glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat *params)=NULL;
GLvoid (*glGetVertexAttribiv)(GLuint index, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetVertexAttribPointerv)(GLuint index, GLenum pname, GLvoid **pointer)=NULL;
GLboolean (*glIsProgram)(GLuint program)=NULL;
GLboolean (*glIsShader)(GLuint shader)=NULL;
GLvoid (*glLinkProgram)(GLuint program)=NULL;
GLvoid (*glShaderSource)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)=NULL;
GLvoid (*glUseProgram)(GLuint program)=NULL;
GLvoid (*glUniform1f)(GLint location, GLfloat v0)=NULL;
GLvoid (*glUniform2f)(GLint location, GLfloat v0, GLfloat v1)=NULL;
GLvoid (*glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)=NULL;
GLvoid (*glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)=NULL;
GLvoid (*glUniform1i)(GLint location, GLint v0)=NULL;
GLvoid (*glUniform2i)(GLint location, GLint v0, GLint v1)=NULL;
GLvoid (*glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2)=NULL;
GLvoid (*glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)=NULL;
GLvoid (*glUniform1fv)(GLint location, GLsizei count, const GLfloat *value)=NULL;
GLvoid (*glUniform2fv)(GLint location, GLsizei count, const GLfloat *value)=NULL;
GLvoid (*glUniform3fv)(GLint location, GLsizei count, const GLfloat *value)=NULL;
GLvoid (*glUniform4fv)(GLint location, GLsizei count, const GLfloat *value)=NULL;
GLvoid (*glUniform1iv)(GLint location, GLsizei count, const GLint *value)=NULL;
GLvoid (*glUniform2iv)(GLint location, GLsizei count, const GLint *value)=NULL;
GLvoid (*glUniform3iv)(GLint location, GLsizei count, const GLint *value)=NULL;
GLvoid (*glUniform4iv)(GLint location, GLsizei count, const GLint *value)=NULL;
GLvoid (*glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glValidateProgram)(GLuint program)=NULL;
GLvoid (*glVertexAttrib1d)(GLuint index, GLdouble x)=NULL;
GLvoid (*glVertexAttrib1dv)(GLuint index, const GLdouble *v)=NULL;
GLvoid (*glVertexAttrib1f)(GLuint index, GLfloat x)=NULL;
GLvoid (*glVertexAttrib1fv)(GLuint index, const GLfloat *v)=NULL;
GLvoid (*glVertexAttrib1s)(GLuint index, GLshort x)=NULL;
GLvoid (*glVertexAttrib1sv)(GLuint index, const GLshort *v)=NULL;
GLvoid (*glVertexAttrib2d)(GLuint index, GLdouble x, GLdouble y)=NULL;
GLvoid (*glVertexAttrib2dv)(GLuint index, const GLdouble *v)=NULL;
GLvoid (*glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y)=NULL;
GLvoid (*glVertexAttrib2fv)(GLuint index, const GLfloat *v)=NULL;
GLvoid (*glVertexAttrib2s)(GLuint index, GLshort x, GLshort y)=NULL;
GLvoid (*glVertexAttrib2sv)(GLuint index, const GLshort *v)=NULL;
GLvoid (*glVertexAttrib3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z)=NULL;
GLvoid (*glVertexAttrib3dv)(GLuint index, const GLdouble *v)=NULL;
GLvoid (*glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z)=NULL;
GLvoid (*glVertexAttrib3fv)(GLuint index, const GLfloat *v)=NULL;
GLvoid (*glVertexAttrib3s)(GLuint index, GLshort x, GLshort y, GLshort z)=NULL;
GLvoid (*glVertexAttrib3sv)(GLuint index, const GLshort *v)=NULL;
GLvoid (*glVertexAttrib4Nbv)(GLuint index, const GLbyte *v)=NULL;
GLvoid (*glVertexAttrib4Niv)(GLuint index, const GLint *v)=NULL;
GLvoid (*glVertexAttrib4Nsv)(GLuint index, const GLshort *v)=NULL;
GLvoid (*glVertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)=NULL;
GLvoid (*glVertexAttrib4Nubv)(GLuint index, const GLubyte *v)=NULL;
GLvoid (*glVertexAttrib4Nuiv)(GLuint index, const GLuint *v)=NULL;
GLvoid (*glVertexAttrib4Nusv)(GLuint index, const GLushort *v)=NULL;
GLvoid (*glVertexAttrib4bv)(GLuint index, const GLbyte *v)=NULL;
GLvoid (*glVertexAttrib4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)=NULL;
GLvoid (*glVertexAttrib4dv)(GLuint index, const GLdouble *v)=NULL;
GLvoid (*glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)=NULL;
GLvoid (*glVertexAttrib4fv)(GLuint index, const GLfloat *v)=NULL;
GLvoid (*glVertexAttrib4iv)(GLuint index, const GLint *v)=NULL;
GLvoid (*glVertexAttrib4s)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)=NULL;
GLvoid (*glVertexAttrib4sv)(GLuint index, const GLshort *v)=NULL;
GLvoid (*glVertexAttrib4ubv)(GLuint index, const GLubyte *v)=NULL;
GLvoid (*glVertexAttrib4uiv)(GLuint index, const GLuint *v)=NULL;
GLvoid (*glVertexAttrib4usv)(GLuint index, const GLushort *v)=NULL;
GLvoid (*glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)=NULL;
GLvoid (*glUniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glUniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glUniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glUniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glUniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;
GLvoid (*glUniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)=NULL;

/* OpenGL 3.3 */
GLvoid (*glColorMaski)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)=NULL;
GLvoid (*glGetBooleani_v)(GLenum target, GLuint index, GLboolean *data)=NULL;
GLvoid (*glGetIntegeri_v)(GLenum target, GLuint index, GLint *data)=NULL;
GLvoid (*glEnablei)(GLenum target, GLuint index)=NULL;
GLvoid (*glDisablei)(GLenum target, GLuint index)=NULL;
GLboolean (*glIsEnabledi)(GLenum target, GLuint index)=NULL;
GLvoid (*glBeginTransformFeedback)(GLenum primitiveMode)=NULL;
GLvoid (*glEndTransformFeedback)(GLvoid)=NULL;
GLvoid (*glBindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)=NULL;
GLvoid (*glBindBufferBase)(GLenum target, GLuint index, GLuint buffer)=NULL;
GLvoid (*glTransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode)=NULL;
GLvoid (*glGetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name)=NULL;
GLvoid (*glClampColor)(GLenum target, GLenum clamp)=NULL;
GLvoid (*glBeginConditionalRender)(GLuint id, GLenum mode)=NULL;
GLvoid (*glEndConditionalRender)(GLvoid)=NULL;
GLvoid (*glVertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)=NULL;
GLvoid (*glGetVertexAttribIiv)(GLuint index, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint *params)=NULL;
GLvoid (*glVertexAttribI1i)(GLuint index, GLint x)=NULL;
GLvoid (*glVertexAttribI2i)(GLuint index, GLint x, GLint y)=NULL;
GLvoid (*glVertexAttribI3i)(GLuint index, GLint x, GLint y, GLint z)=NULL;
GLvoid (*glVertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w)=NULL;
GLvoid (*glVertexAttribI1ui)(GLuint index, GLuint x)=NULL;
GLvoid (*glVertexAttribI2ui)(GLuint index, GLuint x, GLuint y)=NULL;
GLvoid (*glVertexAttribI3ui)(GLuint index, GLuint x, GLuint y, GLuint z)=NULL;
GLvoid (*glVertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)=NULL;
GLvoid (*glVertexAttribI1iv)(GLuint index, const GLint *v)=NULL;
GLvoid (*glVertexAttribI2iv)(GLuint index, const GLint *v)=NULL;
GLvoid (*glVertexAttribI3iv)(GLuint index, const GLint *v)=NULL;
GLvoid (*glVertexAttribI4iv)(GLuint index, const GLint *v)=NULL;
GLvoid (*glVertexAttribI1uiv)(GLuint index, const GLuint *v)=NULL;
GLvoid (*glVertexAttribI2uiv)(GLuint index, const GLuint *v)=NULL;
GLvoid (*glVertexAttribI3uiv)(GLuint index, const GLuint *v)=NULL;
GLvoid (*glVertexAttribI4uiv)(GLuint index, const GLuint *v)=NULL;
GLvoid (*glVertexAttribI4bv)(GLuint index, const GLbyte *v)=NULL;
GLvoid (*glVertexAttribI4sv)(GLuint index, const GLshort *v)=NULL;
GLvoid (*glVertexAttribI4ubv)(GLuint index, const GLubyte *v)=NULL;
GLvoid (*glVertexAttribI4usv)(GLuint index, const GLushort *v)=NULL;
GLvoid (*glGetUniformuiv)(GLuint program, GLint location, GLuint *params)=NULL;
GLvoid (*glBindFragDataLocation)(GLuint program, GLuint color, const GLchar *name)=NULL;
GLint (*glGetFragDataLocation)(GLuint program, const GLchar *name)=NULL;
GLvoid (*glUniform1ui)(GLint location, GLuint v0)=NULL;
GLvoid (*glUniform2ui)(GLint location, GLuint v0, GLuint v1)=NULL;
GLvoid (*glUniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2)=NULL;
GLvoid (*glUniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)=NULL;
GLvoid (*glUniform1uiv)(GLint location, GLsizei count, const GLuint *value)=NULL;
GLvoid (*glUniform2uiv)(GLint location, GLsizei count, const GLuint *value)=NULL;
GLvoid (*glUniform3uiv)(GLint location, GLsizei count, const GLuint *value)=NULL;
GLvoid (*glUniform4uiv)(GLint location, GLsizei count, const GLuint *value)=NULL;
GLvoid (*glTexParameterIiv)(GLenum target, GLenum pname, const GLint *params)=NULL;
GLvoid (*glTexParameterIuiv)(GLenum target, GLenum pname, const GLuint *params)=NULL;
GLvoid (*glGetTexParameterIiv)(GLenum target, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetTexParameterIuiv)(GLenum target, GLenum pname, GLuint *params)=NULL;
GLvoid (*glClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint *value)=NULL;
GLvoid (*glClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint *value)=NULL;
GLvoid (*glClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat *value)=NULL;
GLvoid (*glClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)=NULL;
const GLubyte *(*glGetStringi)(GLenum name, GLuint index)=NULL;
GLboolean (*glIsRenderbuffer)(GLuint renderbuffer)=NULL;
GLvoid (*glBindRenderbuffer)(GLenum target, GLuint renderbuffer)=NULL;
GLvoid (*glDeleteRenderbuffers)(GLsizei n, const GLuint *renderbuffers)=NULL;
GLvoid (*glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers)=NULL;
GLvoid (*glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)=NULL;
GLvoid (*glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint *params)=NULL;
GLboolean (*glIsFramebuffer)(GLuint framebuffer)=NULL;
GLvoid (*glBindFramebuffer)(GLenum target, GLuint framebuffer)=NULL;
GLvoid (*glDeleteFramebuffers)(GLsizei n, const GLuint *framebuffers)=NULL;
GLvoid (*glGenFramebuffers)(GLsizei n, GLuint *framebuffers)=NULL;
GLenum (*glCheckFramebufferStatus)(GLenum target)=NULL;
GLvoid (*glFramebufferTexture1D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)=NULL;
GLvoid (*glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)=NULL;
GLvoid (*glFramebufferTexture3D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)=NULL;
GLvoid (*glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)=NULL;
GLvoid (*glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint *params)=NULL;
GLvoid (*glGenerateMipmap)(GLenum target)=NULL;
GLvoid (*glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)=NULL;
GLvoid (*glRenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)=NULL;
GLvoid (*glFramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)=NULL;
GLvoid *(*glMapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)=NULL;
GLvoid (*glFlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length)=NULL;
GLvoid (*glBindVertexArray)(GLuint array)=NULL;
GLvoid (*glDeleteVertexArrays)(GLsizei n, const GLuint *arrays)=NULL;
GLvoid (*glGenVertexArrays)(GLsizei n, GLuint *arrays)=NULL;
GLboolean (*glIsVertexArray)(GLuint array)=NULL;
GLvoid (*glDrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)=NULL;
GLvoid (*glDrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instancecount)=NULL;
GLvoid (*glTexBuffer)(GLenum target, GLenum internalformat, GLuint buffer)=NULL;
GLvoid (*glPrimitiveRestartIndex)(GLuint index)=NULL;
GLvoid (*glCopyBufferSubData)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)=NULL;
GLvoid (*glGetUniformIndices)(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices)=NULL;
GLvoid (*glGetActiveUniformsiv)(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetActiveUniformName)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName)=NULL;
GLuint (*glGetUniformBlockIndex)(GLuint program, const GLchar *uniformBlockName)=NULL;
GLvoid (*glGetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetActiveUniformBlockName)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName)=NULL;
GLvoid (*glUniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)=NULL;
GLvoid (*glDrawElementsBaseVertex)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex)=NULL;
GLvoid (*glDrawRangeElementsBaseVertex)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices, GLint basevertex)=NULL;
GLvoid (*glDrawElementsInstancedBaseVertex)(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instancecount, GLint basevertex)=NULL;
GLvoid (*glMultiDrawElementsBaseVertex)(GLenum mode, const GLsizei *count, GLenum type, const GLvoid *const*indices, GLsizei drawcount, const GLint *basevertex)=NULL;
GLvoid (*glProvokingVertex)(GLenum mode)=NULL;
GLsync (*glFenceSync)(GLenum condition, GLbitfield flags)=NULL;
GLboolean (*glIsSync)(GLsync sync)=NULL;
GLvoid (*glDeleteSync)(GLsync sync)=NULL;
GLenum (*glClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout)=NULL;
GLvoid (*glWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout)=NULL;
GLvoid (*glGetInteger64v)(GLenum pname, GLint64 *data)=NULL;
GLvoid (*glGetSynciv)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values)=NULL;
GLvoid (*glGetInteger64i_v)(GLenum target, GLuint index, GLint64 *data)=NULL;
GLvoid (*glGetBufferParameteri64v)(GLenum target, GLenum pname, GLint64 *params)=NULL;
GLvoid (*glFramebufferTexture)(GLenum target, GLenum attachment, GLuint texture, GLint level)=NULL;
GLvoid (*glTexImage2DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)=NULL;
GLvoid (*glTexImage3DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)=NULL;
GLvoid (*glGetMultisamplefv)(GLenum pname, GLuint index, GLfloat *val)=NULL;
GLvoid (*glSampleMaski)(GLuint maskNumber, GLbitfield mask)=NULL;
GLvoid (*glBindFragDataLocationIndexed)(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name)=NULL;
GLint (*glGetFragDataIndex)(GLuint program, const GLchar *name)=NULL;
GLvoid (*glGenSamplers)(GLsizei count, GLuint *samplers)=NULL;
GLvoid (*glDeleteSamplers)(GLsizei count, const GLuint *samplers)=NULL;
GLboolean (*glIsSampler)(GLuint sampler)=NULL;
GLvoid (*glBindSampler)(GLuint unit, GLuint sampler)=NULL;
GLvoid (*glSamplerParameteri)(GLuint sampler, GLenum pname, GLint param)=NULL;
GLvoid (*glSamplerParameteriv)(GLuint sampler, GLenum pname, const GLint *param)=NULL;
GLvoid (*glSamplerParameterf)(GLuint sampler, GLenum pname, GLfloat param)=NULL;
GLvoid (*glSamplerParameterfv)(GLuint sampler, GLenum pname, const GLfloat *param)=NULL;
GLvoid (*glSamplerParameterIiv)(GLuint sampler, GLenum pname, const GLint *param)=NULL;
GLvoid (*glSamplerParameterIuiv)(GLuint sampler, GLenum pname, const GLuint *param)=NULL;
GLvoid (*glGetSamplerParameteriv)(GLuint sampler, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetSamplerParameterIiv)(GLuint sampler, GLenum pname, GLint *params)=NULL;
GLvoid (*glGetSamplerParameterfv)(GLuint sampler, GLenum pname, GLfloat *params)=NULL;
GLvoid (*glGetSamplerParameterIuiv)(GLuint sampler, GLenum pname, GLuint *params)=NULL;
GLvoid (*glQueryCounter)(GLuint id, GLenum target)=NULL;
GLvoid (*glGetQueryObjecti64v)(GLuint id, GLenum pname, GLint64 *params)=NULL;
GLvoid (*glGetQueryObjectui64v)(GLuint id, GLenum pname, GLuint64 *params)=NULL;
GLvoid (*glVertexAttribDivisor)(GLuint index, GLuint divisor)=NULL;
GLvoid (*glVertexAttribP1ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value)=NULL;
GLvoid (*glVertexAttribP1uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)=NULL;
GLvoid (*glVertexAttribP2ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value)=NULL;
GLvoid (*glVertexAttribP2uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)=NULL;
GLvoid (*glVertexAttribP3ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value)=NULL;
GLvoid (*glVertexAttribP3uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)=NULL;
GLvoid (*glVertexAttribP4ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value)=NULL;
GLvoid (*glVertexAttribP4uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)=NULL;

GLboolean GL_ARB_texture_rectangle_Flag=0;

int GLExtensionsInitialized_Flag=0;

#ifdef WIN32
int WGLExtensionsInitialized_Flag=0;
#else
int GLXExtensionsInitialized_Flag=0;
#endif

void *glGetProcAddress(char *Name, int *Return)
{
	void *FuncPtr=NULL;

#ifdef WIN32
	FuncPtr=(void *)wglGetProcAddress(Name);
#else
	FuncPtr=(void *)glXGetProcAddressARB(Name);
#endif

	if(FuncPtr!=NULL)
		*Return&=1;
	else
		*Return&=0;

	return FuncPtr;
}

int FindSubString(char *string, char *substring)
{
	if(string)
	{
		char *str=string;
		size_t len=strlen(substring);

		while((str=strstr(str, substring))!=NULL)
		{
			str+=len;

			if(*str==' '||*str=='\0')
				return 1;
		}
	}

	return 0;
}

void GLSetupExtensions(void)
{
	int Return=1;
	char *GLExtensionString=NULL;

/*	glCullFace=glGetProcAddress("glCullFace", &Return);
	glFrontFace=glGetProcAddress("glFrontFace", &Return);
	glHint=glGetProcAddress("glHint", &Return);
	glLineWidth=glGetProcAddress("glLineWidth", &Return);
	glPointSize=glGetProcAddress("glPointSize", &Return);
	glPolygonMode=glGetProcAddress("glPolygonMode", &Return);
	glScissor=glGetProcAddress("glScissor", &Return);
	glTexParameterf=glGetProcAddress("glTexParameterf", &Return);
	glTexParameterfv=glGetProcAddress("glTexParameterfv", &Return);
	glTexParameteri=glGetProcAddress("glTexParameteri", &Return);
	glTexParameteriv=glGetProcAddress("glTexParameteriv", &Return);
	glTexImage1D=glGetProcAddress("glTexImage1D", &Return);
	glTexImage2D=glGetProcAddress("glTexImage2D", &Return);
	glDrawBuffer=glGetProcAddress("glDrawBuffer", &Return);
	glClear=glGetProcAddress("glClear", &Return);
	glClearColor=glGetProcAddress("glClearColor", &Return);
	glClearStencil=glGetProcAddress("glClearStencil", &Return);
	glClearDepth=glGetProcAddress("glClearDepth", &Return);
	glStencilMask=glGetProcAddress("glStencilMask", &Return);
	glColorMask=glGetProcAddress("glColorMask", &Return);
	glDepthMask=glGetProcAddress("glDepthMask", &Return);
	glDisable=glGetProcAddress("glDisable", &Return);
	glEnable=glGetProcAddress("glEnable", &Return);
	glFinish=glGetProcAddress("glFinish", &Return);
	glFlush=glGetProcAddress("glFlush", &Return);
	glBlendFunc=glGetProcAddress("glBlendFunc", &Return);
	glLogicOp=glGetProcAddress("glLogicOp", &Return);
	glStencilFunc=glGetProcAddress("glStencilFunc", &Return);
	glStencilOp=glGetProcAddress("glStencilOp", &Return);
	glDepthFunc=glGetProcAddress("glDepthFunc", &Return);
	glPixelStoref=glGetProcAddress("glPixelStoref", &Return);
	glPixelStorei=glGetProcAddress("glPixelStorei", &Return);
	glReadBuffer=glGetProcAddress("glReadBuffer", &Return);
	glReadPixels=glGetProcAddress("glReadPixels", &Return);
	glGetBooleanv=glGetProcAddress("glGetBooleanv", &Return);
	glGetDoublev=glGetProcAddress("glGetDoublev", &Return);
	glGetError=glGetProcAddress("glGetError", &Return);
	glGetFloatv=glGetProcAddress("glGetFloatv", &Return);
	glGetIntegerv=glGetProcAddress("glGetIntegerv", &Return);
	glGetString=glGetProcAddress("glGetString", &Return);
	glGetTexImage=glGetProcAddress("glGetTexImage", &Return);
	glGetTexParameterfv=glGetProcAddress("glGetTexParameterfv", &Return);
	glGetTexParameteriv=glGetProcAddress("glGetTexParameteriv", &Return);
	glGetTexLevelParameterfv=glGetProcAddress("glGetTexLevelParameterfv", &Return);
	glGetTexLevelParameteriv=glGetProcAddress("glGetTexLevelParameteriv", &Return);
	glIsEnabled=glGetProcAddress("glIsEnabled", &Return);
	glDepthRange=glGetProcAddress("glDepthRange", &Return);
	glViewport=glGetProcAddress("glViewport", &Return);
	glDrawArrays=glGetProcAddress("glDrawArrays", &Return);
	glDrawElements=glGetProcAddress("glDrawElements", &Return);
	glGetPointerv=glGetProcAddress("glGetPointerv", &Return);
	glPolygonOffset=glGetProcAddress("glPolygonOffset", &Return);
	glCopyTexImage1D=glGetProcAddress("glCopyTexImage1D", &Return);
	glCopyTexImage2D=glGetProcAddress("glCopyTexImage2D", &Return);
	glCopyTexSubImage1D=glGetProcAddress("glCopyTexSubImage1D", &Return);
	glCopyTexSubImage2D=glGetProcAddress("glCopyTexSubImage2D", &Return);
	glTexSubImage1D=glGetProcAddress("glTexSubImage1D", &Return);
	glTexSubImage2D=glGetProcAddress("glTexSubImage2D", &Return);
	glBindTexture=glGetProcAddress("glBindTexture", &Return);
	glDeleteTextures=glGetProcAddress("glDeleteTextures", &Return);
	glGenTextures=glGetProcAddress("glGenTextures", &Return);
	glIsTexture=glGetProcAddress("glIsTexture", &Return);*/
#ifdef WIN32
	glDrawRangeElements=glGetProcAddress("glDrawRangeElements", &Return);
	glTexImage3D=glGetProcAddress("glTexImage3D", &Return);
	glTexSubImage3D=glGetProcAddress("glTexSubImage3D", &Return);
	glCopyTexSubImage3D=glGetProcAddress("glCopyTexSubImage3D", &Return);
	glActiveTexture=glGetProcAddress("glActiveTexture", &Return);
	glSampleCoverage=glGetProcAddress("glSampleCoverage", &Return);
	glCompressedTexImage3D=glGetProcAddress("glCompressedTexImage3D", &Return);
	glCompressedTexImage2D=glGetProcAddress("glCompressedTexImage2D", &Return);
	glCompressedTexImage1D=glGetProcAddress("glCompressedTexImage1D", &Return);
	glCompressedTexSubImage3D=glGetProcAddress("glCompressedTexSubImage3D", &Return);
	glCompressedTexSubImage2D=glGetProcAddress("glCompressedTexSubImage2D", &Return);
	glCompressedTexSubImage1D=glGetProcAddress("glCompressedTexSubImage1D", &Return);
	glGetCompressedTexImage=glGetProcAddress("glGetCompressedTexImage", &Return);
	glBlendFuncSeparate=glGetProcAddress("glBlendFuncSeparate", &Return);
	glMultiDrawArrays=glGetProcAddress("glMultiDrawArrays", &Return);
	glMultiDrawElements=glGetProcAddress("glMultiDrawElements", &Return);
	glPointParameterf=glGetProcAddress("glPointParameterf", &Return);
	glPointParameterfv=glGetProcAddress("glPointParameterfv", &Return);
	glPointParameteri=glGetProcAddress("glPointParameteri", &Return);
	glPointParameteriv=glGetProcAddress("glPointParameteriv", &Return);
	glBlendColor=glGetProcAddress("glBlendColor", &Return);
	glBlendEquation=glGetProcAddress("glBlendEquation", &Return);
#endif
	glGenQueries=glGetProcAddress("glGenQueries", &Return);
	glDeleteQueries=glGetProcAddress("glDeleteQueries", &Return);
	glIsQuery=glGetProcAddress("glIsQuery", &Return);
	glBeginQuery=glGetProcAddress("glIsQuery", &Return);
	glEndQuery=glGetProcAddress("glEndQuery", &Return);
	glGetQueryiv=glGetProcAddress("glGetQueryiv", &Return);
	glGetQueryObjectiv=glGetProcAddress("glGetQueryObjectiv", &Return);
	glGetQueryObjectuiv=glGetProcAddress("glGetQueryObjectuiv", &Return);
	glBindBuffer=glGetProcAddress("glBindBuffer", &Return);
	glDeleteBuffers=glGetProcAddress("glDeleteBuffers", &Return);
	glGenBuffers=glGetProcAddress("glGenBuffers", &Return);
	glIsBuffer=glGetProcAddress("glIsBuffer", &Return);
	glBufferData=glGetProcAddress("glBufferData", &Return);
	glBufferSubData=glGetProcAddress("glBufferSubData", &Return);
	glGetBufferSubData=glGetProcAddress("glGetBufferSubData", &Return);
	glMapBuffer=glGetProcAddress("glMapBuffer", &Return);
	glUnmapBuffer=glGetProcAddress("glUnmapBuffer", &Return);
	glGetBufferParameteriv=glGetProcAddress("glGetBufferParameteriv", &Return);
	glGetBufferPointerv=glGetProcAddress("glGetBufferPointerv", &Return);
	glBlendEquationSeparate=glGetProcAddress("glBlendEquationSeparate", &Return);
	glDrawBuffers=glGetProcAddress("glDrawBuffers", &Return);
	glStencilOpSeparate=glGetProcAddress("glStencilOpSeparate", &Return);
	glStencilFuncSeparate=glGetProcAddress("glStencilFuncSeparate", &Return);
	glStencilMaskSeparate=glGetProcAddress("glStencilMaskSeparate", &Return);
	glAttachShader=glGetProcAddress("glAttachShader", &Return);
	glBindAttribLocation=glGetProcAddress("glBindAttribLocation", &Return);
	glCompileShader=glGetProcAddress("glCompileShader", &Return);
	glCreateProgram=glGetProcAddress("glCreateProgram", &Return);
	glCreateShader=glGetProcAddress("glCreateShader", &Return);
	glDeleteProgram=glGetProcAddress("glDeleteProgram", &Return);
	glDeleteShader=glGetProcAddress("glDeleteShader", &Return);
	glDetachShader=glGetProcAddress("glDetachShader", &Return);
	glDisableVertexAttribArray=glGetProcAddress("glDisableVertexAttribArray", &Return);
	glEnableVertexAttribArray=glGetProcAddress("glEnableVertexAttribArray", &Return);
	glGetActiveAttrib=glGetProcAddress("glGetActiveAttrib", &Return);
	glGetActiveUniform=glGetProcAddress("glGetActiveUniform", &Return);
	glGetAttachedShaders=glGetProcAddress("glGetAttachedShaders", &Return);
	glGetAttribLocation=glGetProcAddress("glGetAttribLocation", &Return);
	glGetProgramiv=glGetProcAddress("glGetProgramiv", &Return);
	glGetProgramInfoLog=glGetProcAddress("glGetProgramInfoLog", &Return);
	glGetShaderiv=glGetProcAddress("glGetShaderiv", &Return);
	glGetShaderInfoLog=glGetProcAddress("glGetShaderInfoLog", &Return);
	glGetShaderSource=glGetProcAddress("glGetShaderSource", &Return);
	glGetUniformLocation=glGetProcAddress("glGetUniformLocation", &Return);
	glGetUniformfv=glGetProcAddress("glGetUniformfv", &Return);
	glGetUniformiv=glGetProcAddress("glGetUniformiv", &Return);
	glGetVertexAttribdv=glGetProcAddress("glGetVertexAttribdv", &Return);
	glGetVertexAttribfv=glGetProcAddress("glGetVertexAttribfv", &Return);
	glGetVertexAttribiv=glGetProcAddress("glGetVertexAttribiv", &Return);
	glGetVertexAttribPointerv=glGetProcAddress("glGetVertexAttribPointerv", &Return);
	glIsProgram=glGetProcAddress("glIsProgram", &Return);
	glIsShader=glGetProcAddress("glIsShader", &Return);
	glLinkProgram=glGetProcAddress("glLinkProgram", &Return);
	glShaderSource=glGetProcAddress("glShaderSource", &Return);
	glUseProgram=glGetProcAddress("glUseProgram", &Return);
	glUniform1f=glGetProcAddress("glUniform1f", &Return);
	glUniform2f=glGetProcAddress("glUniform2f", &Return);
	glUniform3f=glGetProcAddress("glUniform3f", &Return);
	glUniform4f=glGetProcAddress("glUniform4f", &Return);
	glUniform1i=glGetProcAddress("glUniform1i", &Return);
	glUniform2i=glGetProcAddress("glUniform2i", &Return);
	glUniform3i=glGetProcAddress("glUniform3i", &Return);
	glUniform4i=glGetProcAddress("glUniform4i", &Return);
	glUniform1fv=glGetProcAddress("glUniform1fv", &Return);
	glUniform2fv=glGetProcAddress("glUniform2fv", &Return);
	glUniform3fv=glGetProcAddress("glUniform3fv", &Return);
	glUniform4fv=glGetProcAddress("glUniform4fv", &Return);
	glUniform1iv=glGetProcAddress("glUniform1iv", &Return);
	glUniform2iv=glGetProcAddress("glUniform2iv", &Return);
	glUniform3iv=glGetProcAddress("glUniform3iv", &Return);
	glUniform4iv=glGetProcAddress("glUniform4iv", &Return);
	glUniformMatrix2fv=glGetProcAddress("glUniformMatrix2fv", &Return);
	glUniformMatrix3fv=glGetProcAddress("glUniformMatrix3fv", &Return);
	glUniformMatrix4fv=glGetProcAddress("glUniformMatrix4fv", &Return);
	glValidateProgram=glGetProcAddress("glValidateProgram", &Return);
	glVertexAttrib1d=glGetProcAddress("glVertexAttrib1d", &Return);
	glVertexAttrib1dv=glGetProcAddress("glVertexAttrib1dv", &Return);
	glVertexAttrib1f=glGetProcAddress("glVertexAttrib1f", &Return);
	glVertexAttrib1fv=glGetProcAddress("glVertexAttrib1fv", &Return);
	glVertexAttrib1s=glGetProcAddress("glVertexAttrib1s", &Return);
	glVertexAttrib1sv=glGetProcAddress("glVertexAttrib1sv", &Return);
	glVertexAttrib2d=glGetProcAddress("glVertexAttrib2d", &Return);
	glVertexAttrib2dv=glGetProcAddress("glVertexAttrib2dv", &Return);
	glVertexAttrib2f=glGetProcAddress("glVertexAttrib2f", &Return);
	glVertexAttrib2fv=glGetProcAddress("glVertexAttrib2fv", &Return);
	glVertexAttrib2s=glGetProcAddress("glVertexAttrib2s", &Return);
	glVertexAttrib2sv=glGetProcAddress("glVertexAttrib2sv", &Return);
	glVertexAttrib3d=glGetProcAddress("glVertexAttrib3d", &Return);
	glVertexAttrib3dv=glGetProcAddress("glVertexAttrib3dv", &Return);
	glVertexAttrib3f=glGetProcAddress("glVertexAttrib3f", &Return);
	glVertexAttrib3fv=glGetProcAddress("glVertexAttrib3fv", &Return);
	glVertexAttrib3s=glGetProcAddress("glVertexAttrib3s", &Return);
	glVertexAttrib3sv=glGetProcAddress("glVertexAttrib3sv", &Return);
	glVertexAttrib4Nbv=glGetProcAddress("glVertexAttrib4Nbv", &Return);
	glVertexAttrib4Niv=glGetProcAddress("glVertexAttrib4Niv", &Return);
	glVertexAttrib4Nsv=glGetProcAddress("glVertexAttrib4Nsv", &Return);
	glVertexAttrib4Nub=glGetProcAddress("glVertexAttrib4Nub", &Return);
	glVertexAttrib4Nubv=glGetProcAddress("glVertexAttrib4Nubv", &Return);
	glVertexAttrib4Nuiv=glGetProcAddress("glVertexAttrib4Nuiv", &Return);
	glVertexAttrib4Nusv=glGetProcAddress("glVertexAttrib4Nusv", &Return);
	glVertexAttrib4bv=glGetProcAddress("glVertexAttrib4bv", &Return);
	glVertexAttrib4d=glGetProcAddress("glVertexAttrib4d", &Return);
	glVertexAttrib4dv=glGetProcAddress("glVertexAttrib4dv", &Return);
	glVertexAttrib4f=glGetProcAddress("glVertexAttrib4f", &Return);
	glVertexAttrib4fv=glGetProcAddress("glVertexAttrib4fv", &Return);
	glVertexAttrib4iv=glGetProcAddress("glVertexAttrib4iv", &Return);
	glVertexAttrib4s=glGetProcAddress("glVertexAttrib4s", &Return);
	glVertexAttrib4sv=glGetProcAddress("glVertexAttrib4sv", &Return);
	glVertexAttrib4ubv=glGetProcAddress("glVertexAttrib4ubv", &Return);
	glVertexAttrib4uiv=glGetProcAddress("glVertexAttrib4uiv", &Return);
	glVertexAttrib4usv=glGetProcAddress("glVertexAttrib4usv", &Return);
	glVertexAttribPointer=glGetProcAddress("glVertexAttribPointer", &Return);
	glUniformMatrix2x3fv=glGetProcAddress("glUniformMatrix2x3fv", &Return);
	glUniformMatrix3x2fv=glGetProcAddress("glUniformMatrix3x2fv", &Return);
	glUniformMatrix2x4fv=glGetProcAddress("glUniformMatrix2x4fv", &Return);
	glUniformMatrix4x2fv=glGetProcAddress("glUniformMatrix4x2fv", &Return);
	glUniformMatrix3x4fv=glGetProcAddress("glUniformMatrix3x4fv", &Return);
	glUniformMatrix4x3fv=glGetProcAddress("glUniformMatrix4x3fv", &Return);

	// Something went horribly wrong, or incomplete GL2.1 support
	if(!Return)
		return;

	// GL Extensions
	GLExtensionString=(char *)glGetString(GL_EXTENSIONS);

	if(FindSubString(GLExtensionString, "GL_ARB_texture_rectangle"))
		GL_ARB_texture_rectangle_Flag=1;

	glColorMaski=glGetProcAddress("glColorMaski", &Return);
	glGetBooleani_v=glGetProcAddress("glGetBooleani_v", &Return);
	glGetIntegeri_v=glGetProcAddress("glGetIntegeri_v", &Return);
	glEnablei=glGetProcAddress("glEnablei", &Return);
	glDisablei=glGetProcAddress("glDisablei", &Return);
	glIsEnabledi=glGetProcAddress("glIsEnabledi", &Return);
	glBeginTransformFeedback=glGetProcAddress("glBeginTransformFeedback", &Return);
	glEndTransformFeedback=glGetProcAddress("glEndTransformFeedback", &Return);
	glBindBufferRange=glGetProcAddress("glBindBufferRange", &Return);
	glBindBufferBase=glGetProcAddress("glBindBufferBase", &Return);
	glTransformFeedbackVaryings=glGetProcAddress("glTransformFeedbackVaryings", &Return);
	glGetTransformFeedbackVarying=glGetProcAddress("glGetTransformFeedbackVarying", &Return);
	glClampColor=glGetProcAddress("glClampColor", &Return);
	glBeginConditionalRender=glGetProcAddress("glBeginConditionalRender", &Return);
	glEndConditionalRender=glGetProcAddress("glEndConditionalRender", &Return);
	glVertexAttribIPointer=glGetProcAddress("glVertexAttribIPointer", &Return);
	glGetVertexAttribIiv=glGetProcAddress("glGetVertexAttribIiv", &Return);
	glGetVertexAttribIuiv=glGetProcAddress("glGetVertexAttribIuiv", &Return);
	glVertexAttribI1i=glGetProcAddress("glVertexAttribI1i", &Return);
	glVertexAttribI2i=glGetProcAddress("glVertexAttribI2i", &Return);
	glVertexAttribI3i=glGetProcAddress("glVertexAttribI3i", &Return);
	glVertexAttribI4i=glGetProcAddress("glVertexAttribI4i", &Return);
	glVertexAttribI1ui=glGetProcAddress("glVertexAttribI1ui", &Return);
	glVertexAttribI2ui=glGetProcAddress("glVertexAttribI2ui", &Return);
	glVertexAttribI3ui=glGetProcAddress("glVertexAttribI3ui", &Return);
	glVertexAttribI4ui=glGetProcAddress("glVertexAttribI4ui", &Return);
	glVertexAttribI1iv=glGetProcAddress("glVertexAttribI1iv", &Return);
	glVertexAttribI2iv=glGetProcAddress("glVertexAttribI2iv", &Return);
	glVertexAttribI3iv=glGetProcAddress("glVertexAttribI3iv", &Return);
	glVertexAttribI4iv=glGetProcAddress("glVertexAttribI4iv", &Return);
	glVertexAttribI1uiv=glGetProcAddress("glVertexAttribI1uiv", &Return);
	glVertexAttribI2uiv=glGetProcAddress("glVertexAttribI2uiv", &Return);
	glVertexAttribI3uiv=glGetProcAddress("glVertexAttribI3uiv", &Return);
	glVertexAttribI4uiv=glGetProcAddress("glVertexAttribI4uiv", &Return);
	glVertexAttribI4bv=glGetProcAddress("glVertexAttribI4bv", &Return);
	glVertexAttribI4sv=glGetProcAddress("glVertexAttribI4sv", &Return);
	glVertexAttribI4ubv=glGetProcAddress("glVertexAttribI4ubv", &Return);
	glVertexAttribI4usv=glGetProcAddress("glVertexAttribI4usv", &Return);
	glGetUniformuiv=glGetProcAddress("glGetUniformuiv", &Return);
	glBindFragDataLocation=glGetProcAddress("glBindFragDataLocation", &Return);
	glGetFragDataLocation=glGetProcAddress("glGetFragDataLocation", &Return);
	glUniform1ui=glGetProcAddress("glUniform1ui", &Return);
	glUniform2ui=glGetProcAddress("glUniform2ui", &Return);
	glUniform3ui=glGetProcAddress("glUniform3ui", &Return);
	glUniform4ui=glGetProcAddress("glUniform4ui", &Return);
	glUniform1uiv=glGetProcAddress("glUniform1uiv", &Return);
	glUniform2uiv=glGetProcAddress("glUniform2uiv", &Return);
	glUniform3uiv=glGetProcAddress("glUniform3uiv", &Return);
	glUniform4uiv=glGetProcAddress("glUniform4uiv", &Return);
	glTexParameterIiv=glGetProcAddress("glTexParameterIiv", &Return);
	glTexParameterIuiv=glGetProcAddress("glTexParameterIuiv", &Return);
	glGetTexParameterIiv=glGetProcAddress("glGetTexParameterIiv", &Return);
	glGetTexParameterIuiv=glGetProcAddress("glGetTexParameterIuiv", &Return);
	glClearBufferiv=glGetProcAddress("glClearBufferiv", &Return);
	glClearBufferuiv=glGetProcAddress("glClearBufferuiv", &Return);
	glClearBufferfv=glGetProcAddress("glClearBufferfv", &Return);
	glClearBufferfi=glGetProcAddress("glClearBufferfi", &Return);
	glGetStringi=glGetProcAddress("glGetStringi", &Return);
	glIsRenderbuffer=glGetProcAddress("glIsRenderbuffer", &Return);
	glBindRenderbuffer=glGetProcAddress("glBindRenderbuffer", &Return);
	glDeleteRenderbuffers=glGetProcAddress("glDeleteRenderbuffers", &Return);
	glGenRenderbuffers=glGetProcAddress("glGenRenderbuffers", &Return);
	glRenderbufferStorage=glGetProcAddress("glRenderbufferStorage", &Return);
	glGetRenderbufferParameteriv=glGetProcAddress("glGetRenderbufferParameteriv", &Return);
	glIsFramebuffer=glGetProcAddress("glIsFramebuffer", &Return);
	glBindFramebuffer=glGetProcAddress("glBindFramebuffer", &Return);
	glDeleteFramebuffers=glGetProcAddress("glDeleteFramebuffers", &Return);
	glGenFramebuffers=glGetProcAddress("glGenFramebuffers", &Return);
	glCheckFramebufferStatus=glGetProcAddress("glCheckFramebufferStatus", &Return);
	glFramebufferTexture1D=glGetProcAddress("glFramebufferTexture1D", &Return);
	glFramebufferTexture2D=glGetProcAddress("glFramebufferTexture2D", &Return);
	glFramebufferTexture3D=glGetProcAddress("glFramebufferTexture3D", &Return);
	glFramebufferRenderbuffer=glGetProcAddress("glFramebufferRenderbuffer", &Return);
	glGetFramebufferAttachmentParameteriv=glGetProcAddress("glGetFramebufferAttachmentParameteriv", &Return);
	glGenerateMipmap=glGetProcAddress("glGenerateMipmap", &Return);
	glBlitFramebuffer=glGetProcAddress("glBlitFramebuffer", &Return);
	glRenderbufferStorageMultisample=glGetProcAddress("glRenderbufferStorageMultisample", &Return);
	glFramebufferTextureLayer=glGetProcAddress("glFramebufferTextureLayer", &Return);
	glMapBufferRange=glGetProcAddress("glMapBufferRange", &Return);
	glFlushMappedBufferRange=glGetProcAddress("glFlushMappedBufferRange", &Return);
	glBindVertexArray=glGetProcAddress("glBindVertexArray", &Return);
	glDeleteVertexArrays=glGetProcAddress("glDeleteVertexArrays", &Return);
	glGenVertexArrays=glGetProcAddress("glGenVertexArrays", &Return);
	glIsVertexArray=glGetProcAddress("glIsVertexArray", &Return);
	glDrawArraysInstanced=glGetProcAddress("glDrawArraysInstanced", &Return);
	glDrawElementsInstanced=glGetProcAddress("glDrawElementsInstanced", &Return);
	glTexBuffer=glGetProcAddress("glTexBuffer", &Return);
	glPrimitiveRestartIndex=glGetProcAddress("glPrimitiveRestartIndex", &Return);
	glCopyBufferSubData=glGetProcAddress("glCopyBufferSubData", &Return);
	glGetUniformIndices=glGetProcAddress("glGetUniformIndices", &Return);
	glGetActiveUniformsiv=glGetProcAddress("glGetActiveUniformsiv", &Return);
	glGetActiveUniformName=glGetProcAddress("glGetActiveUniformName", &Return);
	glGetUniformBlockIndex=glGetProcAddress("glGetUniformBlockIndex", &Return);
	glGetActiveUniformBlockiv=glGetProcAddress("glGetActiveUniformBlockiv", &Return);
	glGetActiveUniformBlockName=glGetProcAddress("glGetActiveUniformBlockName", &Return);
	glUniformBlockBinding=glGetProcAddress("glUniformBlockBinding", &Return);
	glDrawElementsBaseVertex=glGetProcAddress("glDrawElementsBaseVertex", &Return);
	glDrawRangeElementsBaseVertex=glGetProcAddress("glDrawRangeElementsBaseVertex", &Return);
	glDrawElementsInstancedBaseVertex=glGetProcAddress("glDrawElementsInstancedBaseVertex", &Return);
	glMultiDrawElementsBaseVertex=glGetProcAddress("glMultiDrawElementsBaseVertex", &Return);
	glProvokingVertex=glGetProcAddress("glProvokingVertex", &Return);
	glFenceSync=glGetProcAddress("glFenceSync", &Return);
	glIsSync=glGetProcAddress("glIsSync", &Return);
	glDeleteSync=glGetProcAddress("glDeleteSync", &Return);
	glClientWaitSync=glGetProcAddress("glClientWaitSync", &Return);
	glWaitSync=glGetProcAddress("glWaitSync", &Return);
	glGetInteger64v=glGetProcAddress("glGetInteger64v", &Return);
	glGetSynciv=glGetProcAddress("glGetSynciv", &Return);
	glGetInteger64i_v=glGetProcAddress("glGetInteger64i_v", &Return);
	glGetBufferParameteri64v=glGetProcAddress("glGetBufferParameteri64v", &Return);
	glFramebufferTexture=glGetProcAddress("glFramebufferTexture", &Return);
	glTexImage2DMultisample=glGetProcAddress("glTexImage2DMultisample", &Return);
	glTexImage3DMultisample=glGetProcAddress("glTexImage3DMultisample", &Return);
	glGetMultisamplefv=glGetProcAddress("glGetMultisamplefv", &Return);
	glSampleMaski=glGetProcAddress("glSampleMaski", &Return);
	glBindFragDataLocationIndexed=glGetProcAddress("glBindFragDataLocationIndexed", &Return);
	glGetFragDataIndex=glGetProcAddress("glGetFragDataIndex", &Return);
	glGenSamplers=glGetProcAddress("glGenSamplers", &Return);
	glDeleteSamplers=glGetProcAddress("glDeleteSamplers", &Return);
	glIsSampler=glGetProcAddress("glIsSampler", &Return);
	glBindSampler=glGetProcAddress("glBindSampler", &Return);
	glSamplerParameteri=glGetProcAddress("glSamplerParameteri", &Return);
	glSamplerParameteriv=glGetProcAddress("glSamplerParameteriv", &Return);
	glSamplerParameterf=glGetProcAddress("glSamplerParameterf", &Return);
	glSamplerParameterfv=glGetProcAddress("glSamplerParameterfv", &Return);
	glSamplerParameterIiv=glGetProcAddress("glSamplerParameterIiv", &Return);
	glSamplerParameterIuiv=glGetProcAddress("glSamplerParameterIuiv", &Return);
	glGetSamplerParameteriv=glGetProcAddress("glGetSamplerParameteriv", &Return);
	glGetSamplerParameterIiv=glGetProcAddress("glGetSamplerParameterIiv", &Return);
	glGetSamplerParameterfv=glGetProcAddress("glGetSamplerParameterfv", &Return);
	glGetSamplerParameterIuiv=glGetProcAddress("glGetSamplerParameterIuiv", &Return);
	glQueryCounter=glGetProcAddress("glQueryCounter", &Return);
	glGetQueryObjecti64v=glGetProcAddress("glGetQueryObjecti64v", &Return);
	glGetQueryObjectui64v=glGetProcAddress("glGetQueryObjectui64v", &Return);
	glVertexAttribDivisor=glGetProcAddress("glVertexAttribDivisor", &Return);
	glVertexAttribP1ui=glGetProcAddress("glVertexAttribP1ui", &Return);
	glVertexAttribP1uiv=glGetProcAddress("glVertexAttribP1uiv", &Return);
	glVertexAttribP2ui=glGetProcAddress("glVertexAttribP2ui", &Return);
	glVertexAttribP2uiv=glGetProcAddress("glVertexAttribP2uiv", &Return);
	glVertexAttribP3ui=glGetProcAddress("glVertexAttribP3ui", &Return);
	glVertexAttribP3uiv=glGetProcAddress("glVertexAttribP3uiv", &Return);
	glVertexAttribP4ui=glGetProcAddress("glVertexAttribP4ui", &Return);
	glVertexAttribP4uiv=glGetProcAddress("glVertexAttribP4uiv", &Return);

	// Something went horribly wrong, or incomplete GL3.3 support
	if(!Return)
		return;

	GLExtensionsInitialized_Flag=1;
}

#ifdef WIN32
void WGLSetupExtensions(void)
{
	int Return=1;
	char *WGLExtensionString=NULL;

	wglGetExtensionsStringARB=glGetProcAddress("wglGetExtensionsStringARB", &Return);

	if(Return)
		WGLExtensionString=(char *)wglGetExtensionsStringARB(wglGetCurrentDC());

	if(FindSubString(WGLExtensionString, "WGL_ARB_create_context_profile"))
		WGL_ARB_create_context_profile_Flag=1;

	if(FindSubString(WGLExtensionString, "WGL_ARB_create_context_robustness"))
		WGL_ARB_create_context_robustness_Flag=1;

	if(FindSubString(WGLExtensionString, "WGL_ARB_create_context"))
	{
		Return=1;

		wglCreateContextAttribsARB=glGetProcAddress("wglCreateContextAttribsARB", &Return);

		if(Return)
			WGL_ARB_create_context_Flag=1;
	}

	if(FindSubString(WGLExtensionString, "WGL_ARB_framebuffer_sRGB"))
		WGL_ARB_framebuffer_sRGB_Flag=1;

	if(FindSubString(WGLExtensionString, "WGL_ARB_make_current_read"))
	{
		Return=1;

		wglMakeContextCurrentARB=glGetProcAddress("wglMakeContextCurrentARB", &Return);
		wglGetCurrentReadDCARB=glGetProcAddress("wglGetCurrentReadDCARB", &Return);

		if(Return)
			WGL_ARB_make_current_read_Flag=1;
	}

	if(FindSubString(WGLExtensionString, "WGL_ARB_multisample"))
		WGL_ARB_multisample_Flag=1;

	if(FindSubString(WGLExtensionString, "WGL_ARB_pixel_format"))
	{
		Return=1;

		wglGetPixelFormatAttribivARB=glGetProcAddress("wglGetPixelFormatAttribivARB", &Return);
		wglGetPixelFormatAttribfvARB=glGetProcAddress("wglGetPixelFormatAttribfvARB", &Return);
		wglChoosePixelFormatARB=glGetProcAddress("wglChoosePixelFormatARB", &Return);

		if(Return)
			WGL_ARB_pixel_format_Flag=1;
	}

	WGLExtensionsInitialized_Flag=1;
}
#else
void GLXSetupExtensions(Display *dpy)
{
	int Return=1;
	char *GLXExtensionString=NULL;

	GLXExtensionString=(char *)glXQueryExtensionsString(dpy, DefaultScreen(dpy));

	if(FindSubString(GLXExtensionString, "GLX_ARB_create_context"))
	{
		glXCreateContextAttribsARB=glGetProcAddress("glXCreateContextAttribsARB", &Return);

		if(Return)
			GLX_ARB_create_context_Flag=1;
	}

	if(FindSubString(GLXExtensionString, "GLX_ARB_create_context_profile"))
		GLX_ARB_create_context_profile_Flag=1;

	if(FindSubString(GLXExtensionString, "GLX_ARB_create_context_robustness"))
		GLX_ARB_create_context_robustness_Flag=1;

	if(FindSubString(GLXExtensionString, "GLX_ARB_framebuffer_sRGB"))
		GLX_ARB_framebuffer_sRGB_Flag=1;

	if(FindSubString(GLXExtensionString, "GLX_ARB_multisample"))
		GLX_ARB_multisample_Flag=1;

	GLXExtensionsInitialized_Flag=1;
}
#endif

int CreateContext(GLContext_t *Context, int Color, int Depth, int Stencil, int Accum, unsigned long Flags)
{
#ifdef WIN32
	int PixelFormat;
	unsigned int NumFormats;
	int Attrib[128], i=0;
	int ContextAttribs[8];

	if(!(GLExtensionsInitialized_Flag||WGLExtensionsInitialized_Flag))
	{
		PIXELFORMATDESCRIPTOR pfd;
		HWND hWndTemp=NULL;
		HDC hDCTemp=NULL;
		HGLRC hRCTemp=NULL;

		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion=1;
		pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL;
		pfd.iPixelType=PFD_TYPE_RGBA;
		pfd.cColorBits=32;
		pfd.cDepthBits=24;
		pfd.iLayerType=PFD_MAIN_PLANE;
		
		hWndTemp=CreateWindow("static", NULL, WS_POPUP, 0, 0, 1, 1, NULL, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);
		hDCTemp=GetDC(hWndTemp);

		if(!(PixelFormat=ChoosePixelFormat(hDCTemp, &pfd)))
		{
			MessageBox(Context->hWnd, "ChoosePixelFormat Failed!", NULL, MB_OK);
			return 0;
		}

		if(!SetPixelFormat(hDCTemp, PixelFormat, NULL))
		{
			MessageBox(Context->hWnd, "SetPixelFormat Failed!", NULL, MB_OK);
			return 0;
		}

		if(!(hRCTemp=wglCreateContext(hDCTemp)))
		{
			MessageBox(Context->hWnd, "wglCreateContext Failed!", NULL, MB_OK);
			return 0;
		}


		if(!wglMakeCurrent(hDCTemp, hRCTemp))
		{
			MessageBox(Context->hWnd, "wglMakeCurrent Failed!", NULL, MB_OK);
			return 0;
		}

		if(!GLExtensionsInitialized_Flag)
			GLSetupExtensions();

		if(!WGLExtensionsInitialized_Flag)
			WGLSetupExtensions();

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRCTemp);
		ReleaseDC(hWndTemp, hDCTemp);
		DestroyWindow(hWndTemp);
	}

	if(!WGL_ARB_pixel_format_Flag)
		return 0;

	Context->hDC=GetDC(Context->hWnd);

	Attrib[i++]=WGL_DRAW_TO_WINDOW_ARB;
	Attrib[i++]=TRUE;
	Attrib[i++]=WGL_SUPPORT_OPENGL_ARB;
	Attrib[i++]=TRUE;

	if(Flags&OGL_SINGLEBUFFER)
	{
		Attrib[i++]=WGL_DOUBLE_BUFFER_ARB;
		Attrib[i++]=FALSE;
	}

	if(Flags&OGL_DOUBLEBUFFER)
	{
		Attrib[i++]=WGL_DOUBLE_BUFFER_ARB;
		Attrib[i++]=TRUE;
	}

	Attrib[i++]=WGL_PIXEL_TYPE_ARB;
	Attrib[i++]=WGL_TYPE_RGBA_ARB;

	Attrib[i++]=WGL_COLOR_BITS_ARB;
	Attrib[i++]=Color;
	Attrib[i++]=WGL_ACCUM_BITS_ARB;
	Attrib[i++]=Accum;
	Attrib[i++]=WGL_DEPTH_BITS_ARB;
	Attrib[i++]=Depth;
	Attrib[i++]=WGL_STENCIL_BITS_ARB;
	Attrib[i++]=Stencil;

	if(Flags&OGL_AUXBUFFERS1)
	{
		Attrib[i++]=WGL_AUX_BUFFERS_ARB;
		Attrib[i++]=1;
	}

	if(Flags&OGL_AUXBUFFERS2)
	{
		Attrib[i++]=WGL_AUX_BUFFERS_ARB;
		Attrib[i++]=2;
	}

	if(Flags&OGL_AUXBUFFERS3)
	{
		Attrib[i++]=WGL_AUX_BUFFERS_ARB;
		Attrib[i++]=3;
	}

	if(Flags&OGL_AUXBUFFERS4)
	{
		Attrib[i++]=WGL_AUX_BUFFERS_ARB;
		Attrib[i++]=4;
	}

	if(WGL_ARB_multisample_Flag)
	{
		if(Flags&OGL_SAMPLES2X)
		{
			Attrib[i++]=WGL_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=TRUE;
			Attrib[i++]=WGL_SAMPLES_ARB;
			Attrib[i++]=2;
		}

		if(Flags&OGL_SAMPLES4X)
		{
			Attrib[i++]=WGL_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=TRUE;
			Attrib[i++]=WGL_SAMPLES_ARB;
			Attrib[i++]=4;
		}

		if(Flags&OGL_SAMPLES6X)
		{
			Attrib[i++]=WGL_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=TRUE;
			Attrib[i++]=WGL_SAMPLES_ARB;
			Attrib[i++]=6;
		}

		if(Flags&OGL_SAMPLES8X)
		{
			Attrib[i++]=WGL_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=TRUE;
			Attrib[i++]=WGL_SAMPLES_ARB;
			Attrib[i++]=8;
		}
	}

	Attrib[i++]=0;

	if(!wglChoosePixelFormatARB(Context->hDC, Attrib, NULL, 1, &PixelFormat, &NumFormats))
	{
		MessageBox(Context->hWnd, "wglChoosePixelFormatARB failed!", NULL, MB_OK);
		return 0;
	}

	if(!SetPixelFormat(Context->hDC, PixelFormat, NULL))
	{
		MessageBox(Context->hWnd, "SetPixelFormat Failed!", NULL, MB_OK);
		return 0;
	}

	if(Flags&OGL_CORE33)
	{
		if(WGL_ARB_create_context_Flag)
		{
			i=0;
			ContextAttribs[i++]=WGL_CONTEXT_MAJOR_VERSION_ARB;
			ContextAttribs[i++]=3;
			ContextAttribs[i++]=WGL_CONTEXT_MINOR_VERSION_ARB;
			ContextAttribs[i++]=3;
			ContextAttribs[i++]=WGL_CONTEXT_FLAGS_ARB;
			ContextAttribs[i++]=WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
			ContextAttribs[i++]=0;

			if(!(Context->hRC=wglCreateContextAttribsARB(Context->hDC, 0, ContextAttribs)))
			{
				MessageBox(Context->hWnd, "wglCreateContextAttribsARB Failed!", NULL, MB_OK);
				return 0;
			}
		}
		else
		{
			MessageBox(Context->hWnd, "Requested OpenGL 3.3 CORE, WGL_ARB_create_context not supported!", NULL, MB_OK);
			return 0;
		}
	}
	else
	{
		if(!(Context->hRC=wglCreateContext(Context->hDC)))
		{
			MessageBox(Context->hWnd, "wglCreateContext Failed!", NULL, MB_OK);
			return 0;
		}
	}

	if(!wglMakeCurrent(Context->hDC, Context->hRC))
	{
		MessageBox(Context->hWnd, "wglMakeCurrent Failed!", NULL, MB_OK);
		return 0;
	}

	return 1;
#else
	int i, Attrib[128];
	int ContextAttribs[8];
	GLXFBConfig *fbconfig=NULL;

	if(!GLXExtensionsInitialized_Flag)
		GLXSetupExtensions(dpy);

	i=0;
	Attrib[i++]=GLX_X_RENDERABLE,
	Attrib[i++]=True;
	Attrib[i++]=GLX_DRAWABLE_TYPE;
	Attrib[i++]=GLX_WINDOW_BIT;
	Attrib[i++]=GLX_RENDER_TYPE;
	Attrib[i++]=GLX_RGBA_BIT;

	if(Flags&OGL_SINGLEBUFFER)
	{
		Attrib[i++]=GLX_DOUBLEBUFFER;
		Attrib[i++]=False;
	}

	if(Flags&OGL_DOUBLEBUFFER)
	{
		Attrib[i++]=GLX_DOUBLEBUFFER;
		Attrib[i++]=True;
	}

	Attrib[i++]=GLX_BUFFER_SIZE;
	Attrib[i++]=Color;
	Attrib[i++]=GLX_DEPTH_SIZE;
	Attrib[i++]=Depth;
	Attrib[i++]=GLX_STENCIL_SIZE;
	Attrib[i++]=Stencil;

	if(GLX_ARB_multisample_Flag)
	{
		if(Flags&OGL_SAMPLES2X)
		{
			Attrib[i++]=GLX_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=True;
			Attrib[i++]=GLX_SAMPLES_ARB;
			Attrib[i++]=2;
		}

		if(Flags&OGL_SAMPLES4X)
		{
			Attrib[i++]=GLX_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=True;
			Attrib[i++]=GLX_SAMPLES_ARB;
			Attrib[i++]=4;
		}

		if(Flags&OGL_SAMPLES6X)
		{
			Attrib[i++]=GLX_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=True;
			Attrib[i++]=GLX_SAMPLES_ARB;
			Attrib[i++]=6;
		}

		if(Flags&OGL_SAMPLES8X)
		{
			Attrib[i++]=GLX_SAMPLE_BUFFERS_ARB;
			Attrib[i++]=True;
			Attrib[i++]=GLX_SAMPLES_ARB;
			Attrib[i++]=8;
		}
	}

	Attrib[i++]=None;

	if((fbconfig=glXChooseFBConfig(dpy, DefaultScreen(dpy), Attrib, &i))==NULL)
	{
		fprintf(stderr, "Error: glXChooseFBConfig failed\n");
		return 0;
	}

	if(Flags&OGL_CORE33)
	{
		if(GLX_ARB_create_context_Flag)
		{
			i=0;
			ContextAttribs[i++]=GLX_CONTEXT_MAJOR_VERSION_ARB;
			ContextAttribs[i++]=3;
			ContextAttribs[i++]=GLX_CONTEXT_MINOR_VERSION_ARB;
			ContextAttribs[i++]=3;
			ContextAttribs[i++]=GLX_CONTEXT_FLAGS_ARB;
			ContextAttribs[i++]=GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
			ContextAttribs[i++]=None;

			if((Context->ctx=glXCreateContextAttribsARB(dpy, fbconfig[0], NULL, True, ContextAttribs))==NULL)
			{
				fprintf(stderr, "glXCreateContextAttribsARB failed.\n");
				return 0;
			}
		}
		else
		{
			fprintf(stderr, "Error: Requested OpenGL 3.3 CORE, GLX_ARB_create_context not supported!\n");
			return 0;
		}
	}
	else
	{
		if((Context->ctx=glXCreateNewContext(dpy, fbconfig[0], GLX_RGBA, NULL, True))==NULL)
		{
			fprintf(stderr, "Error: glXCreateContext failed\n");
			return 0;
		}
	}

	glXGetFBConfigAttrib(dpy, fbconfig[0], GLX_VISUAL_ID, &Context->visualid);

	if(!GLExtensionsInitialized_Flag)
	{
		glXMakeCurrent(dpy, ((_XPrivDisplay)dpy)->screens[0].root, Context->ctx);
		GLSetupExtensions();
		glXMakeCurrent(dpy, None, NULL);
	}

	XFree(fbconfig);

	return 1;
#endif
}

void DestroyContext(GLContext_t *Context)
{
#ifdef WIN32
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(Context->hRC);
	ReleaseDC(Context->hWnd, Context->hDC);
#else
	glXDestroyContext(dpy, Context->ctx);
#endif

	memset(Context, 0, sizeof(GLContext_t));
}
