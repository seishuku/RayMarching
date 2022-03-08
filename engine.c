#include <windows.h>
#include <process.h>
#include <intrin.h>

#pragma intrinsic(__rdtsc)

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "opengl.h"
#include "math.h"
#include "font.h"
#include "image.h"

#ifndef FREE
#define FREE(p) { if(p) { free(p); p=NULL; } }
#endif

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(x) ((char *)NULL+(x))
#endif

GLContext_t Context;

char szAppName[]="OpenGL";

int Width=1024, Height=576;

int Done=0, Key[256];

unsigned __int64 Frequency, StartTime, EndTime;
float avgfps=0.0f, fps=0.0f, fTimeStep, fTime=0.0f;
int Frames=0;

typedef enum
{
	TEXTURE_HDR_REFLECT,

	GLSL_RAYMARCH_SHADER,
	GLSL_RAYMARCH_TEXREFLECT,
	GLSL_RAYMARCH_MV,
	GLSL_RAYMARCH_MVINV,
	GLSL_RAYMARCH_FFOV,
	GLSL_RAYMARCH_FTIME,
	GLSL_RAYMARCH_ISIZE,

	NUM_OBJECTS
} ObjectNames;

unsigned int Objects[NUM_OBJECTS];

unsigned int VAO;

float Projection[16], ModelView[16], MVP[16];

float QuatX[4], QuatY[4], Quat[4];

float RotateX=0.0f, RotateY=0.0f;
float PanX=0.0f, PanY=0.0f, Zoom=400.0f;

void Render(void);
int Init(void);
GLuint CreateProgram(char *VertexFilename, char *FragmentFilename);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

unsigned __int64 rdtsc(void)
{
	return __rdtsc();
}

unsigned __int64 GetFrequency(void)
{
	unsigned __int64 TimeStart, TimeStop, TimeFreq;
	unsigned __int64 StartTicks, StopTicks;
	volatile unsigned __int64 i;

	QueryPerformanceFrequency((LARGE_INTEGER *)&TimeFreq);

	QueryPerformanceCounter((LARGE_INTEGER *)&TimeStart);
	StartTicks=rdtsc();

	for(i=0;i<1000000;i++);

	StopTicks=rdtsc();
	QueryPerformanceCounter((LARGE_INTEGER *)&TimeStop);

	return (StopTicks-StartTicks)*TimeFreq/(TimeStop-TimeStart);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASS wc;
	MSG msg;
	RECT Rect;

	wc.style=CS_VREDRAW|CS_HREDRAW|CS_OWNDC;
	wc.lpfnWndProc=WndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor=LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground=GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=szAppName;

	RegisterClass(&wc);

	SetRect(&Rect, 0, 0, Width, Height);
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

	Context.hWnd=CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS, CW_USEDEFAULT, CW_USEDEFAULT, Rect.right-Rect.left, Rect.bottom-Rect.top, NULL, NULL, hInstance, NULL);

	ShowWindow(Context.hWnd, SW_SHOW);
	SetForegroundWindow(Context.hWnd);

	if(!CreateContext(&Context, 32, 24, 0, 0, OGL_CORE33|OGL_DOUBLEBUFFER))
	{
		DestroyWindow(Context.hWnd);

		return -1;
	}

	if(!Init())
	{
		DestroyContext(&Context);
		DestroyWindow(Context.hWnd);

		return -1;
	}

	Frequency=GetFrequency();

	while(!Done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message==WM_QUIT)
				Done=1;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			StartTime=rdtsc();
			Render();
			SwapBuffers(Context.hDC);
			EndTime=rdtsc();

			fTimeStep=(float)(EndTime-StartTime)/Frequency;
			fTime+=fTimeStep;
			avgfps+=1.0f/fTimeStep;

			if(Frames++>100)
			{
				fps=avgfps/Frames;
				avgfps=0.0f;
				Frames=0;
			}
		}
	}

	Font_Destroy();

	DestroyContext(&Context);
	DestroyWindow(Context.hWnd);

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static POINT old;
	POINT pos, delta;

	switch(uMsg)
	{
		case WM_CREATE:
			break;

		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_DESTROY:
			break;

		case WM_SIZE:
			Width=LOWORD(lParam);
			Height=HIWORD(lParam);
			break;

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			SetCapture(hWnd);
			ShowCursor(FALSE);

			GetCursorPos(&pos);
			old.x=pos.x;
			old.y=pos.y;
			break;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
			ShowCursor(TRUE);
			ReleaseCapture();
			break;

		case WM_MOUSEMOVE:
			GetCursorPos(&pos);

			if(!wParam)
			{
				old.x=pos.x;
				old.y=pos.y;
				break;
			}

			delta.x=pos.x-old.x;
			delta.y=old.y-pos.y;

			if(!delta.x&&!delta.y)
				break;

			SetCursorPos(old.x, old.y);

			switch(wParam)
			{
				case MK_LBUTTON:
					RotateX+=delta.x;
					RotateY-=delta.y;
					break;

				case MK_MBUTTON:
					PanX+=delta.x;
					PanY+=delta.y;
					break;

				case MK_RBUTTON:
					Zoom+=delta.y;
					break;
			}
			break;

		case WM_KEYDOWN:
			Key[wParam]=1;

			switch(wParam)
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;

				default:
					break;
			}
			break;

		case WM_KEYUP:
			Key[wParam]=0;
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

