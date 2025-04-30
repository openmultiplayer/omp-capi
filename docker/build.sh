#!/bin/bash

# Available configs: Debug, [RelWithDebInfo], Release
[[ -z "$CONFIG" ]] \
&& config=Release \
|| config="$CONFIG"

[[ -z "$TARGET_BUILD_ARCH" ]] \
&& target_build_arch=x86 \
|| target_build_arch="$TARGET_BUILD_ARCH"

docker build \
    -t omp-capi/build:ubuntu-18.04 ./ \
|| exit 1

folders=('build')
for folder in "${folders[@]}"; do
    if [[ ! -d "./${folder}" ]]; then
        mkdir ${folder}
    fi
    sudo chown -R 1000:1000 ${folder} || exit 1
done

docker run \
    --rm \
    -t \
    -w /code \
    -v $PWD/..:/code \
    -v $PWD/build:/code/build \
    -e CONFIG=${config} \
    -e TARGET_BUILD_ARCH=${target_build_arch} \
    omp-capi/build:ubuntu-18.04
