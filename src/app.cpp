/**
 * @file 
 * @author Benedict R. Gaster
 */

#include <iostream>
#include <iomanip>
#include <cstring>

#include <app.hpp>

namespace uwe {

    App::App() : 
        output_framerate_{false} {
    }

    App::~App() {

    }

    void App::init(int width, int height) {
        context_.init(width, height);
    }

    void App::run() {
        SDL_Event event;
        bool running = true;
        
        unsigned int frames = 0;
        Uint64 start = SDL_GetPerformanceCounter();

        begin();

        while( running )
        {
            while( SDL_PollEvent( &event ) ) {
                if( ( SDL_QUIT == event.type ) ||
                    ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) ) {
                    running = false;
                    break;
                }
                else if (event.type == SDL_KEYDOWN) {
                    key_pressed(static_cast<Scancode>(event.key.keysym.scancode), event.key.repeat != 0);
                }
                else if (event.type == SDL_KEYUP) {
                    key_released(static_cast<Scancode>(event.key.keysym.scancode));
                }
            }

            update();
            
            draw();
            
            // finally present the renderer to the GPU
            SDL_RenderPresent( context_.get_renderer() );

            frames++;
            if (output_framerate_) {
                const uint64_t end = SDL_GetPerformanceCounter();
                const static uint64_t freq = SDL_GetPerformanceFrequency();
                const double seconds = ( end - start ) / static_cast< double >( freq );
                if( seconds > 2.0 )
                {
                    std::cout
                        << frames << " frames in "
                        << std::setprecision(1) << std::fixed << seconds << " seconds = "
                        << std::setprecision(1) << std::fixed << frames / seconds << " FPS ("
                        << std::setprecision(3) << std::fixed << ( seconds * 1000.0 ) / frames << " ms/frame)"
                        << std::endl;
                    start = end;
                    frames = 0;
                }
            }
        }

    }
} // namespace uwe