unsigned int TransformsID;
unsigned int QuadVAO, QuadVertID;
unsigned int MDI;

float QuadVerts[]=
{
	-1.0f, 1.0f, 0.0f,
	-1.0f,-1.0f, 0.0f,
	 1.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f
};

void DrawModel(void)
{
	glBindVertexArray(QuadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3*4);
}

void BuildVBO(void)
{
	glGenVertexArrays(1, &QuadVAO);
	glBindVertexArray(QuadVAO);

	// Generate vertex buffer object and bind it
	glGenBuffers(1, &QuadVertID);
	glBindBuffer(GL_ARRAY_BUFFER, QuadVertID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*4, QuadVerts, GL_STATIC_DRAW);

	// Set vertex attribute pointer layouts
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));	//Vertex
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Set viewport
	glViewport(0, 0, Width, Height);

	// Set up model view matrix (translate and rotation)
	MatrixIdentity(ModelView);
	MatrixTranslate(PanX, PanY, Zoom, ModelView);

	QuatAngle(RotateX, 0.0f, 1.0f, 0.0f, QuatX);
	QuatAngle(RotateY, 1.0f, 0.0f, 0.0f, QuatY);
	QuatMultiply(QuatX, QuatY, Quat);
	QuatMatrix(Quat, ModelView);

	// Select the shader program
	glUseProgram(Objects[GLSL_RAYMARCH_SHADER]);

	glUniform1i(Objects[GLSL_RAYMARCH_TEXREFLECT], 0);

	glUniformMatrix4fv(Objects[GLSL_RAYMARCH_MV], 1, GL_FALSE, ModelView);

	MatrixInverse(ModelView, ModelView); // Inverse modelview matrix
	glUniformMatrix4fv(Objects[GLSL_RAYMARCH_MVINV], 1, GL_FALSE, ModelView);

	glUniform1f(Objects[GLSL_RAYMARCH_FFOV], 90.0f);
	glUniform2i(Objects[GLSL_RAYMARCH_ISIZE], Width, Height);

	glUniform1f(Objects[GLSL_RAYMARCH_FTIME], fTime);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Objects[TEXTURE_HDR_REFLECT]);

	DrawModel();

	glActiveTexture(GL_TEXTURE0);

	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	Font_Print(0.0f, 0.0f, "FPS: %0.1f", fps);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

