#!/usr/bin/env bash

parallel --eta -j 8 ./bin/CropFace {} ::: $1
