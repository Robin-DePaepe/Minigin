#pragma once

namespace minigin
{
	template<typename states>
	class State
	{
	public:
		//rule of 5
		State() = default;
		virtual ~State() = default;

		State(const State& other) = delete;
		State(State&& other) noexcept = delete;
		State& operator=(const State& other) = delete;
		State& operator=(State&& other) noexcept = delete;

		//functions
		virtual states Update() = 0;
		virtual void Render() const = 0;

		virtual void StartAction() = 0;
		virtual void EndAction() = 0;
	};
}