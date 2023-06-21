#pragma once


class PlayerDialogueHook : public Actor
{
public:
	static void Install();

private:
	static void SetDialogueWithPlayer(Actor* a_this, bool a_flag, bool a_forceGreet, TESTopicInfo* a_topic);
	static inline REL::Relocation<decltype(SetDialogueWithPlayer)> _SetDialogueWithPlayer;
};
