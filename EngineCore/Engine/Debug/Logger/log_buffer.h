#pragma once
#include "log_entry.h"
#include <vector>
#include <memory>
#include <atomic>

namespace Engine {
	static constexpr size_t LOG_CAPACITY = 4096;

	class LogBuffer {
	private:
		std::vector<LogEntry> m_buffer;  // Heap-allocated instead of stack
		std::atomic<size_t> m_writeIndex{ 0 };
		std::atomic<size_t> m_readIndex{ 0 };
		std::atomic<size_t> m_capacity{ 0 };

	public:
		LogBuffer() {
			// Allocate on heap during construction
			m_buffer.resize(LOG_CAPACITY);
			m_capacity.store(LOG_CAPACITY, std::memory_order_release);
		}

		~LogBuffer() = default;

		// Prevent copies (circular buffer state would be invalid)
		LogBuffer(const LogBuffer&) = delete;
		LogBuffer& operator=(const LogBuffer&) = delete;

		// Allow moves
		LogBuffer(LogBuffer&& other) noexcept
			: m_buffer(std::move(other.m_buffer))
			, m_writeIndex(other.m_writeIndex.load())
			, m_readIndex(other.m_readIndex.load())
			, m_capacity(other.m_capacity.load())
		{
		}

		LogBuffer& operator=(LogBuffer&& other) noexcept {
			if (this != &other) {
				m_buffer = std::move(other.m_buffer);
				m_writeIndex.store(other.m_writeIndex.load());
				m_readIndex.store(other.m_readIndex.load());
				m_capacity.store(other.m_capacity.load());
			}
			return *this;
		}

		bool push(const LogEntry& entry) {
			size_t cap = m_capacity.load(std::memory_order_acquire);
			size_t current = m_writeIndex.load(std::memory_order_relaxed);
			size_t next = (current + 1) % cap;

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
			size_t cap = m_capacity.load(std::memory_order_acquire);

			if (current == m_writeIndex.load(std::memory_order_acquire)) {
				// Buffer is empty
				return false;
			}

			entry = m_buffer[current];
			m_readIndex.store((current + 1) % cap, std::memory_order_release);

			return true;
		}

		// Query buffer state
		bool isEmpty() const {
			return m_readIndex.load(std::memory_order_acquire) == 
				   m_writeIndex.load(std::memory_order_acquire);
		}

		bool isFull() const {
			size_t cap = m_capacity.load(std::memory_order_acquire);
			size_t writeIdx = m_writeIndex.load(std::memory_order_acquire);
			size_t next = (writeIdx + 1) % cap;
			return next == m_readIndex.load(std::memory_order_acquire);
		}

		size_t capacity() const {
			return m_capacity.load(std::memory_order_acquire);
		}

		// Reset the buffer (only safe when no active readers/writers)
		void clear() {
			m_writeIndex.store(0, std::memory_order_release);
			m_readIndex.store(0, std::memory_order_release);
		}
	};
}