ARG     PASTREE_ROOT_IMAGE
FROM    ${PASTREE_ROOT_IMAGE}

# Build arguments
ARG     LIBDXP_GIT_REMOTE_URL
ARG     LIBDXP_GIT_REF

# APT-GET context
ARG     DEBIAN_FRONTEND=noninteractive
ARG     APTGET_OPTS="-y --no-install-recommends"

# Update APT-GET package lists
RUN     apt-get update ${APTGET_OPTS} \
        && apt-get upgrade ${APTGET_OPTS}

# Essential packages
RUN     apt-get install ${APTGET_OPTS} build-essential ca-certificates clang git network-manager \
                libmagic-dev libssl-dev

# Other packages
RUN     apt-get install ${APTGET_OPTS} curl wget wireshark \
                emacs-nox vim

# Clone, build, and install libdxp
ARG     LIBDXP_PREFIX="/usr/local"
ARG     LIBDXP_PATH="${LIBDXP_PREFIX}/lib/libdxp"
RUN     git clone --recurse-submodules ${LIBDXP_GIT_REMOTE_URL} ${LIBDXP_PATH} \
        && cd ${LIBDXP_PATH} \
        && git checkout ${LIBDXP_GIT_REF} \
        && make \
        && mkdir -p ${LIBDXP_PREFIX}/include \
        && ln -s ${LIBDXP_PATH}/lib/* ${LIBDXP_PREFIX}/lib \
        && ln -s ${LIBDXP_PATH}/include/* ${LIBDXP_PREFIX}/include

# Clean up
RUN     apt-get ${APTGET_OPTS} clean \
        && apt-get ${APTGET_OPTS} autoremove
