#pragma once
#include "TooltipInfo.generated.h"

USTRUCT(BlueprintType)
struct FTooltipInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SubTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractionDelay;

	FTooltipInfo()
	{
		Icon = nullptr;
		Title = FText();
		SubTitle = FText();
		Description = FText();
		InteractionDelay = 0.0f;
	}

	FTooltipInfo(UTexture2D* InIcon, const FText& InTitle, const FText& InSubTitle, const FText& InDescription, const float& InInteractionDelay)
	{
		Icon = InIcon;
		Title = InTitle;
		SubTitle = InSubTitle;
		Description = InDescription;
		InteractionDelay = InInteractionDelay;
	}
};
