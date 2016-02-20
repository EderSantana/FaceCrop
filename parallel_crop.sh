#!/usr/bin/bash

# Usarge
# parallel_crop /path/to/face/pics
parallel --eta -j 8 ./bin/CropFace {} ::: $1
