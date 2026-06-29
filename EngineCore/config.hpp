#pragma once
#include "singleton.hpp"

class Config {
private:
	Config() :
		m_screenHeight(600),
		m_screenWidth(800) {}
	~Config() = default;

public:
	Config(const Config&) = delete;
	Config& operator=(const Config&) = delete;

	static Config& getInstance() {
		static Config instance;
		return instance;
	}

	// Window settings
	int m_screenWidth = 800;
	int m_screenHeight = 600;
};