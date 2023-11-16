#ifndef ARTIFACT_H
#define ARTIFACT_H

#include <iostream>
#include <list>

#include "enums.h"
#include "setchanges.h"

class Hero;

class Artifact{
    protected:
        type_artifact artifact_type;
        std::list<std::pair<short_characteristic, int>> changes;

    public:
        Artifact() noexcept;
        Artifact(type_artifact T) noexcept;

        type_artifact getArtifact_Type() const noexcept { return artifact_type; }
        std::list<std::pair<short_characteristic, int>> getChanges() const noexcept {return changes; }

        void SetArtifact_Type(type_artifact T) noexcept;

        void useChanges(Hero &H) const noexcept;
        void unUseChanges(Hero &H) const noexcept;

        Artifact& operator=(const Artifact& I) noexcept;
};

#endif // ARTIFACT_H

