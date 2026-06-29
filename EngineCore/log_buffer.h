#pragma once
#include "log_entry.h"
#include <array>

static constexpr size_t LOG_CAPACITY = 4096;

class LogBuffer {
private:
	std::array<LogEntry, LOG_CAPACITY> m_buffer;

	std::atomic<size_t> m_writeIndex{ 0 };
	std::atomic<size_t> m_readIndex{ 0 };

public:
	bool push(const LogEntry& entry) {
		size_t current = m_writeIndex.load(std::memory_order_relaxed);
		size_t next = (current + 1) % LOG_CAPACITY;

		if (next == m_readIndex.load(std::memory_order_acquire)) {
			// Buffer is full
			return false;
		}

		m_buffer[current] = entry;
		m_writeIndex.store(next, std::memory_order_release);

		return true;
	}

	bool pop(LogEntry& entry) {
		size_t current = m_readIndex.load(std::memory_order_relaxed);
		
		if (current == m_writeIndex.load(std::memory_order_acquire)) {
			// Buffer is empty
			return false;
		}
		
		entry = m_buffer[current];
		m_readIndex.store((current + 1) % LOG_CAPACITY, std::memory_order_release);
		
		return true;
	}
};