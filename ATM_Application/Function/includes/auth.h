#pragma once
#include <unordered_map>
#include "Data.h"

int ITauth();
int Login(std::unordered_map<int,User>& accounts, User *& currentUser);