// Include SDL headers
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#undef main

// Include ImGui headers
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl2.h>
#include <imgui/imgui_impl_sdl.h>


int main(int argc, char** argv)
{
	// Init all SDL's internal stuff
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create the SDL window, in the centre of the screen, with a width&height of 800x600 that is capable of using OpenGL & is resizable
	SDL_Window* window = SDL_CreateWindow(
		"<Project Title>", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		800, 600, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	// Create the OpenGL context
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// Init ImGui for OpenGL2 and SDL
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL2_Init();
	
	// Show the SDL window
	SDL_ShowWindow(window);

	bool running = true;
	while (running) // Main loop
	{
		// SDL event loop
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			// Let ImGui handle any events that it needs to
			ImGui_ImplSDL2_ProcessEvent(&e);

			// Process any events we need to respond to ourselves.
			switch (e.type)
			{
			case SDL_QUIT: // e.g The user has presses the X button
				running = false;
				break;
			}
		}

		// Start ImGui rendering for this frame.
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		// ANY IMGUI CALLS GO BETWEEN HERE...

		ImGui::ShowDemoWindow();

		ImGui::Begin("OpenGL Version");
			ImGui::Text("%s\n%s\n%s", glGetString(GL_VERSION), glGetString(GL_RENDERER), glGetString(GL_VENDOR));
		ImGui::End();

		// ... AND HERE

		// Render the ImGui stuff to the screen
		ImGui::Render(); // render any imgui internal state to a big internal buffer
		glClear(GL_COLOR_BUFFER_BIT); // clear the screen
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData()); // draw that big internal imgui buffer to the screen.

		// Swap the front and back buffers
		SDL_GL_SwapWindow(window);
	}

	// Cleanup any ImGui resources
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	// Clean up any SDL resources (GL context & window explicitly)
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	// return 0 - all has done successfully
	return 0;
}