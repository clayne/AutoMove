#include "Serialization.h"
#include "Events.h"


namespace Serialization
{
	std::string DecodeTypeCode(uint32_t a_typeCode)
	{
		constexpr std::size_t SIZE = sizeof(uint32_t);

		std::string sig;
		sig.resize(SIZE);
		const char* iter = reinterpret_cast<char*>(&a_typeCode);
		for (std::size_t i = 0, j = SIZE - 1; i < SIZE; ++i, --j) {
			sig[j] = iter[i];
		}

		return sig;
	}

	void SaveCallback(SKSE::SerializationInterface* a_intfc)
	{
		EventRegsHolder::GetSingleton()->Save(a_intfc, kVersion);

		logger::info("Finished saving data"sv);
	}

	void LoadCallback(SKSE::SerializationInterface* a_intfc)
	{
		uint32_t type, version, length;

		while (a_intfc->GetNextRecordInfo(type, version, length)) {

			if (version != kVersion) {
				logger::critical("Loaded data is out of date! Read ({}), expected ({}) for type code ({})", version, kVersion, DecodeTypeCode(type));
				continue;
			}

			EventRegsHolder::GetSingleton()->Load(a_intfc, type);
		}
		logger::info("Finished loading data"sv);
	}

	void RevertCallback(SKSE::SerializationInterface* a_intfc)
	{
		EventRegsHolder::GetSingleton()->Revert(a_intfc);

		logger::info("Finished reverting data"sv);
	}
}
