FROM archlinux:latest

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN pacman -Sy --noconfirm \
  git cmake make gcc valgrind elfutils \
  libx11 libxext libxrandr libglvnd libxinerama libxcursor libxi \
  mesa wayland libxkbcommon xdg-utils dbus \
  openal libogg libvorbis flac freetype2 \
  && pacman -Scc --noconfirm

ENV DEBUGINFOD_URLS="https://debuginfod.archlinux.org/"

WORKDIR /tmp

RUN git clone https://github.com/SFML/SFML.git && \
  git -C SFML checkout 2.6.x && \
  cmake -S SFML -B SFML/build -DCMAKE_BUILD_TYPE=RelWithDebInfo && \
  cmake --build SFML/build --parallel && \
  cmake --install SFML/build

RUN git clone https://github.com/SFML/CSFML.git && \
  git -C CSFML checkout 2.6.x && \
  cmake -S CSFML -B CSFML/build -DCMAKE_BUILD_TYPE=RelWithDebInfo && \
  cmake --build CSFML/build --parallel && \
  cmake --install CSFML/build

RUN echo '/usr/local/lib' | tee /etc/ld.so.conf.d/sfml.conf && ldconfig

RUN useradd -m dockeruser
USER dockeruser
WORKDIR /home/dockeruser

COPY . ./game
WORKDIR /home/dockeruser/game

CMD [ "./wolf3d" ]
