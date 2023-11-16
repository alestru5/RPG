#include "artifact.h"
#include "hero.h"

Artifact::Artifact(){
    artifact_type = type_artifact::casual;
    changes = SetChanges::createChanges(type_artifact::casual);
}

Artifact::Artifact(type_artifact T){
    artifact_type = T;
    changes = SetChanges::createChanges(T);
}

void Artifact::SetArtifact_Type(type_artifact T){
    artifact_type = T;
    changes = SetChanges::createChanges(T);
}

void Artifact::useChanges(Hero &H){
    for (auto &i: changes){
        H.getTable().setValue(i.first, H.getTable().getValue(i.first) + i.second);
    }
}

void Artifact::unUseChanges(Hero &H){
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
