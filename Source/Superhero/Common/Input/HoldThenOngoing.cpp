//MIT 
//Based on https://dev.epicgames.com/community/snippets/Qm2/unreal-engine-enhanced-input-double-tap-input-trigger
//Thanks to user colorindarkness 
#include "HoldThenOngoing.h"


ETriggerState UHoldThenOngoing::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{

	

	// Transition to Ongoing on actuation. Update the held duration.
	if (IsActuated(ModifiedValue))
	{
		float LastHeldDuration = HeldDuration;
		HeldDuration += DeltaTime;
		// Only trigger once but don't cancel and just keep going afterwards. It's like pulse signal but it only triggers once
		if (LastHeldDuration < HoldTimeThreshold && HoldTimeThreshold < HeldDuration)
		{
			return ETriggerState::Triggered;
		}
	}
	else
	{
		// Reset duration
		HeldDuration = 0.0f;

	}
	return ETriggerState::Ongoing;

	
}