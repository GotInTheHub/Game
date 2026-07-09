#pragma once

namespace Engine
{
	class EngineContext;

	class IEngineSystem
	{
	public:
		virtual ~IEngineSystem() = default;

		virtual bool initialize(EngineContext& context) = 0;

		virtual void shutdown() = 0;

		virtual void update(float dt) = 0;
	};
}