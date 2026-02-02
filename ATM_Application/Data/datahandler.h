#pragma once
#include "Data.h"
#include <unordered_map>
int SaveData(std::unordered_map<int,User>& accounts);
int LoadData(std::unordered_map<int,User>& accounts);
int Record(SessionRecord *Record);

void FreeHistory(User &U);