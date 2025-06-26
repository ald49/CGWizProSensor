#pragma once
#include <Arduino.h>
#include "painlessMesh.h"
#include <scale.h>

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

void setupNetMeshClient();

void loopNetMeshClient();