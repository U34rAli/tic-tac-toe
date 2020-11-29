/**
 * @file 
 * @author Benedict R. Gaster
 */
#pragma once

#include <events.hpp>
#include <context.hpp>

namespace uwe {

    class App {
    private:
        Context context_;

        bool output_framerate_;
    public:
        App();
        ~App();

        void init(int width, int height);
        void run();

        /// toggles output framerate to console
        void toggle_framerate() {
            output_framerate_ = !output_framerate_;
        }

        virtual void begin() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        virtual void key_pressed(Scancode scancode, bool is_repeat) {

        };

        virtual void key_released(Scancode scancode) {
            
        };

        virtual void mouse_pressed() {

        };

        virtual void mouse_released() {
            
        };

        virtual void mouse_moved() {
            
        };

        // API
        int get_framebuffer_width() const {
            return context_.get_tex_width();
        }

        int get_framebuffer_height() const {
            return context_.get_tex_height();
        }

        uint8_t& framebuffer(size_t offset) {
            return context_.pixel(offset);
        }

        void set_framebuffer(size_t offset, Colour colour) {
            context_.set_pixel(offset, colour);
        }

        void clear(Colour colour) {
            SDL_SetRenderDrawColor( 
                context_.get_renderer(), 
                colour.blue_,
                colour.green_,
                colour.red_,
                colour.alpha_ );
            SDL_RenderClear( context_.get_renderer() );
        }
    };

    void run();
} // namespace uwe