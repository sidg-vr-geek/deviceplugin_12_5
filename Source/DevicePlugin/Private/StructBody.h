#pragma once

#include "StructBody.generated.h"

USTRUCT()
struct F_BONE
{
        GENERATED_BODY()

                UPROPERTY(BlueprintReadOnly) FRotator rotation;
};

USTRUCT()
struct F_ARM
{
        GENERATED_BODY()

                UPROPERTY(BlueprintReadOnly) F_BONE			upper;
        UPROPERTY(BlueprintReadOnly) F_BONE			lower;
};

USTRUCT()
struct F_ARMS
{
        GENERATED_BODY()

                UPROPERTY(BlueprintReadOnly) F_ARM			left;
        UPROPERTY(BlueprintReadOnly) F_ARM			right;
};

USTRUCT()
struct F_BODY
{
        GENERATED_BODY()

                UPROPERTY(BlueprintReadOnly) F_ARMS			arms;
};
