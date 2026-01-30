#pragma once
#include <unordered_map>
#include "Data.h"
using namespace std;

int SaveData(unordered_map<int,User>& accounts);
int LoadData(unordered_map<int,User>& accounts);
int Record(SessionRecord *Record);
