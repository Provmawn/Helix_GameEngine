#ifndef FPSLIMITER_H
#define FPSLIMITER_H
namespace helix
{
	class FPSLimiter
	{
	public:
		using FPS_t = float;
		FPSLimiter();
		~FPSLimiter();
		void Init(FPS_t max_fps);
		void SetMaxFPS(FPS_t max_fps);
		void Begin();
		FPS_t End();
	private:
		void CalculateFPS();
		FPS_t m_max_fps{};
		unsigned int m_start_ticks{};
		FPS_t m_fps{};
		unsigned int m_frametime{};
	};
}
#endif

