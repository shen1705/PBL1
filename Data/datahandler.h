#pragma once
#include "Data.h"
int SaveData(UserList* accounts);
int LoadData(UserList* &accounts);
int Record(SessionRecord *Record);

void FreeHistory(User &U);