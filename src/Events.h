#pragma once


class EventRegsHolder
{
public:
	[[nodiscard]] static EventRegsHolder* GetSingleton()
	{
		static EventRegsHolder singleton;
		return &singleton;
	}

	enum : std::uint32_t
	{
		kCustomMarker = 'MARK',
		kFastTravel = 'TRVL',
		kPlayerDialogue = 'DIAL'
	};

	SKSE::RegistrationSet<std::uint32_t> customMarker{ "OnCustomMarkerChange"sv };
	SKSE::RegistrationSet<std::uint32_t> fastTravel{ "OnFastTravelConfirm"sv };
	SKSE::RegistrationSet<Actor*, bool> playerDialogue{ "OnPlayerDialogue"sv };

	void Save(SKSE::SerializationInterface* a_intfc, std::uint32_t a_version);
	void Load(SKSE::SerializationInterface* a_intfc, std::uint32_t a_type);
	void Revert(SKSE::SerializationInterface* a_intfc);

private:
	EventRegsHolder() = default;
	EventRegsHolder(const EventRegsHolder&) = delete;
	EventRegsHolder(EventRegsHolder&&) = delete;
	~EventRegsHolder() = default;

	EventRegsHolder& operator=(const EventRegsHolder&) = delete;
	EventRegsHolder& operator=(EventRegsHolder&&) = delete;

};

