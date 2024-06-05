#!/bin/bash

# Available configs: Debug, [RelWithDebInfo], Release
[[ -z "$CONFIG" ]] \
&& config=RelWithDebInfo \
|| config="$CONFIG"

docker build \
    -t omp-capi/build:ubuntu-18.04} \
    build_ubuntu-18.04/ \
|| exit 1

folders=('build' 'conan')
for folder in "${folders[@]}"; do
    if [[ ! -d "./${folder}" ]]; then
        mkdir ${folder} &&
        chown 1000:1000 ${folder} || exit 1
    fi
done

docker run \
    --rm \
    -t \
    -w /code \
    -v $PWD/..:/code \
    -v $PWD/build:/code/build \
    -v $PWD/conan:/home/user/.conan \
    -e CONFIG=${config} \
    omp-capi/build:ubuntu-18.04
