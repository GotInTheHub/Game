#pragma once

#include <unordered_map>
#include <typeindex>
#include <cassert>
#include <stdexcept>
#include <iostream>

namespace Engine
{
	class EngineContext
	{
	public:
		template<typename T>
		void provide(T* system)
		{
			m_systems[std::type_index(typeid(T))] = system;
		}

		// Use when the system is required to exist. Asserts in debug;
		// same trust level the old reference-based context gave you.
		template<typename T>
		T& get()
		{
			T* system = tryGet<T>();
			assert(system && "EngineContext::get<T>() - System not registered");
			
			if (!system) {
				std::cout << "EngineContext::get<T>() - System not registered: " << typeid(T).name() << std::endl;
				throw std::runtime_error("EngineContext::get<T>() - System not registered");
			}

			return *system;
		}

		// Use when the system is optional (e.g. a console command that
		// only works if a particular system happens to be present).
		template<typename T>
		T* tryGet()
		{
			auto it = m_systems.find(std::type_index(typeid(T)));
			return it == m_systems.end()
				? nullptr
				: static_cast<T*>(it->second);
		}

	private:
		std::unordered_map<std::type_index, void*> m_systems;
	};
}