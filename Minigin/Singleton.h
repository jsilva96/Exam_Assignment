#pragma once
namespace dae
{
	template <typename T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}

		virtual ~Singleton() = default;
	protected:
		Singleton() = default;

	private:
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) noexcept = delete;

		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) noexcept = delete;
	};
}