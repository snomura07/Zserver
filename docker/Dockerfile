FROM ubuntu:24.04

# for timezone
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y --no-install-recommends \
    cmake \
    git \
    wget \
    nano \
    python3-pip \
    curl \
    sudo \
    unzip \
    libtool \
    autoconf \
    automake \
    pkg-config \
    libgtk-3-dev \
    build-essential \
    python3-dev \
    protobuf-compiler=3.21.12-8.2ubuntu0.3 \
    libprotobuf-dev=3.21.12-8.2ubuntu0.3 \
    libzmq3-dev=4.3.5-1build2 \
    && rm -rf /var/lib/apt/lists/*

# ライブラリパスの設定
RUN ldconfig
