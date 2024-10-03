#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>
namespace SDL2
{
	//SDL.h
	int INIT(Uint32 flags)
	{
		return SDL_Init(flags); //initializes SDL library.
		// returns -ve on failure
		//also: SDL_InitSubSystem(flags);
		/*
		flags:
			SDL_INIT_TIMER: timer subsystem
			SDL_INIT_AUDIO: audio subsystem
			SDL_INIT_VIDEO: video subsystem; automatically initializes the events subsystem
			SDL_INIT_JOYSTICK: joystick subsystem; automatically initializes the events subsystem
			SDL_INIT_HAPTIC: haptic (force feedback) subsystem
			SDL_INIT_GAMECONTROLLER: controller subsystem; automatically initializes the joystick subsystem
			SDL_INIT_EVENTS: events subsystem
			SDL_INIT_EVERYTHING: all of the above subsystems
			SDL_INIT_NOPARACHUTE: compatibility; this flag is ignored
		*/
	}
	void QUIT_sub(Uint32 flags)
	{
		return SDL_QuitSubSystem(flags);
	}
	void QUIT()
	{
		return SDL_Quit(); //shutdowns each and every subsystem
	}
	Uint32 WASINIT(Uint32 flags)
	{
		return SDL_WasInit(flags);
	}
	//
	//SDL_error.h
	void Clr_ERR()
	{
		return SDL_ClearError();
	}
	const char* Get_ERR()
	{
		return SDL_GetError();
	}
	//
	//SDL_Surface.h
	int cpysurf(SDL_Surface * src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) //makes scaled copy of a surface
	{
		return SDL_BlitScaled(src, srcrect, dst, dstrect);
	}
	int f_cpysurf(SDL_Surface * src, const SDL_Rect* srcrect, SDL_Surface* dst, SDL_Rect* dstrect) //a fast surface copy
	{
		return SDL_BlitSurface(src, srcrect, dst, dstrect);
	}
	SDL_Surface* Load_bmp(const char* file)
	{
		return SDL_LoadBMP(file);
	}
	int Save_bmp(SDL_Surface* surface, const char* file)
	{
		return SDL_SaveBMP(surface, file);
	}
	/*
	struct SDL_Surface:
	{
		Uint32 flags; (internal use)
		SDL_PixelFormat* format; (the format of the pixels stored in the surface; see SDL_PixelFormat for details (read-only)
		int w, h; (the width and height in pixels (read-only))
		int pitch; (the length of a row of pixels in bytes (read-only))
		void* pixels; (the pointer to the actual pixel data; see Remarks for details (read-write))
		void* userdata; (an arbitrary pointer you can set (read-write))
		int locked; (used for surfaces that require locking (internal use))
		void* lock_data; (used for surfaces that require locking (internal use))
		SDL_Rect clip_rect; (an SDL_Rect structure used to clip blits to the surface which can be set by SDL_SetClipRect() (read-only))
		SDL_BlitMap* map; (info for fast blit mapping to other surfaces (internal use))
		int refcount; (reference count that can be incremented by the application)
	}
	*/
	//
	//SDL_event.h
	/*
	SDL_bool QuitReq()
	{
		return SDL_QuitRequested();
	}
	*/
	int Poll_E(SDL_Event * event)
	{
		return SDL_PollEvent(event);
	}
	//
	//SDL_Clipboard.h
	char* getClipboardText()
	{
		return SDL_GetClipboardText();
	}
	SDL_bool hasClipboardText()
	{
		return SDL_HasClipboardText();
	}
	int setClipboardText(const char* text)
	{
		return SDL_SetClipboardText(text);
	}
	//
	//SDL_pixels.h
	/*
	struct SDL_color:
	{
		Uint8 r (the red component in the range 0-255)
		Uint8 g (the green component in the range 0-255)
		Uint8 b (the blue component in the range 0-255)
		Uint8 a (the alpha component in the range 0-255)
	}
	*/
	//
	//SDL_timer.h
	Uint32 gettime()
	{
		return SDL_GetTicks();
	}
	//
	//SDL_platform.h
	const char* getOS()
	{
		return SDL_GetPlatform();
	}
	//
	//SDL_cpuinfo.h
	int getCPUcachelinesize()
	{
		return SDL_GetCPUCacheLineSize();
	}
	int getCPUcount()
	{
		return SDL_GetCPUCount();
	}
	int getRAM()
	{
		return SDL_GetSystemRAM();
	}
	SDL_PowerState getpowerinfo(int*secs, int*perc)
	{
		return SDL_GetPowerInfo(secs, perc);
		//passing NULL on secs is allowed (if you don't care how long in secs it will last)
		//-1 will be returned if battery time can't be determined or if it's not running on battery
		//passing NULL on perc is also allowed
		//-1 will be returned if percentage is not determined or if it's not running on battery
	}
	/*
	enum SDL_PowerState:
	{
		SDL_POWERSTATE_UNKNOWN ------------ cannot determine power status
		SDL_POWERSTATE_ON_BATTERY -------------- not plugged in, running on the battery
		SDL_POWERSTATE_NO_BATTERY ---------------- plugged in, no battery available
		SDL_POWERSTATE_CHARGING ------------------ plugged in, charging battery
		SDL_POWERSTATE_CHARGED ------------------- plugged in, battery charged
	}
	*/
	//
	//SDL_Event.h
	int showCurs(int toogle)
	{
		return SDL_ShowCursor(toogle);
		//returns -ve on error
		//pass SDL_ENABLE to show cursor
		//pass SDL_DISABLE to hide cursor
		//pass SDL_QUERY to query the current state
	}
	SDL_Window* getMouseFocus()
	{
		return SDL_GetMouseFocus();
	}
	//
	//SDL_rect.h
	SDL_bool FrecsEq(const SDL_FRect* a, const SDL_FRect* b)
	{
		return SDL_FRectEquals(a, b); //checks if two Frectangles are exactly the same
	}
	SDL_bool FpinFrec(const SDL_FPoint* p, const SDL_FRect* r)
	{
		return SDL_PointInFRect(p, r);
	}
	/*
	struct SDL_Point:
	{
		int x; (the x coordinate of the point)
		int y; (the y coordinate of the point)
	}
	struct SDL_Fpoint:
	{
		float x; (the x coordinate of the point)
		float y; (the y coordinate of the point)
	}
	struct SDL_Frect:
	{
		float x; (the x location of the rectangle's upper left corner)
		float y; (the y location of the rectangle's upper left corner)
		float w; (the width of the rectangle)
		float h; (the height of the rectangle)
	}
	*/
	//
	//SDL_render.h
	SDL_Renderer* crtren(SDL_Window* window, int index, Uint32 flags)
	{
		return SDL_CreateRenderer(window, index, flags);
		/*
		window:	the window where rendering is displayed
		index:	the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
		flags:	0, or one or more SDL_RendererFlags OR'd together
			:
				- SDL_RENDERER_SOFTWARE -------------- the renderer is a software fallback
				- SDL_RENDERER_ACCELERATED ----------- the renderer uses hardware acceleration
				- SDL_RENDERER_PRESENTVSYNC ---------- present is synchronized with the refresh rate
				- SDL_RENDERER_TARGETTEXTURE ----------- the renderer supports rendering to texture
		*/
	}
	void pst(SDL_Renderer* rend)
	{
		return SDL_RenderPresent(rend);
	}
	int clr(SDL_Renderer* rend)
	{
		SDL_RenderClear(rend);
	}
	int getRenBlend(SDL_Renderer * renderer, SDL_BlendMode * blendmode)
	{
		return SDL_GetRenderDrawBlendMode(renderer, blendmode);
	}
	int getRenCol(SDL_Renderer * renderer, Uint8 * r, Uint8 * g, Uint8 * b, Uint8 * a)
	{
		return SDL_GetRenderDrawColor(renderer, r, g, b, a);
	}
	int getRenInfo(SDL_Renderer* renderer, SDL_RendererInfo * info)
	{
		return SDL_GetRendererInfo(renderer, info);
	}
	int getRenSize(SDL_Renderer * renderer, int * w, int * h)
	{
		return SDL_GetRendererOutputSize(renderer, w, h);
	}
	SDL_Renderer* render_soft(SDL_Surface * surface)
	{
		return SDL_CreateSoftwareRenderer(surface);
	}
	int getRenDriverInfo(int index, SDL_RendererInfo * info)
	{
		return SDL_GetRenderDriverInfo(index, info);
	}
	void killren(SDL_Renderer* ren)
	{
		SDL_DestroyRenderer(ren);
	}
	int Quer_TEX(SDL_Texture * texture, Uint32 * format, int * access, int * w, int * h)
	{
		return SDL_QueryTexture(texture, format, access, w, h);
	}
	int SetTexAlpha(SDL_Texture * texture, Uint8 alpha)
	{
		return SDL_SetTextureAlphaMod(texture, alpha);
	}
	int SetTexBlend(SDL_Texture * texture, SDL_BlendMode blendmode)
	{
		return SDL_SetTextureBlendMode(texture, blendmode);
		/*
		enum BLENDMODE
		{
			SDL_BLENDMODE_NONE ---------- no blending
							   ---------- dstRGBA = srcRGBA
			SDL_BLENDMODE_BLEND ---------- alpha blending
								---------- dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
								---------- dstA = srcA + (dstA * (1-srcA))
			SDL_BLENDMODE_ADD ------------- additive blending
							  ------------- dstRGB = (srcRGB * srcA) + dstRGB
							  -------------- dstA = dstA
			SDL_BLENDMODE_MOD -------------- color modulate
							  -------------- dstRGB = srcRGB * dstRGB
							  -------------- dstA = dstA
			SDL_BLENDMODE_MUL -------------- color multiply
							  --------------- dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA))
							  --------------- dstA = (srcA * dstA) + (dstA * (1-srcA))
		}
		*/
	}
	int SetTexCol(SDL_Texture * texture, Uint8 r, Uint8 g, Uint8 b)
	{
		return SDL_SetTextureColorMod(texture, r, g, b);
	}
	SDL_Texture* crttex(SDL_Renderer* ren, Uint32 format, int access, int w, int h)
	{
		return SDL_CreateTexture(ren, format, access, w, h);
		/*
		Values
			SDL_TEXTUREACCESS_STATIC: changes rarely, not lockable
			SDL_TEXTUREACCESS_STREAMING: changes frequently, lockable
			SDL_TEXTUREACCESS_TARGET: can be used as a render target
		*/
	}
	SDL_Texture* crttex_sur(SDL_Renderer* ren, SDL_Surface* surf)
	{
		return SDL_CreateTextureFromSurface(ren,surf);
	}
	void killtex(SDL_Texture* texture)
	{
		return SDL_DestroyTexture(texture);
	}
	int renclr(SDL_Renderer*ren)
	{
		return SDL_RenderClear(ren);
	}
	int crtWin_Ren(int width, int height, Uint32 Window_flags, SDL_Window** window, SDL_Renderer** renderer)
	{
		return SDL_CreateWindowAndRenderer(width, height, Window_flags, window, renderer);
	}
	SDL_Texture* getren_target(SDL_Renderer* ren)
	{
		return SDL_GetRenderTarget(ren);
	}
	int get_o_putsize(SDL_Renderer* ren, int* w, int* h)
	{
		return SDL_GetRendererOutputSize(ren, w, h);
	}
	int getren_info(SDL_Renderer* ren, SDL_RendererInfo * info)
	{
		return SDL_GetRendererInfo(ren, info);
	}
	int getren_drawcolor(SDL_Renderer* ren, Uint8*r, Uint8*g, Uint8*b, Uint8*a)
	{
		return SDL_GetRenderDrawColor(ren, r, g, b, a);
	}
	int getren_drawblendmode(SDL_Renderer* ren, SDL_BlendMode *blen)
	{
		return SDL_GetRenderDrawBlendMode(ren, blen);
	}
	int rencpy(SDL_Renderer* ren, SDL_Texture* tex, const SDL_Rect * src, const SDL_Rect * dst)
	{
		return SDL_RenderCopy(ren, tex, src, dst);
	}
	int rencpyx(SDL_Renderer* ren, SDL_Texture *tex,
	const SDL_Rect *src, const SDL_Rect *dst, const double angle,
	const SDL_Point* center, const SDL_RendererFlip flip)
	{
		return SDL_RenderCopyEx(ren, tex, src, dst, angle, center, flip);
		/*
		flip:  (can be OR'd together)
			- SDL_FLIP_NONE --------- donot flip
			- SDL_FLIP_HORIZONTAL ------------ flip horizontally
			- SDL_FLIP_VERTICAL ------------- flip vertically
		*/
	}
	//SDL2_image.h
	void freeANIM(IMG_Animation *anim)
	{
		return IMG_FreeAnimation(anim);
	}
	int INIT_IMG(int flags)
	{
		return IMG_Init(flags); //returns 0 on failure or the flags on success
		/*
		flags: (can be OR'd together)
			IMG_INIT_JPG
			IMG_INIT_PNG
			IMG_INIT_TIF
			IMG_INIT_WEBP
			IMG_INIT_JXL
			IMG_INIT_AVIF
		*/
	}
	//
	int isAVIF(SDL_RWops *src)
	{
		return IMG_isAVIF(src);
	}
	int isBMP(SDL_RWops *src)
	{
		return IMG_isBMP(src);
	}
	int isCUR(SDL_RWops *src)
	{
		return IMG_isCUR(src);
	}
	int isGIF(SDL_RWops *src)
	{
		return IMG_isGIF(src);
	}
	int isICO(SDL_RWops *src)
	{
		return IMG_isICO(src);
	}
	int isJPG(SDL_RWops *src)
	{
		return IMG_isJPG(src);
	}
	int isJXL(SDL_RWops *src)
	{
		return IMG_isJXL(src);
	}
	int isLBM(SDL_RWops *src)
	{
		return IMG_isLBM(src);
	}
	int isPCX(SDL_RWops *src)
	{
		return IMG_isPCX(src);
	}
	int isPNG(SDL_RWops *src)
	{
		return IMG_isPNG(src);
	}
	int isPNM(SDL_RWops *src)
	{
		return IMG_isPNM(src);
	}
	int isQOI(SDL_RWops *src)
	{
		return IMG_isQOI(src);
	}
	int isSVG(SDL_RWops *src)
	{
		return IMG_isSVG(src);
	}
	int isTIF(SDL_RWops *src)
	{
		return IMG_isTIF(src);
	}
	int isWEBP(SDL_RWops *src)
	{
		return IMG_isWEBP(src);
	}
	int isXCF(SDL_RWops *src)
	{
		return IMG_isXCF(src);
	}
	int isXPM(SDL_RWops *src)
	{
		return IMG_isXPM(src);
	}
	int isXV(SDL_RWops *src)
	{
		return IMG_isXV(src);
	}
	SDL_Surface* Load_IMG(SDL_RWops *file, int freesrc)
	{
		return IMG_Load_RW(file, freesrc);
	}
	SDL_Surface* Load_IMG(const char* file)
	{
		return IMG_Load(file);
	}
	IMG_Animation * Load_ANIM(SDL_RWops *file, int freesrc)
	{
		return IMG_LoadAnimation_RW(file, freesrc);
	}
	IMG_Animation * Load_ANIM(const char* file)
	{
		return IMG_LoadAnimation(file);
	}
	IMG_Animation * Load_ANIM_TYPE(SDL_RWops *src, int freesrc, const char *type)
	{
		return IMG_LoadAnimationTyped_RW(src, freesrc, type);
	}
	SDL_Surface* Load_AVIF(SDL_RWops *src)
	{
		return IMG_LoadAVIF_RW(src); //loads AVIF image directly
		// same functions:
		// IMG_LoadBMP_RW
		// IMG_LoadCUR_RW
		// IMG_LoadGIF_RW
		// IMG_LoadICO_RW
		// IMG_LoadJPG_RW
		// IMG_LoadJXL_RW
		// ...
	}
	SDL_Texture * Load_TEXTURE(SDL_Renderer* renderer, const char* file)
	{
		return IMG_LoadTexture(renderer, file); //load an image from filepath into a GPU texture
		// there exists an _RW version (parameter const char* replaced by SDL_RWops)
		// there exists a typed_RW version too, with the last parameter a const char* type
	}
	int SaveJPG(SDL_Surface* surface, const char* file, int qual)
	{
		return IMG_SaveJPG(surface, file, qual);
		//save a surface to a JPEG image file...
		//there exists an RW version
		//there exists a PNG version with RW version too
	}
	void QUIT_IMG()
	{
		return IMG_Quit(); //Deinitializeds SDL_image
	}
	//
	//SDL_mixer.h
	//channels
	void Pause_chann(int chann_no)
	{
		return Mix_Pause(chann_no);
	}
	int allocate_channels(int num)
	{
		return Mix_AllocateChannels(num);
		// returns the new number of allocated channels
	}
	int Expire_Chann(int chann_no, int ticks)
	{
		return Mix_ExpireChannel(chann_no, ticks);
		//returns no_ of channels that changed expirations
		// pass the channel no to expire
		// pass the number of milliseconds to let channel play before halting, -1 to not halt
	}
	int FadeinChann(int chann_no, Mix_Chunk*chunk, int loops, int ms)
	{
		return Mix_FadeInChannel(chann_no, chunk, loops, ms);
		// pass -1 on chann_no to find any available
		// the chunk parameter is for a new chunk to play
		// the loops parameter is for the no_ of times the chunk should loop, -1 for (kinda) infinite loops
		// ms is the number of milliseconds to spend fading in
	}
	int FadeinChann_t(int chann_no, Mix_Chunk*chunk, int loops, int ms, int ticks)
	{
		return Mix_FadeInChannelTimed(chann_no, chunk, loops, ms, ticks);
		// pass -1 on chann_no to find any available
		// the chunk parameter is for a new chunk to play
		// the loops parameter is for the no_ of times the chunk should loop, -1 for (kinda) infinite loops
		// ms is the number of milliseconds to spend fading in
		// ticks is the max no_ of milliseconds of this chunk to mix for playback
	}
	int FadeoutChann(int chann_no, int ms)
	{
		return Mix_FadeOutChannel(chann_no, ms);
		//returns the number of channes scheduled to fade
		//chann_no is the channel to fade out
		//ms is the no_ of milliseconds to fade before halting channel
	}
	Mix_Fading FadingChannel(int chann_no)
	{
		return Mix_FadingChannel(chann_no);
		//cannot specify MAX_CHANNEL_POST or -1
		//returns the current fading status of the channel
		//MIX_NO_FADING - no fading or an invalid channel specified
		//MIX_FADING_OUT or
		//MIX_FADING_IN
	}
	int haltchann(int chann_no)
	{
		return Mix_HaltChannel(chann_no);
		//halts playing of a channel
		//returns 0 on success, -1 on error
	}
	int GrpChann(int chann_no, int tagno)
	{
		return Mix_GroupChannel(chann_no, tagno);
		//assigns a tag to a channel
		//returns 0 on failure, non-zero on success
	}
	int GrpChanns(int chann_no1, int chann_non, int tagno)
	{
		return Mix_GroupChannels(chann_no1, chann_non, tagno);
		//returns 0 on success, -ve on error
		//chann_no1: first channel to set tag
		//chann_non: last channel to set tag (inclusive)
		//tagno: group_no for channels
	}
	Mix_Chunk * GetChunk(int chann_no)
	{
		return Mix_GetChunk(chann_no); //returns the associated chunk in the channel
	}
	int chann_paused(int chann_no)
	{
		return Mix_Paused(chann_no);
		//checks whether a channel is paused
		//1 if paused, 0 if not
		//if -1 is passed, it returns the no_ of paused channels
	}
	int Play_chann(int chann_no, Mix_Chunk * chunk, int loops, int ticks)
	{
		return Mix_PlayChannelTimed(chann_no, chunk, loops, ticks);
		//play an audio chunk on a specific channel for a specific time (ticks, in ms)
		//returns the channel to play the sound or -1 if it can't be played
	}
	int chann_playing(int chann_no)
	{
		return Mix_Playing(chann_no);
		//returns non-zero if channel is playing, 0 if not
		//if -1 is passed, it returns the no_ of playing channels
		// !!! paused channnels are treated as playing !!!
	}
	int Reserve_chann(int num)
	{
		return Mix_ReserveChannels(num);
		//returns the no_ of reserved channels
	}
	void Resume_chann(int chann_no)
	{
		return Mix_Resume(chann_no);
		//resumes a particular channel
	}
	int SetPan_chann(int chann_no, Uint8 left, Uint8 right)
	{
		return Mix_SetPanning(chann_no, left, right);
		//returns 0 on error, non-zero on success
	}
	int SetReverseStereo_chann(int chann_no, int flip)
	{
		return Mix_SetReverseStereo(chann_no, flip);
		//returns 0 on failure, non-zero on success
		//pass non-zero to reverse, zero to disable effect (on flip)
	}
	int Set_channVOL(int chann_no, int vol)
	{
		return Mix_Volume(chann_no, vol);
		//sets the volume for a channel
		//returns the previous volume
		//if vol is -1, returns current vol
		//if chann_no is -1, returns the average vol of all channels
	}
	//
	//Music
	SDL_bool hasMusDecoder(const char* name)
	{
		return Mix_HasMusicDecoder(name);
	}
	void Resume_MUSIC()
	{
		return Mix_ResumeMusic();
		//resumes the music stream
	}
	int GetNumMusDecoders()
	{
		return Mix_GetNumMusicDecoders();
		//returns number of music decoders available
	}
	int haltMUSIC()
	{
		return Mix_HaltMusic();
		//halts playing of the entire music stream
		//returns 0 regardless
	}
	Mix_Music* Load_MUS(const char*file)
	{
		return Mix_LoadMUS(file);
	}
	Mix_Music* Load_MUS(SDL_RWops*file, int freesrc)
	{
		return Mix_LoadMUS_RW(file,freesrc);
	}
	double getMus_t(Mix_Music* music)
	{
		return Mix_MusicDuration(music);
		//returns music duration in secs or -1.0 on error
	}
	int MUSIC_paused()
	{
		return Mix_PausedMusic();
		//checks whether the entire music stream is paused
		//returns 1 if true, 0 if not
	}
	void Pause_MUSIC()
	{
		return Mix_PauseMusic();
		//pauses the music stream
	}
	int MUSIC_playing()
	{
		return Mix_PlayingMusic();
		//returns non-zero if the music stream is playing, 0 if not
		// !!! Paused music is treated as playing !!!
	}
	int Play_MUS(Mix_Music * music, int loops)
	{
		return Mix_PlayMusic(music, loops);
		//returns 0 on success, -1 on error
		//plays a new music object
	}
	void Rewind_MUSIC()
	{
		return Mix_RewindMusic();
	}
	int Set_MUSICPOS(double pos)
	{
		return Mix_SetMusicPosition(pos);
		//sets the current position in music stream, in seconds
		//returns 0 on sucess, -1 on failure
	}
	int FadeinMus(Mix_Music * music, int loops, int ms, double position = 0)
	{
		return Mix_FadeInMusicPos(music, loops, ms, position);
		//returns 0 on success, -1 on error
		// music is the new music object to play
		// loop is number of times the chunk shoud loop, -1 for infinite
		// ms is the number of milliseconds to spend fading in
		// position is the position to start fading (in seconds)
	}
	int FadeoutMUSIC(int ms)
	{
		return Mix_FadeOutMusic(ms);
		// halt the entire music stream after fading it our for ms (milliseconds)
	}
	Mix_Fading FadingMus()
	{
		return Mix_FadingMusic();
		//returns the current fading status of the entire music stream
	}
	void FreeMus(Mix_Music*music)
	{
		return Mix_FreeMusic(music); //frees a music object
	}
	const char* GetAlbum(const Mix_Music* music)
	{
		return Mix_GetMusicAlbumTag(music);
		//returns the music's album name if available, otherwise ""
	}
	const char* GetArtist(const Mix_Music* music)
	{
		return Mix_GetMusicArtistTag(music);
		//returns the music's artist name if available, otherwise ""
	}
	const char* GetMusicDecoder(int index)
	{
		return Mix_GetMusicDecoder(index);
	}
	double GetMusLoop_endt(Mix_Music *music)
	{
		return Mix_GetMusicLoopEndTime(music);
		//returns -1 if the feature is not used for the music or not supported for some codec
		//returns time in seconds
		//if null is passed, it returns the duration of a currently playing music
	}
	double GetMusLoop_t(Mix_Music *music)
	{
		return Mix_GetMusicLoopLengthTime(music);
		//returns -1 if the feature is not used for the music or not supported for some codec
		//returns time in seconds
		//if null is passed, it returns the duration of a currently playing music
	}
	double GetMusLoop_start_t(Mix_Music *music)
	{
		return Mix_GetMusicLoopStartTime(music);
		//returns -1 if the feature is not used for the music or not supported for some codec
		//returns time in seconds
		//if null is passed, it returns the duration of a currently playing music
	}
	double GetMusPos(Mix_Music *music)
	{
		return Mix_GetMusicPosition(music);
		//returns -1 if the feature is not used for the music or not supported for some codec
		//gets the time of the current position of a music stream in seconds
	}
	const char* GetMusTitle(const Mix_Music * music)
	{
		return Mix_GetMusicTitle(music);
		//returns the music's title or ""
		//same to Mix_GetMusicTitleTag(music);
	}
	Mix_MusicType GetMusType(const Mix_Music *music)
	{
		return Mix_GetMusicType(music);
		//can pass NULL for the currently playing music
		//returns the format of a mixer music
		//returns MUS_NONE inf nothing is playing
	}
	int GetMusVol(Mix_Music*music)
	{
		return Mix_GetMusicVolume(music);
		//returns the music's current vol between 0 - 128 (max)
	}
	//
	//chunk
	Mix_Chunk* Load_WAV(const char* file)
	{
		return Mix_LoadWAV(file);
	}
	Mix_Chunk* Load_WAV(SDL_RWops* file, int freesrc)
	{
		return Mix_LoadWAV_RW(file, freesrc);
	}
	int Set_chunkVOL(Mix_Chunk * chunk, int vol)
	{
		return Mix_VolumeChunk(chunk, vol);
		//sets the volume for a chunk
		// returns the previous volume
		// if vol is -1, returns current volume
		// if chunk is NULL, returns -1
	}
	void FreeChunk(Mix_Chunk * chunk)
	{
		return Mix_FreeChunk(chunk); //frees an audio chunk
	}
	const char* GetChunkDecoder(int index)
	{
		return Mix_GetChunkDecoder(index); //pass index of the chunk's decoder
		//returns the chunk decoders name
	}
	int GetNumChunkDecoders()
	{
		return Mix_GetNumChunkDecoders();
		//returns number of chunk decoders available
	}
	SDL_bool hasChunkDecoder(const char* name)
	{
		return Mix_HasChunkDecoder(name);
	}
	//
	//group
	int FadeoutGrp(int tag_no, int ms)
	{
		return Mix_FadeOutGroup(tag_no, ms);
		//tag_no is the tag_no for the group of channels
		//ms is the number of milliseconds to fade before halting the group
	}
	int GrpAvail(int tagno)
	{
		return Mix_GroupAvailable(tagno);
		//returns the first available channel in a group of channel, tagno
	}
	int Grpcount(int tagno)
	{
		return Mix_GroupCount(tagno);
		//returns the number of channels in a tag
	}
	int GrpNewer(int tagno)
	{
		return Mix_GroupNewer(tagno);
		//returns the most recent sample playing in a group of channels
	}
	int GrpOldest(int tagno)
	{
		return Mix_GroupOldest(tagno);
		//returns the oldest sample playing in a group of channels
	}
	int haltGrp(int tagno)
	{
		return Mix_HaltGroup(tagno);
		//halts playing of a group of channels
		//returns 0 on success
	}
	//
	//audio
	void closeAUD()
	{
		return Mix_CloseAudio(); //closes mixer
	}
	int INIT_AUD(int flags)
	{
		return Mix_Init(flags);
		//returns all currently initialized flags
		/*
		flags:
			MIX_INIT_FLAC
			MIX_INIT_MOD
			MIX_INIT_MP3
			MIX_INIT_OGG
			MIX_INIT_MID
			MIX_INIT_OPUS
			MIX_INIT_WAVPACK
		*/
	}
	int MasVol(int vol)
	{
		return Mix_MasterVolume(vol);
		//sets the master volume for all channels
		//returns the previous volume, if -1 is passed it returns the current volume
	}
	int Open_AUD(int freq, Uint16 format, int channels, int chunksize)
	{
		return Mix_OpenAudio(freq, format, channels, chunksize);
		//returns 0 on success, -1 on error.
	}
	int Open_AUD_Device(int freq, Uint16 format, int channels, int chunksize, const char* device, int changes)
	{
		return Mix_OpenAudioDevice(freq, format, channels, chunksize, device, changes);
		//returns 0 on success, -1 on error.
	}
	void Pause_AUD(int pause_on)
	{
		//return Mix_PauseAudio(pause_on);
		//pauses or resumes the whole audio output
		//1 for pause, 0 for resume
	}
	int QuerySpec(int * freq, Uint16* format, int * channels)
	{
		return Mix_QuerySpec(freq, format, channels);
		//returns 1 if audio device is opened, 0 otherwise
		//freq - will be filled with the audio device's frequency in Hz.
		//format - will be filled with audio device's format
		//channels - will be filled with the audio device's channel count
	}
	void QUIT_AUD()
	{
		return Mix_Quit();
	}
	const char* GetAUD_ERR()
	{
		return Mix_GetError();
	}
	//
	
}

