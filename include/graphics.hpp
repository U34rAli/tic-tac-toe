/**
 * @file 
 * @author Benedict R. Gaster
 */
#pragma once

#include <vector>

#include <SDL2/SDL.h>

namespace uwe {
    class Context {
    public:
        /** @brief Create a context
         * @param width an integer setting the window width
         * @param height an integer setting the window height
         */
        Context(int width, int height);

        /// Destory context
        ~Context();

        /// Output details of GPU backend and texture formats
        void dump_renderer_info();

        /// run the control loop, returns only when user exits
        void run();
    private:
        int height_;                ///< window height
        int width_;                 ///< window width
        int tex_width_;             ///< texture width
        int tex_height_;            ///< texture height
        SDL_Window* window_;        ///< window handle
        SDL_Renderer* renderer_;    ///< graphics backend handle
        SDL_Texture* texture_;      ///< pixel buffer texture handle

        std::vector< uint8_t > pixels_; ///< pixels representing framebuffer
    };
}

