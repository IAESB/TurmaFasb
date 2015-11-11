#include "model.h"

Repository Model::repository;

Model::Model()
{
}

void Model::openRepository(const string& url)
{
    repository.open(url);
}

