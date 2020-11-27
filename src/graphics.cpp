#include <iostream>

#include <graphics.hpp>
#include <iomanip>
#include <cstring>

namespace uwe {

    Context::Context(int width, int height) : 
        width_{width}, 
        height_{height},
        tex_width_{width},
        tex_height_{height},
        pixels_(tex_width_ * tex_height_ * 4, 0) {
        SDL_Init( SDL_INIT_EVERYTHING );

        window_ = SDL_CreateWindow(
            "SDL2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width_, height_,
            SDL_WINDOW_SHOWN);

        renderer_ = SDL_CreateRenderer(
            window_,
            -1,
            SDL_RENDERER_ACCELERATED);

        texture_ = SDL_CreateTexture(
            renderer_,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            tex_width_, 
            tex_height_);
    }

    Context::~Context() {
        SDL_DestroyRenderer( renderer_ );
        SDL_DestroyWindow( window_ );
        SDL_Quit();
    }

    void Context::run() {
        SDL_Event event;
        bool running = true;
        bool useLocktexture = false;
        
        unsigned int frames = 0;
        Uint64 start = SDL_GetPerformanceCounter();

        while( running )
        {

            SDL_SetRenderDrawColor( renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE );
            SDL_RenderClear( renderer_ );

            while( SDL_PollEvent( &event ) ) {
                if( ( SDL_QUIT == event.type ) ||
                    ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
                {
                    running = false;
                    break;
                }
                if( SDL_KEYDOWN == event.type && SDL_SCANCODE_L == event.key.keysym.scancode )
                {
                    useLocktexture = !useLocktexture;
                    std::cout << "Using " << ( useLocktexture ? "SDL_LockTexture() + memcpy()" : "SDL_UpdateTexture()" ) << std::endl;
                }
            }
            
            // splat down some random pixels
            for( unsigned int i = 0; i < 1000; i++ ) {
                const unsigned int x = rand() % tex_width_;
                const unsigned int y = rand() % tex_height_;

                const unsigned int offset = ( tex_width_ * 4 * y ) + x * 4;
                pixels_[ offset + 0 ] = rand() % 256;        // b
                pixels_[ offset + 1 ] = rand() % 256;        // g
                pixels_[ offset + 2 ] = rand() % 256;        // r
                pixels_[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a
            }

            if( useLocktexture ) {
                unsigned char* lockedPixels = nullptr;
                int pitch = 0;
                SDL_LockTexture(
                    texture_,
                    NULL,
                    reinterpret_cast< void** >( &lockedPixels ),
                    &pitch
                    );
                std::memcpy( lockedPixels, pixels_.data(), pixels_.size() );
                SDL_UnlockTexture( texture_ );
            }
            else {
                SDL_UpdateTexture(
                    texture_,
                    NULL,
                    pixels_.data(),
                    tex_width_ * 4);
            }

            SDL_RenderCopy( renderer_, texture_, NULL, NULL );
            SDL_RenderPresent( renderer_ );
            
            frames++;
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

    void Context::dump_renderer_info() {
        SDL_RendererInfo info;
        SDL_GetRendererInfo( renderer_, &info );
        std::cout << "Renderer name: " << info.name << std::endl;
        std::cout << "Texture formats: " << std::endl;
        for( uint32_t i = 0; i < info.num_texture_formats; i++ ) {
            std::cout << SDL_GetPixelFormatName( info.texture_formats[i] ) << std::endl;
        }
    }
}