int Init(void)
{
	Objects[TEXTURE_HDR_REFLECT]=Image_Upload("grace.tga", IMAGE_RGBE|IMAGE_CUBEMAP_ANGULAR|IMAGE_CLAMP);

	// Load shaders
	Objects[GLSL_RAYMARCH_SHADER]=CreateProgram("raymarch_v.glsl", "raymarch_f.glsl");

	glUseProgram(Objects[GLSL_RAYMARCH_SHADER]);
	Objects[GLSL_RAYMARCH_MV]=glGetUniformLocation(Objects[GLSL_RAYMARCH_SHADER], "mv");
	Objects[GLSL_RAYMARCH_MVINV]=glGetUniformLocation(Objects[GLSL_RAYMARCH_SHADER], "mvinv");
	Objects[GLSL_RAYMARCH_FFOV]=glGetUniformLocation(Objects[GLSL_RAYMARCH_SHADER], "fFOV");
	Objects[GLSL_RAYMARCH_ISIZE]=glGetUniformLocation(Objects[GLSL_RAYMARCH_SHADER], "iSize");
	Objects[GLSL_RAYMARCH_FTIME]=glGetUniformLocation(Objects[GLSL_RAYMARCH_SHADER], "fTime");
	Objects[GLSL_RAYMARCH_TEXREFLECT]=glGetUniformLocation(Objects[GLSL_RAYMARCH_SHADER], "TexReflect");

	BuildVBO();

	// Set OpenGL states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	return 1;
}

int LoadShader(GLuint Shader, char *Filename)
{
	FILE *stream=NULL;
	char *buffer=NULL;
	size_t length;

	if((stream=fopen(Filename, "rb"))==NULL)
		return 0;

	fseek(stream, 0, SEEK_END);
	length=ftell(stream);
	fseek(stream, 0, SEEK_SET);

	buffer=(char *)malloc(length+1);

	if(buffer==NULL)
		return 0;

	fread(buffer, 1, length, stream);
	buffer[length]='\0';

	glShaderSource(Shader, 1, (const char **)&buffer, NULL);

	fclose(stream);
	free(buffer);

	return 1;
}

GLuint CreateProgram(char *VertexFilename, char *FragmentFilename)
{
	GLuint Program, Vertex, Fragment;
	GLint _Status, LogLength;
	char *Log=NULL;

	Program=glCreateProgram();

	if(VertexFilename)
	{
		Vertex=glCreateShader(GL_VERTEX_SHADER);

		if(LoadShader(Vertex, VertexFilename))
		{
			glCompileShader(Vertex);
			glGetShaderiv(Vertex, GL_COMPILE_STATUS, &_Status);

			if(!_Status)
			{
				glGetShaderiv(Vertex, GL_INFO_LOG_LENGTH, &LogLength);
				Log=(char *)malloc(LogLength);

				if(Log)
				{
					glGetShaderInfoLog(Vertex, LogLength, NULL, Log);
#ifdef WIN32
					MessageBox(Context.hWnd, Log, VertexFilename, MB_OK);
#else
					fprintf(stderr, "%s - %s\n", VertexFilename, Log);
#endif

					free(Log);
				}
			}
			else
				glAttachShader(Program, Vertex);
		}

		glDeleteShader(Vertex);
	}

	if(FragmentFilename)
	{
		Fragment=glCreateShader(GL_FRAGMENT_SHADER);

		if(LoadShader(Fragment, FragmentFilename))
		{
			glCompileShader(Fragment);
			glGetShaderiv(Fragment, GL_COMPILE_STATUS, &_Status);

			if(!_Status)
			{
				glGetShaderiv(Fragment, GL_INFO_LOG_LENGTH, &LogLength);
				Log=(char *)malloc(LogLength);

				if(Log)
				{
					glGetShaderInfoLog(Fragment, LogLength, NULL, Log);
#ifdef WIN32
					MessageBox(Context.hWnd, Log, FragmentFilename, MB_OK);
#else
					fprintf(stderr, "%s - %s\n", FragmentFilename, Log);
#endif

					free(Log);
				}
			}
			else
				glAttachShader(Program, Fragment);
		}

		glDeleteShader(Fragment);
	}

	glLinkProgram(Program);
	glGetProgramiv(Program, GL_LINK_STATUS, &_Status);

	if(!_Status)
	{
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &LogLength);
		Log=(char *)malloc(LogLength);

		if(Log)
		{
			glGetProgramInfoLog(Program, LogLength, NULL, Log);
#ifdef WIN32
			MessageBox(Context.hWnd, Log, "Link", MB_OK);
#else
			fprintf(stderr, "Link - %s\n", Log);
#endif

			free(Log);
		}
	}

	return Program;
}
