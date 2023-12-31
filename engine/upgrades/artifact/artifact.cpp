#include "artifact.h"

void Artifact::setAll(std::string at, int c) noexcept{
    artifact_type = at;
    changes.push_back(std::make_pair("s", c));
    changes.push_back(std::make_pair("a", c));
    changes.push_back(std::make_pair("e", c));
    changes.push_back(std::make_pair("i", c));
}

void Artifact::useChanges(Hero &H) const noexcept{
    for (auto &i: changes){
        H.getTable().setValue(i.first, H.getTable().getValue(i.first) + i.second);
    }
}

void Artifact::unUseChanges(Hero &H) const noexcept{
    for (auto &i: changes){
        H.getTable().setValue(i.first, H.getTable().getValue(i.first) - i.second);
    }
}

Artifact& Artifact::operator=(const Artifact& I) noexcept{
    if (this != &I){
        artifact_type = I.artifact_type;
        changes = I.changes;
    }
    return *this;
}
