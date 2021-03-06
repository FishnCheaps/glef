#pragma once
//Standart libs
#include "common/commonIncludes.h"

//Glef libs
#include "GlefCollor.hpp"
#include "GlefWindow.hpp"
#include "GlefEnums.hpp"
#include "GlefModel.hpp"
#include "GlefObject.hpp"
#include "GlefCamera.hpp"
#include "GlefRenderEngine.hpp"
using namespace glm;

class Glef {
public:
	/** Initialize Glef API
	@param samples Define amount of fragments per shader (default 4)
	@param major_version Define version of OpenGL, that should be used
	@param minor_version Define versin of OpenGL, that should be used if major version was no found
	@returns Refference to Glef instance
	*/
	static Glef& use(int samples = 4, float major_version = 3, float minor_version = 3)
	{
		static Glef instance;
		return instance;
	}
	Glef(Glef const&) = delete;
	void operator=(Glef const&) = delete;

	/** Create new window
	@param title Define window title. (New Window by default)
	@param width Window width (1024 by default)
	@param height Window height (768 by default)
	@returns Status of window creation (glef_status) OK-if window was successfully created or ERROR-if there was error uppon creation
	*/
	glef_status CreateWindow(std::string title="New Window",int width= 1024, int height=768)
	{
		GfWindow window;
		window.window_ptr = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window.window_ptr == NULL) {
			std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\
						 Try the 2.1 version of the tutorials." << std::endl;
			getchar();
			glfwTerminate();
			return ERROR;
		}
		windows.push_back(window);
		return OK;
	}
	std::vector<GfLight*> lights;
	/** Create new window and set is as active
	@param title Define window title. (New Window by default)
	@param width Window width (1024 by default)
	@param height Window height (768 by default)
	@returns Status of window creation (glef_status) OK-if window was successfully created or ERROR-if there was error uppon creation
	*/
	glef_status CreateAndMakeActiveWindow(std::string title = "New Window", int width = 1024, int height = 768)
	{
		GfWindow window;
		window.window_ptr = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window.window_ptr == NULL) {
			std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\
						 Try the 2.1 version of the tutorials." << std::endl;
			getchar();
			glfwTerminate();
			return ERROR;
		}
		glfwMakeContextCurrent(window.window_ptr);
		windows.push_back(window);
		active_window = window;

		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize GLEW" << std::endl;
			getchar();
			glfwTerminate();
			//status = ERROR;
		}
		glfwSetInputMode(window.window_ptr, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(window.window_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwPollEvents();
		glfwSetCursorPos(window.window_ptr, 1024 / 2, 768 / 2);
		return OK;
	}
	/** Get currently active window
	@returns Current window instance
	*/
	GfWindow getActiveWindow() 
	{
		return active_window;
	}
	/** Drow all frames inside
	@param camera Camera that will be used to render
	*/
	void Proceed(GfCameraActive *camera) {
		active_window.setBackgroundCollor(GfCollorFactory::use().getCollor(Blue));

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		for (auto i = 0; i<objects.size(); i++)
		{
			objects[i]->init();
			camera->preProcessObject(objects[i]);			
		}
		GfRenderEngine GRE;
		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Enable depth test
			GRE.computeCameraMatricesFromInputs(camera, &active_window, &(camera->controls));
			for (auto i=0;i<objects.size();i++)
			{
				if (objects[i]->force != nullptr)
					GRE.computeModelMatricesFromForce(objects[i], &active_window, objects[i]->force);
				//objects[i]->proceed();
				//objects[i]->useElement(camera,&active_window);
				if (objects[i]->is_textured&&lights.size() == 0)
					GRE.RenderModelWithMovableCameraForEveryObjectTextured(objects[i], objects[i]->textureFromModelTMP(), camera, &active_window, &camera->controls, objects[i]->shader);
				else if (objects[i]->is_textured)
					GRE.RenderModelWithMovableCameraForLight(objects[i], objects[i]->textureFromModelTMP(), camera, &active_window, &camera->controls, objects[i]->shader,lights[0]);
				else
					GRE.RenderModelWithMovableCameraForEveryObjectColored(objects[i], camera, &active_window, &camera->controls, objects[i]->shader);
			}

			glfwSwapBuffers(Glef::use().getActiveWindow().window_ptr);
			glfwPollEvents();

		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(Glef::use().getActiveWindow().window_ptr, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(Glef::use().getActiveWindow().window_ptr) == 0);

		// Close OpenGL window and terminate GLFW
		glfwTerminate();
		return;
	}
	/** Drow all frames inside
	@param camera Camera that will be used to render
	*/
	void Proceed(GfCamera *camera) {
		active_window.setBackgroundCollor(GfCollorFactory::use().getCollor(Blue));

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		for (auto i = 0; i<objects.size(); i++)
		{
			objects[i]->init();
			camera->preProcessObject(objects[i]);
		}

		do {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Enable depth test
			for (auto i = 0; i<objects.size(); i++)
			{
				objects[i]->proceed();
			}

			glfwSwapBuffers(Glef::use().getActiveWindow().window_ptr);
			glfwPollEvents();

		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(Glef::use().getActiveWindow().window_ptr, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(Glef::use().getActiveWindow().window_ptr) == 0);

		// Close OpenGL window and terminate GLFW
		glfwTerminate();
		return;
	}
	
	
	void addObject(GfModel &obj)
	{
		objects.push_back(&obj);
	}
private:
	Glef(int samples=4, float major_version = 3, float minor_version = 3)
	{
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW" << std::endl;
			getchar();
			status = ERROR;
		}

		glfwWindowHint(GLFW_SAMPLES, samples);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	}
	GfWindow active_window;
	std::vector <GfWindow> windows;
	glef_status status = UNKNOWN;
	std::vector<GfModel*> objects;
};