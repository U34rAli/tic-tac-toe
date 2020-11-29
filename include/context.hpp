/**
 * @file 
 * @author Benedict R. Gaster
 */
#pragma once

#include <vector>

#include <SDL2/SDL.h>

#include <events.hpp>

namespace uwe {
    class Colour {
    public:
        uint8_t blue_;
        uint8_t green_;
        uint8_t red_;
        uint8_t alpha_;

        Colour(uint8_t red, uint8_t green,  uint8_t  blue, uint8_t alpha):
            red_{red},
            green_{green},
            blue_{blue},
            alpha_{alpha} {
        }

        static Colour red() {
            return Colour{ 255, 0, 0, SDL_ALPHA_OPAQUE };
        }

        static Colour green() {
            return Colour{ 0, 255, 0, SDL_ALPHA_OPAQUE };
        }

        static Colour blue() {
            return Colour{ 0, 0, 255, SDL_ALPHA_OPAQUE };
        }

        static Colour white() {
            return Colour{ 255, 255, 255, SDL_ALPHA_OPAQUE };
        }

        static Colour black() {
            return Colour{ 0, 0, 0, SDL_ALPHA_OPAQUE };
        }
    };

    class Context {
    public:
        /** @brief Create a context
         * @param width an integer setting the window width
         * @param height an integer setting the window height
         */
        Context();

        /// Destory context
        ~Context();

        void init(int width, int height);

        /// Output details of GPU backend and texture formats
        void dump_renderer_info();

        /// run the control loop, returns only when user exits
        //void run(App* app);

        int get_height() const {
            return height_;
        }

        int get_width() const {
            return width_;
        }

        SDL_Window* get_window() const {
            return window_;
        }

        SDL_Renderer* get_renderer() const {
            return renderer_;
        }

        SDL_Texture* get_texture() const {
            return texture_;
        }

        std::vector< uint8_t >& get_pixels() {
            return pixels_;
        }

        uint8_t& pixel(size_t offset) {
            return pixels_[offset];
        }

        void set_pixel(size_t offset, Colour colour) {
            pixels_[offset + 0] = colour.blue_;
            pixels_[offset + 1] = colour.green_;
            pixels_[offset + 2] = colour.red_;
            pixels_[offset + 3] = colour.alpha_;
        }

        int get_tex_width() const {
            return tex_width_;
        }

        int get_tex_height() const {
            return tex_height_;
        }
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

