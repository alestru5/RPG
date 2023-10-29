#include "artifact.h"

Artifact::Artifact(){
    try{
        artifact_type = type_artifact::casual;
        changes = SetChanges::createChanges(type_artifact::casual);
    } catch(...){
        throw;
    }
}

Artifact::Artifact(type_artifact T){
    try{
        artifact_type = T;
        changes = SetChanges::createChanges(T);
    } catch(...){
        throw;
    }
}

void Artifact::SetArtifact_Type(type_artifact T){
    try{
        artifact_type = T;
        changes = SetChanges::createChanges(T);
    } catch(...){
        throw;
    }
}

Artifact& Artifact::operator=(const Artifact& I) noexcept{
    if (this != &I){
        artifact_type = I.artifact_type;
        changes = I.changes;
    }
    return *this;
}
